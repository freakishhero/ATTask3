#pragma once
#pragma comment(lib, "dinput8")
#include <dinput.h>

struct GameData;

class InputHandler
{
public:
	InputHandler(GameData* _GD, HWND _hWnd, HINSTANCE _hInstance);
	~InputHandler();
	bool ReadInput(); //Get current Mouse and Keyboard states
private:
	IDirectInput8*			direct_input;
	IDirectInputDevice8*	keyboard;
	unsigned char			keyboard_state[256];
	unsigned char			last_keyboard_state[256];
};