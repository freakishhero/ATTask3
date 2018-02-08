#pragma once
#include "SpriteGameObject.h"
#include "TileType.h"

class Tile : public SpriteGameObject
{
public:
	Tile(int ID, TileType _type, Vector2 _position);
	virtual ~Tile();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData2D* _DD) override;
	void DestroyTile();
	void SetTileType(TileType _type);
	TileType GetTileType() const;
	int GetID() const;
	void SetID(int _ID);
private:
	TileType tile_type;
	int ID = 0;
};
