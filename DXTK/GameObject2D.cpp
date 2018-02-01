#include "GameObject2D.h"

GameObject2D::GameObject2D()
	: pos(Vector2::Zero)
	, rot(0)
	, scale(Vector2::One)
	, color(Color(1.0f, 1.0f, 1.0f, 1.0f))
	, origin(Vector2::Zero)
	//, physics(nullptr)
	//, collisions(nullptr)
{
	//physics = new PhysicsComponent(pos, Vector2(0, 1.5f), 0.1f, 0.9);
	//physics->enableGravity(false);
	//physics->enablePhysics(false);
	//collisions = new CollisionComponent(pos, 0, 60, 0, 60);
}

Vector2 GameObject2D::GetPos() const
{
	return pos + origin;
}

float GameObject2D::GetRot() const
{
	return rot;
}

Color GameObject2D::GetColor() const
{
	return color;
}

Vector2 GameObject2D::GetScale() const
{
	return scale;
}

Vector2 GameObject2D::GetOrigin() const
{
	return origin;
}

void GameObject2D::SetPos(const Vector2& _pos)
{
	pos = _pos;
}

void GameObject2D::ModifyPos(const Vector2& _pos)
{
	pos += _pos;
}

void GameObject2D::SetRot(const float _rot)
{
	rot = _rot;
}

void GameObject2D::SetColour(const Color& _colour)
{
	color = _colour;
}

void GameObject2D::SetScale(const Vector2& _scale)
{
	scale = _scale;
}

void GameObject2D::SetScale(const float _scale)
{
	scale = _scale * Vector2::One;
}

void GameObject2D::SetOrigin(const Vector2& _origin)
{
	origin = _origin;
}
