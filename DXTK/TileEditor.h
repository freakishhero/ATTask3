#pragma once
#include "SpriteGameObject.h"
#include "Tile.h"

class TileEditor : public SpriteGameObject
{
public:
	TileEditor(Sprite* _sprite);
	virtual ~TileEditor();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData2D* _DD) override;
	bool IsVisible() const override;
	void SetVisible(bool _visible) override;
	void SetTypeReplace(TileType _type);
	TileType* GetTileReplace();

private:
	TileType tile_replace;
	void ReplaceTile(Tile* _tile);
};