#pragma once
#ifndef CARD_H
#define CARD_H
#include <string>

class Card
{
public:
	//The colour of the card
	enum colour
	{
		red = 0,
		yellow,
		green,
		blue,
		black = 4 //Wild
	};
	//The value of the card, v stands for value
	 enum value
	{
		v0 = 0, v1, v2, v3, v4, v5, v6, v7, v8, v9,
		vSkip, vReverse, vDraw2, vWild, vWildDraw4 = 14
	};

	//Constructor
	Card(colour c, value v);

	//Returns the string of the colour
	std::string getColour();
	//Converts an int to the enum colour value
	static colour convertToColour(int value);
	//Returns the string of the value
	std::string getValue();
	//Converts an int to the enum value
	static value convertToValue(int value);

	//Compares the colour of the card with another card, returns true if successful
	bool compareColour(Card* c);
	//Compares the colour of the card with another colour, returns true if successful
	bool compareColour(Card::colour colour);
	//Compares the value of the card with another card, returns true if successful
	bool compareValue(Card* c);
	//Compared the value of the card with another value, returns true if successful
	bool compareValue(Card::value value);

	//Changes the colour of the card
	void changeColour(Card::colour newColour);
	//Changes the value of the card
	void changeValue(Card::value newCalue);

private:
	colour m_colour;
	value m_value;
};

#endif