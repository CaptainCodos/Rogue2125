#include "cmp_actor_stats.h"
#include "cmp_inventory.h"
#include "cmp_skills.h"
#include "cmp_player_movement.h"

#include "cmp_sprite.h"
#include "cmp_physics.h"
#include "system_physics.h"
//#include <Box2D/Dynamics/b2Body.h>

using namespace std;
using namespace sf;

using namespace Physics;

ActorStatsComponent::ActorStatsComponent(Entity* p) 
	: Component(p)
{
	for (int i = 0; i < 5; i++)
	{
		m_resistances[i] = 0.0f;
	}

	m_isInvincible = false;

	GenerateStats(0);
}

int ActorStatsComponent::GetID() { return m_actorID; }

void ActorStatsComponent::update(double dt)
{
	
}

void ActorStatsComponent::render()
{

}

void ActorStatsComponent::ApplyDamage(float dmg, vector<int> dmgTypes)
{
	if (m_isInvincible)
		return;

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
	switch (ID)
	{
	case 0:
		a = _parent->addComponent<SkillsComponent>();
		b = _parent->addComponent<InventoryComponent>();
		c = _parent->addComponent<PlayerMoveComp>(b, a);
		break;
	case 1:

		break;
	case 2:

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