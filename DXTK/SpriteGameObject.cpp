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
	physics = new PhysicsComponent(pos, Vector2(0, 1.5f), 0.1f, 100.0f);
	physics->enableGravity(false);
	physics->enablePhysics(false);
	collisions = new CollisionComponent(pos, 0, 64, 0, 64);
}

SpriteGameObject::~SpriteGameObject()
{

}

void SpriteGameObject::Tick(GameData* _GD)
{
	if (collisions)
		collisions->Tick(_GD);

	if(physics)
		physics->tick(_GD);

	if (!sprite)
		return;
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

PhysicsComponent * SpriteGameObject::getPhysics() const
{
	return physics;
}

CollisionComponent * SpriteGameObject::getCollisions() const
{
	return collisions;
}
