#include "StateManager.h"

StateManager::StateManager()
{
	m_newState = false;
}

StateManager::~StateManager()
{

}

void StateManager::registerState(std::string id, State* state)
{
	assert(m_registeredStates[id] == 0);

	m_registeredStates[id] = state;
}

State* StateManager::getState(std::string id)
{
	assert(m_registeredStates[id] != 0);

	return m_registeredStates[id];
}

void StateManager::push(std::string id)
{
	assert(m_registeredStates[id] != 0);

	State* newState = m_registeredStates[id];

	if (peek() != NULL)
	{
		peek()->onObscuring();
	}
	
	newState->onEnter();
	m_currentStates.push(newState);

	m_newState = true;
}

State* StateManager::pop()
{
	State* topState = peek();

	if (topState == NULL)
	{
		return NULL;
	}
	else
	{
		topState->onExit();
		m_currentStates.pop();
		m_newState = true;

		if (peek() != NULL)
		{
			peek()->onRevealing();
		}

		return topState;
	}
}

State* StateManager::peek()
{
	if (empty())
	{
		return NULL;
	}

	return m_currentStates.top();
}

void StateManager::clearCurrentStates()
{
	while (!empty())
	{
		m_currentStates.pop();
	}
}

void StateManager::changeState(std::string id)
{
	assert(m_registeredStates[id] != 0);

	//1. Pop state
	if (peek() != NULL)
	{
		//1a. Run onExit on the popped state
		pop()->onExit();
	}

	//2. Push new state
	push(id);

	//3. Run onEnter on the new state
	peek()->onEnter();

	m_newState = true;
}

void StateManager::update(float timestep, InputController* input)
{
	if (!empty())
	{
		if (m_newState && !input->checkKeyPress())
		{
			m_newState = false;
		}

		if (!m_newState && input != NULL)
		{
			handleInput(timestep, input);
		}

		Updateable<GameObject>* u = dynamic_cast<Updateable<GameObject>*>(peek());

		if (u != NULL)
		{
			u->onUpdate(timestep);
		}
	}
}

void StateManager::render(Direct3D* renderer, Camera* camera)
{
	if (!empty())
	{
		Renderable<GameObject>* r = dynamic_cast<Renderable<GameObject>*>(peek());

		if (r != NULL)
		{
			r->onRender(renderer, camera);
		}
	}
}

void StateManager::handleInput(float timestep, InputController* input)
{
	if (!empty())
	{
		Inputable<GameObject>* i = dynamic_cast<Inputable<GameObject>*>(peek());
		
		if (i != NULL)
		{
			i->handleInput(timestep, input);
		}
	}
}