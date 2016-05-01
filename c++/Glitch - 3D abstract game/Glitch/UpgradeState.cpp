#include "UpgradeState.h"

UpgradeState::UpgradeState(StateManager* sm, SpriteBatch* sb, SpriteFont* sfL, SpriteFont* sfS, SoundManager* sManager, InputController* input, TextureManager* tm)
	: State(sm)
{
	m_spriteBatch = sb;
	m_spriteFontLarge = sfL;
	m_spriteFontSmall = sfS;

	m_player = NULL;
	m_points = 0;

	m_upgradeSound = sManager->GetSound("Assets/Sounds/upgrade.wav");
	m_title = tm->getTexture("upgrade");

	//25% more every time you upgrade
	m_costIncrement = 0.2;

	//Init cap values
	m_playerSpeedCap = 45;
	m_playerDamageResistanceCap = 15;
	m_healthBonusCap = 80;
	m_weaponSpeedCap = 200;
	m_weaponDamageCap = 10;
	m_weaponPenetrationCap = 3;
	m_weaponCooldownCap = 0.20;

	//Set up the initial cost of each stat
	m_playerSpeedCost = 50;
	m_playerDamageResistanceCost = 1500;
	m_healthBonusCost = 75;
	m_weaponSpeedCost = 50;
	m_weaponDamageCost = 200;
	m_weaponPenetrationCost = 25000;
	m_weaponCooldownCost = 200;

	//Set up the increment values. These do not change
	m_playerSpeedIncrement = 1;
	m_playerDamageResistanceIncrement = 1;
	m_healthBonusIncrement = 5;
	m_weaponSpeedIncrement = 5;
	m_weaponDamageIncrement = 1;
	m_weaponPenetrationIncrement = 1;
	m_weaponCooldownIncrement = 0.05f;

	//Width of the small button
	int buttonWidth = 61;
	int buttonHeight = 88 / 2;

	int largeButtonWidth = 210;
	int largeButtonHeight = 170 / 2;
	
	//Init buttons
	m_playerSpeedAddButton = new Button(buttonWidth, buttonHeight, tm->getTexture("buttonSmall"), L"+", Vector2(PLAYERXLOC + STRINGPADDING, UPGRADEYLOC + UPGRADEPADDING), sb, sfL, input, [this]
	{
		modifyValues(true, m_playerSpeed, m_playerSpeedIncrement, m_playerSpeedCost, m_playerSpeedPrevCost);
	});
	m_playerSpeedSubtractButton = new Button(buttonWidth, buttonHeight, tm->getTexture("buttonSmall"), L"-", Vector2(PLAYERXLOC + STRINGPADDING + BUTTONPADDING, UPGRADEYLOC + UPGRADEPADDING), sb, sfL, input, [this]
	{
		modifyValues(false, m_playerSpeed, m_playerSpeedIncrement, m_playerSpeedCost, m_playerSpeedPrevCost);
	});

	m_playerDamageResistanceAddButton = new Button(buttonWidth, buttonHeight, tm->getTexture("buttonSmall"), L"+", Vector2(PLAYERXLOC + STRINGPADDING, UPGRADEYLOC + UPGRADEPADDING * 2), sb, sfL, input, [this]
	{
		modifyValues(true, m_playerDamageResistance, m_playerDamageResistanceIncrement, m_playerDamageResistanceCost, m_playerDamageResistancePrevCost);
	});
	m_playerDamageResistanceSubtractButton = new Button(buttonWidth, buttonHeight, tm->getTexture("buttonSmall"), L"-", Vector2(PLAYERXLOC + STRINGPADDING + BUTTONPADDING, UPGRADEYLOC + UPGRADEPADDING * 2), sb, sfL, input, [this]
	{
		modifyValues(false, m_playerDamageResistance, m_playerDamageResistanceIncrement, m_playerDamageResistanceCost, m_playerDamageResistancePrevCost);
	});

	m_healthBonusAddButton = new Button(buttonWidth, buttonHeight, tm->getTexture("buttonSmall"), L"+", Vector2(PLAYERXLOC + STRINGPADDING, UPGRADEYLOC + UPGRADEPADDING * 3), sb, sfL, input, [this]
	{
		modifyValues(true, m_healthBonus, m_healthBonusIncrement, m_healthBonusCost, m_healthBonusPrevCost);
	});
	m_healthBonusSubtractButton = new Button(buttonWidth, buttonHeight, tm->getTexture("buttonSmall"), L"-", Vector2(PLAYERXLOC + STRINGPADDING + BUTTONPADDING, UPGRADEYLOC + UPGRADEPADDING * 3), sb, sfL, input, [this]
	{
		modifyValues(false, m_healthBonus, m_healthBonusIncrement, m_healthBonusCost, m_healthBonusPrevCost);
	});

	m_weaponSpeedAddButton = new Button(buttonWidth, buttonHeight, tm->getTexture("buttonSmall"), L"+", Vector2(WEAPONXLOC + STRINGPADDING, UPGRADEYLOC + UPGRADEPADDING), sb, sfL, input, [this]
	{
		modifyValues(true, m_weaponSpeed, m_weaponSpeedIncrement, m_weaponSpeedCost, m_weaponSpeedPrevCost);
	});
	m_weaponSpeedSubtractButton = new Button(buttonWidth, buttonHeight, tm->getTexture("buttonSmall"), L"-", Vector2(WEAPONXLOC + STRINGPADDING + BUTTONPADDING, UPGRADEYLOC + UPGRADEPADDING), sb, sfL, input, [this]
	{
		modifyValues(false, m_weaponSpeed, m_weaponSpeedIncrement, m_weaponSpeedCost, m_weaponSpeedPrevCost);
	});

	m_weaponDamageAddButton = new Button(buttonWidth, buttonHeight, tm->getTexture("buttonSmall"), L"+", Vector2(WEAPONXLOC + STRINGPADDING, UPGRADEYLOC + UPGRADEPADDING * 2), sb, sfL, input, [this]
	{
		modifyValues(true, m_weaponDamage, m_weaponDamageIncrement, m_weaponDamageCost, m_weaponDamagePrevCost);
	});
	m_weaponDamageSubtractButton = new Button(buttonWidth, buttonHeight, tm->getTexture("buttonSmall"), L"-", Vector2(WEAPONXLOC + STRINGPADDING + BUTTONPADDING, UPGRADEYLOC + UPGRADEPADDING * 2), sb, sfL, input, [this]
	{
		modifyValues(false, m_weaponDamage, m_weaponDamageIncrement, m_weaponDamageCost, m_weaponDamagePrevCost);
	});

	m_weaponPenetrationAddButton = new Button(buttonWidth, buttonHeight, tm->getTexture("buttonSmall"), L"+", Vector2(WEAPONXLOC + STRINGPADDING, UPGRADEYLOC + UPGRADEPADDING * 3), sb, sfL, input, [this]
	{
		modifyValues(true, m_weaponPenetration, m_weaponPenetrationIncrement, m_weaponPenetrationCost, m_weaponPenetrationPrevCost);
	});
	m_weaponPenetrationSubtractButton = new Button(buttonWidth, buttonHeight, tm->getTexture("buttonSmall"), L"-", Vector2(WEAPONXLOC + STRINGPADDING + BUTTONPADDING, UPGRADEYLOC + UPGRADEPADDING * 3), sb, sfL, input, [this]
	{
		modifyValues(false, m_weaponPenetration, m_weaponPenetrationIncrement, m_weaponPenetrationCost, m_weaponPenetrationPrevCost);
	});

	m_weaponCooldownAddButton = new Button(buttonWidth, buttonHeight, tm->getTexture("buttonSmall"), L"+", Vector2(WEAPONXLOC + STRINGPADDING, UPGRADEYLOC + UPGRADEPADDING * 4), sb, sfL, input, [this]
	{
		modifyValues(true, m_weaponCooldown, m_weaponCooldownIncrement, m_weaponCooldownCost, m_weaponCooldownPrevCost);
	});
	m_weaponCooldownSubtractButton = new Button(buttonWidth, buttonHeight, tm->getTexture("buttonSmall"), L"-", Vector2(WEAPONXLOC + STRINGPADDING + BUTTONPADDING, UPGRADEYLOC + UPGRADEPADDING * 4), sb, sfL, input, [this]
	{
		modifyValues(false, m_weaponCooldown, m_weaponCooldownIncrement, m_weaponCooldownCost, m_weaponCooldownPrevCost);
	});

	m_finish = new Button(largeButtonWidth, largeButtonHeight, tm->getTexture("button"), L"finish", Vector2(WEAPONXLOC + STRINGPADDING, UPGRADEYLOC + UPGRADEPADDING * 8), sb, sfL, input, [this]
	{
		resume();
	});
}

