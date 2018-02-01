#include "GameObject.h"
#include "GameData.h"

GameObject::GameObject()
	: world_mat(Matrix::Identity)
	, rot_mat(Matrix::Identity)
	, fudge(Matrix::Identity)
	, pos(Vector3::Zero)
	, scale(Vector3::One)
	, yaw(0)
	, pitch(0)
	, roll(0)
	, physics_on(false)
	, drag(0)
	, velocity(Vector3::Zero)
	, acceleration(Vector3::Zero)
{
}


void GameObject::Tick(GameData* _GD)
{
	if (physics_on)
	{
		Vector3 newVel = velocity + _GD->delta_time * (acceleration - drag*velocity);
		Vector3 newPos = pos + _GD->delta_time * velocity;

		velocity = newVel;
		pos = newPos;
	}

	//build up the world matrix depending on the new position of the GameObject
	//the assumption is that this class will be inherited by the class that ACTUALLY changes this
	Matrix  scaleMat = Matrix::CreateScale(scale);
	rot_mat = Matrix::CreateFromYawPitchRoll(yaw, pitch, roll); //possible not the best way of doing this!
	Matrix  transMat = Matrix::CreateTranslation(pos);

	world_mat = fudge * scaleMat * rot_mat * transMat;

	//zero acceleration ready for the next time round
	acceleration = Vector3::Zero;
}


Vector3 GameObject::GetPos() const
{
	return pos;
}


Vector3 GameObject::GetScale() const
{
	return scale;
}

Matrix GameObject::GetWorldMat() const
{
	return world_mat;
}

float GameObject::GetPitch() const
{
	return pitch;
}


float GameObject::GetYaw() const
{
	return yaw;
}


float GameObject::GetRoll() const
{
	return roll;
}


bool GameObject::IsPhysicsOn() const
{
	return physics_on;
}


float GameObject::GetDrag() const
{
	return drag;
}


void GameObject::SetPos(Vector3 _pos)
{
	pos = _pos;
}


void GameObject::SetScale(float _scale)
{
	scale = _scale * Vector3::One;
}


void GameObject::SetScale(float _x, float _y, float _z)
{
	scale = Vector3(_x, _y, _z);
}


void GameObject::SetScale(Vector3 _scale)
{
	scale = _scale;
}


void GameObject::SetYaw(float _yaw)
{
	yaw = _yaw;
}


void GameObject::SetPitch(float _pitch)
{
	pitch = _pitch;
}


void GameObject::SetYawPitchRoll(float _yaw, float _pitch, float _roll)
{
	yaw = _yaw;
	pitch = _pitch;
	roll = _roll;
}


void GameObject::SetPhysicsOn(bool _physics)
{
	physics_on = _physics;
}


void GameObject::TogglePhysics()
{
	physics_on = !physics_on;
}


void GameObject::SetDrag(float _drag)
{
	drag = _drag;
}


void GameObject::SetRoll(float _roll)
{
	roll = _roll;
}
