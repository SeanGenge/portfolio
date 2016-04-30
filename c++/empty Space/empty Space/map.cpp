#include "map.h"

void generateMap(Map m[mapMaxRow][mapMaxColumn], int nMonsters, int nArtefacts, COORD* playerLoc)
{
	//Clears all the squares to empty
	for (int row = 0; row < mapMaxRow; row++)
	{
		for (int col = 0; col < mapMaxColumn; col++)
		{
			m[row][col] = empty;
		}
	}

	//Creates a border of walls around the edges
	for (int row = 0; row < mapMaxRow; row++)
	{
		for (int col = 0; col < mapMaxColumn; col++)
		{
			if (col == 0 || col == mapMaxColumn - 1) m[row][col] = wall;
			if (row == 0 || row == mapMaxRow - 1) m[row][col] = wall;
		}
	}

	//Adds the player on a random place on column 1
	int r = rand() % (mapMaxRow - 2) + 1;
	m[r][1] = human;

	playerLoc->X = 1;
	playerLoc->Y = r;


	//Adds the monsters and artefacts to random squares
	//on the map except the second last column
	do
	{
		int row, col;

		//Only chooses squares which has empty in them
		do
		{
			//Ignores the edges as they are walls and the last column
			row = rand() % (mapMaxRow - 2) + 1;
			col = rand() % (mapMaxColumn - 3) + 1;
		} while (m[row][col] != empty);

		//Adds monsters first
		if (nMonsters != 0)
		{
			m[row][col] = monster;
			nMonsters--;
		}//Adds artefacts second
		else if (nArtefacts != 0)
		{
			m[row][col] = artefact;
			nArtefacts--;
		}
	} while (nMonsters != 0 || nArtefacts != 0);

	//Adds the finish square somewhere on the second last column
	r = rand() % (mapMaxRow - 2) + 1;
	m[r][mapMaxColumn - 2] = finish;
}

void drawMap(int x, int y, Map m[mapMaxRow][mapMaxColumn], bool displayAll)
{
	//Draws the edge walls, if displayAll, draws the other items as well
	for (int row = 0; row < mapMaxRow; row++)
	{
		for (int col = 0; col < mapMaxColumn; col++)
		{
			//Goes to the specified square
			gotoXY(x + col, y + row);

			//Edge walls
			if (col == 0 || col == mapMaxColumn - 1 || row == 0 || row == mapMaxRow - 1)
			{
				cText("#", c_dark_green);
			}

			if (m[row][col] == human)cText("P", c_dark_yellow);

			//Draws everything else if displayAll is true
			if (displayAll)
			{
				switch (m[row][col])
				{
				case monster:
					cText("m", c_dark_red);
					break;
				case artefact:
					cText("a", c_dark_blue);
					break;
				case finish:
					cText("e", c_dark_pink);
					break;
				}
			}
		}
	}
}

bool checkMapSquare(Map square)
{
	if (square == wall) return false;
	else return true;
}

Map mapIntToMap(int value)
{
	switch (value)
	{
	case 1: return Map::human;
	case 2: return Map::wall;
	case 3: return Map::monster;
	case 4: return Map::artefact;
	case 5: return Map::finish;
	default: return Map::empty; //Empty
	}
}