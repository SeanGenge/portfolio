#pragma once

#include <vector>
#include <iomanip>
#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"
#include "Button.h"

#include "Player.h"
#include "Health.h"

#include "GameState.h"
#include "State.h"
#include "Updateable.h"
#include "Renderable.h"

#include "TextureManager.h"
#include "SoundManager.h"

//The different upgrade locations
#define PLAYERXLOC 75
#define WEAPONXLOC 500
//The y location for the different stat upgrades
#define UPGRADEYLOC 300
//The y location for the current player stat upgrades
#define CURRENTUPGRADEYLOC 50
//The padding for the current stats y location
#define CURRENTPADDING 25
//The maximum string length of each sub title
#define STRINGPADDING 250
//The padding between each upgrade
#define UPGRADEPADDING 50
//The padding between two adjacent buttons
#define BUTTONPADDING 60

/*
	This is the upgrade system. The reason why I decided to use the player's score as the cost is to add another dimension to the game.
	This means the player has to make wise choices to increase his score, if he decides to simply spend it on the player's speed then
	he may not deal enough damage and therefore will not regain his points back as the level increases in difficulty.
	To prevent the player moving too fast or having too high damage resistance, some stat cost increase much faster than others or some having
	a cap limit
*/

using namespace DirectX;

class UpgradeState : public State, public Updateable<GameObject>, public Renderable<GameObject>
{
private:
	//Used to draw textures and font
	SpriteBatch* m_spriteBatch;
	SpriteFont* m_spriteFontLarge;
	SpriteFont* m_spriteFontSmall;

	Texture* m_title;

	Player* m_player;
	Health* m_health;
	int m_points;

	//The sound of the upgrade menu opening
	Sound* m_upgradeSound;

	//The increment cost factor (percentage) for each stat when upgrading
	float m_costIncrement;

	//The maximum cap values
	float m_playerSpeedCap;
	float m_playerDamageResistanceCap;
	float m_healthBonusCap;
	float m_weaponSpeedCap;
	float m_weaponDamageCap;
	float m_weaponPenetrationCap;
	float m_weaponCooldownCap;

	//Holds the previous cost value
	std::vector<int> m_playerSpeedPrevCost;
	std::vector<int> m_playerDamageResistancePrevCost;
	std::vector<int> m_healthBonusPrevCost;
	std::vector<int> m_weaponSpeedPrevCost;
	std::vector<int> m_weaponDamagePrevCost;
	std::vector<int> m_weaponPenetrationPrevCost;
	std::vector<int> m_weaponCooldownPrevCost;

	//The cost of each stat upgrade
	int m_playerSpeedCost;
	int m_playerDamageResistanceCost;
	int m_healthBonusCost;
	int m_weaponSpeedCost;
	int m_weaponDamageCost;
	int m_weaponPenetrationCost;
	int m_weaponCooldownCost;

	//The amount that each upgrade is incremented by
	float m_playerSpeedIncrement;
	float m_playerDamageResistanceIncrement;
	float m_healthBonusIncrement;
	float m_weaponSpeedIncrement;
	float m_weaponDamageIncrement;
	float m_weaponPenetrationIncrement;
	float m_weaponCooldownIncrement;

	//Temp upgrade variables to check how much each stat will be upgraded by at the end
	float m_playerSpeed;
	float m_playerDamageResistance;
	float m_healthBonus;
	float m_weaponSpeed;
	float m_weaponDamage;
	float m_weaponPenetration;
	float m_weaponCooldown;

	//Player upgrade buttons
	Button* m_playerSpeedAddButton;
	Button* m_playerSpeedSubtractButton;

	Button* m_playerDamageResistanceAddButton;
	Button* m_playerDamageResistanceSubtractButton;

	Button* m_healthBonusAddButton;
	Button* m_healthBonusSubtractButton;

	//Weapon upgrade buttons
	Button* m_weaponSpeedAddButton;
	Button* m_weaponSpeedSubtractButton;

	Button* m_weaponDamageAddButton;
	Button* m_weaponDamageSubtractButton;

	Button* m_weaponPenetrationAddButton;
	Button* m_weaponPenetrationSubtractButton;

	Button* m_weaponCooldownAddButton;
	Button* m_weaponCooldownSubtractButton;

	//Finish button
	Button* m_finish;

	//Checks whether the specific upgrade can be upgraded. Returns true is yes and false otherwise.
	inline bool canUpgrade(float prevValue, float increment, float cap);

	inline void drawGUI();
	inline void displayUpgradeTitle();
	inline void displayPlayerStats();
	inline void displayPlayerOptions();
	inline void displayWeaponOptions();
	inline void displayPlayerButtons();
	inline void displayWeaponButtons();
	inline void displayFinishButton();

	inline void updatePlayerButtons();
	inline void updateWeaponButtons();
	inline void updateFinishButton();

	//Modifies the cost, total value and the previous values. add is whether you want to increment if not it will decrement
	//variable is the variable you want to modify
	void modifyValues(bool add, float& variable, float increment, int& cost, std::vector<int>& prevCost);

	void resume();

public:
	UpgradeState(StateManager* sm, SpriteBatch* sb, SpriteFont* sfL, SpriteFont* sfS, SoundManager* sManager, InputController* input, TextureManager* tm);

	void onEnter();
	void onExit();
	void onObscuring();
	void onRevealing();

	//Allows objects to be rendered on the screen but not updated
	void setRenderableObjects(std::vector<GameObject*> g);
	//Pass the player to the state
	void setPlayer(Player* player) { m_player = player; }
	void setHealth(Health* health) { m_health = health; }
	void setPoints(int points) { m_points = points; }

	//Returns true if all the stats are fully upgraded
	bool fullyUpgraded();

	void onUpdate(float timestep);
	void onRender(Direct3D* renderer, Camera* camera);
};