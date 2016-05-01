#pragma once

/*
	Purpose: Manages all the different game states
*/

#include <stack>
#include <map>
#include <string>
#include <cassert>
#include "Direct3D.h"
#include "Camera.h"
#include "State.h"
#include "GameObject.h"

#include "Updateable.h"
#include "Renderable.h"
#include "Inputable.h"

class State;

class StateManager
{
private:
	//The current state that that game is in
	std::stack<State*> m_currentStates;
	//Contains all the registered states
	std::map<std::string, State*> m_registeredStates;

	//Checks whether the state was recently changed. Used to pause handleInput until all keys have been released
	bool m_newState;

public:
	//Constructor
	StateManager();
	//Destructor
	~StateManager();

	//Removes all the current states from the stack
	void clearCurrentStates();
	//Pushes a state on to current states with selected id. Asserts an error if state with id does not exist
	void push(std::string id);
	//Removes the top state and returns it. Returns NULL if stack is empty
	State* pop();
	//Looks at the top state on the stack. Returns NULL if stack is empty
	State* peek();
	//Changes the top state (Pop top state and push new state)
	void changeState(std::string id);

	//Registers a state with the state manager. id must be unique if not asserts an error
	void registerState(std::string id, State* state);
	//Retrieves a state from the registered states. If no states exits then asserts an error
	State* getState(std::string id);

	int size() { return m_currentStates.size(); }
	bool empty() { return m_currentStates.empty(); }

	//Update and render the current state if the current state is updateable or renderable
	//handleInput is called in update
	void update(float timestep, InputController* input);
	void render(Direct3D* renderer, Camera* camera);
	void handleInput(float timestep, InputController* input);
};