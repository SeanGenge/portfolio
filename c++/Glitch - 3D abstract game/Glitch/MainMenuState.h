#pragma once

#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"
#include "TextureManager.h"
#include "Button.h"
#include "SoundManager.h"
#include "SoundPool.h"

#include "State.h"
#include "Renderable.h"
#include "Updateable.h"

class MainMenuState : public State, public Renderable <GameObject>, public Updateable <GameObject>
{
private:
	//Used to draw textures and font
	SpriteBatch* m_spriteBatch;
	SpriteFont* m_spriteFont;

	//Sound
	Sound* m_mainMenu;

	//Textures
	Texture* m_title;

	//The buttons
	Button* m_play;
	Button* m_exit;

	inline void drawGUI();
	inline void displayTitle();
	inline void displayButtons();

	inline void updateButtons();

	void clickPlay();
public:
	MainMenuState(StateManager* sm, SpriteBatch* sb, SpriteFont* sf, InputController* input, TextureManager* tm, SoundManager* sManager);

	void onEnter();
	void onExit();
	void onObscuring();
	void onRevealing();

	void onUpdate(float timestep);
	void onRender(Direct3D* renderer, Camera* camera);
};