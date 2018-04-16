#pragma once

#include "NPA.h"

class Interactable : public NPA
{
public:
	Interactable();
	~Interactable() = default;

	void GenerateData();
protected:

private:

};

class Barrel : public Interactable
{
public:
	Barrel();
	~Barrel() = default;

	void GenerateData();

	void CreateFromData(std::vector<std::string> data);
	void CreateFromBarrelData(std::vector<std::string> data, int &count);
	std::vector<std::string> GetDataForSave();
protected:

private:

};

class Crate : public Interactable
{
public:
	Crate();
	~Crate() = default;

	void GenerateData();

	void CreateFromData(std::vector<std::string> data);
	void CreateFromCrateData(std::vector<std::string> data, int &count);
	std::vector<std::string> GetDataForSave();
protected:

private:

};

class Trap : public Interactable
{
public:
	Trap();
	~Trap() = default;

	int GetTrapID();

	void GenerateData();

	void CreateFromData(std::vector<std::string> data);
	void CreateFromTrapData(std::vector<std::string> data, int &count);
	std::vector<std::string> GetDataForSave();
protected:

private:
	int m_trapID;
};