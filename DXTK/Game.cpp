#include "Game.h"
#include "TileType.h"
#include "TileManager.h"
#include "InputHandler.h"
#include "SimpleMath.h"
#include "FollowCamera.h"
#include <windows.h>
#include <time.h>
#include "Tile.h"
#include "Player.h"
#include "Sprite.h"
#include <d3d11.h>

using namespace DirectX;
using namespace SimpleMath;

Game::Game(ID3D11Device* _pd3dDevice, HWND _hWnd, HINSTANCE _hInstance)
	: play_time()
	, hWnd(_hWnd)
{
	//Get screen width and work out aspect ratio
	RECT rc;
	GetClientRect(hWnd, &rc);
	game_data.window_width = rc.right - rc.left;
	game_data.window_height = rc.bottom - rc.top;
	game_data.aspect_ratio = static_cast<float>(game_data.window_width) / static_cast<float>(game_data.window_height);

	input_handler = std::make_unique<InputHandler>(&game_data, _hWnd, _hInstance);

	//DirectXTK sprite batch
	ID3D11DeviceContext* pd3dImmediateContext;
	_pd3dDevice->GetImmediateContext(&pd3dImmediateContext);
	draw_data.sprite_batch = std::make_unique<SpriteBatch>(pd3dImmediateContext);
	draw_data.font = std::make_unique<SpriteFont>(_pd3dDevice, L"..\\Assets\\calibri.spritefont");

	// Seed the random number generator.
	srand(static_cast<unsigned int>(time(nullptr)));

	tile_manager = std::make_unique<TileManager>(_pd3dDevice);
	
	Sprite* sprite = new Sprite(L"../Assets/Player.dds", _pd3dDevice);
	player = std::make_unique<Player>(sprite);
	
	// Camera that follows an object.
	camera = std::make_unique<FollowCamera>(0.25f * XM_PI, game_data.aspect_ratio, 1.0f,
		10000.0f, player.get(), Vector3(0, 0, -100));

	int x = 0;
	int y = 0;
	int iterator = 0;
	TileType type = TileType::AIR;
	for (int i = 0; i < 500; i++)
	{	
		if (y < 256)
			type = TileType::AIR;
		else if (y > 256 && y <= 320)
			type = TileType::GRASS;
		else if (y > 320 && y <= 640)
			type = TileType::DIRT;
		else if (y > 640)
			type = TileType::STONE;

		tiles.push_back(tile_manager->createTile(type, Vector2(x, y)));
		x += 64;
		iterator++;
		if (iterator == game_data.window_width / 64)
		{
			iterator = 0;
			x = 0;
			y +=64;
		}
	}

	game_data.follow_camera = camera.get();
}


Game::~Game()
{
}

// Executes the basic game loop.
bool Game::Tick()
{
	input_handler->ReadInput();

	DWORD currentTime = GetTickCount();
	game_data.delta_time = min((float)(currentTime - play_time) / 1000.0f, 0.1f);
	play_time = currentTime;

	for (auto& tile : tiles)
	{
		tile->Tick(&game_data);
	}
	player->Tick(&game_data);

	if (game_data.keyboard_state[DIK_ESCAPE] & 0x80)
	{
		game_data.exit = true;
	}

	if (game_data.exit == true)
	{
		return false;
	}

	return true;
}

void Game::Draw(ID3D11DeviceContext * _pd3dImmediateContext)
{
	draw_data.sprite_batch->Begin(SpriteSortMode_BackToFront, nullptr, nullptr, nullptr, nullptr, nullptr, camera->GetWorldMat());
	for (auto& tile : tiles)
	{
		tile->Draw(&draw_data);
	}
	player->Draw(&draw_data);
	draw_data.sprite_batch->End();
}
