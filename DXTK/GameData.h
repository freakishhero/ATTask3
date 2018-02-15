#pragma once
#include <vector>
#include <dinput.h>

enum GameState;
enum PlayerState;
class Tile;
class FollowCamera;

struct GameData
{
	bool exit = false; //Should the main game loop should stop?
	float delta_time = 0;  //Time passed since the last frame
	int window_width = 0; //Width of the window
	int window_height = 0; //Height of the window

	float aspect_ratio = 0; //AspectRatio of the window.
	GameState game_state;
	PlayerState player_state;
	FollowCamera* follow_camera = nullptr;
	std::vector<Tile*> tiles;

	unsigned char* keyboard_state = nullptr; //Current state of the Keyboard
	unsigned char* last_keyboard_state = nullptr; //Last state of the keyboard
	DIMOUSESTATE* mouse_state = nullptr;
	POINT mouse_pos;

	const int TILE_SPRITES = 6;
	const float TILE_WIDTH = 64;
	const float TILE_HEIGHT = 64;
	const int MAX_DEPTH = 16;
};
