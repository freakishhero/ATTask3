#include "Tile.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "Sprite.h"
#include "SpriteGameObject.h"

Tile::Tile(int _ID, TileType _type, Vector2 _position)
{
	tile_type = _type;
	pos = _position;
	ID = _ID;

	if (tile_type == TileType::BEDROCK)
		destructable = false;
}

Tile::~Tile()
{
}

void Tile::Tick(GameData * _GD)
{
	if (surface_tile && tile_type == TileType::DIRT)
	{
		tile_type = TileType::GRASS;
	}
	SpriteGameObject::Tick(_GD);
}

void Tile::Draw(DrawData2D * _DD)
{
	if (visible)
	{
		_DD->sprite_batch->Draw(sprite->getResourceView(), pos, nullptr, color, rot, origin, scale, SpriteEffects_None);
	}
}

void Tile::DestroyTile()
{
	tile_type = TileType::AIR;
}

void Tile::SetTileType(TileType _type)
{
	tile_type = _type;
}

TileType Tile::GetTileType() const
{
	return tile_type;
}

void Tile::SetSurfaceTile(bool _state)
{
	surface_tile = _state;
}

int Tile::GetID() const
{
	return ID;
}

void Tile::SetID(int _ID)
{
	ID = _ID;
}

bool Tile::isDestructable()
{
	return destructable;
}
