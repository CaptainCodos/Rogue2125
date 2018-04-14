#include "cmp_actor_move.h"

using namespace std;
using namespace sf;

ActorMoveComp::ActorMoveComp(Entity* p) 
	: Component(p)
{
	m_vel = Vector2f(0.0f, 0.0f);
	m_accel = Vector2f(0.0f, 0.0f);
	m_drag = Vector2f(0.0f, 0.0f);

	m_baseMaxSpeed = 4.0f;
	m_maxSpeed = 4.0f;
}

void ActorMoveComp::SetMaxSpeed(float speed) { m_maxSpeed = speed; }
void ActorMoveComp::SetBaseMaxSpeed(float speed) { m_baseMaxSpeed = speed; }

float ActorMoveComp::GetBaseMaxSpeed() { return m_baseMaxSpeed; }
Vector2f& ActorMoveComp::GetVelRef() { return m_vel; }
Vector2f ActorMoveComp::GetVel() { return m_vel; }
Vector2f& ActorMoveComp::GetAccel() { return m_accel; }

void ActorMoveComp::update(double dt)
{
	_parent->setPosition(_parent->getPosition() + (m_vel * (float)dt));

	if (length(m_accel) > 1.0f)
	{
		normalize(m_accel);
		m_accel = m_accel * 2.0f * m_maxSpeed;
	}
	else
	{
		m_accel = m_accel * 2.0f * m_maxSpeed;
	}

	m_vel += CalculateAccel(m_maxSpeed) * (float)dt;
	if (length(m_vel) > m_maxSpeed)
	{
		m_vel = normalize(m_vel);
		m_vel = m_vel * m_maxSpeed;
	}

	if (length(m_vel) < 0.5f)
	{
		m_vel.x = 0.0f;
		m_vel.y = 0.0f;
	}
}

void ActorMoveComp::render() {}

Vector2f ActorMoveComp::CalculateAccel(float max)
{
	float drag = pow(length(m_vel) / sqrt(max), 3.0f);
	m_drag = -normalize(m_vel) * drag;

	if (length(m_drag) < 60.0f && length(m_vel) > 0.2f)
	{
		m_drag = normalize(m_drag);
		m_drag = m_drag * 60.0f;
	}

	return m_accel + m_drag;
}