#include "graphics.h"

void displayTitle()
{
	Game* g = Game::getGame();
	g->clearScreen();

	gotoXY(TAB * 3 + 7, 1);
	cText("<- ", c_red);
	cText("Empty Space", c_light_teal);
	cText(" ->", c_red);
}

void drawStatusBoard(int x, int y, int sizeX, int sizeY, std::string disp, Colour dispC, std::vector<std::string> description, Colour descC, bool dispTitle, std::string title, Colour titleC)
{
	if (dispTitle)
	{
		//Centers the text relative to the box
		gotoXY(x + (sizeX / 2) - (title.size() / 2), y);
		cText(title, titleC);
		y++;
	}

	//Draws the box
	for (int y1 = 0; y1 < sizeY; y1++)
	{
		for (int x1 = 0; x1 < sizeX; x1++)
		{
			gotoXY(x + x1 , y + y1);

			if (y1 == 0 || y1 == sizeY - 1 || x1 == 0 || x1 == sizeX - 1) cText(disp, dispC);
		}
	}

	//Draws the information in the status box
	//Makes the last status item teal
	for (int i = 0; i < description.size(); i++)
	{
		gotoXY(x + 1, y + 1 +  i);
		if (i == description.size() - 1) descC = c_light_teal;
		cText(description.at(i), descC);
	}
}

void drawMain(Map map[mapMaxRow][mapMaxColumn], bool displayAll, std::vector<std::string> status)
{
	drawMap(LEFT_BOARD, 5, map, displayAll);
	//Draws the board which will come with updates on the game, fights, if you find an artefact
	drawStatusBoard(RIGHT_BOARD, 4, 36, 10, ".", c_white, status, c_white, true, "Status");
}

//Draws how many monsters and artefacts there are in the game
void drawGameStat(int x, int y, int nM, int nA)
{
	gotoXY(x, y);
	std::cout << "Number of monsters - " << nM;
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "Number of artefacts - " << nA;
}

