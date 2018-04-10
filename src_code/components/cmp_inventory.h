#pragma once
#include "ecm.h"
#include "../general/item.h"
#include "../general/equipment.h"
#include "../general/skill.h"

class InventoryComponent : public Component
{
public:
	InventoryComponent(Entity* p);
	~InventoryComponent() = default;

	void SaveInventory();
	void LoadInventory();
protected:

private:
	int m_width;
	int m_height;

	std::shared_ptr<TankGun> m_guns[7];
	std::shared_ptr<TankHead> m_heads[7];
	std::shared_ptr<TankBody> m_bodies[7];
	std::shared_ptr<TankEngine> m_engines[7];

	std::shared_ptr<Useable> m_useables[7][7];
};