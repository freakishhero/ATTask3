#include "Player.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "Sprite.h"
#include "SpriteGameObject.h"

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