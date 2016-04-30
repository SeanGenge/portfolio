#include "playerHandling.h"

void displayPlayerChoices(int x, int y)
{
	gotoXY(x, y);
	std::cout << "- Options -";
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "1 - Attack";
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "2 - Use Artefact";
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "3 - See monster abilities";
}

int displayArtefacts(int x, int y, Human* h, bool displayBack)
{
	//Keeps track of how many artefact of each type there are
	std::vector<std::pair<Artefact::type, int>> num = sortArtefacts(h);

	if (!num.empty())
	{
		//Prints the number of artefacts found
		for (int i = 0; i < num.size(); i++)
		{
			gotoXY(x, y + i);
			std::cout << "(" << (i + 1) << ") - " << num.at(i).second << "x - " << Artefact::getSType(num.at(i).first)
				<< " - " << Artefact::getDescription(num.at(i).first);
		}
	}
	else
	{
		gotoXY(x, y - 1);
		std::cout << "You have no artefacts!";
	}

	if (displayBack)
	{
		gotoXY(x, y + num.size());
		std::cout << "(" << (num.size() + 1) << ") - Go back";
	}

	return num.size();
}

std::vector<std::pair<Artefact::type, int>> sortArtefacts(Human* h)
{
	//Keeps track of how many artefact of each type there are
	std::vector<std::pair<Artefact::type, int>> numArtefacts;

	//Counts how many of each artefact there are
	for (int i = 0; i < h->getArtefacts().size(); i++)
	{
		if (!numArtefacts.empty())
		{
			bool found = false;
			for (int j = 0; j < numArtefacts.size(); j++)
			{
				if (numArtefacts.at(j).first == h->getArtefacts().at(i)->getType())
				{
					numArtefacts.at(j).second++;
					found = true;
					break;
				}
			}

			if (!found) numArtefacts.push_back(std::make_pair(h->getArtefacts().at(i)->getType(), 1));
		}
		else numArtefacts.push_back(std::make_pair(h->getArtefacts().at(i)->getType(), 1));
	}

	return numArtefacts;
}

void getPlayerInput(int x, int y, int min, int max, std::string* input, std::string disp)
{
	*input = "";

	do
	{
		gotoXY(x, y);
		std::cout << disp << " ";
		getInput(x + disp.size() + 1, y, input);

		if (!checkInput(*input, min, max)) eraseText(x + disp.size() + 1, y, input->length());
	} while (!checkInput(*input, min, max));
}

void changeName(int x, int y)
{
	//Gets input for a new name
	displayTitle();
	gotoXY(x, y);
	std::cout << "Changing players name";
	gotoXY(x, getCurrentXY().Y + 2);
	std::cout << "Current name -> " + Human::getHumanObject()->getName();
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "New name -> ";
	std::string input;
	getInput(getCurrentXY().X, getCurrentXY().Y, &input);

	Human::getHumanObject()->setName(input);
}

void upgradeCharacterStartGame()
{
	int p = 2;
	std::string input;
	int y = 4;
	Human* h = Human::getHumanObject();
	double hp = h->getMaxHealth();
	double att = h->getAttack();
	double def = h->getDefence();
	int speed = h->getSpeed();

	do
	{
		displayTitle();
		displayHumanStats(RIGHT_BOARD, y + 3, Human::getHumanObject());
		gotoXY(LEFT_BOARD, y);
		std::cout << "What stats would you like to increase?";
		gotoXY(LEFT_BOARD, getCurrentXY().Y + 1);
		std::cout << "You can only upgrade one stat once";
		gotoXY(LEFT_BOARD, getCurrentXY().Y + 1);
		std::cout << "Points remaining - " + std::to_string(p);
		gotoXY(LEFT_BOARD, getCurrentXY().Y + 2);
		std::cout << "1 - Health";
		gotoXY(LEFT_BOARD, getCurrentXY().Y + 1);
		std::cout << "2 - Attack";
		gotoXY(LEFT_BOARD, getCurrentXY().Y + 1);
		std::cout << "3 - Defence";
		gotoXY(LEFT_BOARD, getCurrentXY().Y + 1);
		std::cout << "4 - Speed";
		gotoXY(LEFT_BOARD, getCurrentXY().Y + 1);
		std::cout << "0 - Continue";

		getPlayerInput(LEFT_BOARD, getCurrentXY().Y + 1, 0, 4, &input, "->");

		//Upgrades the human stats
		if (input.compare("1") == 0)
		{
			if (h->getMaxHealth() == hp + 5)
			{
				h->setMaxHealth(h->getMaxHealth() - 5);
				h->setCurrentHealth(h->getMaxHealth());
				p++;
			}
			else if (p > 0)
			{
				h->setMaxHealth(h->getMaxHealth() + 5);
				h->setCurrentHealth(h->getMaxHealth());
				p--;
			}
		}
		else if (input.compare("2") == 0)
		{
			if (h->getAttack() == att + 1)
			{
				h->setAttack(h->getAttack() - 1);
				p++;
			}
			else if (p > 0)
			{
				h->setAttack(h->getAttack() + 1);
				p--;
			}
		}
		else if (input.compare("3") == 0)
		{
			if (h->getDefence() == def + 1)
			{
				h->setDefence(h->getDefence() - 1);
				p++;
			}
			else if (p > 0)
			{
				h->setDefence(h->getDefence() + 1);
				p--;
			}
		}
		else if (input.compare("4") == 0)
		{
			if (h->getSpeed() == speed + 1)
			{
				h->setSpeed(h->getSpeed() - 1);
				p++;
			}
			else if (p > 0)
			{
				h->setSpeed(h->getSpeed() + 1);
				p--;
			}
		}
	} while (input.compare("0") != 0);
}