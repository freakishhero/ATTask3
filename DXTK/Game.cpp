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
#include "Chunk.h"
#include "Player.h"
#include "Sprite.h"
#include <d3d11.h>
#include <AntTweakBar.h>

using namespace DirectX;
using namespace SimpleMath;

void TW_CALL ResetPos(void* clientData);

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

	TwInit(TW_DIRECT3D11, _pd3dDevice); // for Direct3D 11
	TwWindowSize(game_data.window_width, game_data.window_height);
	TwBar* tweakBar;
	tweakBar = TwNewBar("Control Panel");

	input_handler = std::make_unique<InputHandler>(&game_data, _hWnd, _hInstance);

	//DirectXTK sprite batch
	ID3D11DeviceContext* pd3dImmediateContext;
	_pd3dDevice->GetImmediateContext(&pd3dImmediateContext);
	draw_data.sprite_batch = std::make_unique<SpriteBatch>(pd3dImmediateContext);
	draw_data.font = std::make_unique<SpriteFont>(_pd3dDevice, L"..\\Assets\\Fonts\\calibri.spritefont");

	// Seed the random number generator.
	srand(static_cast<unsigned int>(time(nullptr)));

	game_data.tile_manager = std::make_unique<TileManager>(&game_data, _pd3dDevice);

	collision_manager = std::make_unique<CollisionManager>();

	level_loader = std::make_unique<LevelLoader>();
	
	// Camera that follows an object.
	game_data.follow_camera = std::make_unique<FollowCamera>(0.25f * XM_PI, game_data.aspect_ratio, 1.0f,
		10000.0f, nullptr, Vector3(0, 0, -100));

	//Generates air tiles and assigns them a type using perlin noise.
	createChunk();

	//FIX THIS NOOOOOOB
	game_data.tiles = chunks[0]->GetTiles();
	Sprite* sprite = new Sprite(L"../Assets/Sprites/Player/Player.dds", _pd3dDevice);
	player = std::make_unique<Player>(sprite);
	Sprite* sprite1 = new Sprite(L"../Assets/Sprites/Player/Selector.dds", _pd3dDevice);
	player->SetTileEditor(new TileEditor(sprite1));
	player->DisableEditMode();
	player->GetPhysics()->enablePhysics(true);
	player->GetPhysics()->enableGravity(true);
	collision_manager->initPlayer(player.get());
	game_data.game_state = GameState::PLAY;

	game_data.follow_camera->SetTarget(player.get());

	//Tweak Bar Control Panel
	//TwAddButton(tweakBar, "Create Sand", ResetPos, this, "label='Create a new grain of sand'");
	// Create a new TwType called rotationType associated with the Scene::RotMode enum, and use it
	TwEnumVal editor_tiles[] = { 
	{ (int)TileType::AIR, "Empty" },
	{ (int)TileType::DIRT,  "Dirt" },
	{ (int)TileType::COBBLESTONE, "Cobblestone" },
	{ (int)TileType::STONE, "Stone" },
	{ (int)TileType::SAND, "Sand" },
	{ (int)TileType::PLANK, "Plank" }
	};

	TwType tileType = TwDefineEnum("Block", editor_tiles, 6);
	TwAddVarRW(tweakBar, "Selected Tile", tileType, player->GetTileEditor()->GetTileReplace(),
		" group='Scene' keyIncr=f1 keyDecr=f2 help='Change the tile to place' ");

}


Game::~Game()
{
	TwTerminate();
}

// Executes the basic game loop.
bool Game::Tick()
{
	DWORD currentTime = GetTickCount();
	game_data.delta_time = min((float)(currentTime - play_time) / 1000.0f, 0.1f);
	play_time = currentTime;

	input_handler->Tick(&game_data);
	game_data.tile_manager->Tick(&game_data);
	collision_manager->tick(&game_data);

	for (auto& chunk : chunks)
	{
		chunk->Tick(&game_data);
	}
	player->Tick(&game_data);

	game_data.follow_camera->Tick(&game_data);

	if (game_data.exit == true)
	{
		return false;
	}

	return true;
}

void Game::Draw(ID3D11DeviceContext * _pd3dImmediateContext)
{
	draw_data.sprite_batch->Begin(SpriteSortMode_BackToFront, nullptr, nullptr, nullptr, nullptr, nullptr, game_data.follow_camera->GetWorldMat());
	for (auto& chunk : chunks)
	{
		chunk->Draw(&draw_data);

	}

	player->Draw(&draw_data);
	draw_data.sprite_batch->End();
	if(game_data.game_state == GameState::EDIT)
	TwDraw();
}

void Game::createChunk()
{
	chunks.push_back(new Chunk(&game_data));
	std::vector<int> tile_types;
	for (int i = 0; i < chunks[0]->GetTiles().size(); i++)
	{
		tile_types.push_back((int)chunks[0]->GetTiles()[i]->GetTileType());
	}

	level_loader->SaveLevel(tile_types);

	//chunks[0]->LoadChunkFromTile(level_loader->LoadLevel("Level_01"));
}