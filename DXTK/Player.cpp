#include "Player.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "Sprite.h"
#include "SpriteGameObject.h"
#include <dinput.h>

Player::Player(Sprite* _sprite)
	: visible(true)
{
	sprite = _sprite;
}


Player::~Player()
{
}


void Player::Tick(GameData* _GD)
{
	if (_GD->keyboard_state[DIK_W] & 0x80)
	{
		pos -= Vector2(0, 1000) * _GD->delta_time;
	}
	if (_GD->keyboard_state[DIK_S] & 0x80)
	{
		pos += Vector2(0, 1000) * _GD->delta_time;
	}
	if (_GD->keyboard_state[DIK_A ] & 0x80)
	{
		pos -= Vector2(1000, 0) * _GD->delta_time;
	}
	if (_GD->keyboard_state[DIK_D] & 0x80)
	{
		pos += Vector2(1000, 0) * _GD->delta_time;
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


/* Returns true if the animated object should be drawn, otherwise returns false;
*/
bool Player::IsVisible() const
{
	return visible;
}


/* Set to false to hide the whole image object, otherwise set to true for it to be drawn.
*/
void Player::SetVisible(bool _visible)
{
	visible = _visible;
}