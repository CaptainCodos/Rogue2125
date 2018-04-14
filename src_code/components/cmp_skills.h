#pragma once

#include "ecm.h"

#include "../general/equipment.h"

class SkillsComponent : public Component
{
public:
	SkillsComponent() = delete;
	SkillsComponent(Entity* p);
	~SkillsComponent() = default;

	void update(double dt) override;
	void render() override;

	int GetTotalSkill(std::vector<std::shared_ptr<Equipment>> equip, int ID);
	void LevelUp();
	void AddSkillPoint();
protected:

private:
	int m_level;
	int m_reqXP;
	int m_xp;
	int m_skillPts;

	Skill m_skills[10];
};