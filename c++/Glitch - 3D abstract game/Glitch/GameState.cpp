#include "GameState.h"

GameState::GameState(StateManager* sm, EnemyFactory* ef, Camera* pCam, MeshManager* mManager, TextureManager* tManager, SpriteBatch* sb, SpriteFont* sf, SoundManager* sManager, Difficulty difficulty, Spotlight* flashlight)
	: State(sm)
{
	m_spriteBatch = sb;
	m_spriteFont = sf;

	m_player = new Player(pCam, Vector3(0, 5.1f, 0), sManager, mManager->getMesh("player"), mManager->getMesh("bullet"), flashlight);

	m_enemyF = ef;
	m_enemyF->setPlayer(m_player);
	
	//Load textures
	m_crosshair = tManager->getTexture("crosshair");
	m_hpGreen = tManager->getTexture("hpGreen");
	m_hpOrange = tManager->getTexture("hpOrange");
	m_hpRed = tManager->getTexture("hpRed");
	m_hpBackGray = tManager->getTexture("hpBackGray");
	m_hpBackBlack = tManager->getTexture("hpBackBlack");
	m_nextLevel = tManager->getTexture("nextLevel");

	//Load sounds
	m_upgrade = sManager->GetSound("Assets/Sounds/upgrade.wav");
	m_levelUp = sManager->GetSound("Assets/Sounds/levelUp.wav");

	m_level = new Level(mManager->getMesh("level"), 2.5, 2);
	m_health = new Health(mManager->getMesh("orange"), sManager);
	//Used to spawn health kits
	m_health->setDestroy(true);

	m_skybox = new Skybox(mManager->getMesh("skybox"));
	m_skybox->setScale(Vector3(7.0f, 7.0f, 7.0f));

	m_levelMin = m_level->getMin();
	m_levelMax = m_level->getMax();

	m_centerScreen.x = GetSystemMetrics(SM_CXSCREEN) / 2;
	m_centerScreen.y = GetSystemMetrics(SM_CYSCREEN) / 2;
	
	srand(time(NULL));
}

void GameState::onEnter()
{
	clearRender();
	clearUpdater();
	clearInput();
	m_collision.clear();

	//Render, Update and get Input from objects
	renderObject(m_skybox);
	renderObject(m_level);
	renderObject(m_player);

	updateObject(m_player);
	inputObject(m_player);

	m_collision.push_back(m_player);

	//Set up player
	m_player->resetHealth();
	m_player->setDestroy(false);
	m_player->setPosition(Vector3::Zero);

	//Init variables
	m_upgraded = false;

	m_maxSecondTimer = 1.0f;
	m_SecondTimer = m_maxSecondTimer;

	m_score = 0;
	m_currentLevel = 1;

	//Some stats vary for the different modes, makes advanced much more difficult than normal
	if (m_difficulty == Difficulty::normal)
	{
		m_maxMonsters = 5;
		m_maxSpawnMonsters = 20;
		m_maxSpawnTimer = 0.8f;
		m_healthPercentage = 80;
		m_maxHealthTimer = 40.0f;
	}
	else if (m_difficulty == Difficulty::advanced)
	{
		m_maxMonsters = 10;
		m_maxSpawnMonsters = 25;
		m_maxSpawnTimer = 0.6f;
		m_healthPercentage = 40;
		m_maxHealthTimer = 80.0f;
	}

	m_monstersKilledLevel = 0;
	m_lateSpawnMonsters = 0;

	m_healthTimer = m_maxHealthTimer;

	m_currentSpawnMonsters = 0;
	m_spawnTimer = 3.0f;

	m_maxNextLevelTimer = 2.0f;
	//Do not display next level
	m_nextLevelTimer = 0;

	m_enemyF->setLevel(m_currentLevel);
	
	//Lock mouse to center of screen
	m_lockMouse = true;
	ShowCursor(false);
}

void GameState::onExit()
{

}

void GameState::onObscuring()
{
	ShowCursor(true);
}

void GameState::onRevealing()
{
	ShowCursor(false);
}

void GameState::handleInput(float timestep, InputController* input)
{
	Inputable<GameObject>::handleInput(timestep, input);

	if (input->GetKeyDownOnce(VK_F1))
	{
		//Lock/Unlock mouse from center of screen
		m_lockMouse = m_lockMouse ? false : true;
		ShowCursor(!m_lockMouse);
	}

	if (input->GetKeyDownOnce(VK_ESCAPE) || input->GetKeyDownOnce('P'))
	{
		//Pause the game
		PauseState* p = static_cast<PauseState*>(m_stateManager->getState("pause"));

		//Pass all rendered objects over
		m_collision.push_back(m_skybox);
		m_collision.push_back(m_level);

		//Change the state to game over
		p->setRenderableObjects(m_collision);

		m_stateManager->push("pause");

		m_collision.pop_back();
		m_collision.pop_back();
	}
}

