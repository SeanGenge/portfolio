#include "PauseState.h"

PauseState::PauseState(StateManager* sm, SpriteBatch* sb, SpriteFont* sf, InputController* input, TextureManager* tm)
	: State(sm)
{
	m_spriteBatch = sb;
	m_spriteFont = sf;

	m_title = tm->getTexture("pauseTitle");
	m_glow = tm->getTexture("glowGreen");

	int buttonWidth = 210;
	int buttonHeight = 170 / 2;

	//The starting location of the first button
	int buttonStartX = 492;
	int buttonStartY = 500;

	//The padding between the buttons
	int buttonPadding = 100;

	m_resume = new Button(buttonWidth, buttonHeight, tm->getTexture("button"), L"Resume", Vector2(buttonStartX, buttonStartY), sb, sf, input, [this]
	{
		resume();
	});

	m_menu = new Button(buttonWidth, buttonHeight, tm->getTexture("button"), L"Main menu", Vector2(buttonStartX, buttonStartY + buttonPadding), sb, sf, input, [this]
	{
		menu();
	});
}

void PauseState::onEnter()
{
	
}

void PauseState::onExit()
{
	
}

void PauseState::onObscuring()
{

}

void PauseState::onRevealing()
{

}

void PauseState::setRenderableObjects(std::vector<GameObject*> g)
{
	clearRender();

	//Renders any objects that you pass to it
	for (std::vector<GameObject*>::iterator i = g.begin(); i != g.end(); i++)
	{
		renderObject(*i);
	}
}

void PauseState::onRender(Direct3D* renderer, Camera* camera)
{
	Renderable<GameObject>::onRender(renderer, camera);

	//Draw the underlying gui for the game over state
	drawGUI();
}

void PauseState::resume()
{
	m_stateManager->pop();
}

void PauseState::menu()
{
	m_stateManager->pop();
	m_stateManager->push("mainMenu");
}

void PauseState::drawGUI()
{
	displayGlow();
	displayTitle();
	displayButtons();
}

void PauseState::displayGlow()
{
	//Cover the entire screen. Make it easier to read the game over text and give it a "it is game over" feel

	RECT pos;
	int sizeX = 512;
	int sizeY = 384;
	//Hard coded middle of the screen.
	pos.left = 512 - sizeX;
	pos.right = 512 + sizeX;
	pos.top = 384 - sizeY;
	pos.bottom = 384 + sizeY;

	m_spriteBatch->Draw(m_glow->GetShaderResourceView(), pos);
}

void PauseState::displayButtons()
{
	m_resume->Render();
	m_menu->Render();
}

void PauseState::displayTitle()
{
	RECT pos;
	int sizeX = 280;
	int sizeY = 140;
	//Hard coded middle of the screen.
	pos.left = 512 - sizeX;
	pos.right = 512 + sizeX;
	pos.top = 190 - sizeY;
	pos.bottom = 190 + sizeY;

	m_spriteBatch->Draw(m_title->GetShaderResourceView(), pos);
}

void PauseState::updateButtons()
{
	m_resume->Update();
	m_menu->Update();
}

void PauseState::onUpdate(float timestep)
{
	updateButtons();
}

void PauseState::handleInput(float timestep, InputController* input)
{
	if (input->GetKeyDownOnce(VK_ESCAPE) || input->GetKeyDownOnce('P'))
	{
		//Allows pressing esc or p to resume as well
		resume();
	}
}