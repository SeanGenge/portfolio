#include "Player.h"

Player::Player(Camera* eyes, Vector3 eyeOffset, SoundManager* sManager, Mesh* player, Mesh* bullet, Spotlight* flashlight)
	: GameObject(player)
{
	m_eyes = eyes;
	m_offset = eyeOffset;

	m_flashlight = flashlight;

	m_bulletPool = new ObjectPool<Bullet>(40, bullet);
	//Only need a very small sound pool since sound finishes very fast
	m_bulletSound = new SoundPool(4, sManager, "Assets/Sounds/pistol.wav");
	m_heartbeat = sManager->GetSound("Assets/Sounds/heartbeat.wav");
	m_hit = sManager->GetSound("Assets/Sounds/damage.wav");
	m_deflect = sManager->GetSound("Assets/Sounds/deflect.wav");
	
	m_type = "player";

	m_bulletSpeed = 90;
	m_bulletDamage = 1;
	m_bulletPenetration = 1;

	m_maxSpeed = 18.0f;
	m_gravity = -100.0f;
	m_jumpForce = 40.0f;
	m_damageResistance = 0;

	m_isJumping = false;

	m_yaw = 0;
	m_pitch = 0;

	m_sensitivity = 3.0f;
	m_lowSensitivity = 3.0f;
	m_superLowSensitivity = 0.5f;

	m_leftRight = 0;
	m_forwardBackwards = 0;

	//Load sounds
	m_footstepsSound = sManager->GetSound("Assets/Sounds/footsteps.wav");

	//Set the camera position in front of the object
	m_eyes->SetPosition(m_position + m_offset);

	m_bBoxMin = Vector3(player->getMin().x * 2.5, player->getMin().y, player->getMin().z * 2.5);
	m_bBoxMax = Vector3(player->getMax().x * 2.5, player->getMax().y * 9, player->getMax().z * 2.5);

	m_bBox = new CBoundingBox(m_bBoxMin + m_position, m_bBoxMax + m_position);

	m_maxHealth = 100;
	m_currentHealth = m_maxHealth;

	m_maxBulletCooldown = 0.70f;
	m_bulletCooldown = 0;

	m_maxDamageCooldown = 0.45f;
	m_damageCooldown = m_maxDamageCooldown;
}

void Player::updateBulletCooldown(float timestep)
{
	if (m_bulletCooldown - timestep <= 0)
	{
		m_bulletCooldown = 0;
	}
	else
	{
		m_bulletCooldown -= timestep;
	}
}

void Player::updateDamageCooldown(float timestep)
{
	if (m_damageCooldown - timestep <= 0)
	{
		m_damageCooldown = 0;
	}
	else
	{
		m_damageCooldown -= timestep;
	}
}

void Player::handleInput(float timestep, InputController* input)
{
	//Check for input from the user to move the position of the camera
	if (input->GetKeyDown('W')) //move forward
	{
		m_forwardBackwards += m_maxSpeed;
	}

	if (input->GetKeyDown('A')) //strafe left
	{
		m_leftRight -= m_maxSpeed;
	}

	if (input->GetKeyDown('S')) //move back
	{
		m_forwardBackwards -= m_maxSpeed;
	}

	if (input->GetKeyDown('D')) //strafe right
	{
		m_leftRight += m_maxSpeed;
	}

	if (input->GetKeyDown('L'))
	{
		//m_position = m_flashlight->getPosition();
		m_flashlight->setPosition(m_position + Vector3(0, 2, 0));
	}
	
	if (input->GetDeltaMouseX() != 0) //y rotation of camera (yaw)
	{
		/*if (timestep > 0.01) m_yaw -= input->GetDeltaMouseX() * m_superLowSensitivity * timestep;
		else if (timestep > 0.001) m_yaw -= input->GetDeltaMouseX() * m_lowSensitivity * timestep;
		else */m_yaw -= input->GetDeltaMouseX() * m_sensitivity * timestep;
	}
	if (input->GetDeltaMouseY() != 0) //x rotation of camera (pitch)
	{
		/*if (timestep > 0.01) m_pitch -= input->GetDeltaMouseY() * m_superLowSensitivity * timestep;
		else if (timestep > 0.001) m_pitch -= input->GetDeltaMouseY() * m_lowSensitivity * timestep;
		else */m_pitch -= input->GetDeltaMouseY() * m_sensitivity * timestep;
	}

	//Jumping
	if (input->GetKeyDownOnce(VK_SPACE) && !m_isJumping)
	{
		m_isJumping = true;
		m_velocity.y = m_jumpForce;
	}

	//Shoot a bullet
	if (m_bulletCooldown == 0 && input->GetMouseDown(0)) //0 - Left mouse button
	{
		m_fired = true;
		m_bulletCooldown = m_maxBulletCooldown;
	}
}

