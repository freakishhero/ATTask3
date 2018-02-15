#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(Vector2 _position, float _top, float _bottom, float _left, float _right)
{
	top = _top;
	bottom = _bottom;
	left = _left;
	right = _right;
	pos = _position;
}

Vector2 CollisionComponent::getPos()
{
	return pos;
}

void CollisionComponent::setPos(Vector2 _pos)
{
	pos = _pos;
}

short CollisionComponent::getTop()
{
	return top;
}

short CollisionComponent::getBottom()
{
	return bottom;
}

short CollisionComponent::getLeft()
{
	return left;
}

short CollisionComponent::getRight()
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

void CollisionComponent::setDimensions(float _top, float _bottom, float _left, float _right)
{
	top = _top;
	bottom = _bottom;
	left = _left;
	right = _right;
}