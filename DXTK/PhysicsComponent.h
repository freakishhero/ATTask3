#pragma once
#include <d3d11.h>
#include "SimpleMath.h"
#include "GameData.h"

using namespace DirectX;
using namespace SimpleMath;

class PhysicsComponent
{
public:

	PhysicsComponent(Vector2& _pos, Vector2 _gravity, float _dampening, float _max_speed);
	~PhysicsComponent() = default;

	void tick(GameData* _GD);
	void addForce(Vector2 _direction); //adds acceleration in a direction

	Vector2 getVelocity() const;
	void setVelocity(Vector2 _velocity); //sets velocity of an object

	Vector2 getAcceleration() const;
	void setAcceleration(Vector2 _acceleration); //sets acceleration of an object

	void modifyPos(Vector2 direction, GameData* _GD); //moves an object in a direction

	bool gravityEnabled() const;
	void enableGravity(bool state); //checks whether the object is using gravity

	bool physicsEnabled() const;
	void enablePhysics(bool state); //checks whether the object uses the physics component attached to it

private:
	Vector2 m_velocity;
	Vector2 m_acceleration;
	Vector2& pos;
	Vector2 m_gravity = Vector2::Zero;

	float m_dampening;
	float m_max_speed;

	bool gravity_enabled = true;
	bool physics_enabled = true;

};