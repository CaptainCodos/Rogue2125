#include "cmp_attack.h"
#include <AllMgrs.h>

using namespace std;
using namespace sf;

using namespace DataShapes;

AttackComponent::AttackComponent(Entity* p, DmgData data) 
	: AnimComponent(p)
{
	_parent->addTag("Attack");
	m_circle = Circle(4.0f, p->getPosition());

	m_data = data;
	m_life = 20.0f;
	
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

	std::vector<sf::Uint8> colors;

	for (int i = 0; i < m_data.types.size(); i++)
	{
		colors.push_back(TextureMgr::GetInstance()->colors_Elements[m_data.types[i]].r);
		colors.push_back(TextureMgr::GetInstance()->colors_Elements[m_data.types[i]].g);
		colors.push_back(TextureMgr::GetInstance()->colors_Elements[m_data.types[i]].b);
	}

	sf::Color finalC = sf::Color(0, 0, 0, 255);

	for (int i = 0; i < m_data.types.size(); i++)
	{
		int itr = i * 3;

		finalC.r += colors[itr] / m_data.types.size();
		finalC.b += colors[itr + 1] / m_data.types.size();
		finalC.g += colors[itr + 2] / m_data.types.size();
	}
	//finalC.r *= 1.5f;
	//finalC.g *= 1.5f;
	//finalC.b *= 1.5f;
	SetColor(finalC);

	_parent->setRotation(data.angle);
}

int AttackComponent::GetSenderID() { return m_data.actorID; }
Circle AttackComponent::GetCircle() { return m_circle; }

void AttackComponent::update(double dt)
{
	_parent->setPosition(_parent->getPosition() + (m_data.vel * 32.0f * (float)dt));
	m_circle.pos = _parent->getPosition();
	m_life -= dt;

	if (m_life <= 0.0f)
		_parent->setForDelete();

	AnimComponent::update(dt);
}