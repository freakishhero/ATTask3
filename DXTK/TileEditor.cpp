#include "TileEditor.h"
#include "DrawData2D.h"
#include "Sprite.h"
#include "SpriteGameObject.h"

TileEditor::TileEditor(int _tileSize)
{
	tileSize = _tileSize;
}

TileEditor::~TileEditor()
{
}

void TileEditor::Tick(GameData * _GD)
{
	SpriteGameObject::Tick(_GD);
}

void TileEditor::Draw(DrawData2D * _DD)
{
	if (visible)
	{
		_DD->sprite_batch->Draw(sprite->getResourceView(), pos, nullptr, color, rot, origin, scale, SpriteEffects_None);
	}
}

bool TileEditor::IsVisible() const
{
	return visible;
}

void TileEditor::SetVisible(bool _visible)
{
	visible = _visible;
}
