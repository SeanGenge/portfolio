#include "loadSaveGame.h"

//Extra functionality
void saveGame(Map map[mapMaxRow][mapMaxColumn], std::vector<Monster*>* m, int nM, int nA, Difficulty d, COORD hLoc)
{
	//Opens a file if not create one and saves the state of the game, there can only be one saved game
	//Will overwrite the file if it exists

	/*The order in which the file is saved in
	- Num monsters + num artefacts + difficulty
	- Map
	- Vector of monsters
	- Player details
	*/

	//Will create the file if it does not exist
	std::ofstream out("save.dat");

	//Saves the number of monsters and artefacts
	out << nM << " " << nA << " " << d <<"\n";

	//Saves the map
	for (int row = 0; row < mapMaxRow; row++)
	{
		for (int col = 0; col < mapMaxColumn; col++)
		{
			out << map[row][col];
			if (col != mapMaxColumn - 1) out << " ";
		}
		out << "\n";
	}

	//Saves the player details
	Human* h = Human::getHumanObject();
	//Saves how many parts the players name contain
	int p = 0;
	for (int i = 0; i < h->getName().size(); i++) if (h->getName().at(i) == ' ') p++;
	out << p << "\n";
	//Saves name
	out << h->getName() << "\n";
	//Saves the players score
	out << h->getPoints() << "\n";
	//Saves stats
	out << h->getCurrentHealth() << "\n";
	out << h->getMaxHealth() << "\n";
	out << h->getAttack() << "\n";
	out << h->getDefence() << "\n";
	out << h->getSpeed() << "\n";
	//Saves the number of souls collected
	out << h->getSouls() << "\n";

	//Saves the number of artefacts the player has
	out << h->getArtefacts().size() << "\n";
	//Saves the player artefacts
	if (!h->getArtefacts().empty())
	{
		for (int i = 0; i < h->getArtefacts().size(); i++)
		{
			//Only saves the type as when it is loaded back
			//creates the artefact again
			out << h->getArtefacts().at(i)->getType() << " ";
		}
	}

	//Saves the players location
	out << "\n" << hLoc.X << " " << hLoc.Y;

	out.close();
}

void loadGame(Map map[mapMaxRow][mapMaxColumn], std::vector<Monster*>* m, int* nM, int* nA, Difficulty* d, COORD* hLoc)
{
	//Load's the game data

	/*The order in which the file is loaded from the file
	- Num monsters + num artefacts
	- Map
	- Vector of monsters
	- Player details
	*/

	//The file that will be opened
	std::ifstream in("save.dat");

	//Used to read in values which will be changed to the appropiate type
	int value;

	//Reads the number of monsters and artefacts
	in >> *nM >> *nA >> value;
	*d = mapIntToDifficulty(value);

	//Reads the map
	for (int row = 0; row < mapMaxRow; row++)
	{
		for (int col = 0; col < mapMaxColumn; col++)
		{
			in >> value;
			map[row][col] = mapIntToMap(value);
		}
	}

	//Reads the player details
	Human* h = Human::getHumanObject();
	//Reads name
	std::string input = "", name = "";
	int p;
	in >> p;
	for (int i = 0; i < p + 1; i++)
	{
		in >> input;
		name.append(input);
		if (i != p) name.append(" ");
	}
	h->setName(name);
	//Reads the points
	double dPoints;
	in >> dPoints;
	h->setPoints(dPoints);
	//Reads stats
	in >> value; h->setCurrentHealth(value);
	in >> value; h->setMaxHealth(value);
	in >> value; h->setAttack(value);
	in >> value; h->setDefence(value);
	in >> value; h->setSpeed(value);
	//Gets the number of souls collected
	in >> value; h->addSoul(value);

	//Reads the number of artefacts the player has
	in >> value;
	//Reads the artefacts
	if (value != 0)
	{
		int value2;

		for (int i = 0; i < value; i++)
		{
			//Reads the type and adds it to the player object
			in >> value2;
			h->addArtefact(new Artefact(false, Artefact::changeIntToType(value2)));
		}
	}

	//Reads the players location
	in >> hLoc->X >> hLoc->Y;

	in.close();
}