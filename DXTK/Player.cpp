#include "Player.h"
#include <iostream>
#include "PlayerStates.h"
#include "TileEditor.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "Sprite.h"
#include "SpriteGameObject.h"
#include <dinput.h>
#include <cmath>

Player::Player(Sprite* _sprite)
	: visible(true)
{
	player_state = PlayerState::PS_GROUNDED;
	sprite = _sprite;
}


Player::~Player()
{
	if (tile_editor)
	{
		delete tile_editor;
		tile_editor = nullptr;
	}
}


void Player::Tick(GameData* _GD)
{
	if (_GD->keyboard_state[DIK_ESCAPE] & 0x80)
	{
		_GD->exit = true;
	}

	if (player_state != PlayerState::PS_EDIT)
	{
		if (_GD->keyboard_state[DIK_W] & 0x80)
		{
			pos -= Vector2(0, 100) * _GD->delta_time;
		}
		if (_GD->keyboard_state[DIK_S] & 0x80)
		{
			pos += Vector2(0, 100) * _GD->delta_time;
		}
		if (_GD->keyboard_state[DIK_A] & 0x80)
		{
			pos -= Vector2(100, 0) * _GD->delta_time;
		}
		if (_GD->keyboard_state[DIK_D] & 0x80)
		{
			pos += Vector2(100, 0) * _GD->delta_time;
		}
		if (_GD->keyboard_state[DIK_1] & 0x80)
		{
			EnableEditMode();
		}
	}
	else 
	{
		if (_GD->keyboard_state[DIK_2] & 0x80)
		{
			DisableEditMode();
		}

		tile_editor->SetPos(Vector2(
			_GD->mouse_pos.x = floor(_GD->mouse_pos.x / _GD->TILE_WIDTH) * _GD->TILE_WIDTH,
			_GD->mouse_pos.y = floor(_GD->mouse_pos.y / _GD->TILE_HEIGHT) * _GD->TILE_HEIGHT
			));

			if (_GD->mouse_state->rgbButtons[0])
			{
				for (auto& tile : _GD->tiles)
				{
					if (tile->GetPos() == Vector2(_GD->mouse_pos.x, _GD->mouse_pos.y))
					{
						if (tile->isDestructable())
						{
							if (tile->GetTileType() != TileType::AIR)
								tile->DestroyTile();
						}
						
						//else
							//tile->SetTileType(TileType::COBBLESTONE);
					}
				}
			}

			if (_GD->mouse_state->rgbButtons[0] && _GD->keyboard_state[DIK_LSHIFT] & 0x80)
			{
				for (auto& tile : _GD->tiles)
				{
					if (tile->GetPos() == Vector2(_GD->mouse_pos.x, _GD->mouse_pos.y))
					{
						if (tile->GetTileType() == TileType::AIR)
						{
								tile->SetTileType(TileType::COBBLESTONE);
						}

						//else
						//tile->SetTileType(TileType::COBBLESTONE);
					}
				}
			}

		tile_editor->Tick(_GD);
	}
	SpriteGameObject::Tick(_GD);
}


void Player::Draw(DrawData2D* _DD)
{
	if (visible)
	{
		_DD->sprite_batch->Draw(sprite->getResourceView(), pos, nullptr, color, rot, origin, scale, SpriteEffects_None);
	}

	if (tile_editor)
	{
		tile_editor->Draw(_DD);
	}
}

bool Player::IsVisible() const
{
	return visible;
}

void Player::SetVisible(bool _visible)
{
	visible = _visible;
}

void Player::SetTileEditor(TileEditor * _te)
{
	tile_editor = _te;
}

TileEditor * Player::GetTileEditor()
{
	return tile_editor;
}

void Player::EnableEditMode()
{
	player_state = PlayerState::PS_EDIT;
	visible = false;
	tile_editor->SetVisible(true);
}

void Player::DisableEditMode()
{
	player_state = PlayerState::PS_GROUNDED;
	visible = true;
	tile_editor->SetVisible(false);
}