void UpgradeState::onEnter()
{
	m_upgradeSound->Play();

	//Set all upgrade variables to 0
	m_playerSpeed = 0;
	m_playerDamageResistance = 0;
	m_healthBonus = 0;
	m_weaponSpeed = 0;
	m_weaponDamage = 0;
	m_weaponPenetration = 0;
	m_weaponCooldown = 0;

	m_playerSpeedPrevCost.clear();
	m_playerDamageResistancePrevCost.clear();
	m_healthBonusPrevCost.clear();
	m_weaponSpeedPrevCost.clear();
	m_weaponDamagePrevCost.clear();
	m_weaponPenetrationPrevCost.clear();
	m_weaponCooldownPrevCost.clear();
}

void UpgradeState::onExit()
{

}

void UpgradeState::onObscuring()
{

}

void UpgradeState::onRevealing()
{

}

void UpgradeState::setRenderableObjects(std::vector<GameObject*> g)
{
	clearRender();

	//Renders any objects that you pass to it
	for (std::vector<GameObject*>::iterator i = g.begin(); i != g.end(); i++)
	{
		renderObject(*i);
	}
}

void UpgradeState::onRender(Direct3D* renderer, Camera* camera)
{
	Renderable<GameObject>::onRender(renderer, camera);

	//Draw the underlying gui for the upgrade state
	drawGUI();
}

