#include "Card.h"

Card::Card(colour c, value v)
{
	m_colour = c;
	m_value = v;
}

std::string Card::getColour()
{
	switch (m_colour)
	{
	case red:
		return "red";
	case yellow:
		return "yellow";
	case green:
		return "green";
	case blue:
		return "blue";
	case black:
		return "black";
	}
}

std::string Card::getValue()
{
	switch (m_value)
	{
	case vSkip:
		return "skip";
	case vReverse:
		return "reverse";
	case vDraw2:
		return "draw 2";
	case vWild:
		return "wild";
	case vWildDraw4:
		return "wild draw 4";
	default: //Returns a number as a string
		return std::to_string(m_value);
	}
}

Card::colour Card::convertToColour(int value)
{
	switch (value)
	{
	case 0:
		return Card::red;
	case 1:
		return Card::yellow;
	case 2:
		return Card::green;
	case 3:
		return Card::blue;
	case 4:
		return Card::black;
	default: //Tries and gets a value between 0 and 4
		value %= 5;
		convertToColour(value);
		break;
	}
}

Card::value Card::convertToValue(int value)
{
	switch (value)
	{
	case 0: return v0;
	case 1: return v1; case 2: return v2; case 3: return v3;
	case 4: return v4; case 5: return v5; case 6: return v6;
	case 7: return v7; case 8: return v8; case 9: return v9;
	case 10:
		return vSkip;
	case 11:
		return vReverse;
	case 12:
		return vDraw2;
	case 13:
		return vWild;
	case 14:
		return vWildDraw4;
	default: //Tries and gets a valid value
		value %= 14;
		convertToValue(value);
		break;
	}
}

bool Card::compareColour(Card* c)
{
	if (m_colour == c->m_colour) return true;
	else return false;
}

bool Card::compareColour(Card::colour colour)
{
	if (m_colour == colour) return true;
	else return false;
}

bool Card::compareValue(Card* c)
{
	if (m_value == c->m_value) return true;
	else return false;
}

bool Card::compareValue(Card::value value)
{
	if (m_value == value) return true;
	else return false;
}

void Card::changeColour(Card::colour newColour)
{
	m_colour = newColour;
}

void Card::changeValue(Card::value newValue)
{
	m_value = newValue;
}