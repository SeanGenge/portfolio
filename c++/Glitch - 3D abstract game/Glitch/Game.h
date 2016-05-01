/*	FIT2049 - Example Code
*	Game.h
*	Created by Elliott Wilson - 2015 - Monash Univeristy
*	This class is where we create all of the object for a game
*	It contains the overall Update and Render method for the whole game
*	Most of the code you write will be here
*/

#ifndef GAME_H
#define GAME_H

#include "Direct3D.h"
#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"
#include "DirectXTK/CommonStates.h"
#include "TexturedShader.h"
#include "FlashlightShader.h"
#include "Spotlight.h"
#include "InputController.h"
#include "Camera.h"
#include "Button.h"

#include "StateManager.h"
#include "MainMenuState.h"
#include "LevelChooseState.h"
#include "PauseState.h"
#include "UpgradeState.h"
#include "GameState.h"
#include "GameOverState.h"

#include "EnemyFactory.h"

#include "Mesh.h"
#include "MeshManager.h"
#include "Texture.h"
#include "TextureManager.h"
#include "SoundManager.h"

using namespace DirectX;

class Game
{
private:
	Direct3D* m_renderer;		//Our renderer is passed in when the Game is created
	InputController* m_input;	//
	Camera* m_currentCam;		//Our game has a Camera to see everything with!
	Shader* m_shader;			//We also need a shader to draw things with, later we will probably have multiple shaders
	Shader* m_texturedShader;
	Shader* m_texturedSkyboxShader;
	Shader* m_flashlightShader;

	TextureManager* m_tManager;
	MeshManager* m_mManager;
	SoundManager* m_sManager;

	StateManager* m_stateManager;

	SpriteBatch* m_spriteBatch;	//The sprite batch can be used to draw things in 2D screen space, we can draw textures and text
	SpriteFont* m_arial;		//If we want to draw text then need a font to draw it with, a Sprite Font can do that!
	SpriteFont* m_arialSmall;

public:
	Game();		//Constructor
	~Game();	//Destructor

	bool Initialise(Direct3D* renderer, InputController* input);	//The initialise method loads all of the content for the game (meshes, textures, etc.)

	void Update(float timestep);	//The overall Update method for the game. All gameplay logic will be done somewhere within this method
	void Render();					//The overall Render method for the game. Here all of the meshes that need to be drawn will be drawn

	void Shutdown();		//Cleanup everything we initialised
};

#endif