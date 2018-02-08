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
	void SetSelectedTile(Tile* _tile);
	Tile* GetSelectedTile() const;

private:
	Tile* selected_tile = nullptr;
};