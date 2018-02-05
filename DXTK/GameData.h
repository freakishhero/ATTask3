#pragma once
#include "PlayerStates.h"

class FollowCamera;

struct GameData
{
	bool exit = false; //Should the main game loop should stop?
	float delta_time = 0;  //Time passed since the last frame
	int window_width; //Width of the window
	int window_height; //Height of the window
	float aspect_ratio = 0; //AspectRatio of the window.

	PlayerState player_state = PlayerState::PS_GROUNDED; //Player state
	FollowCamera* follow_camera = nullptr; //Global camera for the player

	unsigned char* keyboard_state; //Current state of the Keyboard
	unsigned char* last_keyboard_state; //Last state of the keyboard
};
