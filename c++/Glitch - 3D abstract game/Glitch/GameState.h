#pragma once

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "State.h"
#include "GameOverState.h"
#include "PauseState.h"
#include "UpgradeState.h"

#include "Inputable.h"
#include "Updateable.h"
#include "Renderable.h"

#include "Collisions.h"

#include "Spotlight.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Player.h"
#include "Health.h"
#include "Level.h"
#include "Skybox.h"
#include "MemoryPool.h"
#include "EnemyFactory.h"
#include "GameGUI.h"

using namespace DirectX;

class GameState : public State, public Updateable<GameObject>, public Renderable<GameObject>, public Inputable<GameObject>
{
private:
	Player* m_player;
	Level* m_level;
	Skybox* m_skybox;
	//Takes care of all the enemies
	EnemyFactory* m_enemyF;

	//Locks the mouse to the center of the screen
	POINT m_centerScreen;
	bool m_lockMouse;

	//The crosshair
	Texture* m_crosshair;
	//The next level sign
	Texture* m_nextLevel;

	//The hp textures
	Texture* m_hpGreen;
	Texture* m_hpOrange;
	Texture* m_hpRed;
	Texture* m_hpBackGray;
	Texture* m_hpBackBlack;

	//The different sounds
	Sound* m_upgrade;
	Sound* m_levelUp;

	//Used to draw textures and font
	SpriteBatch* m_spriteBatch;
	SpriteFont* m_spriteFont;
	
	//Any object in this vector will be checked for collision detection
	std::vector<GameObject*> m_collision;

	//The score of the player
	int m_score;
	//The current level of the player
	int m_currentLevel;

	//Difficulty of the game
	Difficulty m_difficulty;

	//Checks if the player has already upgraded
	bool m_upgraded;

	//The maximum number of monsters in the current level
	int m_maxMonsters;
	//The number of monsters killed in the current level
	int m_monstersKilledLevel;
	//Used to keep track for each level how many additional enemies get spawned by another enemy
	int m_lateSpawnMonsters;

	//The maximum allowed spawned monsters at one given time
	int m_maxSpawnMonsters;
	//The total number of monsters that are rendered
	int m_currentSpawnMonsters;
	//The max spawn timer value
	float m_maxSpawnTimer;
	//A timer to not make all the monsters spawn at once
	float m_spawnTimer;

	//Timer for 1 second
	float m_maxSecondTimer;
	float m_SecondTimer;

	//The length of time the next level texture is displayed on the screen
	//Will only display the texture if the timer is equal to the max timer
	float m_maxNextLevelTimer;
	float m_nextLevelTimer;

	//The min and max of the level
	Vector3 m_levelMin;
	Vector3 m_levelMax;

	//The percentage to spawn a health pack
	int m_healthPercentage;
	//Timer for the health pack, after touching a pack you need to wait x seconds before another one can spawn
	float m_maxHealthTimer;
	float m_healthTimer;
	//Only need one health pack as only one can spawn at a time
	Health* m_health;

	//Collision detection between objects
	inline void detectCollision(float timestep);
	//Clears all dead objects
	inline void cleanDeadObjects();

	//Checks if the player fired a bullet
	inline void checkPlayerFired();
	//Checks if an enemy spawns multiple enemies or bullets etc.
	inline void checkEnemySpawnedObject();

	//Move to a new level
	inline void nextLevel();
	//Spawn a new monster
	inline void spawnMonster();
	//Spawns health packs
	inline void spawnHealth();

	//Upgrade your character or weapon
	inline void upgrade();

	//Update timer
	inline void updateTimer(float timestep, float& timer);

	//Specific events when an object is dead
	inline void playerDead();
	inline void enemyDead(Enemy* e);

	//Draws the GUI
	inline void drawGUI();

public:
	GameState(StateManager* sm, EnemyFactory* ef, Camera* pCam, MeshManager* mManager, TextureManager* tManager, SpriteBatch* sb, SpriteFont* sf, SoundManager* sManager, Difficulty difficulty, Spotlight* flashlight);

	void onEnter();
	void onExit();
	void onObscuring();
	void onRevealing();

	void setScore(int score) { m_score = score; }
	void setDifficulty(Difficulty d) { m_difficulty = d; m_enemyF->setDifficulty(d); }

	void onUpdate(float timestep);
	void onRender(Direct3D* renderer, Camera* camera);
	void handleInput(float timestep, InputController* input);
};