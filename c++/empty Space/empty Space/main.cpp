#include "main.h"

int main()
{
	//Sets the console title
	SetConsoleTitle("Empty Space By Sean Genge");

	//Creates a new game
	Game* game = Game::getGame();
	game->SetWindowHeight(500);
	
	//Get a random seed
	srand(time(NULL));
	
	//Start the game
	mainGame(game);

	return 0;
}

void setupVariables(bool* gameStart, bool* displayAll, Human** h, Map map[mapMaxRow][mapMaxColumn], std::vector<Monster*>* m, Difficulty* diff, int* nMonsters, int* nArtefacts, COORD* hLoc, Map* currentSquare, bool* winGame, bool* loadGame)
{
	//Creates a new human with default stats
	(*h)->deleteHuman();
	*h = Human::getHumanObject("Human", 25, 4, 4, 4);
	//Makes sure the monster vector is empty
	m->clear();
	*currentSquare = empty;

	*loadGame = false;
	*winGame = false;
	*gameStart = false;
	*displayAll = false;
	hLoc->X = 0;
	hLoc->Y = 0;

	*diff = beginner;
	setupDifficulty(*diff, nMonsters, nArtefacts);

	//Sets all the items in map to empty
	for (int row = 0; row < mapMaxRow; row++)
	{
		for (int col = 0; col < mapMaxColumn; col++)
		{
			map[row][col] = empty;
		}
	}
}

void resetGame(bool* gameStart, bool* displayAll, Human** h, std::string hName, Map map[mapMaxRow][mapMaxColumn], std::vector<Monster*>* m, COORD* hLoc, Map* currentSquare, bool* winGame, bool* loadGame)
{
	//Resets the human to default stats
	(*h)->deleteHuman();
	*h = Human::getHumanObject(hName, 25, 4, 4, 4);
	//Makes sure the monster vector is empty
	m->clear();
	*currentSquare = empty;

	*loadGame = false;
	*winGame = false;
	*gameStart = false;
	*displayAll = false;
	hLoc->X = 0;
	hLoc->Y = 0;

	//Sets all the items in map to empty
	for (int row = 0; row < mapMaxRow; row++)
	{
		for (int col = 0; col < mapMaxColumn; col++)
		{
			map[row][col] = empty;
		}
	}
}

