#include "Game.h"

Game* Game::_instance = NULL;

Game::Game()
{
	m_isRunning = true;
}

Game* Game::getGame()
{
	if (!_instance) _instance = new Game;

	return _instance;
}

void Game::setGameState(bool isRunning)
{
	m_isRunning = isRunning;
}

//Got this code online, much better than screen("CLS") and produces less flickering
//uses less resources than system therefore can be somewhat faster
void Game::clearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	//Get the number of cells in the current buffer
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	//Fill the entire buffer with spaces
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
		)) return;

	//Fill the entire buffer with the current colors and attributes
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		)) return;

	//Move the cursor home
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

bool Game::run()
{
	if (m_isRunning) return true;
	else return false;
}