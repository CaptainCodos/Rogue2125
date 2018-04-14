#include "cmp_actor_stats.h"
#include "cmp_inventory.h"
#include "cmp_skills.h"
#include "cmp_player_movement.h"
#include "cmp_actor_move.h"

#include "cmp_sprite.h"
//#include "cmp_physics.h"

#include "system_physics.h"
//#include <Box2D/Dynamics/b2Body.h>

using namespace std;
using namespace sf;

using namespace Physics;
using namespace DataShapes;

ActorStatsComponent::ActorStatsComponent(Entity* p)
	: Component(p)
{
	_parent->addTag("Actor");
	m_moveComp = _parent->addComponent<ActorMoveComp>();

	float s = 20.0f;
	m_circle = Circle(s / 2.0f, p->getPosition());
	m_rect = Rectangle(p->getPosition(), Vector2f(s, s));
	m_rect.SetPosCentre(p->getPosition());
	//m_rect.SetSize(Vector2f(20.0f, 20.0f));

	for (int i = 0; i < 5; i++)
	{
		m_resistances[i] = 0.0f;
	}

	m_isInvincible = false;
	m_isDynamic = true;
	m_isPhysical = true;

	m_hp = 100.0f;

	GenerateStats(0);
}

int ActorStatsComponent::GetID() { return m_actorID; }
int ActorStatsComponent::GetSecID() { return m_secID; }
shared_ptr<ActorMoveComp> ActorStatsComponent::GetMoveComp() { return m_moveComp; }
Circle ActorStatsComponent::GetCircle() { return m_circle; }
Rectangle ActorStatsComponent::GetRect() { return m_rect; }
Vector2i ActorStatsComponent::GetCoords() { return m_actorCoords; }
Vector2f ActorStatsComponent::GetTrueCoords() { return _parent->getPosition(); }

void ActorStatsComponent::SetPosition(Vector2f pos) { _parent->setPosition(pos); }

void ActorStatsComponent::update(double dt)
{
	m_circle.pos = _parent->getPosition();
	m_rect.SetPosCentre(_parent->getPosition());
	Vector2f pPos = _parent->getPosition();
	m_actorCoords = Vector2i(pPos.x / 32, pPos.y / 32);

	if (m_hp <= 0.0f)
	{
		OnDeath();
		_parent->setForDelete();
	}

	m_oldCoords = m_actorCoords;
}

void ActorStatsComponent::render()
{

}

void ActorStatsComponent::ApplyDamage(float dmg, vector<int> dmgTypes)
{
	if (m_isInvincible)
		return;

	if (m_actorID == 0)
	{
		for (int i = 0; i < dmgTypes.size(); i++)
		{
			float iDmg = dmg / dmgTypes.size();

			vector<shared_ptr<Equipment>> eq = _parent->GetCompatibleComponent<InventoryComponent>()[0]->GetEquipped();
			float totalRes = 0.0f;
			for (int k = 0; k < eq.size(); k++)
			{
				totalRes += (m_resistances[dmgTypes[i]] * (1.0f + (0.04f * _parent->GetCompatibleComponent<SkillsComponent>()[0]->GetTotalSkill(eq, 5 + dmgTypes[i])))) + eq[k]->GetResistMod(dmgTypes[i]);
			}

			if (totalRes > 0.8f)
				totalRes = 0.8f;
			else if (totalRes < -0.5f)
				totalRes = -0.5f;

			m_hp -= iDmg * (1.0f - totalRes);
		}
	}
	else
	{
		for (int i = 0; i < dmgTypes.size(); i++)
		{
			float iDmg = dmg / dmgTypes.size();

			float totalRes = m_resistances[dmgTypes[i]];

			m_hp -= iDmg * (1.0f - totalRes);
		}
	}

	if (m_hp <= 0.0f)
	{
		OnDeath();
		_parent->setForDelete();
	}
}

void ActorStatsComponent::GenerateStats(int ID)
{
	m_actorID = ID;

	shared_ptr<SkillsComponent> a;
	shared_ptr<InventoryComponent> b;
	shared_ptr<PlayerMoveComp> c;

	//int secID = 0;

	switch (ID)
	{
	case 0:
		a = _parent->addComponent<SkillsComponent>();
		b = _parent->addComponent<InventoryComponent>();
		c = _parent->addComponent<PlayerMoveComp>(m_moveComp, b, a);

		_parent->addTag("Player");
		break;
	case 1:
		_parent->addTag("Enemy");

		m_secID = RandomInt(0, 3);
		break;
	case 2:
		_parent->addTag("Interactable");

		m_secID = RandomInt(0, 3);
		break;
	case 3:
		_parent->addTag("World");

		m_isInvincible = true;
		m_isDynamic = false;

		m_secID = RandomInt(0, 4);

		switch (m_secID)
		{
		case 0:
			m_isPhysical = false;
			break;
		case 1:
			m_isInvincible = false;
			m_hp *= 10.0f;


			break;
		case 2:

			break;
		case 3:

			break;
		}

		break;
	}
}

void ActorStatsComponent::GeneratePlayerStats()
{
	m_resistances[0] = 0.15f;
	m_resistances[1] = 0.1f;
	m_resistances[2] = 0.05f;
	m_resistances[3] = 0.0f;
	m_resistances[4] = 0.1f;
}

void ActorStatsComponent::GenerateEnemyStats()
{

}

void ActorStatsComponent::GenerateWObjStats()
{

}

void ActorStatsComponent::OnDeath()
{

}