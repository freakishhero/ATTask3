#include "TileManager.h"
#include "TileType.h"
#include "Tile.h"
#include "Sprite.h"
#include "GameData.h"

TileManager::TileManager(ID3D11Device* _d3d_device)
{
	tileSprites.push_back(new Sprite(L"../Assets/Air.dds", _d3d_device));
	tileSprites.push_back(new Sprite(L"../Assets/Grass.dds", _d3d_device));
	tileSprites.push_back(new Sprite(L"../Assets/Dirt.dds", _d3d_device));
	tileSprites.push_back(new Sprite(L"../Assets/Stone.dds", _d3d_device));
	tileSprites.push_back(new Sprite(L"../Assets/CobbleStone.dds", _d3d_device));
	tileSprites.push_back(new Sprite(L"../Assets/Bedrock.dds", _d3d_device));
}

TileManager::~TileManager()
{
}



Tile* TileManager::createTile(int _ID, TileType _type, DirectX::SimpleMath::Vector2 _position)
{
	Tile* tile = new Tile(_ID, _type, _position);

	switch (_type)
	{
	case TileType::AIR:
		tile->SetSprite(tileSprites[0]);
			break;
	case TileType::GRASS:
		tile->SetSprite(tileSprites[1]);
		break;
	case TileType::DIRT:
		tile->SetSprite(tileSprites[2]);
		break;
	case TileType::STONE:
		tile->SetSprite(tileSprites[3]);
		break;
	case TileType::COBBLESTONE:
		tile->SetSprite(tileSprites[4]);
		break;
	case TileType::BEDROCK:
		tile->SetSprite(tileSprites[4]);
		break;
	}
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

void TileManager::Tick(GameData * _GD)
{
	Tile* surface_tile;

	for (auto& tile : _GD->tiles)
	{
		if (tile->GetTileType() != TileType::AIR)
		{
			CheckSurfaceTile(tile, _GD);
		}
		
	}


	for (auto& tile : _GD->tiles)
	{
		switch (tile->GetTileType())
		{
		case TileType::AIR:
			tile->SetSprite(tileSprites[0]);
			break;
		case TileType::GRASS:
			tile->SetSprite(tileSprites[1]);
			break;
		case TileType::DIRT:
			tile->SetSprite(tileSprites[2]);
			break;
		case TileType::STONE:
			tile->SetSprite(tileSprites[3]);
			break;
		case TileType::COBBLESTONE:
			tile->SetSprite(tileSprites[4]);
			break;
		case TileType::BEDROCK:
			tile->SetSprite(tileSprites[5]);
			break;
		}
	}
	
}
