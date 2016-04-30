#include "Player.h"

int Player::_totalPlayers = 0;

Player::Player(std::string name, bool isBot, std::string botDifficulty)
{
	m_name = name;
	m_isBot = isBot;
	m_botDifficulty = botDifficulty;

	_totalPlayers++;
}

Player::~Player()
{
	_totalPlayers--;

	std::vector<Card*>::iterator i;
	for (i = m_hand.begin(); i != m_hand.end(); i++) delete *i;

	m_hand.clear();
}

bool Player::isBot()
{
	//Default is human player
	return m_isBot;
}

std::string Player::getDifficulty()
{
	return m_botDifficulty;
}

void Player::toggleBot(bool activate)
{
	m_isBot = activate;

	//If the bot is disabled, change the difficulty of the bot to none
	if (activate == false) m_botDifficulty = "none";
	//If bot is enabled, change difficulty to easy
	if (activate == true) m_botDifficulty = "easy";
}

void Player::changeDifficulty(std::string newDifficulty)
{
	if (newDifficulty.compare("easy") != 0 && newDifficulty.compare("hard") != 0)  m_botDifficulty = "easy";
	else m_botDifficulty = newDifficulty;
}

Player* Player::newPlayer(std::string name, int maxLength, bool isBot, std::string botDifficulty)
{
	if (name.empty() != true && name.length() <= maxLength)
	{
		if (name.at(0) != ' ')
		{
			if ((botDifficulty.compare("easy") != 0 && botDifficulty.compare("hard") != 0) && isBot) botDifficulty = "easy";
			else if(botDifficulty.compare("none") != 0 && !isBot) botDifficulty = "none";

			Player* newPlayer = new Player(name, isBot, botDifficulty);
			return newPlayer;
		}
	}
}

int Player::getTotalPlayerObjects()
{
	return _totalPlayers;
}

bool Player::changeName(std::string newName, int maxLength)
{
	if (newName.size() <= maxLength && newName.empty() == false)
	{
		//Makes sure the starting letter is not a space
		if (newName.at(0) != ' ')
		{
			m_name = newName;
			return true;
		}
	}
}

std::string Player::getName()
{
	return m_name;
}

std::vector<Card*> Player::getHand()
{
	return m_hand;
}

Card* Player::getCard(int index)
{
	return m_hand.at(index);
}

bool Player::newHand(int maxHand, std::vector<Card*>* deck)
{
	//Makes sure correct values are typed in
	if (maxHand > 0 || deck->empty() != true)
	{
		//Destroys all the objects that the hand is holding
		if (m_hand.empty() != true)
		{
			for (std::vector<Card*>::iterator i = m_hand.begin(); i != m_hand.end(); i++) delete (*i);
		}

		m_hand.clear();

		for (int i = 0; i < maxHand; i++)
		{
			//Makes sure it only adds cards until maxHand is reached or the deck is empty
			if (deck->empty() != true)
			{
				m_hand.push_back(deck->at(0));
				deck->erase(deck->begin());
			}
			else break;
		}

		return true;
	}
	else return false;
}

bool Player::removeCard(int index)
{
	//Makes sure the hand is not empty and the index is within the range of the hand
	if (m_hand.empty() != true && m_hand.size() > index)
	{
		m_hand.erase(m_hand.begin() + index);
		return true;
	}
	else return false;
}

bool Player::removeCard(Card::value v, Card::colour c)
{
	if (m_hand.empty() != true)
	{
		for (int i = 0; i < m_hand.size(); i++)
		{
			//Erases the card if the value and the colour matches
			if (m_hand.at(i)->compareValue(v) && m_hand.at(i)->compareColour(c))
			{
				m_hand.erase(m_hand.begin() + i);
				break;
			}
		}

		return true;
	}
	else return false;
}

bool Player::removeCard(Card* card)
{
	//Tries and finds a card which matches these criteria, must match both correctly
	for (int i = 0; i < m_hand.size(); i++)
	{
		if (m_hand.at(i)->compareColour(card) && m_hand.at(i)->compareValue(card))
		{
			m_hand.erase(m_hand.begin() + i);
			return true;
		}
	}

	return false;
}

void Player::addCard(Card* c)
{
	m_hand.push_back(c);
}

bool Player::addCard(std::vector<Card*>* deck)
{
	if (deck->empty() != true)
	{
		m_hand.push_back(deck->at(0));
		deck->erase(deck->begin());

		return true;
	}
	else return false;
}

bool Player::addCard(std::vector<Card*>* deck, int numCards)
{
	if (deck->empty() != true || numCards > 0)
	{
		for (int i = 0; i < numCards; i++)
		{
			if (deck->empty() != true)
			{
				m_hand.push_back(deck->at(0));
				deck->erase(deck->begin());
			}
			else break;
		}

		return true;
	}
	else return false;
}