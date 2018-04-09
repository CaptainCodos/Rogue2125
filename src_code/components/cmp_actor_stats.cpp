#include "cmp_actor_stats.h"
#include "cmp_text.h"

using namespace std;
using namespace sf;

ActorStatsComponent::ActorStatsComponent(Entity* p) 
	: Component(p)
{
	m_resistances[5] = { 0.0f };

	m_isInvincible = false;

	OnDeath();
}

void ActorStatsComponent::update(double dt)
{
	if (m_hp <= 0.0f)
	{
		OnDeath();
		_parent->setForDelete();
	}
}

void ActorStatsComponent::render()
{

}

void ActorStatsComponent::ApplyDamage(float dmg, vector<int> dmgTypes)
{
	if (m_isInvincible)
		return;
}

void ActorStatsComponent::GenerateStats(char ID)
{
	m_actorID = ID;

	switch (ID)
	{
	case 0:

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