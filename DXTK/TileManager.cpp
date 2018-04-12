#include "TileManager.h"
#include "TileType.h"
#include "Tile.h"
#include "Sprite.h"
#include "GameData.h"
#include <string>
#include <iostream>

TileManager::TileManager(GameData* _GD, ID3D11Device* _d3d_device)
{
	for (int i = 0; i < _GD->TILE_SPRITES; i++)
	{
		std::string id = std::to_string(i);
		std::string file_path = "../Assets/Sprites/Tiles/DDS/" + id + ".dds";
		const char* c_string = file_path.c_str();
		tileSprites.push_back(new Sprite(charToWChar(c_string), _d3d_device));
	}
}

TileManager::~TileManager()
{
}

Tile* TileManager::createTile(int _ID, TileType _type, DirectX::SimpleMath::Vector2 _position)
{
	Tile* tile = new Tile(_ID, _type, _position);
	tile->SetSprite(tileSprites[(int)_type]);
	return tile;
}

wchar_t * TileManager::charToWChar(const char * _string)
{
	size_t size = strlen(_string) + 1;
	static wchar_t* wa = NULL;

	if (wa)
	{
		delete[] wa;
		wa = NULL;
	}

	wa = new wchar_t[size];
	mbstowcs_s(nullptr, wa, size, _string, size);

	return wa;
}

void TileManager::Tick(GameData * _GD)
{
	//elapsed += 1 * _GD->delta_time;
	for (auto& tile : _GD->tiles)
	{
		/*if (!tile->IsSurfaceTile() && tile->GetTileType() != TileType::AIR && elapsed >= 10)
		{	
			if (tile->checkSurfaceTile(_GD))
			{
				tile->SetSurfaceTile(true);
			}
			else
			{
				tile->SetSurfaceTile(false);
			}
		}*/
		tile->SetSprite(tileSprites[(int)tile->GetTileType()]);
	}
	HandleGrass(_GD);
	//if (elapsed >= 10)
	//	elapsed = 0;
	
}

Tile* TileManager::GetTileFromWorld(Vector2 pos, GameData * _GD)
{
	if (pos.x < 0 || pos.y < 0)
		return nullptr;

	int grid_x = floor(pos.x / _GD->TILE_WIDTH);
	int grid_y = floor(pos.y / _GD->TILE_HEIGHT);

	int index = (_GD->window_width / _GD->TILE_WIDTH) * grid_y + grid_x;

	return _GD->tiles[index];
}

void TileManager::HandleGrass(GameData* _GD)
{
	for (int w = 0; w < _GD->window_width / _GD->TILE_WIDTH; w++)
	{
		for (int h = 0; h < _GD->window_height / _GD->TILE_HEIGHT; h++)
		{
			Tile* tile = GetTileFromWorld(DirectX::SimpleMath::Vector2(w * _GD->TILE_WIDTH, h * _GD->TILE_HEIGHT), _GD);

			if (tile && tile->GetTileType() == TileType::GRASS)
				break;

			if (tile && tile->GetTileType() == TileType::DIRT)
			{
				tile->SetTileType(TileType::GRASS);
				break;
			}
		}
		
	}
}
