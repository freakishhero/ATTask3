#include "Game.h"
#include "GameStates.h"
#include "TileType.h"
#include "TileManager.h"
#include "TileEditor.h"
#include "InputHandler.h"
#include "SimpleMath.h"
#include "FollowCamera.h"
#include "PhysicsComponent.h"
#include "CollisionManager.h"
#include <windows.h>
#include <time.h>
#include "Tile.h"
#include "Player.h"
#include "Sprite.h"
#include "PerlinNoise.h"
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

	tile_manager = std::make_unique<TileManager>(&game_data, _pd3dDevice);

	collision_manager = std::make_unique<CollisionManager>();
	
	// Camera that follows an object.
	camera = std::make_unique<FollowCamera>(0.25f * XM_PI, game_data.aspect_ratio, 1.0f,
		10000.0f, player.get(), Vector3(0, 0, -100));

	noise = new PerlinNoise(rand() % 1000000 + 10000000);

	/*float x = 0;
	float y = game_data.window_height - 64;;
	int amount = rand() % 500 + 100;
	int iterator = 0;	
	TileType type = TileType::BEDROCK;
	for (int i = 0; i < amount; i++)
	{	
			

		if (y < 256)
			type = TileType::AIR;
		else if (y > 256 && y <= 320)
			type = TileType::BEDROCK;
		else if (y > 320 && y <= 640)
			type = TileType::DIRT;
		else if (y > 640)
			type = TileType::STONE;
		tiles.push_back(tile_manager->createTile(i, type, Vector2(x, y)));
		x += 64;
		iterator++;
		if (iterator == game_data.window_width / 64)
		{
			iterator = 0;
			x = 0;
			y +=64;
		}
	}*/

	//Generates air tiles and assigns them a type using perlin noise.
	createTiles();
	game_data.tiles = tiles;
	generateChunk();
	game_data.tiles = tiles;

	Sprite* sprite = new Sprite(L"../Assets/Player.dds", _pd3dDevice);
	player = std::make_unique<Player>(sprite);
	Sprite* sprite1 = new Sprite(L"../Assets/Selection.dds", _pd3dDevice);
	player->SetTileEditor(new TileEditor(sprite1));
	player->DisableEditMode();
	player->GetPhysics()->enablePhysics(true);
	player->GetPhysics()->enableGravity(true);
	collision_manager->initPlayer(player.get());
	game_data.follow_camera = camera.get();
	game_data.game_state = GameState::PLAY;

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

	input_handler->Tick(&game_data);
	tile_manager->Tick(&game_data);
	collision_manager->tick(&game_data);

	for (auto& tile : tiles)
	{
		tile->Tick(&game_data);
	}
	player->Tick(&game_data);

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

void Game::createTiles()
{
	int id = 0;
	for (int w = 0; w < game_data.window_width / game_data.TILE_WIDTH; w++)
	{
		for (int h = 0; h < game_data.window_width / game_data.TILE_WIDTH; h++)
		{
			Vector2 pos = Vector2(w * game_data.TILE_WIDTH, h  * game_data.TILE_HEIGHT);
			tiles.push_back(tile_manager->createTile(id, TileType::AIR, Vector2(pos)));
			id++;
		}
	}
}

void Game::generateChunk()
{
	for (int i = 0; i < game_data.window_width / game_data.TILE_WIDTH; i++) //x = width 
	{
		int height = 2 + noise->generateNoise(i, game_data.TILE_HEIGHT / 6);

		for (int j = game_data.window_height / game_data.TILE_HEIGHT; j > game_data.window_height / game_data.TILE_HEIGHT - height; j--) //y = height
		{
			Vector2 pos = Vector2(i * game_data.TILE_WIDTH, j  * game_data.TILE_HEIGHT);
			for (auto& tile : game_data.tiles)
			{
				if (tile->GetPos() == pos)
				{
					int random = j == game_data.MAX_DEPTH - 1 ? rand() % 1 + 1 : rand() % 2 + 1;
					if (j == game_data.MAX_DEPTH)
					{
						//tiles.push_back(tile_manager->createTile(i, TileType::BEDROCK, Vector2(pos)));
						tile->SetTileType(TileType::BEDROCK);
					}
					else if (j > game_data.MAX_DEPTH - 4 && j < game_data.MAX_DEPTH && random == 1)
					{
						//tiles.push_back(tile_manager->createTile(game_data.tiles.size(), TileType::STONE, Vector2(pos)));
						tile->SetTileType(TileType::STONE);
					}
					else
					{
						//tiles.push_back(tile_manager->createTile(i, TileType::DIRT, Vector2(pos)));
						tile->SetTileType(TileType::DIRT);
					}
				}
			}
		}
	}

	/*
	for (int i = 0; i < game_data.window_width / game_data.TILE_WIDTH; i++) //x = width 
	{
		int height = 2 + noise->generateNoise(i, game_data.TILE_HEIGHT / 6);

		for (int j = game_data.window_height / game_data.TILE_HEIGHT; j > game_data.window_height / game_data.TILE_HEIGHT - height; j--) //y = height
		{
			Vector2 pos = Vector2(i * game_data.TILE_WIDTH, j  * game_data.TILE_HEIGHT);
			int random = j == game_data.MAX_DEPTH - 1 ? rand() % 1 + 1 : rand() % 2 + 1;
			if (j == game_data.MAX_DEPTH)
			{
				tiles.push_back(tile_manager->createTile(i, TileType::BEDROCK, Vector2(pos)));
			}
			else if (j > game_data.MAX_DEPTH - 4 && j < game_data.MAX_DEPTH && random == 1)
			{
				tiles.push_back(tile_manager->createTile(i, TileType::STONE, Vector2(pos)));
			}
			else
			{
				tiles.push_back(tile_manager->createTile(i, TileType::DIRT, Vector2(pos)));
			}
		}
		
		//TO DO - FILL REST OF TILES WITH AIR
		//create all tiles using air and then loop through using perlin noise to set current tiles to something else???
	}*/

	/*
	for (int i = 0; i < 600; i++)
	{
		tiles.push_back(tile_manager->createTile(i, TileType::AIR, Vector2(0, 0)));
	}

	for (int i = game_data.window_width / 64; i >= 0 ; i--) //x - width 
	{
		int height = 2 + noise->generateNoise(i, 16);
		for (int j = height; j > 1; j--) //y - height
		{
			tiles[i]->SetTileType(TileType::DIRT);
			tiles[i]->SetPos(Vector2(i * game_data.TILE_WIDTH, j * game_data.TILE_HEIGHT));
		}
	}
	*/
}
