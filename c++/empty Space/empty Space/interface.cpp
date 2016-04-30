#include "Interface.h"

//Colours the text
void cText(std::string text, Colour colour, int start, int length)
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (start == -1 || length == -1)
	{
		SetConsoleTextAttribute(hConsole, colour); //Changes colour of text
		std::cout << text;
		SetConsoleTextAttribute(hConsole, c_light_grey); //Sets text back to the default console colour
	}
	else //Colour a specific substr a colour
	{
		if (start != 0)
		{
			SetConsoleTextAttribute(hConsole, c_light_grey);
			//Draws the starting half which is not coloured
			std::cout << text.substr(0, start);
		}
		SetConsoleTextAttribute(hConsole, colour); //Changes the colour of the text
		std::cout << text.substr(start, length);

		SetConsoleTextAttribute(hConsole, c_light_grey); //Sets text back to the default console colour
		std::cout << text.substr(start + length);
	}
}

//Erases the line from xCoord and yCoord of length
void eraseText(int xCoord, int yCoord, int length)
{
	//Deletes the input that the user typed
	gotoXY(xCoord + (length), yCoord);
	for (int i = 0; i < length; i++) std::cout << "\b" << " " << "\b";
}

//Gets input from the user
void getInput(int xCoord, int yCoord, std::string* input)
{
	gotoXY(xCoord, yCoord);

	std::cin.clear();
	std::cin.sync();
	std::getline(std::cin, *input);
}

//Checks if the input the user typed is valid (integer)
bool checkInput(std::string input, int min, int max)
{
	//Checks if only digits were typed
	if (!std::all_of(input.begin(), input.end(), ::isdigit))
	{
		//Checks for negative numbers
		if (input.at(0) != '-' && !std::all_of(input.begin() + 1, input.end(), ::isdigit) || (input.length() == 1 && input.at(0) == '-')) return false;
	}
	//Checks to see if the integer was within the range
	if (atoi(input.c_str()) < min || atoi(input.c_str()) > max) return false;

	return true;
}

//Goes to the selected position in the code
void gotoXY(int x, int y)
{
	COORD pos;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}

//Gets the current position of the cursor
COORD getCurrentXY()
{
	COORD pos;
	HANDLE stdHandle;
	CONSOLE_SCREEN_BUFFER_INFO info;

	stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(stdHandle, &info);

	pos.X = info.dwCursorPosition.X;
	pos.Y = info.dwCursorPosition.Y;

	return pos;
}

//Displays or hides the cursor
//True - Show, False - Hide
void toggleCursor(bool visibility)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	int size = 20;


	if (!visibility) size = 10;
	else size = 20;

	info.dwSize = size;
	info.bVisible = visibility;

	SetConsoleCursorInfo(hOut, &info);
}

void clearConsoleInputBuffer()
{
	PINPUT_RECORD ClearingVar1 = new INPUT_RECORD[256];
	DWORD ClearingVar2;
	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), ClearingVar1, 256, &ClearingVar2);
	delete[] ClearingVar1;
}