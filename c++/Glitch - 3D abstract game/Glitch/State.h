#pragma once

/*
	Purpose: Represents any kind of state the game can be in, including AI logic
*/

#include "StateManager.h"

class StateManager;

class State
{
protected:
	StateManager* m_stateManager;

public:
	//Constructor
	State(StateManager* stateManager);
	
	//Called when you enter the state
	virtual void onEnter() = 0;
	//Called when you exit the state
	virtual void onExit() = 0;
	//Called when another state is placed on top of this state
	virtual void onObscuring() = 0;
	//Called when the top state is removed revealing this state
	virtual void onRevealing() = 0;

	//Changes the state to another state
	void changeState(StateManager* stateManager, std::string id);
};