bool UpgradeState::fullyUpgraded()
{
	return !canUpgrade(m_player->getWeaponSpeed(), 0, m_weaponSpeedCap) &&
		!canUpgrade(m_player->getWeaponDamage(), 0, m_weaponDamageCap) &&
		!canUpgrade(m_player->getWeaponPenetration(), 0, m_weaponPenetrationCap) &&
		!canUpgrade(m_player->getWeaponCooldown() * -1, 0, m_weaponCooldownCap * -1) &&
		!canUpgrade(m_player->getSpeed(), 0, m_playerSpeedCap) &&
		!canUpgrade(m_player->getDamageResistance(), 0, m_playerDamageResistanceCap) &&
		!canUpgrade(m_health->getHealthBonus(), 0, m_healthBonusCap);
}

void UpgradeState::modifyValues(bool add, float& variable, float increment, int& cost, std::vector<int>& prevCost)
{
	if (m_points - cost >= 0 && add)
	{
		m_points -= cost;
		prevCost.push_back(cost);
		cost += cost * m_costIncrement;
		variable += increment;
	}
	else if (!add && prevCost.size() > 0)
	{
		cost = prevCost.at(prevCost.size() - 1);
		m_points += cost;
		prevCost.pop_back();
		variable -= increment;

		if (variable < 0.00001)
		{
			variable = 0;
		}
	}
}

bool UpgradeState::canUpgrade(float prevValue, float increment, float cap)
{
	return prevValue + increment < cap;
}

void UpgradeState::drawGUI()
{
	displayUpgradeTitle();
	displayPlayerStats();

	displayPlayerOptions();
	displayWeaponOptions();

	displayPlayerButtons();
	displayWeaponButtons();

	displayFinishButton();
}