void drawBattle(Player* a, Player* b, int startY, Map map[mapMaxRow][mapMaxColumn], bool displayAll, std::vector<std::string>* status)
{
	//Draws the top board
	displayTitle();
	drawMain(map, displayAll, *status);

	gotoXY(TAB * 3 + 5, startY);
	std::cout << "- You are in a battle -";
	//Displays the left side of the battle which will be Player a
	gotoXY(LEFT_BOARD, startY + 2);
	std::cout << "Name - " << a->getName();
	if (dynamic_cast<Monster*>(a) != 0)
	{
		gotoXY(LEFT_BOARD, getCurrentXY().Y + 1);
		std::cout << "Rating - " << std::setprecision(2) << std::fixed << dynamic_cast<Monster*>(a)->getRating();
	}
	gotoXY(LEFT_BOARD, getCurrentXY().Y + 1);

	std::ostringstream o, mHealth;
	o << std::setprecision(2) << std::fixed << a->getCurrentHealth() << "/" << a->getMaxHealth();
	mHealth << std::setprecision(2) << std::fixed << a->getMaxHealth();
	if (a->getCurrentHealth() <= a->getMaxHealth() - a->getMaxHealth() * 0.60)
	{
		//If less than 40% health, change health to red
		cText("Health - " + o.str(), c_red, 9, o.str().size() - mHealth.str().size() - 1);
	}
	else if(a->getCurrentHealth() <= a->getMaxHealth() - a->getMaxHealth() * 0.20)
	{
		//If less than 80% health, change health to yellow
		cText("Health - " + o.str(), c_yellow, 9, o.str().size() - mHealth.str().size() - 1);
	}
	else //Change health to green if in good shape
	{
		cText("Health - " + o.str(), c_light_green, 9, o.str().size() - mHealth.str().size() - 1);
	}
	gotoXY(LEFT_BOARD, getCurrentXY().Y + 1);
	std::cout << "Attack - " << std::setprecision(2) << std::fixed << a->getAttack();
	gotoXY(LEFT_BOARD, getCurrentXY().Y + 1);
	std::cout << "Defence - " << std::setprecision(2) << std::fixed << a->getDefence();
	gotoXY(LEFT_BOARD, getCurrentXY().Y + 1);
	std::cout << "Speed - " << a->getSpeed();

	//Displays the right side of the battle which will be Player b
	gotoXY(RIGHT_BOARD, startY + 2);
	std::cout << "Name - " << b->getName();
	if (dynamic_cast<Monster*>(b) != 0)
	{
		gotoXY(RIGHT_BOARD, getCurrentXY().Y + 1);
		std::cout << "Rating - " << std::setprecision(2) << std::fixed << dynamic_cast<Monster*>(b)->getRating();
	}
	gotoXY(RIGHT_BOARD, getCurrentXY().Y + 1);
	o.str(""); mHealth.str("");
	o << std::setprecision(2) << std::fixed << b->getCurrentHealth() << "/" << b->getMaxHealth();
	mHealth << std::setprecision(2) << std::fixed << b->getMaxHealth();
	if (b->getCurrentHealth() <= b->getMaxHealth() - b->getMaxHealth() * 0.60)
	{
		//If less than 40% health, change health to red
		cText("Health - " + o.str(), c_red, 9, o.str().size() - mHealth.str().size() - 1);
	}
	else if (b->getCurrentHealth() <= b->getMaxHealth() - b->getMaxHealth() * 0.20)
	{
		//If less than 80% health, change health to yellow
		cText("Health - " + o.str(), c_yellow, 9, o.str().size() - mHealth.str().size() - 1);
	}
	else //Change health to green if in good shape
	{
		cText("Health - " + o.str(), c_light_green, 9, o.str().size() - mHealth.str().size() - 1);
	}
	gotoXY(RIGHT_BOARD, getCurrentXY().Y + 1);
	std::cout << "Attack - " << std::setprecision(2) << std::fixed << b->getAttack();
	gotoXY(RIGHT_BOARD, getCurrentXY().Y + 1);
	std::cout << "Defence - " << std::setprecision(2) << std::fixed << b->getDefence();
	gotoXY(RIGHT_BOARD, getCurrentXY().Y + 1);
	std::cout << "Speed - " << b->getSpeed();
}

void displayMonsterAbilities(int x, int y, Monster* m)
{
	gotoXY(x, y);
	std::cout << "- " << m->getName() << " abilities -";

	//Displays the monsters abilities
	for (int i = 0; i < m->getAbilities().size(); i++)
	{
		gotoXY(x, y + i + 2);
		std::cout << m->getAbilities().at(i);
	}
}

void playerOptions(int x, int y)
{
	gotoXY(x, y);
	std::cout << "- Options -";
	gotoXY(x, getCurrentXY().Y + 2);
	std::cout << "(1) - View artefacts";
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "(2) - Upgrade Character";
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "(3) - Menu";
}

void displayHumanStats(int x, int y, Human* h)
{
	gotoXY(x, y);
	std::cout << "Name - " << h->getName();
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "Health - " << std::setprecision(2) << std::fixed << h->getCurrentHealth() << "/" << h->getMaxHealth();
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "Attack - " << std::setprecision(2) << std::fixed << h->getAttack();
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "Defence - " << std::setprecision(2) << std::fixed << h->getDefence();
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "Speed - " << h->getSpeed();
}

void displayUpgradeOptions(int x, int y, Human* h, bool displayBack)
{

	gotoXY(x, y);
	std::cout << "- Upgrade Character -";
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "Each upgrade = Full Health";
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "Souls collected - " << h->getSouls();
	gotoXY(x, getCurrentXY().Y + 2);
	std::cout << "(1) - Health (Cost - 2, Gain - +5)";
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "(2) - Attack (Cost - 1, Gain - +1)";
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "(3) - Defence (Cost - 1, Gain - +1)";
	gotoXY(x, getCurrentXY().Y + 1);
	std::cout << "(4) - Speed (Cost - 1, Gain - +1)";

	if (displayBack)
	{
		gotoXY(x, getCurrentXY().Y + 1);
		std::cout << "(5) Go back";
	}
}