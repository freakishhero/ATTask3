#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(Vector2 _position, float _top, float _bottom, float _left, float _right)
{
	top = _top;
	bottom = _bottom;
	left = _left;
	right = _right;
	pos = _position;
}

Vector2 CollisionComponent::GetPos()
{
	return pos;
}

void CollisionComponent::SetPos(Vector2 _pos)
{
	pos = _pos;
}

short CollisionComponent::GetTop()
{
	return top;
}

short CollisionComponent::GetBottom()
{
	return bottom;
}

short CollisionComponent::GetLeft()
{
	return left;
}

short CollisionComponent::GetRight()
{
	return right;
}

void CollisionComponent::Tick(GameData * _GD)
{
	top = pos.y;
	bottom = pos.y;
	left = pos.x;
	right = pos.x;
}

void CollisionComponent::SetDimensions(float _top, float _bottom, float _left, float _right)
{
	top = _top;
	bottom = _bottom;
	left = _left;
	right = _right;
}