#pragma once

#include "Player.h"
#include "GameObject.h"
#include "Collisions.h"

class Player;
class Level;
class Bullet;

enum class Difficulty
{
	normal = 0,
	advanced
};

class Enemy : public GameObject
{
protected:
	//The difficulty of the enemy. Used to determine the set of attacks
	Difficulty m_difficulty;

	//The enemy needs to know where the player is
	Player* m_player;

	//The total points that this enemy is worth
	int m_points;
	//The total health of the enemy
	int m_maxHealth;
	//The current health of the enemy
	int m_currentHealth;
	//The total speed of the enemy
	int m_speed;
	//The damage of the enemy
	int m_damage;

	//The bounding box and the actual min and max of the box
	CBoundingBox* m_bBox;
	Vector3 m_boxMin;
	Vector3 m_boxMax;
	float m_scaleDefault;

	//Used to make the enemies grow when spawning
	Vector3 m_boxMinDefault;
	Vector3 m_boxMaxDefault;
	//Used to check if the enemy is fully spawned
	bool m_spawned;

	//The advanced move set
	virtual void advanced(float timestep) = 0;
	//The normal move set
	virtual void normal(float timestep) = 0;

	//Run when the enemy is spawning
	inline void spawn(float timestep);

	//Collision code for different objects
	virtual void collisionEnemy(Enemy* g);
	virtual void collisionLevel(Level* g, float timestep);
	virtual void collisionBullet(Bullet* g);
	virtual void collisionPlayer(Player* g);

public:
	Enemy(Mesh* mesh, Player* player, Difficulty difficulty, float scale, int points, int maxHealth, int damage, int speed);

	void setPoints(int points) { m_points = points; }
	void setMaxHealth(int newHealth, bool changeCurrentHealth);
	void damage(float damage);
	void setSpeed(int speed) { m_speed = speed; }

	int getPoints() { return m_points; }
	int getMaxHealth() { return m_maxHealth; }
	int getHealth() { return m_currentHealth; }
	int getSpeed() { return m_speed; }
	int getDamage() { return m_damage; }

	void updateBBox();
	CBoundingBox* getBBox() { return m_bBox; }

	bool dead() { return m_currentHealth ? false : true; }

	//This method can be used to render objects from a state instead of the actual enemy itself. eg. Enemy bullets, other enemies etc.
	//Returns NULL in enemy class
	virtual GameObject* getObject();
	void collision(GameObject* g, float timestep);
	virtual void update(float timestep);
};