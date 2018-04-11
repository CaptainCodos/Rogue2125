#include "cmp_tank_section.h"

using namespace std;

TankSection::TankSection(Entity* p, shared_ptr<Equipment> item, shared_ptr<SkillsComponent> skills)
	: AnimComponent(p)
{
	m_item = item;
	m_skills = skills;
}

void TankSection::update(double dt)
{
	AnimComponent::update(dt);

	if (m_item->GetPriID() == 0 && m_item->GetSecID() == 0)
	{
		shared_ptr<TankGun> gun = static_pointer_cast<TankGun>(m_item);

		gun->update(dt);

		if (gun->GetFired())
		{
			DmgData data = gun->GetShotData();
		}
	}
}