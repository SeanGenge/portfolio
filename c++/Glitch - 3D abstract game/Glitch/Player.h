#pragma once

#include "GameObject.h"
#include "InputController.h"
#include "Camera.h"
#include "ObjectPool.h"
#include "SoundPool.h"
#include "Enemy.h"
#include "Level.h"
#include "Bullet.h"
#include "Health.h"
#include "Collisions.h"
#include "SoundManager.h"
#include "Spotlight.h"

class Enemy;
class Bullet;
class Health;

class Player : public GameObject
{
private:
	//The camera of the player
	Camera* m_eyes;
	//The offset of the camera from the player
	Vector3 m_offset;
	
	//The player's flashlight
	Spotlight* m_flashlight;

	//All the bullets
	ObjectPool<Bullet>* m_bulletPool;
	//Holds all fired bullets. Used to place back into memory pool
	std::vector<Bullet*> m_bulletDestroy;

	//Bounding box
	CBoundingBox* m_bBox;

	//Sounds of the player
	Sound* m_footstepsSound;
	Sound* m_heartbeat;
	Sound* m_hit;
	Sound* m_deflect;
	SoundPool* m_bulletSound;

	//Holds all the bullet sound objects and check if the sound is finished
	std::vector<Sound*> m_bulletSoundDestroy;

	//When set to true, creates a new bullet
	bool m_fired;

	//Cooldown for firing bullets
	float m_maxBulletCooldown;
	float m_bulletCooldown;

	//Weapon variables
	int m_bulletSpeed;
	int m_bulletDamage;
	int m_bulletPenetration;

	//Prevents losing health so fast
	float m_maxDamageCooldown;
	float m_damageCooldown;

	//The maximum speed of the player
	float m_maxSpeed;
	//The max jump height;
	float m_jumpForce;
	//Gravity of the player
	float m_gravity;
	//The velocity of the player
	Vector3 m_velocity;
	//Checks whether the player has already jumped
	bool m_isJumping;

	//The max health of the player
	int m_maxHealth;
	//The current health of the player
	int m_currentHealth;

	//The damage resistance of the player
	int m_damageResistance;

	//The current rotation of the camera
	float m_yaw;
	float m_pitch;
	//How sensitive the movement is when rotating
	float m_sensitivity;
	//Lower the sensitivity if the timestep is too high
	float m_lowSensitivity;
	//Even lower sens when the timestep is insanely high
	float m_superLowSensitivity;

	//The value that moves the camera left and right
	float m_leftRight;
	//The value that moves the camera forward and backwards
	float m_forwardBackwards;

	//The default min and max of the bounding box
	Vector3 m_bBoxMin;
	Vector3 m_bBoxMax;

	//Checks whether the player plays the hit or deflect sound depending on the damage
	inline void playHit(int damage);

	//Collision code for different objects
	inline void collisionEnemy(Enemy* g);
	inline void collisionLevel(Level* g, float timestep);
	inline void collisionBullet(Bullet* g);
	inline void collisionHealth(Health* g);

	inline void checkDestroyBullets();
	inline void checkDestroyBulletSounds();

public:
	//You pass the global camera in for the player to move it as it's eyes
	Player(Camera* eyes, Vector3 eyeOffset, SoundManager* sManager, Mesh* player, Mesh* bullet, Spotlight* flashlight);

	//Get the bounding box
	CBoundingBox* getBBox() { return m_bBox; }
	//Updates the bounding box
	inline void updateBBox();

	float getSpeed() { return m_maxSpeed; }
	float getGravity() { return m_gravity; }

	int getWeaponSpeed() { return m_bulletSpeed; }
	int getWeaponDamage() { return m_bulletDamage; }
	int getWeaponPenetration() { return m_bulletPenetration; }
	float getWeaponCooldown() { return m_maxBulletCooldown; }

	void damage(int damage);
	void setMaxHealth(int health);
	void setCurrentHealth(int health);
	void setSpeed(int speed) { m_maxSpeed = speed; }
	void setDamageResistance(int damageR) { m_damageResistance = damageR; }

	void setWeaponSpeed(int speed) { m_bulletSpeed = speed; }
	void setWeaponDamage(int damage) { m_bulletDamage = damage; }
	void setWeaponPenetration(int penetration) { m_bulletPenetration = penetration; }
	void setWeaponCooldown(float cooldown) { m_maxBulletCooldown = cooldown; }

	void resetHealth();
	int getHealth() { return m_currentHealth; }
	int getMaxHealth() { return m_maxHealth; }
	int getDamageResistance() { return m_damageResistance; }

	float getYaw() { return m_yaw; }
	float getPitch() { return m_pitch; }

	inline void updateBulletCooldown(float timestep);
	inline void updateDamageCooldown(float timestep);

	//Retrieves a bullet if fired if not returns NULL
	Bullet* checkFired();

	void collision(GameObject* g, float timestep);

	void handleInput(float timestep, InputController* input);
	void update(float timestep);
	void render(Direct3D* renderer, Camera* camera);
};