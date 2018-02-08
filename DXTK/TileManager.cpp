#include "TileManager.h"
#include "TileType.h"
#include "Tile.h"
#include "Sprite.h"

TileManager::TileManager(ID3D11Device* _d3d_device)
{
	tileSprites.push_back(new Sprite(L"../Assets/Air.dds", _d3d_device));
	tileSprites.push_back(new Sprite(L"../Assets/Grass.dds", _d3d_device));
	tileSprites.push_back(new Sprite(L"../Assets/Dirt.dds", _d3d_device));
	tileSprites.push_back(new Sprite(L"../Assets/Stone.dds", _d3d_device));
	tileSprites.push_back(new Sprite(L"../Assets/CobbleStone.dds", _d3d_device));
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
	}
	return tile;
}