void UpgradeState::displayUpgradeTitle()
{
	RECT pos;
	int sizeX = 250;
	int sizeY = 75;
	//Hard coded middle of the screen.
	pos.left = 350 - sizeX;
	pos.right = 350 + sizeX;
	pos.top = 150 - sizeY;
	pos.bottom = 150 + sizeY;

	m_spriteBatch->Draw(m_title->GetShaderResourceView(), pos);
}

void UpgradeState::displayPlayerStats()
{
	if (m_player != NULL)
	{
		//Display title for player upgrades
		m_spriteFontSmall->DrawString(m_spriteBatch, L"Current stats", Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC - CURRENTPADDING), Colors::Aqua);
		
		std::wstring points = L"Points: " + std::to_wstring(m_points);
		std::wstring pSpeed = L"Player speed: " + std::to_wstring(m_player->getSpeed()).substr(0, 4) + L" (+" + std::to_wstring(m_playerSpeed).substr(0, 4) + L")";
		std::wstring pDamageResistance = L"Damage resistance: " + std::to_wstring(m_player->getDamageResistance()).substr(0, 4) + L" (+" + std::to_wstring(m_playerDamageResistance).substr(0, 4) + L")";
		std::wstring pHealthBonus = L"Health bonus: " + std::to_wstring(m_health->getHealthBonus()).substr(0, 4) + L" (+" + std::to_wstring(m_healthBonus).substr(0, 4) + L")";

		std::wstring wSpeed = L"Weapon speed: " + std::to_wstring(m_player->getWeaponSpeed()).substr(0, 4) + L" (+" + std::to_wstring(m_weaponSpeed).substr(0, 4) + L")";
		std::wstring wDamage = L"Weapon damage: " + std::to_wstring(m_player->getWeaponDamage()).substr(0, 4) + L" (+" + std::to_wstring(m_weaponDamage).substr(0, 4) + L")";
		std::wstring wPenetration = L"Weapon Penetration: " + std::to_wstring(m_player->getWeaponPenetration()).substr(0, 4) + L" (+" + std::to_wstring(m_weaponPenetration).substr(0, 4) + L")";
		std::wstring wCooldown = L"Weapon cooldown: " + std::to_wstring(m_player->getWeaponCooldown()).substr(0, 4) + L" (-" + std::to_wstring(m_weaponCooldown).substr(0, 4) + L")";

		//Player upgrade options
		m_spriteFontSmall->DrawString(m_spriteBatch, points.c_str(), Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC), Colors::White);
		if (m_playerSpeed > 0)
		{
			m_spriteFontSmall->DrawString(m_spriteBatch, pSpeed.c_str(), Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC + CURRENTPADDING), Colors::Green);
		}
		else
		{
			m_spriteFontSmall->DrawString(m_spriteBatch, pSpeed.c_str(), Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC + CURRENTPADDING), Colors::White);
		}
		if (m_playerDamageResistance > 0)
		{
			m_spriteFontSmall->DrawString(m_spriteBatch, pDamageResistance.c_str(), Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC + CURRENTPADDING * 2), Colors::Green);
		}
		else
		{
			m_spriteFontSmall->DrawString(m_spriteBatch, pDamageResistance.c_str(), Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC + CURRENTPADDING * 2), Colors::White);
		}
		if (m_healthBonus > 0)
		{
			m_spriteFontSmall->DrawString(m_spriteBatch, pHealthBonus.c_str(), Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC + CURRENTPADDING * 3), Colors::Green);
		}
		else
		{
			m_spriteFontSmall->DrawString(m_spriteBatch, pHealthBonus.c_str(), Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC + CURRENTPADDING * 3), Colors::White);
		}

		if (m_weaponSpeed > 0)
		{
			m_spriteFontSmall->DrawString(m_spriteBatch, wSpeed.c_str(), Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC + CURRENTPADDING * 4), Colors::Green);
		}
		else
		{
			m_spriteFontSmall->DrawString(m_spriteBatch, wSpeed.c_str(), Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC + CURRENTPADDING * 4), Colors::White);
		}
		if (m_weaponDamage > 0)
		{
			m_spriteFontSmall->DrawString(m_spriteBatch, wDamage.c_str(), Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC + CURRENTPADDING * 5), Colors::Green);
		}
		else
		{
			m_spriteFontSmall->DrawString(m_spriteBatch, wDamage.c_str(), Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC + CURRENTPADDING * 5), Colors::White);
		}
		if (m_weaponPenetration > 0)
		{
			m_spriteFontSmall->DrawString(m_spriteBatch, wPenetration.c_str(), Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC + CURRENTPADDING * 6), Colors::Green);
		}
		else
		{
			m_spriteFontSmall->DrawString(m_spriteBatch, wPenetration.c_str(), Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC + CURRENTPADDING * 6), Colors::White);
		}
		if (m_weaponCooldown > 0)
		{
			m_spriteFontSmall->DrawString(m_spriteBatch, wCooldown.c_str(), Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC + CURRENTPADDING * 7), Colors::Green);
		}
		else
		{
			m_spriteFontSmall->DrawString(m_spriteBatch, wCooldown.c_str(), Vector2(WEAPONXLOC + STRINGPADDING - 25, CURRENTUPGRADEYLOC + CURRENTPADDING * 7), Colors::White);
		}
	}
}

