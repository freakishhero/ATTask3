#include "TileEditor.h"
#include "DrawData2D.h"
#include "Tile.h"
#include "TileManager.h"
#include "Sprite.h"
#include "SpriteGameObject.h"
#include "FollowCamera.h"
#include "GameData.h"
#include <iostream>

TileEditor::TileEditor(Sprite* _sprite)
{
	tile_replace = TileType::AIR;
	sprite = _sprite;
}

TileEditor::~TileEditor()
{
}

void TileEditor::Tick(GameData * _GD)
{
	pos = Vector2(
		(_GD->mouse_pos.x - ((_GD->window_width / 2) - _GD->follow_camera->GetPos().x)),
		(_GD->mouse_pos.y - ((_GD->window_height / 2) - _GD->follow_camera->GetPos().y)));

	if (_GD->mouse_state->rgbButtons[0])
	{
		Tile* tile = _GD->tile_manager->GetTileFromWorld(pos, _GD);

		if (tile != nullptr)
		{
			if (tile->isDestructable())
			{
				ReplaceTile(tile);

				int index = tile->GetID();
				int bot_x = index % 30;
				int bot_y = (index / 30) + 1;

				int bot_index = 30 * bot_y + bot_x;

				if (_GD->tiles[bot_index]->GetTileType() == TileType::GRASS)
				{
					_GD->tiles[bot_index]->SetTileType(TileType::DIRT);
				}
			}
		}
	}
	SpriteGameObject::Tick(_GD);
}

void TileEditor::Draw(DrawData2D * _DD)
{
	if (visible)
	{
		_DD->sprite_batch->Draw(sprite->getResourceView(), Vector2(pos.x - 16, pos.y - 16), nullptr, color, rot, origin, scale, SpriteEffects_None);
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

void TileEditor::SetTypeReplace(TileType _type)
{
	tile_replace = _type;
}

TileType* TileEditor::GetTileReplace()
{
	return &tile_replace;
}


void TileEditor::ReplaceTile(Tile* _tile)
{
	if (tile_replace != TileType::AIR && _tile->GetTileType() == TileType::AIR)
		_tile->SetTileType(tile_replace);
	if (tile_replace == TileType::AIR && _tile->GetTileType() != TileType::AIR)
		_tile->SetTileType(tile_replace);
}
