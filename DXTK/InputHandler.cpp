#include "InputHandler.h"
#include "CommonStates.h"
#include <windows.h>
#include "GameData.h"

InputHandler::InputHandler(GameData* _GD, HWND _hWnd, HINSTANCE _hInstance)
{
	keyboard = nullptr;
	direct_input = nullptr;

	HRESULT hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&direct_input, NULL);
	hr = direct_input->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	hr = keyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = keyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	_GD->keyboard_state = keyboard_state;
	_GD->last_keyboard_state = last_keyboard_state;
}
 
InputHandler::~InputHandler()
{
}

bool InputHandler::ReadInput()
{
	//copy over old keyboard state
	memcpy(last_keyboard_state, keyboard_state, sizeof(unsigned char) * 256);

	//clear out previous state
	ZeroMemory(&keyboard_state, sizeof(unsigned char) * 256);

	// Read the keyboard device.
	HRESULT hr = keyboard->GetDeviceState(sizeof(keyboard_state), (LPVOID)&keyboard_state);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
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
