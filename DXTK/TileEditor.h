#pragma once
#include "SpriteGameObject.h"

class TileEditor : public SpriteGameObject
{
public:
	TileEditor(int _tileSize);
	virtual ~TileEditor();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData2D* _DD) override;
	bool IsVisible() const override;
	void SetVisible(bool _visible) override;

private:
	int tileSize;
};