void UpgradeState::displayPlayerOptions()
{
	//Display title for player upgrades
	m_spriteFontSmall->DrawString(m_spriteBatch, L"Player upgrades (Increment, Cost in points)", Vector2(PLAYERXLOC, UPGRADEYLOC - 15), Colors::White);

	std::wstring speed = L"Speed (" + std::to_wstring(m_playerSpeedIncrement).substr(0, 4) + L", " + std::to_wstring(m_playerSpeedCost) + L")";
	std::wstring damageResistance = L"Resist damage (" + std::to_wstring(m_playerDamageResistanceIncrement).substr(0, 4) + L", " + std::to_wstring(m_playerDamageResistanceCost) + L")";
	std::wstring healthBonus = L"Health bonus (" + std::to_wstring(m_healthBonusIncrement).substr(0, 4) + L", " + std::to_wstring(m_healthBonusCost) + L")";
	
	//Player upgrade options
	m_spriteFontSmall->DrawString(m_spriteBatch, speed.c_str(), Vector2(PLAYERXLOC, UPGRADEYLOC + UPGRADEPADDING), Colors::White);
	m_spriteFontSmall->DrawString(m_spriteBatch, damageResistance.c_str(), Vector2(PLAYERXLOC, UPGRADEYLOC + UPGRADEPADDING * 2), Colors::White);
	m_spriteFontSmall->DrawString(m_spriteBatch, healthBonus.c_str(), Vector2(PLAYERXLOC, UPGRADEYLOC + UPGRADEPADDING * 3), Colors::White);
}

void UpgradeState::displayWeaponOptions()
{
	//Display title for weapon upgrades
	m_spriteFontSmall->DrawString(m_spriteBatch, L"Weapon upgrades (Increment, Cost in points)", Vector2(WEAPONXLOC, UPGRADEYLOC - 15), Colors::White);

	std::wstring speed = L"Speed (" + std::to_wstring(m_weaponSpeedIncrement).substr(0, 4) + L", " + std::to_wstring(m_weaponSpeedCost) + L")";
	std::wstring damage = L"Damage (" + std::to_wstring(m_weaponDamageIncrement).substr(0, 4) + L", " + std::to_wstring(m_weaponDamageCost) + L")";
	std::wstring penetration = L"Penetration (" + std::to_wstring(m_weaponPenetrationIncrement).substr(0, 4) + L", " + std::to_wstring(m_weaponPenetrationCost) + L")";
	std::wstring cooldown = L"Cooldown (" + std::to_wstring(m_weaponCooldownIncrement).substr(0, 4) + L", " + std::to_wstring(m_weaponCooldownCost) + L")";

	//Player upgrade options
	m_spriteFontSmall->DrawString(m_spriteBatch, speed.c_str(), Vector2(WEAPONXLOC, UPGRADEYLOC + UPGRADEPADDING), Colors::White);
	m_spriteFontSmall->DrawString(m_spriteBatch, damage.c_str(), Vector2(WEAPONXLOC, UPGRADEYLOC + UPGRADEPADDING * 2), Colors::White);
	m_spriteFontSmall->DrawString(m_spriteBatch, penetration.c_str(), Vector2(WEAPONXLOC, UPGRADEYLOC + UPGRADEPADDING * 3), Colors::White);
	m_spriteFontSmall->DrawString(m_spriteBatch, cooldown.c_str(), Vector2(WEAPONXLOC, UPGRADEYLOC + UPGRADEPADDING * 4), Colors::White);
}

