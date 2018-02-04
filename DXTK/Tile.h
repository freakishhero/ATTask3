#pragma once
#include "SpriteGameObject.h"
#include "TileType.h"

class Tile : public SpriteGameObject
{
public:
	Tile(TileType _type, Vector2 _position);
	virtual ~Tile();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData2D* _DD) override;

private:
	TileType tile_type;
};
