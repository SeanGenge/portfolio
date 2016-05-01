#pragma once

#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"
#include "TextureManager.h"
#include "Button.h"

#include "State.h"
#include "Renderable.h"
#include "Updateable.h"

using namespace DirectX;

class GameOverState : public State, public Renderable<GameObject>, public Updateable<GameObject>
{
private:
	//Used to draw textures and font
	SpriteBatch* m_spriteBatch;
	SpriteFont* m_spriteFont;

	//Background
	Texture* m_glow;

	//Buttons
	Button* m_replay;
	Button* m_menu;

	//The score of the player
	int m_score;
	//The level of the player
	int m_level;

	//Game over texture
	Texture* m_gameOver;

	inline void drawGUI();
	inline void displayGameOver();
	inline void displayButtons();
	inline void displayDetails();
	inline void displayGlow();

	inline void updateButtons();

	void replay();
	void menu();

public:
	GameOverState(StateManager* sm, SpriteBatch* sb, SpriteFont* sf, InputController* input, TextureManager* tm);

	void onEnter();
	void onExit();
	void onObscuring();
	void onRevealing();

	//Allows objects to be rendered on the screen but not updated
	void setRenderableObjects(std::vector<GameObject*> g);
	//Sets the player's score
	void setScore(int score) { m_score = score; }
	//Sets the player's level
	void setLevel(int level) { m_level = level; }

	void onUpdate(float timestep);
	void onRender(Direct3D* renderer, Camera* camera);
};