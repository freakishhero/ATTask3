#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(Vector2& _pos, Vector2 _gravity, float _dampening, float _max_speed)
	: pos(_pos)
{
	m_gravity = _gravity;
	m_dampening = _dampening;
	m_max_speed = _max_speed;

	/* ensures that dampening is always between
	0 & one or 'a sensible value'*/
	if (m_dampening < 0 || m_dampening > 1)
	{
		m_dampening = 0.5f;
	}
}

Vector2 PhysicsComponent::getVelocity() const
{
	return m_velocity;
}

void PhysicsComponent::setVelocity(Vector2 _velocity)
{
	m_velocity = _velocity;
}

Vector2 PhysicsComponent::getAcceleration() const
{
	return m_acceleration;
}

void PhysicsComponent::setAcceleration(Vector2 _acceleration)
{
	m_acceleration = _acceleration;
}

void PhysicsComponent::modifyPos(Vector2 direction)
{
	pos += direction;
}

bool PhysicsComponent::gravityEnabled() const
{
	return gravity_enabled;
}

void PhysicsComponent::enableGravity(bool state)
{
	/* toggles whether the attached object
	is using gravity*/
	gravity_enabled = state;
}

bool PhysicsComponent::physicsEnabled() const
{
	return physics_enabled;
}

void PhysicsComponent::enablePhysics(bool state)
{
	/* toggles whether the attached object
	is using the physics component*/
	physics_enabled = state;
}

void PhysicsComponent::tick(GameData* _GD)
{
	// checks that hte object is using physics
	if (physics_enabled)
	{
		//applies basic velocity and acceleration
		m_velocity += m_acceleration * _GD->delta_time;
		m_acceleration *= (1 - m_dampening);

		//Stops the object from reaching too high speeds
		if (m_velocity.Length() > m_max_speed || m_velocity.Length() < -m_max_speed)
		{
			m_velocity.Normalize();
			m_velocity *= m_max_speed;
		}

		// Checks that the object adheres to gravity
		if (gravity_enabled)
		{
			//applies gravity to the object
			m_velocity += m_gravity * _GD->delta_time;
		}
		//repositions the object
		pos += m_velocity;
	}
}

void PhysicsComponent::addForce(Vector2 _direction)
{
	/*
	0,1 = up
	0,-1 = down
	1,0 = right
	-1,0 = left;
	*/

	//applies a force to the object in a specific direction
	m_velocity += _direction;
	m_acceleration += m_velocity;
}