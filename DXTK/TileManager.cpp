#include "TileManager.h"
#include "TileType.h"
#include "Tile.h"
#include "Sprite.h"
#include "GameData.h"
#include <string>

TileManager::TileManager(GameData* _GD, ID3D11Device* _d3d_device)
{
	for (int i = 0; i < _GD->TILE_SPRITES; i++)
	{
		std::string id = std::to_string(i);
		std::string file_path = "../Assets/" + id + ".dds";
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

void TileManager::CheckSurfaceTile(Tile * _tile, GameData* _GD)
{
	for (auto& tile : _GD->tiles)
	{
		if (_tile != tile && tile->GetTileType() != TileType::AIR)
		{
			if (_tile->GetPos().x == tile->GetPos().x)
			{
				if (_tile->GetPos().y < tile->GetPos().y)
				{
					_tile->SetSurfaceTile(true);
				}
				else
				{
					_tile->SetSurfaceTile(false);
				}
			}
		}
	}
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
	elapsed += 1 * _GD->delta_time;
	for (auto& tile : _GD->tiles)
	{
		if (!tile->IsSurfaceTile() && tile->GetTileType() != TileType::AIR && elapsed >= 10)
		{	
			CheckSurfaceTile(tile, _GD);
		}

		tile->SetSprite(tileSprites[(int)tile->GetTileType()]);
	}
	if (elapsed >= 10)
		elapsed = 0;
}
