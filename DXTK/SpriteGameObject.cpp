#include "SpriteGameObject.h"
#include "DrawData2D.h"
#include "GameData.h"
#include "Sprite.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"

SpriteGameObject::SpriteGameObject(Sprite* _texture, RECT* _rect)
	: sprite(_texture)
	, visible(true)
	, rect(_rect)
{
	physics = new PhysicsComponent(pos, Vector2(0, 10.0f), 0.1f, 5.0f);
	physics->enableGravity(false);
	physics->enablePhysics(false);
	collisions = new CollisionComponent(pos);
}

SpriteGameObject::~SpriteGameObject()
{

}

void SpriteGameObject::Tick(GameData* _GD)
{
	if (collisions)
	{
		collisions->SetPos(pos);
		collisions->Tick(_GD);
	}

	if(physics)
		physics->tick(_GD);

	if (!sprite)
		return;

	center_pos = Vector2(pos.x + _GD->TILE_WIDTH / 2, pos.y + _GD->TILE_HEIGHT / 2);
}

void SpriteGameObject::Draw(DrawData2D* _DD)
{
	if (sprite && visible)
		_DD->sprite_batch->Draw(sprite->getResourceView(), pos, rect, color, rot, origin, scale, SpriteEffects_None);
}

Sprite* SpriteGameObject::GetSprite() const
{
	return sprite;
}

void SpriteGameObject::SetSprite(Sprite* _sprite)
{
	sprite = _sprite;
}

Sprite* SpriteGameObject::LoadSprite(const std::string& file_name)
{

	/*Sprite* L"..\\Assets\\calibri.spritefont"

	// Construct a new texture if one is not associated with the key.
	auto texture = std::make_unique<Texture>(file_name, d3d_device);
	auto p_texture = texture.get();

	textures[file_name] = std::move(texture);*/
	Sprite* p_texture;
	return p_texture;
}

void SpriteGameObject::CenterOrigin()
{
	if (sprite)
		origin = Vector2(static_cast<float>(sprite->getWidth()) / 2,
			static_cast<float>(sprite->getHeight()) / 2);
}

bool SpriteGameObject::IsVisible() const
{
	return visible;
}

void SpriteGameObject::SetVisible(bool _visible)
{
	visible = _visible;
}

RECT* SpriteGameObject::GetRect() const
{
	return rect;
}

void SpriteGameObject::SetRect(RECT* _rect)
{
	rect = _rect;
}

PhysicsComponent * SpriteGameObject::GetPhysics() const
{
	return physics;
}

CollisionComponent * SpriteGameObject::GetCollisions() const
{
	return collisions;
}