void mainGame(Game* g)
{
	/*	Declare main variables	*/

	//If the user starts the game
	bool gameStart;
	//Returns true if the game is returned to a previous state
	bool loadGame;
	//If the player wins the game
	bool winGame;
	//Used to display where the monsters and artefacts are on the map
	bool displayAll;
	//The human player
	Human* human = NULL;
	//The player's (Human) x and y coordinates in the map
	COORD hLoc;
	//The actual map of the game
	Map map[mapMaxRow][mapMaxColumn];
	//Used to order the monsters in increasing difficulty to add a difficulty curve as you progress
	std::vector<Monster*> monster;
	//Holds the number of items in the status box
	std::vector<std::string> status;
	//The current square value that the player is on, eg. Artefact or monster
	Map currentSquare;

	//The difficulty of the game
	Difficulty difficulty;
	//The number of monsters in the map
	int numMonsters;
	//The number of artefacts in the map
	int numArtefacts;

	//Hides the cursor
	toggleCursor(false);

	//Check key press
	//Checks for a key press
	bool keyPressed = true;

	//Initializes the starting values for the game
	setupVariables(&gameStart, &displayAll, &human, map, &monster, &difficulty, &numMonsters, &numArtefacts, &hLoc, &currentSquare, &winGame, &loadGame);

	do
	{
		//Initializes the starting values for the game
		resetGame(&gameStart, &displayAll, &human, human->getName(), map, &monster, &hLoc, &currentSquare, &winGame, &loadGame);

		//menu
		displayTitle();
		mainMenu(TAB * 3, getCurrentXY().Y + 2, &difficulty, map, &monster, &numMonsters, &numArtefacts, &gameStart, &loadGame, &hLoc);

		if (gameStart)
		{
			clearStatus(&status);
			//Adds the beginning status alerts
			addStatus("** Welcome to empty space! **", &status);
			addStatus("** Use the arrow keys to move **", &status);

			if (!loadGame)
			{
				//Lets the player upgrade the character before playing the game
				upgradeCharacterStartGame();
				//Setups the main game and map
				setupDifficulty(difficulty, &numMonsters, &numArtefacts);
				generateMap(map, numMonsters, numArtefacts, &hLoc);
				setupMonsters(difficulty, &monster, numMonsters);
			}
			else addStatus("** Game successfully loaded **", &status);

			do
			{
				//Draws items
				displayTitle();
				drawMain(map, displayAll, status);
				drawGameStat(LEFT_BOARD, 16, numMonsters, numArtefacts);
				//Draws the options that the player can choose from
				playerOptions(LEFT_BOARD, 20);

				do
				{
					//Sleep(40);
					if (!keyPressed && keyPress(VK_LEFT))
					{
						if (!movePlayer(map, &hLoc, 0, &currentSquare)) addStatus("There is a wall to the left", &status);
						keyPressed = true;
					}
					else if (!keyPressed && keyPress(VK_UP))
					{
						if (!movePlayer(map, &hLoc, 1, &currentSquare)) addStatus("There is a wall above you", &status);
						keyPressed = true;
					}
					else if (!keyPressed && keyPress(VK_RIGHT))
					{
						if (!movePlayer(map, &hLoc, 2, &currentSquare)) addStatus("There is a wall to the right", &status);
						keyPressed = true;
					}
					else if (!keyPressed && keyPress(VK_DOWN))
					{
						if (!movePlayer(map, &hLoc, 3, &currentSquare)) addStatus("There is a wall below you", &status);
						keyPressed = true;
					}
					else if (!keyPressed && keyPress(VK_ESCAPE)) //Key - 0 (Display the board)
					{
						displayAll = displayAll ? false : true;
						keyPressed = true;
					}
					else if (!keyPressed && keyPress(49)) //Key - 1 (View artefacts)
					{
						displayTitle();
						drawMain(map, displayAll, status);
						displayArtefacts(LEFT_BOARD, 17, human, false);
						keyPressed = true;
						gotoXY(TAB * 3, getCurrentXY().Y + 2);
						system("PAUSE");
					}
					else if (!keyPressed && keyPress(50)) //Key - 2 (Upgrade character)
					{
						clearConsoleInputBuffer();
						
						displayTitle();
						drawMain(map, displayAll, status);
						displayHumanStats(RIGHT_BOARD, 17, human);
						displayUpgradeOptions(LEFT_BOARD, 17, human, true);
						std::string input;
						getPlayerInput(LEFT_BOARD, getCurrentXY().Y + 1, 1, 5, &input, "->");
						//Changes the players stats as well as the monsters
						if (input.compare("5") != 0)
						{
							//Health
							if (input.compare("1") == 0 && human->getSouls() >= 2)
							{
								//Cap on health is 100
								if (human->getMaxHealth() < 100)
								{
									upgrade(human, &monster, atoi(input.c_str()), difficulty);
									addStatus("You upgraded your health", &status);

									human->addSoul(-2);
								}
								else addStatus("Health is at max", &status);
							}
							else if (input.compare("1") == 0) addStatus("You do not have enough souls!", &status);

							//Attack, defence and speed
							if ((input.compare("2") == 0 || input.compare("3") == 0 || input.compare("4") == 0) && human->getSouls() >= 1)
							{
								//Cap on other stats is 10
								if ((input.compare("2") == 0) && human->getAttack() < 10)
								{
									addStatus("You upgraded your attack", &status);
									upgrade(human, &monster, atoi(input.c_str()), difficulty);
									human->addSoul(-1);
								}
								else if ((input.compare("2") == 0)) addStatus("Attack is at max", &status);

								if ((input.compare("3") == 0) && human->getDefence() < 10)
								{
									addStatus("You upgraded your defence", &status);
									upgrade(human, &monster, atoi(input.c_str()), difficulty);
									human->addSoul(-1);
								}
								else if ((input.compare("3") == 0)) addStatus("Defence is at max", &status);

								if ((input.compare("4") == 0) && human->getSpeed() < 10)
								{
									addStatus("You upgraded your speed", &status);
									upgrade(human, &monster, atoi(input.c_str()), difficulty);
									human->addSoul(-1);
								}
								else if ((input.compare("4") == 0)) addStatus("Speed is at max", &status);
							}
							else if (input.compare("2") == 0 || input.compare("3") == 0 || input.compare("4") == 0) addStatus("You do not have enough souls!", &status);
						}

						keyPressed = true;
					}
					else if (!keyPressed && keyPress(51)) //Key - 3 (Display menu, the in game menu)
					{
						displayTitle();
						drawMain(map, displayAll, status);
						displayInGameMenu(LEFT_BOARD, 17, map, &monster, numMonsters, numArtefacts, difficulty, &status, hLoc);
						
						keyPressed = true;
					}
					else
					{
						//Prevents the game from redrawing the game every time the player holds on a key
						do
						{
							//Only allows the player to move one block at a time
							if (keyPressed && !keyPress(VK_UP) && !keyPress(VK_DOWN) && !keyPress(VK_LEFT) && !keyPress(VK_RIGHT) && !keyPress(VK_ESCAPE) && !keyPress(49) && !keyPress(50) && !keyPress(51))
							{
								keyPressed = false;
							}
						} while (keyPressed && (keyPress(VK_UP) || keyPress(VK_DOWN) || keyPress(VK_LEFT) || keyPress(VK_RIGHT) || keyPress(VK_ESCAPE) || keyPress(49) || keyPress(50) || keyPress(51)));
					}
				} while (!keyPressed);

				//Checks to see if an even should occur
				if (checkEventHappened(&currentSquare)) performEvent(&currentSquare, &status, human, &monster, map, displayAll, difficulty, &winGame, &numMonsters, &numArtefacts);
			} while (!checkGameFinished(human, winGame)/*human is alive or the human won the game (Kill the boss)*/);
		}
	} while (g->run());
}

