#include "cmp_actor_stats.h"
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


	/*auto eC = _parent->addComponent<ShapeComponent>();
	eC->setShape<CircleShape>(15.0f, 20);
	eC->getShape().setOrigin(Vector2f(15.0f, 15.0f));*/
}

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