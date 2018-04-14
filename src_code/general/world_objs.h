#pragma once

#include "NPA.h"
#include "equipment.h"
#include <memory>

class WorldObj : public NPA
{
public:
	WorldObj();
	~WorldObj() = default;

	void GenerateData();
protected:

private:

};

class FloorChange : WorldObj
{
public:
	FloorChange();
	~FloorChange() = default;

	void GenerateData(int dir, sf::Vector2i outCoords);

	void CreateFromData(std::vector<std::string> data);
	void CreateFromFloorChangeData(std::vector<std::string> data, int &count);
	std::vector<std::string> GetDataForSave();

	int GetDir();
	sf::Vector2i GetOutPos();
protected:

private:
	int m_dir;
	sf::Vector2i m_outCoords;
};

class Door : WorldObj
{
public:
	Door();
	~Door() = default;

	void GenerateData(bool locked);

	void CreateFromData(std::vector<std::string> data);
	void CreateFromDoorData(std::vector<std::string> data, int &count);
	std::vector<std::string> GetDataForSave();

	bool IsLocked();

	void ToggleOpen();
	void Unlock();
protected:

private:
	bool m_open;
	bool m_locked;
};

class AutoShop : WorldObj
{
public:
	AutoShop();
	~AutoShop() = default;

	void GenerateData();

	void CreateFromData(std::vector<std::string> data);
	void CreateFromShopData(std::vector<std::string> data, int &count);
	std::vector<std::string> GetDataForSave();


protected:

private:
	std::shared_ptr<TankGun> m_gunItem;
	std::shared_ptr<TankHead> m_headItem;
	std::shared_ptr<TankBody> m_bodyItem;
	std::shared_ptr<TankEngine> m_engineItem;

	std::shared_ptr<Useable> m_useables[3][3];
};

class SkillLibrary : WorldObj
{
public:
	SkillLibrary();
	~SkillLibrary() = default;

	void GenerateData();

	void CreateFromData(std::vector<std::string> data);
	void CreateFromLibraryData(std::vector<std::string> data, int &count);
	std::vector<std::string> GetDataForSave();
protected:

private:

};