bool keyPress(int key)
{
	return (GetKeyState(key) & 0x8000);
}

void upgrade(Human* h, std::vector<Monster*>* m, int stat, Difficulty d)
{
	//Changes how much the monsters would upgrade depending on the difficulty
	double upgrade = 0;

	switch (d)
	{
	case beginner:
		upgrade = 0.08;
		break;
	case average:
		upgrade = 0.10;
		break;
	case impossible:
		upgrade = 0.10;
		break;
	}

	switch (stat)
	{
	case 1: //Health
		h->setMaxHealth(h->getMaxHealth() + 5);

		//Upgrades the monsters as well to not make it too easy
		for (int i = 0; i < m->size(); i++)
		{
			m->at(i)->setMaxHealth(m->at(i)->getMaxHealth() + m->at(i)->getMaxHealth() * upgrade + 0.1);
			m->at(i)->setCurrentHealth(m->at(i)->getMaxHealth());
			m->at(i)->setRating();
		}
		break;
	case 2: //Strength
		h->setAttack(h->getAttack() + 1);
		
		//Upgrades the monsters as well to not make it too easy
		for (int i = 0; i < m->size(); i++)
		{
			//Upgrades defence for attack
			m->at(i)->setDefence(m->at(i)->getDefence() + m->at(i)->getDefence() * upgrade);
			m->at(i)->setRating();
		}
		break;
	case 3: //Defence
		h->setDefence(h->getDefence() + 1);

		//Upgrades the monsters as well to not make it too easy
		for (int i = 0; i < m->size(); i++)
		{
			//Upgrades attack for defence
			m->at(i)->setAttack(m->at(i)->getAttack() + m->at(i)->getAttack() * upgrade);
			m->at(i)->setRating();
		}
		break;
	case 4: //Speed
		h->setSpeed(h->getSpeed() + 1);
		break;
	}

	h->setCurrentHealth(h->getMaxHealth());
}

bool checkGameFinished(Human* h, bool winGame)
{
	//Checks if the human is dead
	if (!h->isAlive())
	{
		displayTitle();
		gotoXY(TAB * 3, getCurrentXY().Y + 5);
		std::cout << "Sorry, you were defeated!";
		//Calculate the artefact scores
		for (int i = 0; i < h->getArtefacts().size(); i++)
		{
			h->setPoints(h->getPoints() + 0.05 * h->getArtefacts().at(i)->getScore());
		}
		gotoXY(TAB * 3, getCurrentXY().Y + 1);
		std::cout << "Your score for this game is " << h->getPoints();
		askPlayAgain();

		return true;
	}

	//Checks if the player beat the boss
	if (winGame)
	{
		displayTitle();
		gotoXY(TAB * 3, getCurrentXY().Y + 5);
		std::cout << "Congratulaions! You beat the boss!";
		//Calculate the artefact scores
		for (int i = 0; i < h->getArtefacts().size(); i++)
		{
			h->setPoints(h->getPoints() + 0.05 * h->getArtefacts().at(i)->getScore());
		}
		gotoXY(TAB * 3, getCurrentXY().Y + 1);
		std::cout << "Your score for this game is " << h->getPoints();
		askPlayAgain();

		return true;
	}

	return false;
}