Bullet* Player::checkFired()
{
	if (m_fired)
	{
		Bullet* bullet = m_bulletPool->getObject();

		if (bullet != NULL)
		{
			//Play sound
			Sound* bulletSound = m_bulletSound->getObject();

			if (bulletSound != NULL)
			{
				m_bulletSoundDestroy.push_back(bulletSound);
				bulletSound->Play();
			}

			m_bulletDestroy.push_back(bullet);

			bullet->setRotation(Vector3(DirectX::XMConvertToDegrees(m_pitch), DirectX::XMConvertToDegrees(m_yaw), 0));
			bullet->setPosition(m_position + Vector3(0, 4.0f, 0));

			bullet->setDamage(m_bulletDamage);
			bullet->setSpeed(m_bulletSpeed);
			bullet->setPenetration(m_bulletPenetration);

			//Sets the owner to the player
			bullet->setOwner(true);
			//Just to be sure
			bullet->setDestroy(false);
			m_fired = false;

			return bullet;
		}
	}

	//No free bullets so set back to false
	m_fired = false;

	return NULL;
}

void Player::updateBBox()
{
	m_bBox->SetMin(m_bBoxMin + m_position);
	m_bBox->SetMax(m_bBoxMax + m_position);
}

void Player::damage(int damage)
{
	if (m_currentHealth - damage <= 0)
	{
		m_currentHealth = 0;
	}
	else
	{
		m_currentHealth -= damage;
	}
}

void Player::setMaxHealth(int health)
{
	m_maxHealth = health;

	if (m_currentHealth > health)
	{
		m_currentHealth = m_maxHealth;
	}
}

void Player::setCurrentHealth(int health)
{
	if (m_currentHealth + health >= m_maxHealth)
	{
		m_currentHealth = m_maxHealth;
	}
	else
	{
		m_currentHealth += health;
	}
}

void Player::playHit(int damage)
{
	if (damage == 0)
	{
		m_deflect->Play();
	}
	else
	{
		m_hit->Play();
	}
}

void Player::collision(GameObject* g, float timestep)
{
	std::string type = g->getType();

	if (type == "enemy")
	{
		collisionEnemy(static_cast<Enemy*>(g));
	}
	else if (type == "level")
	{
		collisionLevel(static_cast<Level*>(g), timestep);
	}
	else if (type == "bullet")
	{
		collisionBullet(static_cast<Bullet*>(g));
	}
	else if (type == "health")
	{
		collisionHealth(static_cast<Health*>(g));
	}
}

void Player::collisionEnemy(Enemy* g)
{
	if (m_damageCooldown == 0 && CheckCollision(*g->getBBox(), *getBBox()))
	{
		//Deal damage
		int d = g->getDamage() - m_damageResistance < 0 ? 0 : g->getDamage() - m_damageResistance;

		playHit(d);

		damage(d);
		m_damageCooldown = m_maxDamageCooldown;

		//Checks if the player is dead
		if (m_currentHealth == 0)
		{
			m_heartbeat->Stop();
			m_destroy = true;
		}
	}
}

void Player::collisionLevel(Level* g, float timestep)
{
	//Back wall
	while (CheckPlane(*g->getBackWall(), *getBBox()) != PLANE_IN_FRONT)
	{
		addPosition(Vector3(0, 0, m_maxSpeed * timestep * -1));
		updateBBox();
	}
	//Front wall
	while (CheckPlane(*g->getFrontWall(), *getBBox()) != PLANE_IN_FRONT)
	{
		addPosition(Vector3(0, 0, m_maxSpeed * timestep));
		updateBBox();
	}
	//Left wall
	while (CheckPlane(*g->getLeftWall(), *getBBox()) != PLANE_IN_FRONT)
	{
		addPosition(Vector3(m_maxSpeed * timestep, 0, 0));
		updateBBox();
	}
	//Right wall
	while (CheckPlane(*g->getRightWall(), *getBBox()) != PLANE_IN_FRONT)
	{
		addPosition(Vector3(m_maxSpeed * timestep * -1, 0, 0));
		updateBBox();
	}
}

