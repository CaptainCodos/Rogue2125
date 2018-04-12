#pragma once

#include "ecm.h"
#include "cmp_inventory.h"
#include "cmp_skills.h"
#include "cmp_tank_section.h"

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
	std::shared_ptr<TankSection> m_gun;
	std::shared_ptr<TankSection> m_head;
	std::shared_ptr<TankSection> m_body;
	std::shared_ptr<TankSection> m_engine;

	sf::View m_camera;

	float m_baseMaxSpeed;
	float m_rot;

	sf::Vector2f m_vel;
	sf::Vector2f m_accel;
	sf::Vector2f m_drag;

	float GetMaxSpeed();
	sf::Vector2f CalculateAccel(float max);
	void RotateBody();
	void RotateHead();
};