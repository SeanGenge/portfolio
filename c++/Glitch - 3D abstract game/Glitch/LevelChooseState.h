#pragma once

#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"
#include "TextureManager.h"
#include "Button.h"
#include "SoundManager.h"
#include "SoundPool.h"

#include "Enemy.h"

#include "State.h"
#include "GameState.h"
#include "Renderable.h"
#include "Updateable.h"

class LevelChooseState : public State, public Renderable <GameObject>, public Updateable <GameObject>
{
private:
	//Used to draw textures and font
	SpriteBatch* m_spriteBatch;
	SpriteFont* m_spriteFont;

	//Textures
	Texture* m_greenBox;
	Texture* m_redBox;

	//The buttons
	Button* m_play;
	Button* m_back;
	Button* m_normal;
	Button* m_advanced;

	//Difficulty
	Difficulty m_difficulty;

	//The rectangle for the green or red box
	RECT m_boxSize;
	//The position of text on the box
	Vector2 m_textPos;
	//The y padding of text
	Vector2 m_yTextPadding;

	

	//Checks whether the normal button was clicked
	bool m_clickNormal;

	inline void drawGUI();
	inline void displayNormal();
	inline void displayAdvanced();
	inline void displayButtons();

	inline void updateButtons();

	void clickPlay();
	void clickBack();
public:
	LevelChooseState(StateManager* sm, SpriteBatch* sb, SpriteFont* sf, InputController* input, TextureManager* tm, SoundManager* sManager);

	void onEnter();
	void onExit();
	void onObscuring();
	void onRevealing();

	void onUpdate(float timestep);
	void onRender(Direct3D* renderer, Camera* camera);
};