void Player::collisionBullet(Bullet* g)
{
	if (!g->getOwner())
	{
		if (m_damageCooldown == 0 && CheckCollision(*g->getBBox(), *getBBox()))
		{
			//Bullets is less affected by damage resistance
			int d = g->getDamage() - m_damageResistance / 2 < 0 ? 0 : g->getDamage() - m_damageResistance / 2;

			playHit(d);

			damage(d);
			m_damageCooldown = m_maxDamageCooldown;
		}

		//Checks if the player is dead
		if (m_currentHealth == 0)
		{
			m_heartbeat->Stop();
			m_destroy = true;
		}
	}
}

void Player::collisionHealth(Health* g)
{
	if (CheckCollision(*g->getBBox(), *getBBox()))
	{
		setCurrentHealth(g->getHealthBonus());
	}
}

void Player::resetHealth()
{
	m_currentHealth = m_maxHealth;
}

void Player::checkDestroyBullets()
{
	for (std::vector<Bullet*>::iterator i = m_bulletDestroy.begin(); i != m_bulletDestroy.end(); )
	{
		if ((*i)->checkDestroy())
		{
			m_bulletPool->finished(*i);
			i = m_bulletDestroy.erase(i);
		}

		if (i != m_bulletDestroy.end())
		{
			i++;
		}
	}
}

void Player::checkDestroyBulletSounds()
{
	for (std::vector<Sound*>::iterator i = m_bulletSoundDestroy.begin(); i != m_bulletSoundDestroy.end();)
	{
		if ((*i)->soundFinished())
		{
			m_bulletSound->finished(*i);
			i = m_bulletSoundDestroy.erase(i);
		}

		if (i != m_bulletSoundDestroy.end())
		{
			i++;
		}
	}
}

void Player::update(float timestep)
{
	checkDestroyBullets();
	checkDestroyBulletSounds();

	float degPitch = DirectX::XMConvertToDegrees(m_pitch);

	updateBulletCooldown(timestep);
	updateDamageCooldown(timestep);

	//Restrict the pitch
	if (degPitch >= 89.0f)
	{
		m_pitch = DirectX::XMConvertToRadians(89.0f);
	}

	if (degPitch <= -89.0f)
	{
		m_pitch = DirectX::XMConvertToRadians(-89.0f);
	}

	//Calculate the rotation of the camera
	Matrix camRotation = Matrix::CreateFromYawPitchRoll(m_yaw, m_pitch, 0);
	Matrix yRotation = Matrix::CreateRotationY(m_yaw);

	//The right and forward vectors of the player but only with y rotation
	Vector3 right = Vector3::Transform(Vector3::Right, yRotation);
	Vector3 forward = Vector3::Transform(Vector3::Forward, yRotation);

	//Update the flashlight's position and direction
	m_flashlight->setPosition(m_position + Vector3(0, 5, 0));
	//m_flashlight->setDirection(Vector3(DirectX::XMConvertToDegrees(m_pitch), DirectX::XMConvertToDegrees(m_yaw), 0));
	
	//Play footsteps sound
	if ((m_forwardBackwards != 0 || m_leftRight != 0) && !m_isJumping)
	{
		m_footstepsSound->Play();
	}
	else
	{
		m_footstepsSound->Stop();
	}

	//If low hp, play the players heartbeat
	if (m_currentHealth <= 25)
	{
		m_heartbeat->Play();
	}
	else
	{
		m_heartbeat->Stop();
	}

	//Calculate the target of the camera
	Vector3 target = Vector3::Transform(Vector3::Forward, camRotation);
	target.Normalize();

	//Get the new location of the object
	m_position += m_leftRight * right * timestep;
	m_position += m_forwardBackwards * forward * timestep;

	//Update the position of the bounding box of the player
	updateBBox();
	
	//Jump code
	if (m_isJumping)
	{
		if (m_position.y + m_velocity.y > 30)
			int a = 0;
		if (m_position.y + m_velocity.y * timestep > 0)
		{
			m_velocity.y += m_gravity * timestep;
			m_position += m_velocity.y * timestep * Vector3::Up;
		}
		else
		{
			m_position.y = 0;
			m_velocity.y = 0.0f;
			m_isJumping = false;
		}
	}

	//Update the position of the camera
	m_eyes->SetPosition(m_position + m_offset);

	m_leftRight = 0;
	m_forwardBackwards = 0;

	//Update the target of the camera
	m_eyes->SetLookAt(target + m_position + m_offset);

	m_eyes->Update(timestep);
}

void Player::render(Direct3D* renderer, Camera* camera)
{
	//Do not render player
}