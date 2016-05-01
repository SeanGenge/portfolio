/*	FIT2049 - Example Code
*	InputController.h
*	Created by Elliott Wilson - 2015 - Monash Univeristy
*	This class keeps track of the current state of the keyboard and mouse
*	It receives data from the Window Proc about the current keys and mouse buttons
*	and uses the Windows API for information about the Mouse position
*/

#pragma once

#include <iostream>
#include <Windows.h>

#define LEFT_MOUSE 0						//A value to represent the Left Mouse Button
#define RIGHT_MOUSE 1						//A value to represent the Right Mouse Button
#define MIDDLE_MOUSE 2						//A value to represent the Middle Mouse Button
#define NUMBER_OF_KEYS 256					//The number of entries in the keys arrays

class InputController
{
private:
	HWND m_windowHandle;

	bool m_CurrentKeys[NUMBER_OF_KEYS];		//An array of key values for the current frame
	bool m_PrevKeys[NUMBER_OF_KEYS];		//An array of key values for the previous frame
	bool m_currentMouse[3];					//An array of mouse button values for the current frame
	bool m_prevMouse[3];					//An array of mouse button values for the previous frame
	POINT m_curMousePos;					//The current position of the mouse
	POINT m_mouseDelta;

public:
	InputController(HWND windowHandle);		//Constructor

	void SetKeyDown(UINT keyCode);			//These set methods are used to update the correct values in
	void SetKeyUp(UINT keyCode);			//the current keys/mouse button arrays
	void SetMouseDown(int mouseButton);
	void SetMouseUp(int mouseButton);

	bool GetKeyDown(UINT keyCode);			//Returns true if the selected key is down.
	bool GetKeyDownOnce(UINT keycode);		//Returns true if the selected key is down but after one frame, returns false
	bool GetKeyUp(UINT keyCode);			//Returns true if the selected key was down last frame and up this frame
	bool checkKeyPress();					//Returns true if a key is pressed.

	bool GetMouseDown(int mouseButton);		//Returns true if the selected mouse button is down
	bool GetMouseDownOnce(int mouseButton);
	bool GetMouseUp(int mouseButton);		//Returns true if the selected mouse button was down last frame and up this frame
	int GetMouseX();						//Returns the current mouse X
	int GetMouseY();						//Returns the current mouse Y

	int GetDeltaMouseX();					//Returns the change in the X position of the mouse in one frame
	int GetDeltaMouseY();					//Returns the change in the Y position of the mouse in one frame
	void SetMouseDeltaX(long deltaX);
	void SetMouseDeltaY(long deltaY);

	void BeginUpdate();						//Begins updating the input, this reads the current value of the mouse cursor
	void EndUpdate();						//Ends updating the input, this copys the values of current key/mouse into previous keys/mouse
};