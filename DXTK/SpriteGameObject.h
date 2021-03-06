#pragma once
#include "GameObject2D.h"

class Sprite;
class PhysicsComponent;
class CollisionComponent;

class SpriteGameObject : public GameObject2D
{
public:
	SpriteGameObject(Sprite* _texture = nullptr, RECT* _rect = nullptr);
	virtual ~SpriteGameObject();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData2D* _DD) override;

	Sprite* SpriteGameObject::LoadSprite(const std::string& file_name);
	Sprite* GetSprite() const;
	void SetSprite(Sprite* _sprite);
	void CenterOrigin();

	virtual bool IsVisible() const;
	virtual void SetVisible(bool _visible);

	PhysicsComponent* GetPhysics() const;
	CollisionComponent* GetCollisions() const;
	
protected:
	Sprite* sprite;
	bool visible;
	PhysicsComponent* physics;
	CollisionComponent* collisions;

};
