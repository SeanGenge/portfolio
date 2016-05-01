#include "InputController.h"

InputController::InputController(HWND windowHandle)
{
	m_windowHandle = windowHandle;						//In order to work out the client coords for the mouse we need a window handle

	memset(m_PrevKeys, 0, sizeof(m_PrevKeys));			//Clear out all of those arrays!
	memset(m_CurrentKeys, 0, sizeof(m_CurrentKeys));
	memset(m_prevMouse, 0, sizeof(m_prevMouse));
	memset(m_currentMouse, 0, sizeof(m_currentMouse));

	m_curMousePos.x = 0;
	m_curMousePos.y = 0;
}

void InputController::SetKeyDown(UINT keyCode)
{
	m_CurrentKeys[keyCode] = true;
}

void InputController::SetKeyUp(UINT keyCode)
{
	m_CurrentKeys[keyCode] = false;
}

void InputController::SetMouseDown(int mouseButton)
{
	m_currentMouse[mouseButton] = true;
}

void InputController::SetMouseUp(int mouseButton)
{
	m_currentMouse[mouseButton] = false;
}

bool InputController::GetKeyDown(UINT keyCode)
{
	return m_CurrentKeys[keyCode];
}

bool InputController::GetKeyDownOnce(UINT keycode)
{
	return m_CurrentKeys[keycode] && !m_PrevKeys[keycode];
}

bool InputController::GetKeyUp(UINT keyCode)
{
	return m_PrevKeys[keyCode] && !m_CurrentKeys[keyCode];
}

bool InputController::checkKeyPress()
{
	for (int i = 0; i < NUMBER_OF_KEYS; i++)
	{
		if (m_CurrentKeys[i] == 1)
		{
			return true;
		}
	}

	return false;
}

bool InputController::GetMouseDown(int mouseButton)
{
	return m_currentMouse[mouseButton];
}

bool InputController::GetMouseDownOnce(int mouseButton)
{
	return m_currentMouse[mouseButton] && !m_prevMouse[mouseButton];
}

bool InputController::GetMouseUp(int mouseButton)
{
	return m_prevMouse[mouseButton] && !m_currentMouse[mouseButton];
}

int InputController::GetMouseX()
{
	return m_curMousePos.x;
}

int InputController::GetMouseY()
{
	return m_curMousePos.y;
}

int InputController::GetDeltaMouseX()
{
	return m_mouseDelta.x;
}

int InputController::GetDeltaMouseY()
{
	return m_mouseDelta.y;
}

void InputController::SetMouseDeltaX(long deltaX)
{
	m_mouseDelta.x = deltaX;
}

void InputController::SetMouseDeltaY(long deltaY)
{
	m_mouseDelta.y = deltaY;
}

void InputController::BeginUpdate()
{
	GetCursorPos(&m_curMousePos);
	ScreenToClient(m_windowHandle, &m_curMousePos);
}

void InputController::EndUpdate()
{
	//When we finish an update we copy the values of the current arrays into the last arrays
	memcpy(m_PrevKeys, m_CurrentKeys, sizeof(m_CurrentKeys));
	memcpy(m_prevMouse, m_currentMouse, sizeof(m_currentMouse));

	m_mouseDelta.x = 0;
	m_mouseDelta.y = 0;
}