#pragma once

#include "cmp_sprite.h"
#include "cmp_inventory.h"
//#include "../general/equipment.h"
#include "cmp_skills.h"

class TankSection : public AnimComponent
{
public:
	TankSection() = delete;
	TankSection(Entity* p, std::shared_ptr<Equipment> item, std::shared_ptr<SkillsComponent> skills);
	~TankSection() = default;

	void update(double dt) override;
	//void SetSection(std::shared_ptr<Equipment> part);
protected:

private:
	//std::shared_ptr<InventoryComponent> m_inventory;
	std::shared_ptr<Equipment> m_item;
	std::shared_ptr<SkillsComponent> m_skills;
};