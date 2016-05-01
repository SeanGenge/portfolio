/*	FIT2049 - Example Code
*	Camera.cpp
*	Created by Elliott Wilson - 2015 - Monash Univeristy
*	Implementation of Camera.h
*/

#include "Game.h"

Game::Game()
{
	m_renderer = NULL;
	m_input = NULL;
	m_currentCam = NULL;
	m_shader = NULL;
}

Game::~Game()
{

}

bool Game::Initialise(Direct3D* renderer, InputController* input)
{
	m_renderer = renderer;		//Set our renderer
	m_input = input;			//Set our input controller

	//Create a new "default" camera
	m_currentCam = new Camera();

	//Init lights
	Spotlight* flashlight = new Spotlight();
	flashlight->setPosition(Vector3(0, 2, 0));

	flashlight->setAmbientIntensity(0.05f);

	flashlight->setDiffuseDirection(Vector3(1, 0.5, 0.3));
	flashlight->setDiffuseIntensity(0.1f);

	flashlight->setAttentuation(Vector3(0, 0.005, 0.03));
	flashlight->setSpotPower(8);
	flashlight->setDirection(Vector3(1, 0.5, 0.3));

	m_shader = new Shader();	//Create our shader
	//Initialise the shader, we need to pass in the shader filenames
	if (!m_shader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/PixelShader.ps"))
		return false;

	m_texturedShader = new TexturedShader();
	if (!m_texturedShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/TexturedPixelShader.ps"))
		return false;

	m_texturedSkyboxShader = new TexturedShader();
	if (!m_texturedSkyboxShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/TexturedSkyboxPixelShader.ps"))
		return false;

	m_flashlightShader = new FlashlightShader(flashlight);
	if (!m_flashlightShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/FlashlightVS.hlsl", L"Assets/Shaders/FlashlightPS.hlsl"))
		return false;

	//Init sound manager
	m_sManager = new SoundManager();
	if (!m_sManager->Initialise())
		return false;

	//Init sounds
	if (!m_sManager->Load("Assets/Sounds/footsteps.wav"))
		return false;
	if (!m_sManager->Load("Assets/Sounds/upgrade.wav"))
		return false;
	if (!m_sManager->Load("Assets/Sounds/pistol.wav"))
		return false;
	if (!m_sManager->Load("Assets/Sounds/levelUp.wav"))
		return false;
	if (!m_sManager->Load("Assets/Sounds/heartbeat.wav"))
		return false;
	if (!m_sManager->Load("Assets/Sounds/damage.wav"))
		return false;
	if (!m_sManager->Load("Assets/Sounds/deflect.wav"))
		return false;
	if (!m_sManager->Load("Assets/Sounds/health.wav"))
		return false;
	if (!m_sManager->Load("Assets/Sounds/mainMenu.wav"))
		return false;

	//Init textures
	Texture* tTitle = new Texture();
	if (!tTitle->Initialise(m_renderer, L"Assets/Textures/title.png"))
		return false;

	Texture* tPause = new Texture();
	if (!tPause->Initialise(m_renderer, L"Assets/Textures/pause.png"))
		return false;

	Texture* tGlowRed = new Texture();
	if (!tGlowRed->Initialise(m_renderer, L"Assets/Textures/redGlow.png"))
		return false;

	Texture* tGlowGreen = new Texture();
	if (!tGlowGreen->Initialise(m_renderer, L"Assets/Textures/greenGlow.png"))
		return false;

	Texture* tButton = new Texture();
	if (!tButton->Initialise(m_renderer, L"Assets/Textures/button.png"))
		return false;

	Texture* tButtonSmall = new Texture();
	if (!tButtonSmall->Initialise(m_renderer, L"Assets/Textures/buttonSmall.png"))
		return false;

	Texture* tLevel = new Texture();
	if (!tLevel->Initialise(m_renderer, L"Assets/Textures/level.png"))
		return false;

	Texture* tSkybox = new Texture();
	if (!tSkybox->Initialise(m_renderer, L"Assets/Textures/skybox.png"))
		return false;

	Texture* tred = new Texture();
	if (!tred->Initialise(m_renderer, L"Assets/Textures/red.png"))
		return false;

	Texture* tOrange = new Texture();
	if (!tOrange->Initialise(m_renderer, L"Assets/Textures/orange.png"))
		return false;

	Texture* tPurple = new Texture();
	if (!tPurple->Initialise(m_renderer, L"Assets/Textures/purple.png"))
		return false;

	Texture* tBlue = new Texture();
	if (!tBlue->Initialise(m_renderer, L"Assets/Textures/blue.png"))
		return false;

	Texture* tGreen = new Texture();
	if (!tGreen->Initialise(m_renderer, L"Assets/Textures/green.png"))
		return false;


	Texture* tBullet = new Texture();
	if (!tBullet->Initialise(m_renderer, L"Assets/Textures/bullet.png"))
		return false;

	Texture* tBulletPurple = new Texture();
	if (!tBulletPurple->Initialise(m_renderer, L"Assets/Textures/bulletPurple.jpg"))
		return false;

	Texture* tBulletYellow = new Texture();
	if (!tBulletYellow->Initialise(m_renderer, L"Assets/Textures/bulletYellow.jpg"))
		return false;

	Texture* tCrosshair = new Texture();
	if (!tCrosshair->Initialise(m_renderer, L"Assets/Textures/crosshair.png"))
		return false;

	//Hp textures
	Texture* tHpGreen = new Texture();
	if (!tHpGreen->Initialise(m_renderer, L"Assets/Textures/hpGreen.png"))
		return false;

	Texture* tHpOrange = new Texture();
	if (!tHpOrange->Initialise(m_renderer, L"Assets/Textures/hpOrange.jpg"))
		return false;

	Texture* tHpRed = new Texture();
	if (!tHpRed->Initialise(m_renderer, L"Assets/Textures/hpRed.png"))
		return false;

	Texture* rHpBackBlack = new Texture();
	if (!rHpBackBlack->Initialise(m_renderer, L"Assets/Textures/hpBackBlack.png"))
		return false;

	Texture* tHpBackGray = new Texture();
	if (!tHpBackGray->Initialise(m_renderer, L"Assets/Textures/hpBackGray.jpg"))
		return false;

	Texture* tNextLevel = new Texture();
	if (!tNextLevel->Initialise(m_renderer, L"Assets/Textures/nextLevel.png"))
		return false;

	Texture* tGameOver = new Texture();
	if (!tGameOver->Initialise(m_renderer, L"Assets/Textures/gameOver.png"))
		return false;

	Texture* tUpgrade = new Texture();
	if (!tUpgrade->Initialise(m_renderer, L"Assets/Textures/upgrade.png"))
		return false;

	Texture* tGreenBox = new Texture();
	if (!tGreenBox->Initialise(m_renderer, L"Assets/Textures/greenBox.png"))
		return false;

	Texture* tRedBox = new Texture();
	if (!tRedBox->Initialise(m_renderer, L"Assets/Textures/redBox.png"))
		return false;

	m_tManager = new TextureManager();
	m_tManager->registerTexture("title", tTitle);
	m_tManager->registerTexture("upgrade", tUpgrade);
	m_tManager->registerTexture("pauseTitle", tPause);
	m_tManager->registerTexture("glowRed", tGlowRed);
	m_tManager->registerTexture("glowGreen", tGlowGreen);
	m_tManager->registerTexture("button", tButton);
	m_tManager->registerTexture("buttonSmall", tButtonSmall);
	m_tManager->registerTexture("level", tLevel);
	m_tManager->registerTexture("skybox", tSkybox);
	m_tManager->registerTexture("red", tred);
	m_tManager->registerTexture("orange", tOrange);
	m_tManager->registerTexture("purple", tPurple);
	m_tManager->registerTexture("blue", tBlue);
	m_tManager->registerTexture("green", tGreen);
	m_tManager->registerTexture("bullet", tBullet);
	m_tManager->registerTexture("enemyBulletPurple", tBulletPurple);
	m_tManager->registerTexture("enemyBulletYellow", tBulletYellow);
	m_tManager->registerTexture("crosshair", tCrosshair);
	m_tManager->registerTexture("hpGreen", tHpGreen);
	m_tManager->registerTexture("hpOrange", tHpOrange);
	m_tManager->registerTexture("hpRed", tHpRed);
	m_tManager->registerTexture("hpBackBlack", rHpBackBlack);
	m_tManager->registerTexture("hpBackGray", tHpBackGray);
	m_tManager->registerTexture("nextLevel", tNextLevel);
	m_tManager->registerTexture("gameOver", tGameOver);
	m_tManager->registerTexture("greenBox", tGreenBox);
	m_tManager->registerTexture("redBox", tRedBox);

	//Init meshes
	Mesh* mLevel = new Mesh();
	if (!mLevel->Initialise(m_renderer, "Assets/Meshes/level.obj", Color(0.568f, 0.788f, 0.9f, 1.0f), tLevel, m_flashlightShader))
		return false;

	Mesh* mSkybox = new Mesh();
	if (!mSkybox->Initialise(m_renderer, "Assets/Meshes/skybox.obj", Color(1.0f, 1.0f, 1.0f, 1.0f), tSkybox, m_texturedSkyboxShader))
		return false;

	Mesh* mPlayer = new Mesh();
	if (!mPlayer->Initialise(m_renderer, "Assets/Meshes/orange.obj", Color(1.0f, 1.0f, 1.0f, 1.0f), tOrange, m_texturedShader))
		return false;

	Mesh* mGreen = new Mesh();
	if (!mGreen->Initialise(m_renderer, "Assets/Meshes/green.obj", Color(1.0f, 1.0f, 1.0f, 1.0f), tGreen, m_flashlightShader))
		return false;

	Mesh* mOrange = new Mesh();
	if (!mOrange->Initialise(m_renderer, "Assets/Meshes/orange.obj", Color(1.0f, 1.0f, 1.0f, 1.0f), tOrange, m_flashlightShader))
		return false;

	Mesh* mBlue = new Mesh();
	if (!mBlue->Initialise(m_renderer, "Assets/Meshes/blue.obj", Color(1.0f, 1.0f, 1.0f, 1.0f), tBlue, m_flashlightShader))
		return false;

	Mesh* mPurple = new Mesh();
	if (!mPurple->Initialise(m_renderer, "Assets/Meshes/purple.obj", Color(1.0f, 1.0f, 1.0f, 1.0f), tPurple, m_flashlightShader))
		return false;

	Mesh* mRed = new Mesh();
	if (!mRed->Initialise(m_renderer, "Assets/Meshes/red.obj", Color(1.0f, 1.0f, 1.0f, 1.0f), tred, m_flashlightShader))
		return false;

	Mesh* mBullet = new Mesh();
	if (!mBullet->Initialise(m_renderer, "Assets/Meshes/bullet.obj", Color(1.0f, 1.0f, 1.0f, 1.0f), tBullet, m_flashlightShader))
		return false;

	Mesh* mEnemyBulletPurple = new Mesh();
	if (!mEnemyBulletPurple->Initialise(m_renderer, "Assets/Meshes/bullet.obj", Color(1.0f, 1.0f, 1.0f, 1.0f), tBulletPurple, m_flashlightShader))
		return false;

	Mesh* mEnemyBulletYellow = new Mesh();
	if (!mEnemyBulletYellow->Initialise(m_renderer, "Assets/Meshes/bullet.obj", Color(1.0f, 1.0f, 1.0f, 1.0f), tBulletYellow, m_flashlightShader))
		return false;

	m_mManager = new MeshManager();
	m_mManager->registerMesh("level", mLevel);
	m_mManager->registerMesh("skybox", mSkybox);
	m_mManager->registerMesh("player", mPlayer);
	m_mManager->registerMesh("green", mGreen);
	m_mManager->registerMesh("orange", mOrange);
	m_mManager->registerMesh("blue", mBlue);
	m_mManager->registerMesh("purple", mPurple);
	m_mManager->registerMesh("red", mRed);
	m_mManager->registerMesh("bullet", mBullet);
	m_mManager->registerMesh("enemyBulletPurple", mEnemyBulletPurple);
	m_mManager->registerMesh("enemyBulletYellow", mEnemyBulletYellow);

	EnemyFactory* m_enemyF = new EnemyFactory(m_mManager, NULL, m_mManager->getMesh("bullet"), m_mManager->getMesh("enemyBulletYellow"), Difficulty::normal, 1);

	//Create the sprite batch
	m_spriteBatch = new SpriteBatch(m_renderer->GetDeviceContext());
	//Load our Sprite Font
	m_arial = new SpriteFont(m_renderer->GetDevice(), L"Assets/Fonts/Arial-23pt.spritefont");
	m_arialSmall = new SpriteFont(m_renderer->GetDevice(), L"Assets/Fonts/Arial-12pt.spritefont");

	//Init state manager
	m_stateManager = new StateManager();
	m_stateManager->registerState("mainMenu", new MainMenuState(m_stateManager, m_spriteBatch, m_arial, m_input, m_tManager, m_sManager));
	m_stateManager->registerState("levelChoose", new LevelChooseState(m_stateManager, m_spriteBatch, m_arial, m_input, m_tManager, m_sManager));
	m_stateManager->registerState("game", new GameState(m_stateManager, m_enemyF, m_currentCam, m_mManager, m_tManager, m_spriteBatch, m_arial, m_sManager, Difficulty::normal, flashlight));
	m_stateManager->registerState("pause", new PauseState(m_stateManager, m_spriteBatch, m_arial, m_input, m_tManager));
	m_stateManager->registerState("gameOver", new GameOverState(m_stateManager, m_spriteBatch, m_arial, m_input, m_tManager));
	m_stateManager->registerState("upgrade", new UpgradeState(m_stateManager, m_spriteBatch, m_arial, m_arialSmall, m_sManager, m_input, m_tManager));

	m_stateManager->push("mainMenu");

	return true;
}

void Game::Update(float timestep)
{
	m_input->BeginUpdate();				//The input controller needs to be updated every frame

	m_currentCam->Update(timestep);		//Every update we will update the camera
	m_stateManager->update(timestep, m_input);
	
	m_input->EndUpdate();				//We also need to tell the Input Controller when a frame is over
}

void Game::Render()
{
	m_renderer->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);						//Begin the scene and clear to black
	m_renderer->SetCurrentShader(NULL);

	//When we want to draw 2D objects we need to do it within the Begin and End calls of the Sprite Batch
	CommonStates states(m_renderer->GetDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());

	m_stateManager->render(m_renderer, m_currentCam);

	m_spriteBatch->End();
	m_renderer->EndScene();												//End the scene and present the frame

}

void Game::Shutdown()
{
	//Clean up everything!
	if (m_currentCam)
	{
		delete m_currentCam;
		m_currentCam = NULL;
	}

	if (m_shader)
	{
		m_shader->Release();
		delete m_shader;
		m_shader = NULL;
	}

	if (m_texturedShader)
	{
		m_texturedShader->Release();
		delete m_texturedShader;
		m_texturedShader = NULL;
	}

	if (m_arial)
	{
		delete m_arial;
		m_arial = NULL;
	}

	if (m_spriteBatch)
	{
		delete m_spriteBatch;
		m_spriteBatch = NULL;
	}

	m_mManager->shutdown();
	m_tManager->shutdown();
	m_sManager->Release();
}