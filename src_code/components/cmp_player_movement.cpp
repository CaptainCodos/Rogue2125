#include "cmp_player_movement.h"
#include "maths.h"

using namespace std;
using namespace sf;

PlayerMoveComp::PlayerMoveComp(Entity* p, shared_ptr<InventoryComponent> inv, shared_ptr<SkillsComponent> skills) 
	: Component(p)
{
	m_inv = inv;
	m_skills = skills;
	m_baseMaxSpeed = 5.0f;

	m_vel = Vector2f(0.0f, 0.0f);
}

void PlayerMoveComp::update(double dt)
{
	Vector2f axis = Vector2f(Input::GetAxisValue(0), Input::GetAxisValue(1));
	float maxSpeed = GetMaxSpeed();

	if (axis.x != 0.0f)
		m_accel.x = axis.x;
	else
		m_accel.x = 0.0f;
	
	if (axis.y != 0.0f)
		m_accel.y = axis.y;
	else
		m_accel.y = 0.0f;

	normalize(m_accel);
	m_accel = m_accel * 2.0f * maxSpeed;

	m_vel += CalculateAccel(maxSpeed) * (float)dt;
	_parent->setPosition(_parent->getPosition() + (m_vel * (float)dt));

	cout << "X: " << (int)_parent->getPosition().x << " Y: " << (int)_parent->getPosition().y;
	cout << " vX: " << (int)m_vel.x << " vY: " << (int)m_vel.y << "\n";
}

void PlayerMoveComp::render()
{

}

Vector2f PlayerMoveComp::CalculateAccel(float max)
{
	float drag = pow(length(m_vel) / sqrt(max), 2.0f);
	m_drag = -normalize(m_vel) * drag;

	if (length(m_drag) < 15.0f && length(m_vel) > 0.1f)
	{
		m_drag = normalize(m_drag);
		m_drag = m_drag * 15.0f;
	}

	return m_accel + m_drag;
}

float PlayerMoveComp::GetMaxSpeed()
{
	vector<shared_ptr<Equipment>> all = m_inv->GetEquipped();
	shared_ptr<Equipment> e = all[3];
	return ((m_baseMaxSpeed * (1.0f + (m_skills->GetTotalSkill(all, 4) / 20.0f))) + e->GetStatsMod(3)) * 32.0f;
}