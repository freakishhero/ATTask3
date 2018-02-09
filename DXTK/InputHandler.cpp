#include "InputHandler.h"
#include "CommonStates.h"
#include <windows.h>
#include "GameData.h"

InputHandler::InputHandler(GameData* _GD, HWND& _hWnd, HINSTANCE& _hInstance)
{
	direct_input = nullptr;
	keyboard = nullptr;
	mouse = nullptr;

	HRESULT hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&direct_input, NULL);
	hr = direct_input->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	hr = keyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = keyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	hr = direct_input->CreateDevice(GUID_SysMouse, &mouse, NULL);
	hr = mouse->SetDataFormat(&c_dfDIMouse);
	hr = mouse->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	_GD->keyboard_state = keyboard_state;
	_GD->last_keyboard_state = last_keyboard_state;
	_GD->mouse_state = &mouse_state;
}
 
InputHandler::~InputHandler()
{
	if (direct_input)
	{
		direct_input->Release();
	}
	if (keyboard)
	{
		keyboard->Unacquire();
		keyboard->Release();
	}
	if(mouse)
	{
		mouse->Unacquire();
		mouse->Release();
	}
}

void InputHandler::Tick(GameData* _GD)
{
	ReadKeyboard();
	ReadMouse();
	GetCursorPos(&_GD->mouse_pos);
}

bool InputHandler::ReadKeyboard()
{
	memcpy(last_keyboard_state, keyboard_state, sizeof(unsigned char) * 256);
	ZeroMemory(&keyboard_state, sizeof(keyboard_state));
	HRESULT hr = keyboard->GetDeviceState(sizeof(keyboard_state), (LPVOID)&keyboard_state);

	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool InputHandler::ReadMouse()
{
	ZeroMemory(&mouse_state, sizeof(DIMOUSESTATE));
	HRESULT hr = mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouse_state);

	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			mouse->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}