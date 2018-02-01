#include "Game.h"
#include "SimpleMath.h"
#include "FollowCamera.h"
#include <windows.h>
#include <time.h>
#include "Player.h"
#include "Sprite.h"
#include <d3d11.h>

using namespace DirectX;
using namespace SimpleMath;

Game::Game(ID3D11Device* _pd3dDevice, HWND _hWnd, HINSTANCE _hInstance)
	: play_time()
	, hWnd(_hWnd)
{
	// Find the screen width and calculate aspect ratio.
	RECT rc;
	GetClientRect(hWnd, &rc);
	game_data.window_width = rc.right - rc.left;
	game_data.window_height = rc.bottom - rc.top;
	game_data.aspect_ratio = static_cast<float>(game_data.window_width) /
		static_cast<float>(game_data.window_height);

	// Create DirectXTK spritebatch stuff.

	//ID3D11DeviceContext* pd3dImmediateContext;
	//_pd3dDevice->GetImmediateContext(&pd3dImmediateContext);

	ID3D11DeviceContext* pd3dImmediateContext;
	_pd3dDevice->GetImmediateContext(&pd3dImmediateContext);
	draw_data.sprite_batch = std::make_unique<SpriteBatch>(pd3dImmediateContext);
	draw_data.font = std::make_unique<SpriteFont>(_pd3dDevice, L"..\\Assets\\calibri.spritefont");

	// Seed the random number generator.
	srand(static_cast<unsigned int>(time(nullptr)));

	// Camera that follows an object.
	camera = std::make_unique<FollowCamera>(0.25f * XM_PI, game_data.aspect_ratio, 1.0f,
		10000.0f, nullptr, Vector3(0, 0, -100));

	Sprite* grass = new Sprite("../Debug/grass", _pd3dDevice);
	Sprite* dirt = new Sprite("../Debug/dirt", _pd3dDevice);
	Sprite* stone = new Sprite("../Debug/stone", _pd3dDevice);

	// Player
	int x = 0;
	int y = 384;
	int iterator = 0;
	for (int i = 0; i < 500; i++)
	{
		Sprite* sprite = nullptr;
		if (y <= 384)
			sprite = grass;
		else if (y < 128+ 640)
			sprite = dirt;
		else
			sprite = stone;

		Player* player = new Player(sprite);
		player->ModifyPos(Vector2(x, y));
		tiles.push_back(player);
		x += grass->getWidth();
		iterator++;
		if (iterator == game_data.window_width / grass->getWidth())
		{
			iterator = 0;
			x = 0;
			y += grass->getHeight();
		}
	}
	

	// Set camera
	//camera->SetTarget(player.get());
	//Game Data
	game_data.follow_camera = camera.get();
}


Game::~Game()
{
}

// Executes the basic game loop.
bool Game::Tick()
{
	DWORD currentTime = GetTickCount();
	game_data.delta_time = min((float)(currentTime - play_time) / 1000.0f, 0.1f);
	play_time = currentTime;

	for (auto& tile : tiles)
	{
		tile->Tick(&game_data);
	}

	if (game_data.exit)
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
	draw_data.sprite_batch->End();
}
