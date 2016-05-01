#include "LevelChooseState.h"

LevelChooseState::LevelChooseState(StateManager* sm, SpriteBatch* sb, SpriteFont* sf, InputController* input, TextureManager* tm, SoundManager* sManager)
	: State(sm)
{
	m_spriteBatch = sb;
	m_spriteFont = sf;

	m_greenBox = tm->getTexture("greenBox");
	m_redBox = tm->getTexture("redBox");

	m_clickNormal = true;

	m_difficulty = Difficulty::normal;

	m_textPos = Vector2(620, 170);
	m_yTextPadding = Vector2(0, 40);

	int sizeX = 320;
	int sizeY = 510;
	int posX = 600;
	int posY = 150;

	m_boxSize.left = posX;
	m_boxSize.right = posX + sizeX;
	m_boxSize.top = posY;
	m_boxSize.bottom = posY + sizeY;

	int buttonWidth = 210;
	int buttonHeight = 170 / 2;

	//The starting location of the first button
	int buttonStartX = 200;
	int buttonStartY = 300;

	//The starting location of any buttons on the green or red box (Only 1 button)
	int buttonStartXBox = 800;
	int buttonStartYBox = 600;

	//The padding between the buttons
	int buttonPadding = 100;

	m_normal = new Button(buttonWidth, buttonHeight, tm->getTexture("button"), L"Normal", Vector2(buttonStartX, buttonStartY), sb, sf, input, [this]
	{
		m_difficulty = Difficulty::normal;
		m_clickNormal = true;
	});

	m_advanced = new Button(buttonWidth, buttonHeight, tm->getTexture("button"), L"Advanced", Vector2(buttonStartX, buttonStartY + buttonPadding), sb, sf, input, [this]
	{
		m_difficulty = Difficulty::advanced;
		m_clickNormal = false;
	});

	m_back = new Button(buttonWidth, buttonHeight, tm->getTexture("button"), L"Back", Vector2(buttonStartX, buttonStartY + buttonPadding * 2), sb, sf, input, [this]
	{
		clickBack();
	});

	m_play = new Button(buttonWidth, buttonHeight, tm->getTexture("button"), L"Begin", Vector2(buttonStartXBox, buttonStartYBox), sb, sf, input, [this]
	{
		clickPlay();
	});
}

void LevelChooseState::onEnter()
{

}

void LevelChooseState::onExit()
{

}

void LevelChooseState::onObscuring()
{

}

void LevelChooseState::onRevealing()
{

}

void LevelChooseState::clickPlay()
{
	//Starts the game
	m_stateManager->pop();

	GameState* g = static_cast<GameState*>(m_stateManager->getState("game"));
	g->setDifficulty(m_difficulty);

	m_stateManager->push("game");
}

void LevelChooseState::clickBack()
{
	m_stateManager->pop();
	m_stateManager->push("mainMenu");
}

void LevelChooseState::onRender(Direct3D* renderer, Camera* camera)
{
	Renderable<GameObject>::onRender(renderer, camera);

	//Draw the underlying gui for the game over state
	drawGUI();
}

void LevelChooseState::drawGUI()
{
	if (m_clickNormal)
	{
		displayNormal();
	}
	else
	{
		displayAdvanced();
	}

	displayButtons();
}

void LevelChooseState::displayNormal()
{
	m_spriteBatch->Draw(m_greenBox->GetShaderResourceView(), m_boxSize);

	//Display text for normal
	m_spriteFont->DrawString(m_spriteBatch, L"Normal", m_textPos + Vector2(60, 0), Colors::Black);
	m_spriteFont->DrawString(m_spriteBatch, L"4 unique enemies", m_textPos + m_yTextPadding, Colors::Black);
	m_spriteFont->DrawString(m_spriteBatch, L"Upgrade system", m_textPos + m_yTextPadding * 2, Colors::Black);
	m_spriteFont->DrawString(m_spriteBatch, L"Easy difficulty", m_textPos + m_yTextPadding * 3, Colors::Black);
}

void LevelChooseState::displayAdvanced()
{
	m_spriteBatch->Draw(m_redBox->GetShaderResourceView(), m_boxSize);

	//Display text for advanced
	m_spriteFont->DrawString(m_spriteBatch, L"Advanced", m_textPos + Vector2(60, 0), Colors::Black);
	m_spriteFont->DrawString(m_spriteBatch, L"Normal+", m_textPos + m_yTextPadding, Colors::Black);
	m_spriteFont->DrawString(m_spriteBatch, L"Enemies:", m_textPos + m_yTextPadding * 2, Colors::Black);
	m_spriteFont->DrawString(m_spriteBatch, L"unique abilities", m_textPos + m_yTextPadding * 3, Colors::Black);
	m_spriteFont->DrawString(m_spriteBatch, L"+ damage", m_textPos + m_yTextPadding * 4, Colors::Black);
	m_spriteFont->DrawString(m_spriteBatch, L"+ health", m_textPos + m_yTextPadding * 5, Colors::Black);
	m_spriteFont->DrawString(m_spriteBatch, L"Hard difficulty", m_textPos + m_yTextPadding * 6, Colors::Black);
}

void LevelChooseState::displayButtons()
{
	m_play->Render();
	m_back->Render();
	m_normal->Render();
	m_advanced->Render();
}

void LevelChooseState::onUpdate(float timestep)
{
	updateButtons();
}

void LevelChooseState::updateButtons()
{
	m_play->Update();
	m_back->Update();
	m_normal->Update();
	m_advanced->Update();
}