void UpgradeState::displayPlayerButtons()
{
	if (canUpgrade(m_player->getSpeed(), m_playerSpeed, m_playerSpeedCap))
	{
		m_playerSpeedAddButton->Render();
	}
	if (canUpgrade(m_player->getSpeed(), m_playerSpeed, m_playerSpeedCap) || m_playerSpeed > 0)
	{
		m_playerSpeedSubtractButton->Render();
	}

	if (canUpgrade(m_player->getDamageResistance(), m_playerDamageResistance, m_playerDamageResistanceCap))
	{
		m_playerDamageResistanceAddButton->Render();
	}
	if (canUpgrade(m_player->getDamageResistance(), m_playerDamageResistance, m_playerDamageResistanceCap) || m_playerDamageResistance > 0)
	{
		m_playerDamageResistanceSubtractButton->Render();
	}

	if (canUpgrade(m_health->getHealthBonus(), m_healthBonus, m_healthBonusCap))
	{
		m_healthBonusAddButton->Render();
	}
	if (canUpgrade(m_health->getHealthBonus(), m_healthBonus, m_healthBonusCap) || m_healthBonus > 0)
	{
		m_healthBonusSubtractButton->Render();
	}
}

void UpgradeState::displayWeaponButtons()
{
	if (canUpgrade(m_player->getWeaponSpeed(), m_weaponSpeed, m_weaponSpeedCap))
	{
		m_weaponSpeedAddButton->Render();
	}
	if (canUpgrade(m_player->getWeaponSpeed(), m_weaponSpeed, m_weaponSpeedCap) || m_weaponSpeed > 0)
	{
		m_weaponSpeedSubtractButton->Render();
	}

	if (canUpgrade(m_player->getWeaponDamage(), m_weaponDamage, m_weaponDamageCap))
	{
		m_weaponDamageAddButton->Render();
	}
	if (canUpgrade(m_player->getWeaponDamage(), m_weaponDamage, m_weaponDamageCap )|| m_weaponDamage > 0)
	{
		m_weaponDamageSubtractButton->Render();
	}

	if (canUpgrade(m_player->getWeaponPenetration(), m_weaponPenetration, m_weaponPenetrationCap))
	{
		m_weaponPenetrationAddButton->Render();
	}
	if (canUpgrade(m_player->getWeaponPenetration(), m_weaponPenetration, m_weaponPenetrationCap) || m_weaponPenetration > 0)
	{
		m_weaponPenetrationSubtractButton->Render();
	}

	if (canUpgrade(m_player->getWeaponCooldown() * -1, m_weaponCooldown, m_weaponCooldownCap * -1))
	{
		m_weaponCooldownAddButton->Render();
	}
	if (canUpgrade(m_player->getWeaponCooldown() * -1, m_weaponCooldown, m_weaponCooldownCap * -1) || m_weaponCooldown > 0)
	{
		m_weaponCooldownSubtractButton->Render();
	}
}

void UpgradeState::displayFinishButton()
{
	m_finish->Render();
}

