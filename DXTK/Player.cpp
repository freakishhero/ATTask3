#include "Player.h"
#include <iostream>
#include "PlayerStates.h"
#include "TileEditor.h"
#include "DrawData2D.h"
#include "PhysicsComponent.h"
#include "GameData.h"
#include "GameStates.h"
#include "Sprite.h"
#include "SpriteGameObject.h"
#include <dinput.h>
#include <cmath>
#include "FollowCamera.h"

Player::Player(Sprite* _sprite)
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

	if (!can_move_down)
	{
		physics->enableGravity(false);
	}
	else 
	{
		physics->enableGravity(true);
	}

	if (_GD->game_state != GameState::EDIT)
	{
		if (_GD->keyboard_state[DIK_SPACE] & 0x80 && _GD->player_state != PlayerState::PS_JUMPING)
		{
			pos += Vector2(0, -1) * _GD->delta_time;
			physics->addForce(Vector2(0, -200) * _GD ->delta_time);
			_GD->player_state = PlayerState::PS_JUMPING;
		}
		if (_GD->keyboard_state[DIK_W] & 0x80)
		{
			pos += Vector2(0, -1000) * _GD->delta_time;
		}
		if (_GD->keyboard_state[DIK_A] & 0x80 && can_move_left)
		{
			pos -= Vector2(300, 0) * _GD->delta_time;
		}
		if (_GD->keyboard_state[DIK_D] & 0x80 && can_move_right)
		{
			pos += Vector2(300, 0) * _GD->delta_time;
		}
		if (_GD->keyboard_state[DIK_1] & 0x80)
		{
			EnableEditMode();
			_GD->game_state = GameState::EDIT;
		}
	}
	else 
	{
		if (_GD->keyboard_state[DIK_2] & 0x80)
		{
			DisableEditMode();
			_GD->game_state = GameState::PLAY;
		}

		tile_editor->Tick(_GD);
	}

	if (pos.y > _GD->MAX_DEPTH * (_GD->TILE_HEIGHT * 2))
		pos = Vector2(0, -640);

	if(_GD->game_state != GameState::EDIT)
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

void Player::SetMoveLeft(bool _state)
{
	can_move_left = _state;
}

void Player::SetMoveRight(bool _state)
{
	can_move_right = _state;
}

void Player::SetMoveDown(bool _state)
{
	can_move_down = _state;
}

TileEditor * Player::GetTileEditor()
{
	return tile_editor;
}

void Player::EnableEditMode()
{
	visible = false;
	tile_editor->SetVisible(true);
}

void Player::DisableEditMode()
{
	visible = true;
	tile_editor->SetVisible(false);
}
