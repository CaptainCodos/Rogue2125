#pragma once

#include "ecm.h"
#include "cmp_inventory.h"
#include "cmp_skills.h"

class PlayerMoveComp : public Component
{
public:
	PlayerMoveComp() = delete;
	PlayerMoveComp(Entity* p, std::shared_ptr<InventoryComponent> inv, std::shared_ptr<SkillsComponent> skills);
	~PlayerMoveComp() = default;

	void update(double dt) override;
	void render() override;
protected:

private:
	std::shared_ptr<InventoryComponent> m_inv;
	std::shared_ptr<SkillsComponent> m_skills;

	float m_baseMaxSpeed;

	sf::Vector2f m_vel;
	sf::Vector2f m_accel;
	sf::Vector2f m_drag;

	float GetMaxSpeed();
	sf::Vector2f CalculateAccel(float max);
};