void askPlayAgain()
{
	std::string input;
	gotoXY(TAB * 3, getCurrentXY().Y + 2);
	std::cout << "Would you like to play again? (1- Yes, 0 - No)";
	getPlayerInput(TAB * 3, getCurrentXY().Y + 1, 0, 1, &input, "->");

	if (input.compare("0") == 0) //No
	{
		Game* g = Game::getGame();
		g->setGameState(false);
	}
	else if (input.compare("1") == 0) //Yes
	{

	}
}

bool movePlayer(Map m[mapMaxRow][mapMaxColumn], COORD* hLoc, int direction, Map* currentSquare)
{
	//Direction -> 0-left, 1-up, 2-right, 3-down
	switch (direction)
	{
	case 0: //Left
		//location 0 is the wall
		if (hLoc->X == 1) return false;
		else //Move player
		{
			m[hLoc->Y][hLoc->X] = Map::empty;
			hLoc->X--;
			*currentSquare = m[hLoc->Y][hLoc->X];
			m[hLoc->Y][hLoc->X] = Map::human;
		}
		break;
	case 1: //Up
		//location 0 is the wall
		if (hLoc->Y == 1) return false;
		else //Move player
		{
			m[hLoc->Y][hLoc->X] = Map::empty;
			hLoc->Y--;
			*currentSquare = m[hLoc->Y][hLoc->X];
			m[hLoc->Y][hLoc->X] = Map::human;
		}
		break;
	case 2: //Right
		//location 0 is the wall
		if (hLoc->X == mapMaxColumn - 2) return false;
		else //Move player
		{
			m[hLoc->Y][hLoc->X] = Map::empty;
			hLoc->X++;
			*currentSquare = m[hLoc->Y][hLoc->X];
			m[hLoc->Y][hLoc->X] = Map::human;
		}
		break;
	case 3: //Down
		//location 0 is the wall
		if (hLoc->Y == mapMaxRow - 2) return false;
		else //Move player
		{
			m[hLoc->Y][hLoc->X] = Map::empty;
			hLoc->Y++;
			*currentSquare = m[hLoc->Y][hLoc->X];
			m[hLoc->Y][hLoc->X] = Map::human;
		}
		break;
	}

	return true;
}

void setupMonsters(Difficulty d, std::vector<Monster*>* m, int numMonsters)
{
	//Adds monster is no particular order
	for (int monsterCount = 0; monsterCount < numMonsters; monsterCount++)
	{
		int r = rand() % (NUM_MONSTERS - 1);
		m->push_back(createMonster(d, r));
	}

	//Sorts the monsters in ascending order
	int min;
	for (int j = 0; j < m->size() - 1; j++)
	{
		min = j;

		for (int i = j + 1; i < m->size(); i++)
		{
			//If the monster at i is smaller than the mininum, change the min to i
			if (m->at(i)->getRating() < m->at(min)->getRating()) min = i;
		}

		//Swaps the monsters around
		if (min != j)
		{
			Monster* mMin = m->at(j);
			Monster* mOther = m->at(min);

			m->at(min) = mMin;
			m->at(j) = mOther;
		}
	}
}

Monster* createMonster(Difficulty d, int index)
{
	Monster* m = NULL;

	//Creates a monster and changes stats depending on difficulty
	switch (index)
	{
	case 1: //Zombie
		if (d == beginner) m = new Zombie(2);
		else if (d == impossible) m = new Zombie(1, 2);
		else m = new Zombie(3, 1);
		break;
	case 2: //Minotaur
		if (d == beginner) m = new Minotaur(2);
		else if (d == impossible) m = new Minotaur(1, 2);
		else m = new Minotaur(3, 1);
		break;
	case 3: //Ancient mummy
		if (d == beginner) m = new AncientMummy(2);
		else if (d == impossible) m = new AncientMummy(1, 2);
		else m = new AncientMummy(3, 1);
		break;
	case 4: //BabyDragon
		if (d == beginner) m = new BabyDragon(2);
		else if (d == impossible) m = new BabyDragon(2, 3);
		else m = new BabyDragon(3, 1);
		break;
	default: //Ogre
		if (d == beginner) m = new Ogre(2);
		else if (d == impossible) m = new Ogre(1, 2);
		else m = new Ogre(3, 1);
		break;
	}

	return m;
}