#include "events.h"

bool checkEventHappened(Map* cSquare)
{
	if (*cSquare == Map::empty) return false;
	else return true;
}

void performEvent(Map* cSquare, std::vector<std::string>* status, Human* h, std::vector<Monster*>* m, Map map[mapMaxRow][mapMaxColumn], bool displayAll, Difficulty d, bool* winGame, int* nM, int* nA)
{
	if (*cSquare == Map::monster)
	{
		(*nM)--;
		//Gets the first monster in the vector and erases it
		Monster* mon = getMonster(m);
		addStatus("You encounted -> " + mon->getName(), status);
		battle(h, mon, map, displayAll, status, winGame);
	}
	else if (*cSquare == Map::artefact)
	{
		(*nA)--;
		addArtefact(h, status);
	}
	else if (*cSquare == Map::finish)
	{
		addStatus("You encountered the boss!", status);
		Monster* mon = NULL;
		switch (d)
		{
		case beginner:
			mon = new Hydra(2, 0);
			mon->setMaxHealth(mon->getMaxHealth() - 10);
			static_cast<Player*>(mon)->Player::setCurrentHealth(mon->getMaxHealth());
			break;
		case average:
			mon = new Hydra(2, 1);
			break;
		case impossible:
			mon = new Hydra(2, 3);
			mon->setMaxHealth(mon->getMaxHealth() + 10 + (rand() % 11));
			static_cast<Player*>(mon)->Player::setCurrentHealth(mon->getMaxHealth());
			mon->setAttack(mon->getAttack() + 2);
			mon->setDefence(mon->getDefence() + 1);
			break;
		}

		battle(h, mon, map, displayAll, status, winGame);
	}

	//Clears the square once the event has occured
	*cSquare = Map::empty;
}

