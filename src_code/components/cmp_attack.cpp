#include "cmp_attack.h"
#include <AllMgrs.h>

AttackComponent::AttackComponent(Entity* p, DmgData data) 
	: AnimComponent(p)
{
	m_data = data;
	
	switch (m_data.actorID)
	{
	case 0:
		SetTexture(TextureMgr::GetInstance()->sheet_Projectiles[0], 32);
		break;
	case 1:
		SetTexture(TextureMgr::GetInstance()->sheet_Projectiles[0], 32);
		break;
	case 2:
		SetTexture(TextureMgr::GetInstance()->sheet_Projectiles[0], 32);
		break;
	}

	SetOrigin(sf::Vector2f(0.5f, 0.5f));

	int colors[3] = { 0, 0, 0 };

	for (int i = 0; i < m_data.types.size(); i++)
	{
		colors[0] += TextureMgr::GetInstance()->colors_Elements[m_data.types[i]].r;
		colors[1] += TextureMgr::GetInstance()->colors_Elements[m_data.types[i]].g;
		colors[2] += TextureMgr::GetInstance()->colors_Elements[m_data.types[i]].b;
	}

	for (int i = 0; i < 3; i++)
	{
		colors[0] /= m_data.types.size();
		colors[1] /= m_data.types.size();
		colors[2] /= m_data.types.size();
	}

	SetRotation(m_data.angle);
}

void AttackComponent::update(double dt)
{
	_parent->setPosition(_parent->getPosition() + (m_data.vel * 32.0f * (float)dt));
}