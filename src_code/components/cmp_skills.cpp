#include "cmp_skills.h"

using namespace std;

SkillsComponent::SkillsComponent(Entity* p)
	: Component(p)
{
	for (int i = 0; i < 10; i++)
	{
		m_skills[i] = Skill("", "", i, 0);
		m_skills[i].AutoGenSkill();
	}
}

void SkillsComponent::update(double dt)
{
	if (m_xp >= m_reqXP)
		LevelUp();
}

void SkillsComponent::render()
{

}

int SkillsComponent::GetTotalSkill(vector<shared_ptr<Equipment>> equip, int ID)
{
	int base = m_skills[ID].GetVal();

	for (int i = 0; i < equip.size(); i++)
	{
		base += equip[i]->GetBuff(ID);
	}

	return base;
}

void SkillsComponent::LevelUp()
{
	int diff = m_xp - m_reqXP;
	m_xp = diff;

	m_skillPts += 2;
	m_level++;

	m_reqXP = 100 * pow(1.15f, m_level - 1);
}