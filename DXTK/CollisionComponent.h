#pragma once
#include <d3d11.h>
#include "SimpleMath.h"
#include "GameData.h"

using namespace DirectX;
using namespace SimpleMath;

class CollisionComponent
{
public:
	CollisionComponent(Vector2 _position);
	~CollisionComponent() = default;

	short GetTop() const;
	short GetBottom() const;
	short GetLeft() const;
	short GetRight() const;
	void Tick(GameData* _GD);
	Vector2 GetPos() const;
	void SetPos(Vector2 _pos);

private:
	short top = 0;
	short left = 0;
	short right = 0;
	short bottom = 0;
	Vector2 pos = Vector2::Zero;
};