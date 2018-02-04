#include "Tile.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "Sprite.h"
#include "SpriteGameObject.h"

Tile::Tile(TileType _type, Vector2 _position)
{
	tile_type = _type;
	pos = _position;
}

Tile::~Tile()
{
}

void Tile::Tick(GameData * _GD)
{
	SpriteGameObject::Tick(_GD);
}

void Tile::Draw(DrawData2D * _DD)
{
	_DD->sprite_batch->Draw(sprite->getResourceView(), pos, nullptr, color, rot, origin, scale, SpriteEffects_None);
}
