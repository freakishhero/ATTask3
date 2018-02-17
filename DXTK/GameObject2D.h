#pragma once
#include <d3d11_1.h>
#include "SimpleMath.h"
//#include "CollisionComponent.h"
//#include "PhysicsComponent.h"
//#include "ObjectTag.h"

using namespace DirectX;
using namespace SimpleMath;

struct GameData;
struct DrawData2D;

class GameObject2D
{
public:
	GameObject2D();
	virtual ~GameObject2D() = default;

	virtual void Tick(GameData* _GD) { }
	virtual void Draw(DrawData2D* _DD) {}

	//getters
	Vector2 GetPos() const;
	Vector2 GetCenterPos() const;
	float GetRot() const;
	Color GetColor() const;
	Vector2 GetScale() const;
	Vector2 GetOrigin() const;
	//ObjectTag getObjectTag() const;

	//setters
	virtual void SetPos(const Vector2& _pos);
	void ModifyPos(const Vector2& _pos);
	void SetRot(const float _rot);
	void SetColour(const Color& _colour);
	void SetScale(const Vector2& _scale);
	void SetScale(const float _scale);
	void SetOrigin(const Vector2& _origin);
	//void setObjectTag(const ObjectTag& _tag);
	//PhysicsComponent* getPhysics() const;
	//CollisionComponent* getBoundingBox() const;

protected:
	Vector2 pos;
	Vector2 center_pos;
	float rot;
	Vector2 scale;
	Color color;
	Vector2 origin;
	//ObjectTag object_tag;
	//PhysicsComponent* physics;
	//CollisionComponent* collisions;

};
