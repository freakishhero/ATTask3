#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(Vector2 _position)
{
	pos = _position;
}

Vector2 CollisionComponent::GetPos() const
{
	return pos;
}

void CollisionComponent::SetPos(Vector2 _pos)
{
	pos = _pos;
}

short CollisionComponent::GetTop() const
{
	return top;
}

short CollisionComponent::GetBottom() const
{
	return bottom;
}

short CollisionComponent::GetLeft() const
{
	return left;
}

short CollisionComponent::GetRight() const
{
	return right;
}

void CollisionComponent::Tick(GameData * _GD)
{
	top = pos.y;
	bottom = pos.y + _GD->TILE_HEIGHT;
	left = pos.x;
	right = pos.x + _GD->TILE_WIDTH;
}