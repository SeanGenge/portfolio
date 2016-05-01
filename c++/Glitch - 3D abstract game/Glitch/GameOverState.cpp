#include "GameOverState.h"

GameOverState::GameOverState(StateManager* sm, SpriteBatch* sb, SpriteFont* sf, InputController* input, TextureManager* tm)
	: State(sm)
{
	m_spriteBatch = sb;
	m_spriteFont = sf;
	
	m_level = 0;
	m_score = 0;

	m_gameOver = tm->getTexture("gameOver");
	m_glow = tm->getTexture("glowRed");

	int buttonWidth = 210;
	int buttonHeight = 170 / 2;

	//The starting location of the first button
	int buttonStartX = 492;
	int buttonStartY = 500;

	//The padding between the buttons
	int buttonPadding = 100;

	m_replay = new Button(buttonWidth, buttonHeight, tm->getTexture("button"), L"Replay", Vector2(buttonStartX, buttonStartY), sb, sf, input, [this]
	{
		replay();
	});

	m_menu = new Button(buttonWidth, buttonHeight, tm->getTexture("button"), L"Main menu", Vector2(buttonStartX, buttonStartY + buttonPadding), sb, sf, input, [this]
	{
		menu();
	});
}

void GameOverState::onEnter()
{
	
}

void GameOverState::onExit()
{

}

void GameOverState::onObscuring()
{

}

void GameOverState::onRevealing()
{

}

void GameOverState::setRenderableObjects(std::vector<GameObject*> g)
{
	clearRender();

	//Renders any objects that you pass to it
	for (std::vector<GameObject*>::iterator i = g.begin(); i != g.end(); i++)
	{
		renderObject(*i);
	}
}

void GameOverState::onRender(Direct3D* renderer, Camera* camera)
{
	Renderable<GameObject>::onRender(renderer, camera);

	//Draw the underlying gui for the game over state
	drawGUI();
}

void GameOverState::replay()
{
	m_stateManager->pop();
	m_stateManager->push("game");
}

void GameOverState::menu()
{
	m_stateManager->pop();
	m_stateManager->push("mainMenu");
}

void GameOverState::drawGUI()
{
	displayGlow();
	displayGameOver();
	displayDetails();
	displayButtons();
}

void GameOverState::displayGlow()
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

void GameOverState::displayButtons()
{
	m_replay->Render();
	m_menu->Render();
}

void GameOverState::displayDetails()
{
	std::wstring l = L"Level: " + std::to_wstring(m_level);
	std::wstring s = L"Score: " + std::to_wstring(m_score);

	m_spriteFont->DrawString(m_spriteBatch, l.c_str(), Vector2(460, 360), Colors::Black);
	m_spriteFont->DrawString(m_spriteBatch, s.c_str(), Vector2(460, 390), Colors::Black);
}

void GameOverState::displayGameOver()
{
	RECT pos;
	int sizeX = 280;
	int sizeY = 175;
	//Hard coded middle of the screen.
	pos.left = 512 - sizeX;
	pos.right = 512 + sizeX;
	pos.top = 190 - sizeY;
	pos.bottom = 190 + sizeY;

	m_spriteBatch->Draw(m_gameOver->GetShaderResourceView(), pos);
}

void GameOverState::updateButtons()
{
	m_replay->Update();
	m_menu->Update();
}

void GameOverState::onUpdate(float timestep)
{
	updateButtons();
}