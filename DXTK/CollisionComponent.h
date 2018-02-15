#pragma once
#include <d3d11.h>
#include "SimpleMath.h"
#include "GameData.h"

using namespace DirectX;
using namespace SimpleMath;

class CollisionComponent
{
public:
	CollisionComponent(Vector2 _pos, float _top, float _bottom, float _left, float _right);
	~CollisionComponent() = default;

	short getTop();
	short getBottom();
	short getLeft();
	short getRight();
	void Tick(GameData* _GD);
	Vector2 getPos();
	void setPos(Vector2 _pos);
	void setDimensions(float _top, float _bottom, float _left, float _right);

private:
	float top = 0.0f;
	float left = 0.0f;
	float right = 60.0f;
	float bottom = 60.0f;
	Vector2 pos;
};