void battle(Player* a, Player* b, Map map[mapMaxRow][mapMaxColumn], bool displayAll, std::vector<std::string>* status, bool* winGame)
{
	//Make sure the two players exist
	if (a != NULL && b != NULL)
	{
		Player* attacker = NULL;
		Player* defender = NULL;

		//Changes the one with more speed to be the attacker
		//If the speed is the same, the first player goes first
		if (a->getSpeed() <= b->getSpeed())
		{
			Player* temp = a;
			attacker = b;
			defender = temp;
		}
		else
		{
			Player* temp = b;
			attacker = a;
			defender = temp;
		}

		//Keeps track of the human's stats that can change
		double hDefence = 0;
		double hAttack = 0;
		//The monsters defence
		double mDefence = 0;

		//Sets the stats depending who is the human
		if (dynamic_cast<Human*>(attacker) != 0)
		{
			//If the stats were not saved, save them
			if (hDefence == 0) hDefence = dynamic_cast<Human*>(attacker)->getDefence();
			if (hAttack == 0) hAttack = dynamic_cast<Human*>(attacker)->getAttack();
			if (mDefence == 0) mDefence = dynamic_cast<Monster*>(defender)->getDefence();
		}
		else if (dynamic_cast<Human*>(defender) != 0)
		{
			//If the stats were not saved, save them
			if (hDefence == 0) hDefence = dynamic_cast<Human*>(defender)->getDefence();
			if (hAttack == 0) hAttack = dynamic_cast<Human*>(defender)->getAttack();
			if (mDefence == 0) mDefence = dynamic_cast<Monster*>(attacker)->getDefence();
		}

		//Keeps track of the artefacts used which will be deleted after battle is left
		std::vector<Artefact*> artefactsUsed;

		//Only changes the bottom part of the board where the battle will take place
		const int bottom_board = 17;
		clearConsoleInputBuffer();
		do
		{
		//Draws the battle stats of each opponent
		drawBattle(a, b, bottom_board, map, displayAll, status);

		//The actual battle happens here
		//If player is human, get user input on what they want to do, if not run the turn of the monster
		if (dynamic_cast<Human*>(attacker) != 0)
		{
			//Uses up any artefacts turn if any is active
			for (std::vector<Artefact*>::iterator i = artefactsUsed.begin(); i != artefactsUsed.end(); i++)
			{
				if ((*i)->getType() == Artefact::t_shield)
				{
					dynamic_cast<Human*>(attacker)->setDefence(hDefence);
					/*(*i)->endEffect();*/
					drawBattle(a, b, bottom_board, map, displayAll, status);
				}

				//Deletes all the artefacts
				delete *i;
			}

			artefactsUsed.clear();

			bool finished = false;
			do
			{
				//Get input from player if they want to attack the monster, flee or use an artefact
				displayPlayerChoices(LEFT_BOARD, bottom_board + 9);

				//Checks the input and performs the selected action
				std::string input;
				int inputY = getCurrentXY().Y + 1;

				//Asks for valid input
				getPlayerInput(LEFT_BOARD, inputY, 1, 3, &input, "->");

				//Performs the selected action
				if (input.compare("1") == 0) //Attack
				{
					int roll = Player::getRandom(10);
					std::ostringstream o;
					o << std::setprecision(2) << std::fixed << attacker->calculateDmg(defender, roll);
					addStatus("You dealt " + o.str() + " damage", status);
					attacker->attack(defender, roll);
					finished = true;
				}
				else if (input.compare("2") == 0) //Displays artefacts and lets player pick one or go back
				{
					drawBattle(a, b, bottom_board, map, displayAll, status);
					int n = displayArtefacts(LEFT_BOARD, getCurrentXY().Y + 2, dynamic_cast<Human*>(attacker), true);
					getPlayerInput(LEFT_BOARD, getCurrentXY().Y + 1, 1, n + 1, &input, "->");

					//Uses the artefact if the user chose one
					if (atoi(input.c_str()) != n + 1)
					{
						//Keeps track of how many artefact of each type there are
						std::vector<std::pair<Artefact::type, int>> num = sortArtefacts(dynamic_cast<Human*>(attacker));

						//Finds the first artefact that matches the one selected and use it
						for (int i = 0; i < dynamic_cast<Human*>(attacker)->getArtefacts().size(); i++)
						{
							//If the selected artefact matches one from the human's artefacts, use it
							if (dynamic_cast<Human*>(attacker)->getArtefacts().at(i)->getType() == num.at(atoi(input.c_str()) - 1).first)
							{
								dynamic_cast<Human*>(attacker)->getArtefacts().at(i)->performAction(attacker, defender);
								//Adds the artefact for use to be deleted
								artefactsUsed.push_back(dynamic_cast<Human*>(attacker)->getArtefacts().at(i));
								//Removes the artefact from the human
								dynamic_cast<Human*>(attacker)->removeArtefact(i);

								//Breaks from the loop to not use all the artefacts of the same type
								break;
							}
						}
					}
				}
				else if (input.compare("3") == 0) //Displays the monsters abilities
				{
					drawBattle(a, b, bottom_board, map, displayAll, status);
					//As there is only one human allowed, the defender must be the monster as well as the attacker being the human
					displayMonsterAbilities(LEFT_BOARD, getCurrentXY().Y + 2, dynamic_cast<Monster*>(defender));

					gotoXY(TAB * 2, getCurrentXY().Y + 2);
					system("PAUSE");
				}

				//Draws the battle stats of each opponent
				drawBattle(a, b, bottom_board, map, displayAll, status);

			} while (!finished);

			//Uses up any artefacts turn if any is active
			for (std::vector<Artefact*>::iterator i = artefactsUsed.begin(); i != artefactsUsed.end(); i++)
			{
				if (!(*i)->getType() == Artefact::t_shield)
				{
				
					if ((*i)->getType() == Artefact::t_strength) dynamic_cast<Human*>(attacker)->setAttack(hAttack);
					if ((*i)->getType() == Artefact::t_poison) dynamic_cast<Monster*>(defender)->setDefence(mDefence);
				}
			}
		}
		else //Attacker is a monster
		{
			int roll = Player::getRandom(6);
			std::ostringstream o;
			//Checks if the monster is a boss
			if (dynamic_cast<Monster*>(attacker)->isBoss()) o << std::setprecision(2) << std::fixed << attacker->calculateDmg(defender, roll) * dynamic_cast<Hydra*>(attacker)->getHeadCount();
			else o << std::setprecision(2) << std::fixed << attacker->calculateDmg(defender, roll);
			addStatus(attacker->getName() + " dealt " + o.str() + " damage", status);
			dynamic_cast<Monster*>(attacker)->getTurn(defender, roll);

			drawBattle(a, b, bottom_board, map, displayAll, status);
			//Pauses their turn to the player can keep up
			gotoXY(TAB * 2, getCurrentXY().Y + 2);
			system("PAUSE");
		}

		//If someone dies
		if (!defender->isAlive())
		{
			addStatus("", status);
			addStatus(defender->getName() + " was defeated!", status);
			addStatus(attacker->getName() + " was victorious!", status);

			//If human survives, he gains a soul
			if (dynamic_cast<Human*>(attacker) != 0)
			{
				if (dynamic_cast<Human*>(attacker)->isAlive()) dynamic_cast<Human*>(attacker)->addSoul(1);
				addStatus("You gained a soul!", status);

				dynamic_cast<Human*>(attacker)->setPoints(dynamic_cast<Human*>(attacker)->getPoints() + 0.7 * dynamic_cast<Monster*>(defender)->getRating());

				//Sets the stats of the human back to normal
				dynamic_cast<Human*>(attacker)->setAttack(hAttack);
				dynamic_cast<Human*>(attacker)->setDefence(hDefence);

				if (dynamic_cast<Monster*>(defender)->isBoss()) *winGame = true;
			}
		}
			//Changes the turn of the attacker and defender
			{
				Player* temp = attacker;
				attacker = defender;
				defender = temp;
			}
		} while (attacker->isAlive() && defender->isAlive());

		//Deletes the monster
		if (dynamic_cast<Monster*>(attacker) != 0) delete attacker;
		else if (dynamic_cast<Monster*>(defender) != 0) delete defender;
	}
}

Monster* getMonster(std::vector<Monster*>* m)
{
	if (!m->empty())
	{
		Monster* monster = m->at(0);
		m->erase(m->begin());
		return monster;
	}
	else return NULL;
}

void addArtefact(Human* h, std::vector<std::string>* status)
{
	//Gets a random artefact
	Artefact* a = new Artefact(true);
	addStatus("You found -> " + a->getSType(), status);
	h->addArtefact(a);
}