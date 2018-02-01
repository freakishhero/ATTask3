#pragma once
#include "PlayerStates.h"

#include <string>

class TextureManager;
class InputHandler;
class LevelLoader;
class AudioManager;
class FollowCamera;

//=================================================================
//Data to be passed by game to all Game Objects via Tick
//=================================================================

struct GameData
{
	const static int TILE_SIZE = 60; // Size of the tiles used in game.
	const static int PLAYER_HEIGHT = 60; // Height of the player sprite.
	const static int PLAYER_WIDTH = 32; // Width of the player sprite.

	bool exit = false; // Whether the game should exit or not.
	float delta_time = 0;  // Time step since last frame.
	int window_width; // Width of the window. Static so graphics can be positioned based on screen size.
	int window_height; // Height of the window. Static so graphics can be positioned based on screen size.
	float aspect_ratio = 0; // Aspect ratio of the window.

	std::string selected_level_name;
	PlayerState player_state = PlayerState::PS_GROUNDED;
	FollowCamera* follow_camera = nullptr;
};
