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

	short GetTop();
	short GetBottom();
	short GetLeft();
	short GetRight();
	void Tick(GameData* _GD);
	Vector2 GetPos();
	void SetPos(Vector2 _pos);
	void SetDimensions(float _top, float _bottom, float _left, float _right);

private:
	float top = 0.0f;
	float left = 0.0f;
	float right = 64.0f;
	float bottom = 64.0f;
	Vector2 pos;
};