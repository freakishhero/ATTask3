#include "TileEditor.h"
#include "DrawData2D.h"
#include "Tile.h"
#include "Sprite.h"
#include "SpriteGameObject.h"

TileEditor::TileEditor(Sprite* _sprite)
{
	sprite = _sprite;
}

TileEditor::~TileEditor()
{
}

void TileEditor::Tick(GameData * _GD)
{
	if (selected_tile != nullptr)
	{
		pos = selected_tile->GetPos();
	}
	
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

void TileEditor::SetSelectedTile(Tile * _tile)
{
	selected_tile = _tile;
}

Tile * TileEditor::GetSelectedTile() const
{
	return selected_tile;
}
