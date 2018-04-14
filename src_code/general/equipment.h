#pragma once
#include "item.h"
#include "damage_object.h"
#include "system_player_controls.h"

class Equipment : public Item
{
public:
	Equipment();
	~Equipment() = default;

	void GenerateItem() override;
	virtual void GenerateBasic();
	void CreateFromData(std::vector<std::string> data) override;
	void CreateFromEquipData(std::vector<std::string> data, int &count);
	std::vector<std::string> GetDataForSave();

	int GetBuff(int ID);
	float GetResistMod(int ID);
	float GetStatsMod(int ID);
protected:
	int m_EID;	// Determines type of equipment from file

	std::vector<Skill> m_buffs;
	float m_resMods[5];
	float m_resModOffset;
	float m_statMods[5];
	float m_statModOffset;
private:

};

class TankGun : public Equipment
{
public:
	TankGun();
	~TankGun() = default;

	void GenerateItem() override;
	void GenerateBasic() override;
	void CreateFromData(std::vector<std::string> data) override;
	void CreateFromGunData(std::vector<std::string> data, int &count);
	std::vector<std::string> GetDataForSave();

	bool GetFired();
	DmgData GetShotData(int dmg, int rate);
	void update(double dt, int rate);
protected:
	
private:
	std::vector<int> m_types;
	sf::Vector2f m_dmgRange;	// Damage Range per shot
	float m_fireTime;
	bool m_fire;
	bool m_firing;
	float m_Sps;		// Shots per second
};

class TankHead : public Equipment
{
public:
	TankHead();
	~TankHead() = default;

	void GenerateItem() override;
	void GenerateBasic() override;
	void CreateFromData(std::vector<std::string> data) override;
	std::vector<std::string> GetDataForSave();
protected:

private:

};

class TankBody : public Equipment
{
public:
	TankBody();
	~TankBody() = default;

	void GenerateItem() override;
	void GenerateBasic() override;
	void CreateFromData(std::vector<std::string> data) override;
	std::vector<std::string> GetDataForSave();
protected:

private:

};

class TankEngine : public Equipment
{
public:
	TankEngine();
	~TankEngine() = default;

	void GenerateItem() override;
	void GenerateBasic() override;
	void CreateFromData(std::vector<std::string> data) override;
	std::vector<std::string> GetDataForSave();
protected:

private:

};