#include "MainMenuState.h"

MainMenuState::MainMenuState(StateManager* sm, SpriteBatch* sb, SpriteFont* sf, InputController* input, TextureManager* tm, SoundManager* sManager)
	: State(sm)
{
	m_spriteBatch = sb;
	m_spriteFont = sf;

	m_title = tm->getTexture("title");

	m_mainMenu = sManager->GetSound("Assets/Sounds/mainMenu.wav");

	int buttonWidth = 210;
	int buttonHeight = 170 / 2;

	//The starting location of the first button
	int buttonStartX = 492;
	int buttonStartY = 345;

	//The padding between the buttons
	int buttonPadding = 100;

	m_play = new Button(buttonWidth, buttonHeight, tm->getTexture("button"), L"Begin", Vector2(buttonStartX, buttonStartY), sb, sf, input, [this]
	{
		clickPlay();
	});

	m_exit = new Button(buttonWidth, buttonHeight, tm->getTexture("button"), L"Exit", Vector2(buttonStartX, buttonStartY + buttonPadding), sb, sf, input, [this]
	{
		//Exit the game
		PostQuitMessage(0);
	});
}

void MainMenuState::onEnter()
{
	//Play music
	m_mainMenu->Play();
}

void MainMenuState::onExit()
{
	m_mainMenu->Stop();
}

void MainMenuState::onObscuring()
{
	m_mainMenu->Stop();
}

void MainMenuState::onRevealing()
{
	m_mainMenu->Play();
}

void MainMenuState::clickPlay()
{
	//Starts the game
	m_stateManager->pop();
	m_stateManager->push("levelChoose");
}

void MainMenuState::onRender(Direct3D* renderer, Camera* camera)
{
	Renderable<GameObject>::onRender(renderer, camera);

	//Draw the underlying gui for the game over state
	drawGUI();
}

void MainMenuState::drawGUI()
{
	displayTitle();
	displayButtons();
}

void MainMenuState::displayTitle()
{
	RECT pos;
	int sizeX = 600;
	int sizeY = 350;
	//Hard coded middle of the screen.
	pos.left = 512 - sizeX;
	pos.right = 512 + sizeX;
	pos.top = 220 - sizeY;
	pos.bottom = 220 + sizeY;

	m_spriteBatch->Draw(m_title->GetShaderResourceView(), pos);
}

void MainMenuState::displayButtons()
{
	m_play->Render();
	m_exit->Render();
}

void MainMenuState::onUpdate(float timestep)
{
	updateButtons();

	//Play sound if it has ended
	if (m_mainMenu->soundFinished())
	{
		m_mainMenu->Play();
	}
}

void MainMenuState::updateButtons()
{
	m_play->Update();
	m_exit->Update();
}