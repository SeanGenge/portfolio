#pragma once
#ifndef GAME_H
#define GAME_H
#pragma once
#include <vector>
#include <Windows.h>

class Game
{
private:
	//Constructor
	Game();

	//If the game is running
	int m_isRunning;

public:
	//Only allows one object of the game object
	static Game* getGame();
	//Points to the instance of the game object
	static Game* _instance;

	//Changes the run state to run game or to stop the game loop
	void setGameState(bool isRunning);
	//Clears the screen
	void clearScreen();
	//The game loop, returns true or false
	bool run();
};

#endif