void GameState::onUpdate(float timestep)
{
	//Lock mouse
	if (m_lockMouse)
	{
		SetCursorPos(m_centerScreen.x, m_centerScreen.y);
	}

	//Checks if the player can upgrade their character
	upgrade();

	//Update timers
	updateTimer(timestep, m_spawnTimer);
	updateTimer(timestep, m_nextLevelTimer);
	updateTimer(timestep, m_SecondTimer);

	//Only update the hp timer if the current hp is destroyed
	if (m_health->checkDestroy())
	{
		updateTimer(timestep, m_healthTimer);
	}

	//progress to next level if new level conditions are met
	nextLevel();
	//Spawn a new monster if spawning conditions are met
	spawnMonster();
	//Checks if another enemy spawns an object
	checkEnemySpawnedObject();
	//Checks if the player has fired a projectile
	checkPlayerFired();
	spawnHealth();

	//Update game objects
	Updateable<GameObject>::onUpdate(timestep);

	//Check collision
	detectCollision(timestep);
	//Deletes dead objects
	cleanDeadObjects();
}

void GameState::onRender(Direct3D* renderer, Camera* camera)
{
	Renderable<GameObject>::onRender(renderer, camera);

	//Draw the gui
	drawGUI();
}

void GameState::drawGUI()
{
	GameGUI::drawCrosshair(m_spriteBatch, m_crosshair);
	GameGUI::drawHp(m_spriteBatch, m_player, m_hpBackBlack, m_hpBackGray, m_hpGreen, m_hpOrange, m_hpRed);
	GameGUI::displayDetails(m_spriteBatch, m_spriteFont, m_currentLevel, m_score, m_maxMonsters, m_lateSpawnMonsters, m_monstersKilledLevel);

	if (m_nextLevelTimer > 0)
	{
		GameGUI::drawNextLevel(m_spriteBatch, m_nextLevel, m_nextLevelTimer);
	}
}

void GameState::checkPlayerFired()
{
	Bullet* b = m_player->checkFired();

	if (b != NULL)
	{
		//Player fired a bullet
		renderObject(b);
		updateObject(b);
		m_collision.push_back(b);
	}
}

void GameState::checkEnemySpawnedObject()
{
	//Create new objects (bullets, enemies) from existing enemies or deletes bullets if their time is up
	for (int i = 0; i < m_collision.size(); i++)
	{
		if (m_collision.at(i)->getType() == "enemy")
		{
			Enemy* e = static_cast<Enemy*>(m_collision.at(i));
			GameObject* g = e->getObject();

			if (g != NULL)
			{
				bool spawn = true;
				//Only spawn enemies up to 5 above the max spawns allowed. Prevents too many monsters spawning from enemies
				//Also prevents farming points from enemies that spawn other enemies
				if (g->getType() == "enemy" && (m_currentSpawnMonsters <= 2 || m_currentSpawnMonsters >= m_maxSpawnMonsters + 5))
				{
					spawn = false;
				}
				else if (g->getType() == "enemy")
				{
					//Monster can spawn. Increase number of spawned monsters
					m_currentSpawnMonsters++;
					m_lateSpawnMonsters++;
				}

				if (spawn)
				{
					renderObject(g);
					updateObject(g);
					m_collision.push_back(g);
				}
			}
		}
	}
}

void GameState::updateTimer(float timestep, float& timer)
{
	//Decrease timer
	if (timer != 0)
	{
		if (timer - timestep <= 0)
		{
			timer = 0;
		}
		else
		{
			timer -= timestep;
		}

	}
}

void GameState::spawnMonster()
{
	if (m_spawnTimer == 0 && m_currentSpawnMonsters < m_maxSpawnMonsters && (m_currentSpawnMonsters + m_monstersKilledLevel) < m_maxMonsters + m_lateSpawnMonsters)
	{
		//Spawn a new monster
		GameObject* enemy = m_enemyF->getObject();
		Enemy* e = static_cast<Enemy*>(enemy);

		//Choose the position of the enemy
		Vector3 min = m_level->getMesh()->getMin() * 2;
		Vector3 max = m_level->getMesh()->getMax() * 2;

		//Prevent enemies spawning on the player
		while (true)
		{
			//Choose a random location within the map to spawn the monster
			Vector3 position = Vector3((int)(rand() % (int)(min.x - max.x + 1) + min.x), (int)(rand() % (int)(min.y - max.y + 1) + min.y), (int)(rand() % (int)(min.z - max.z + 1) + min.z));
			e->setPosition(position);
			e->updateBBox();
			
			//Try to make sure the enemy is not spawned on the enemy
			if (!CheckCollision(*e->getBBox(), *m_player->getBBox()))
			{
				break;
			}
		}

		renderObject(enemy);
		updateObject(enemy);
		m_collision.push_back(enemy);
		
		m_currentSpawnMonsters++;
		//Wait a bit before spawning a new monster
		m_spawnTimer = m_maxSpawnTimer;
	}
}