void UpgradeState::updatePlayerButtons()
{

	if (canUpgrade(m_player->getSpeed(), m_playerSpeed, m_playerSpeedCap))
	{
		m_playerSpeedAddButton->Update();
	}
	if (canUpgrade(m_player->getSpeed(), m_playerSpeed, m_playerSpeedCap) || m_playerSpeed > 0)
	{
		m_playerSpeedSubtractButton->Update();
	}

	if (canUpgrade(m_player->getDamageResistance(), m_playerDamageResistance, m_playerDamageResistanceCap))
	{
		m_playerDamageResistanceAddButton->Update();
	}
	if (canUpgrade(m_player->getDamageResistance(), m_playerDamageResistance, m_playerDamageResistanceCap) || m_playerDamageResistance > 0)
	{
		m_playerDamageResistanceSubtractButton->Update();
	}

	if (canUpgrade(m_health->getHealthBonus(), m_healthBonus, m_healthBonusCap))
	{
		m_healthBonusAddButton->Update();
	}
	if (canUpgrade(m_health->getHealthBonus(), m_healthBonus, m_healthBonusCap) || m_healthBonus > 0)
	{
		m_healthBonusSubtractButton->Update();
	}
}

void UpgradeState::updateWeaponButtons()
{
	if (canUpgrade(m_player->getWeaponSpeed(), m_weaponSpeed, m_weaponSpeedCap))
	{
		m_weaponSpeedAddButton->Update();
	}
	if (canUpgrade(m_player->getWeaponSpeed(), m_weaponSpeed, m_weaponSpeedCap) || m_weaponSpeed > 0)
	{
		m_weaponSpeedSubtractButton->Update();
	}

	if (canUpgrade(m_player->getWeaponDamage(), m_weaponDamage, m_weaponDamageCap))
	{
		m_weaponDamageAddButton->Update();
	}
	if (canUpgrade(m_player->getWeaponDamage(), m_weaponDamage, m_weaponDamageCap) || m_weaponDamage > 0)
	{
		m_weaponDamageSubtractButton->Update();
	}

	if (canUpgrade(m_player->getWeaponPenetration(), m_weaponPenetration, m_weaponPenetrationCap))
	{
		m_weaponPenetrationAddButton->Update();

	}
	if (canUpgrade(m_player->getWeaponPenetration(), m_weaponPenetration, m_weaponPenetrationCap) || m_weaponPenetration > 0)
	{
		m_weaponPenetrationSubtractButton->Update();
	}

	if (canUpgrade(m_player->getWeaponCooldown() * -1, m_weaponCooldown, m_weaponCooldownCap * -1))
	{
		m_weaponCooldownAddButton->Update();
	}
	if (canUpgrade(m_player->getWeaponCooldown() * -1, m_weaponCooldown, m_weaponCooldownCap * -1) || m_weaponCooldown > 0)
	{
		m_weaponCooldownSubtractButton->Update();
	}
}

void UpgradeState::updateFinishButton()
{
	m_finish->Update();
}

void UpgradeState::resume()
{
	//Update the upgraded values
	m_player->setSpeed(m_player->getSpeed() + m_playerSpeed);
	m_player->setDamageResistance(m_player->getDamageResistance() + m_playerDamageResistance);
	m_health->setHealthBonus(m_health->getHealthBonus() + m_healthBonus);
	m_player->setWeaponSpeed(m_player->getWeaponSpeed() + m_weaponSpeed);
	m_player->setWeaponDamage(m_player->getWeaponDamage() + m_weaponDamage);
	m_player->setWeaponPenetration(m_player->getWeaponPenetration() + m_weaponPenetration);
	m_player->setWeaponCooldown(m_player->getWeaponCooldown() - m_weaponCooldown);

	GameState* g = static_cast<GameState*>(m_stateManager->getState("game"));
	g->setScore(m_points);

	m_stateManager->pop();
}

void UpgradeState::onUpdate(float timestep)
{
	updatePlayerButtons();
	updateWeaponButtons();
	updateFinishButton();
}