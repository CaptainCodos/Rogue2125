#include "cmp_tank_section.h"
#include "cmp_actor_stats.h"
#include <AllMgrs.h>

using namespace std;

TankSection::TankSection(Entity* p, shared_ptr<Equipment> item, shared_ptr<SkillsComponent> skills)
	: AnimComponent(p)
{
	m_item = item;
	m_skills = skills;

	SetTexture(TextureMgr::GetInstance()->sheet_Items[m_item->GetPriID()][m_item->GetSecID()], 32);
	SetColor(m_item->GetColor());
	SetOrigin(Vector2f(0.5f, 0.5f));
}

void TankSection::update(double dt)
{
	SetTexture(TextureMgr::GetInstance()->sheet_Items[m_item->GetPriID()][m_item->GetSecID()], 32);
	SetColor(m_item->GetColor());

	AnimComponent::basicUpdate(dt);

	m_sprite->setPosition(_parent->getPosition());

	if (m_item->GetPriID() == 0 && m_item->GetSecID() == 0)
	{
		shared_ptr<TankGun> gun = static_pointer_cast<TankGun>(m_item);

		gun->update(dt);

		if (gun->GetFired())
		{
			DmgData data = gun->GetShotData();
			data.actorID = _parent->GetCompatibleComponent<ActorStatsComponent>()[0]->GetID();

			data.vel = Vector2f(sin(GetSpriteAng()), cos(GetSpriteAng())) * 6.0f;
			data.angle = GetSpriteAng();

			Vector2f offset = normalize(data.vel) * 16.0f;


			shared_ptr<Entity> a = _parent->scene->makeEntity();
			a->setPosition(_parent->getPosition() + offset);
			a->addComponent<AttackComponent>(data);
		}
	}
}