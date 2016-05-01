#pragma once

#include "GameObject.h"
#include "Collisions.h"
#include "Level.h"
#include "Enemy.h"

class Enemy;
class Player;

class Bullet : public GameObject
{
protected:
	//The penetration of the bullet. Pass through multiple enemies
	int m_penetration;
	//How fast the bullet travels
	float m_speed;
	//The damage the bullet does per hit
	float m_damage;
	//The maximum time before the bullet is destroyed in seconds
	float m_maxDestroyBulletTimer;
	float m_destroyBulletTimer;

	//Collision
	CBoundingBox* m_bBox;
	//The default min and max of the bounding box
	Vector3 m_bBoxMin;
	Vector3 m_bBoxMax;

	//Who fired the bullet. The player or enemy
	bool m_playerBullet;

	//Collision code for different objects
	inline void collisionEnemy(Enemy* g);
	inline void collisionLevel(Level* g, float timestep);
	inline void collisionBullet(Bullet* g);
	inline void collisionPlayer(Player* g);

public:
	Bullet(Mesh* mesh);

	void setSpeed(float speed) { m_speed = speed; }
	void setDamage(float damage) { m_damage = damage; }
	void setPenetration(int penetration) { m_penetration = penetration; }

	float getSpeed() { return m_speed; }
	float getDamage() { return m_damage; }
	float getPenetration() { return m_penetration; }

	inline void updateDestroyTimer(float timestep);

	inline void updateBBox();
	CBoundingBox* getBBox() { return m_bBox; }

	void setOwner(bool player) { m_playerBullet = player; }
	bool getOwner() { return m_playerBullet; }

	inline void reset();

	void collision(GameObject* g, float timestep);
	virtual void update(float timestep);
};