#pragma once
#include "ecm.h"
#include "../general/equipment.h"
#include "../general/skill.h"

class InventoryComponent : public Component
{
public:
	InventoryComponent(Entity* p);
	~InventoryComponent();

	void update(double dt) override;
	void render() override;

	void SaveInventory();
	void LoadInventory();
	void CreateInventory();
	void FlushInventory();

	void AddItem(std::shared_ptr<Item> item);
	void PrintAllItems();

	std::vector<std::shared_ptr<Equipment>> GetEquipped();
protected:

private:
	int m_width;
	int m_height;

	// Default parts when none are equipped
	std::shared_ptr<TankGun> m_defGun;
	std::shared_ptr<TankHead> m_defHead;
	std::shared_ptr<TankBody> m_defBody;
	std::shared_ptr<TankEngine> m_defEngine;

	// Currently Equipped
	std::shared_ptr<TankGun> m_eqGun;
	std::shared_ptr<TankHead> m_eqHead;
	std::shared_ptr<TankBody> m_eqBody;
	std::shared_ptr<TankEngine> m_eqEngine;

	// Parts in inventory
	std::shared_ptr<TankGun> m_guns[7];
	std::shared_ptr<TankHead> m_heads[7];
	std::shared_ptr<TankBody> m_bodies[7];
	std::shared_ptr<TankEngine> m_engines[7];

	std::shared_ptr<Useable> m_useables[7][7];

	void AddEquipment(std::shared_ptr<Equipment> e);
	void AddUseable(std::shared_ptr<Useable> u);
};