void GameState::nextLevel()
{
	if (m_monstersKilledLevel >= m_maxMonsters + m_lateSpawnMonsters && m_currentSpawnMonsters == 0)
	{
		//All monsters killed for that level, progress to next level
		m_currentLevel++;
		m_maxMonsters += 3;
		m_monstersKilledLevel = 0;
		m_lateSpawnMonsters = 0;

		if (m_healthPercentage - 1 > 10)
		{
			m_healthPercentage--;
		}

		if (m_currentLevel % 3 == 0 && m_maxSpawnTimer - 0.05 > 0.1)
		{
			m_maxSpawnTimer -= 0.05;
		}

		m_upgraded = false;

		//Update the enemy factory
		m_enemyF->setLevel(m_currentLevel);

		m_nextLevelTimer = m_maxNextLevelTimer;

		m_levelUp->Play();
	}
}

void GameState::spawnHealth()
{
	int percentage = rand() % 100 + 1;

	//Prevents stalling to get to full health
	if (m_maxSpawnMonsters >= 5 && m_healthTimer == 0 && percentage <= m_healthPercentage && m_health->checkDestroy())
	{
		//Spawn at a random location. Even in the air
		Vector3 min = m_level->getMesh()->getMin() * 2;
		//Have the health spawn slightly higher off the ground
		min.y += 3;
		Vector3 max = m_level->getMesh()->getMax() * 2;

		//Choose a random location within the map to spawn the monster
		Vector3 position = Vector3((int)(rand() % (int)(min.x - max.x + 1) + min.x), (int)(rand() % (int)(min.y - max.y + 1) + min.y), (int)(rand() % (int)(min.z - max.z + 1) + min.z));
		
		m_health->reset();
		m_health->setPosition(position);

		renderObject(m_health);
		updateObject(m_health);
		m_collision.push_back(m_health);

		m_healthTimer = m_maxHealthTimer;
	}

	if (m_healthTimer == 0 && percentage > m_healthPercentage)
	{
		//To prevent the health spawning so fast every time, give it a break
		m_healthTimer = 20.0f;
	}
	
}

void GameState::upgrade()
{
	if (m_currentLevel % 4 == 0 && !m_upgraded)
	{
		UpgradeState* u = static_cast<UpgradeState*>(m_stateManager->getState("upgrade"));
		u->setPlayer(m_player);
		u->setPoints(m_score);
		u->setHealth(m_health);

		m_upgraded = true;

		//Only displays the upgrade menu if you can upgrade your character
		if (!u->fullyUpgraded())
		{
			m_stateManager->push("upgrade");
		}
	}
}

void GameState::playerDead()
{
	//Run the game over state if the player died
	ShowCursor(true);

	GameOverState* go = static_cast<GameOverState*>(m_stateManager->getState("gameOver"));

	//Pass all rendered objects over
	m_collision.push_back(m_skybox);
	m_collision.push_back(m_level);

	//Change the state to game over
	go->setRenderableObjects(m_collision);
	go->setScore(m_score);
	go->setLevel(m_currentLevel);

	m_stateManager->pop();
	m_stateManager->push("gameOver");

	m_collision.pop_back();
	m_collision.pop_back();
}

void GameState::enemyDead(Enemy* e)
{
	//Update game variables if the object is an enemy

	//Only give points if the actual hp of the enemy is 0
	//Prevents self destruct enemies from giving players points
	if (e->dead())
	{
		float p = e->getPoints();
		m_score += p;
		m_monstersKilledLevel++;
	}

	m_currentSpawnMonsters--;
}

void GameState::detectCollision(float timestep)
{
	//Run collision code for all possible objects
	for (int i = 0; i < m_collision.size(); i++)
	{
		Vector3 f = m_collision.at(i)->getPosition();

		for (int j = 0; j < m_collision.size(); j++)
		{
			//Same object
			if (i == j) continue;

			Vector3 s = m_collision.at(j)->getPosition();
			//Calculate distance between the two objects
			float d = Vector3::DistanceSquared(f, s);

			//First check if the object is close to the other object or if the object is a bullet
			if (d <= 100) //Distance of 10
			{
				m_collision.at(i)->collision(m_collision.at(j), timestep);

				//Checks if the object is dead, if it is then delete object
				if (m_collision.at(i)->checkDestroy())
				{
					//Do not check any more collisions for this object if it is dead
					break;
				}
			}
		}

		float levelCheckOffset = 10.0f;

		//Level checking needs to be done here
		if ((f.y < m_levelMax.y) &&
			((f.x < m_levelMin.x + levelCheckOffset || f.x > m_levelMax.x - levelCheckOffset) ||
			(f.z < m_levelMin.z + levelCheckOffset || f.z > m_levelMax.z - levelCheckOffset) ||
			(f.y < m_levelMin.y)))
		{
			m_collision.at(i)->collision(m_level, timestep);
		}
	}
}

void GameState::cleanDeadObjects()
{
	for (std::vector<GameObject*>::iterator i = m_collision.begin(); i != m_collision.end(); )
	{
		if ((*i)->checkDestroy())
		{
			//Stop rendering and updating the selected object
			removeFromRender(*i);
			removeFromUpdater(*i);

			//Check what the object type is and run specific commands before removing the object
			if ((*i)->getType() == "enemy")
			{
				enemyDead(static_cast<Enemy*>(*i));
			}
			else if ((*i)->getType() == "player")
			{
				playerDead();
				break;
			}

			i = m_collision.erase(i);
		}

		if (i != m_collision.end())
		{
			i++;
		}
	}
}