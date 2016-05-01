#pragma once

#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"
#include "TextureManager.h"
#include "Button.h"

#include "State.h"
#include "Renderable.h"
#include "Updateable.h"
#include "Inputable.h"

using namespace DirectX;

class PauseState : public State, public Renderable<GameObject>, public Updateable<GameObject>, public Inputable<GameObject>
{
private:
	//Used to draw textures and font
	SpriteBatch* m_spriteBatch;
	SpriteFont* m_spriteFont;

	//Background
	Texture* m_title;
	Texture* m_glow;

	//Buttons
	Button* m_resume;
	Button* m_menu;

	inline void drawGUI();
	inline void displayTitle();
	inline void displayButtons();
	inline void displayGlow();

	inline void updateButtons();

	void resume();
	void menu();

public:
	PauseState(StateManager* sm, SpriteBatch* sb, SpriteFont* sf, InputController* input, TextureManager* tm);

	void onEnter();
	void onExit();
	void onObscuring();
	void onRevealing();

	//Allows the pause menu to display the level behind the player
	void setRenderableObjects(std::vector<GameObject*> g);

	void onUpdate(float timestep);
	void onRender(Direct3D* renderer, Camera* camera);
	void handleInput(float timestep, InputController* input);
};