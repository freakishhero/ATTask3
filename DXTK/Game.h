#pragma once

#include "DrawData2D.h"
#include "GameData.h"
#include "StepTimer.h"
#include <d3d11.h>
#include <memory>
#include <vector>

struct DrawData2D;
struct GameData;
class PerlinNoise;
class TileManager;
class CollisionManager;
class InputHandler;
class FollowCamera;
class Player;
class Tile;

class Game final
{
public:

    Game(ID3D11Device* _pd3dDevice, HWND _hWnd, HINSTANCE _hInstance);
	~Game();

    // Basic game loop
    bool Tick();
	void Draw(ID3D11DeviceContext* _pd3dImmediateContext);
	Player* GetPlayer();

private:
    // Device resources.
	DWORD play_time; //amount of time since the game started
	HWND        hWnd;

	void createTiles();
	void generateChunk();
	// Game Objects
	GameData game_data;
	DrawData2D draw_data;
	std::unique_ptr<PerlinNoise> noise;
	std::unique_ptr<Player> player = nullptr;
	
	std::unique_ptr<TileManager> tile_manager = nullptr;
	std::unique_ptr<InputHandler> input_handler = nullptr;
	std::unique_ptr<FollowCamera> camera = nullptr;
	std::unique_ptr<CollisionManager> collision_manager = nullptr;

	std::vector<Tile*> tiles;
};