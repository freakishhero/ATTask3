#include "Player.h"
#include "PlayerStates.h"
#include "TileEditor.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "Sprite.h"
#include "SpriteGameObject.h"
#include <dinput.h>

Player::Player(Sprite* _sprite)
	: visible(true)
{
	player_state = PlayerState::PS_GROUNDED;
	sprite = _sprite;
	tile_editor = new TileEditor(64);
	edit_mode = false;
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
		if (_GD->keyboard_state[DIK_0] & 0x80)
		{
			SetEditMode(true);
		}
	}
	else 
	{
		if (_GD->keyboard_state[DIK_W] & 0x80)
		{
			tile_editor->ModifyPos(Vector2(0, -64) * _GD->delta_time);
		}
		if (_GD->keyboard_state[DIK_S] & 0x80)
		{
			tile_editor->ModifyPos(Vector2(0, 64) * _GD->delta_time);
		}
		if (_GD->keyboard_state[DIK_A] & 0x80)
		{
			tile_editor->ModifyPos(Vector2(-64, 0) * _GD->delta_time);
		}
		if (_GD->keyboard_state[DIK_D] & 0x80)
		{
			pos += Vector2(64, 0) * _GD->delta_time;
		}
		if (_GD->keyboard_state[DIK_0] & 0x80)
		{
			SetEditMode(false);
		}
	}
	
	SpriteGameObject::Tick(_GD);
}


void Player::Draw(DrawData2D* _DD)
{
	if (visible)
	{
		_DD->sprite_batch->Draw(sprite->getResourceView(), pos, nullptr, color, rot, origin, scale, SpriteEffects_None);
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

void Player::SetEditMode(bool _state)
{
	edit_mode = _state;
	if (edit_mode)
	{
		player_state = PlayerState::PS_EDIT;
		visible = false;
		tile_editor->SetVisible(true);
	}
	else 
	{
		player_state = PlayerState::PS_GROUNDED;
		visible = true;
		tile_editor->SetVisible(false);
	}
}
