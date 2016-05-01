#pragma once

#include <ctime>
#include <cstdlib>

#include "Factory.h"
#include "GameObject.h"

#include "GreenEnemy.h"
#include "BlueEnemy.h"
#include "PurpleEnemy.h"
#include "RedEnemy.h"

class PurpleEnemy;

class EnemyFactory : public Factory<GameObject>
{
private:
	//The current level the player is on
	int m_level;
	//The current difficulty of the game
	Difficulty m_difficulty;
	//The player
	Player* m_player;
	Mesh* m_bullet;
	Mesh* m_enemyBullet;

	float m_incr;
	//True if a new level
	bool m_newLevel;

public:
	EnemyFactory(MeshManager* mManager, Player* player, Mesh* bullet, Mesh* enemyBullet, Difficulty difficulty, int level);

	//Sets all the required values on spawning a new enemy
	void setLevel(int newLevel);
	void setDifficulty(Difficulty newDifficulty) { m_difficulty = newDifficulty; }
	void setPlayer(Player* player) { m_player = player; }

	GameObject* getObject();
};