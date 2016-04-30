#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H
#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>
#undef max
#include "Game.h"

#define TAB 8

enum Colour
{
	c_black = 0,
	c_dark_blue = 1,
	c_dark_green = 2,
	c_dark_teal = 3,
	c_dark_red = 4,
	c_dark_pink = 5,
	c_dark_yellow = 6,
	c_light_grey = 7,
	c_dark_grey = 8,
	c_light_blue = 9,
	c_light_green = 10,
	c_light_teal = 11,
	c_red = 12,
	c_pink = 13,
	c_yellow = 14,
	c_white = 15
};

//Displays coloured text
void cText(std::string text, Colour colour, int start = -1, int length = -1);
void gotoXY(int x, int y);
COORD getCurrentXY();
void toggleCursor(bool visibility);
void getInput(int xCoord, int yCoord, std::string* input);
bool checkInput(std::string input, int min, int max);
//Erases the text at (xCoord, yCoord) of length length
void eraseText(int xCoord, int yCoord, int length);
//Clears the keyboard input buffer
void clearConsoleInputBuffer();
#endif