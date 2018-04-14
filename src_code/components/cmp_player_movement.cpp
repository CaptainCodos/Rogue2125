#include "cmp_player_movement.h"
#include "maths.h"
#include "engine.h"

using namespace std;
using namespace sf;

PlayerMoveComp::PlayerMoveComp(Entity* p, std::shared_ptr<ActorMoveComp> aMove, shared_ptr<InventoryComponent> inv, shared_ptr<SkillsComponent> skills)
	: Component(p)
{
	m_moveComp = aMove;
	m_inv = inv;
	m_skills = skills;
	m_baseMaxSpeed = 4.0f;

	m_vel = Vector2f(0.0f, 0.0f);

	m_body = _parent->addComponent<TankSection>(inv->GetEquipped()[2], inv, skills);
	m_engine = _parent->addComponent<TankSection>(inv->GetEquipped()[3], inv, skills);
	m_head = _parent->addComponent<TankSection>(inv->GetEquipped()[1], inv, skills);
	m_gun = _parent->addComponent<TankSection>(inv->GetEquipped()[0], inv, skills);

	//m_body->SetFPS(12.0f);

	m_rot = 0.0f;

	m_camera = View(FloatRect(0, 0, 1600, 900));
	Engine::GetWindow().setView(m_camera);
}

void PlayerMoveComp::update(double dt)
{
	m_camera.setCenter(_parent->getPosition());

	float zoom = 1.0f;
	if (Input::GetKeyDown(Keyboard::E))
		zoom -= dt;
	if (Input::GetKeyDown(Keyboard::Q))
		zoom += dt;

	m_camera.zoom(zoom);

	Engine::GetWindow().setView(m_camera);

	Vector2f axis = Vector2f(Input::GetAxisValue(0), Input::GetAxisValue(1));
	float maxSpeed = GetMaxSpeed();
	m_moveComp->SetMaxSpeed(maxSpeed);

	if (axis.x != 0.0f)
		m_accel.x = axis.x;
	else
		m_accel.x = 0.0f;
	
	if (axis.y != 0.0f)
		m_accel.y = axis.y;
	else
		m_accel.y = 0.0f;

	if (length(m_accel) != 0.0f)
	{
		m_body->SetAnimates(true);
		m_engine->SetAnimates(true);
	}
	else
	{
		m_body->SetAnimates(false);
		m_engine->SetAnimates(false);
	}

	m_moveComp->GetAccel() = m_accel;

	/*if (length(m_accel) > 1.0f)
	{
		normalize(m_accel);
		m_accel = m_accel * 2.0f * maxSpeed;
	}
	else
	{
		m_accel = m_accel * 2.0f * maxSpeed;
	}*/
	
	/*m_vel += CalculateAccel(maxSpeed) * (float)dt;
	if (length(m_vel) > maxSpeed)
	{
		m_vel = normalize(m_vel);
		m_vel = m_vel * maxSpeed;
	}
*/
	if (length(m_moveComp->GetVel()) > 0.2f)
		RotateBody();

	if (Input::MouseInWindow())
		RotateHead();

	/*if (length(m_vel) < 0.5f)
	{
		m_vel.x = 0.0f;
		m_vel.y = 0.0f;
	}*/
}

void PlayerMoveComp::render()
{

}

Vector2f PlayerMoveComp::CalculateAccel(float max)
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

void PlayerMoveComp::RotateBody()
{
	Vector2f nV = normalize(m_moveComp->GetVel());
	float ang = atan2(nV.x, -nV.y) * 57.259f;

	m_body->SetRotation(ang - 180.0f);
	m_engine->SetRotation(ang);
}

void PlayerMoveComp::RotateHead()
{
	Vector2i p = Input::GetMouseRelativeToPos(Vector2i(800, 450));
	Vector2f nV = normalize(Vector2f(p.x, p.y));
	float ang = atan2(nV.x, -nV.y) * 57.259f;

	m_gun->SetRotation(ang);
	m_head->SetRotation(ang);
}

float PlayerMoveComp::GetMaxSpeed()
{
	vector<shared_ptr<Equipment>> all = m_inv->GetEquipped();
	shared_ptr<Equipment> e = all[3];
	return ((m_baseMaxSpeed * (1.0f + (m_skills->GetTotalSkill(all, 4) / 20.0f))) + e->GetStatsMod(3)) * 32.0f;
}