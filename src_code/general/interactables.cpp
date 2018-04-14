#include "interactables.h"

using namespace std;
using namespace sf;

Interactable::Interactable() : NPA()
{
	GenerateData();
}

void Interactable::GenerateData()
{
	m_priID = 1;
}

Barrel::Barrel()
{
	GenerateData();
}

void Barrel::GenerateData()
{
	m_secID = 0;
}

void Barrel::CreateFromData(std::vector<std::string> data)
{
	int c = 0;
	NPA::CreateFromNPAData(data, c);
}

void Barrel::CreateFromBarrelData(std::vector<std::string> data, int & count)
{
}

std::vector<std::string> Barrel::GetDataForSave()
{
	vector<string> data = NPA::GetDataForSave();

	data.push_back("-");
	return data;
}

Crate::Crate()
{
	GenerateData();
}

void Crate::GenerateData()
{
	m_secID = 1;
}

void Crate::CreateFromData(std::vector<std::string> data)
{
	int c = 0;
	NPA::CreateFromNPAData(data, c);
}

void Crate::CreateFromCrateData(std::vector<std::string> data, int & count)
{
}

std::vector<std::string> Crate::GetDataForSave()
{
	vector<string> data = NPA::GetDataForSave();

	data.push_back("-");
	return data;
}

Trap::Trap()
{
	GenerateData();
}

int Trap::GetTrapID() { return m_trapID; }

void Trap::GenerateData()
{
	m_secID = 2;
}

void Trap::CreateFromData(std::vector<std::string> data)
{
	int c = 0;
	NPA::CreateFromNPAData(data, c);
	CreateFromTrapData(data, c);
}

void Trap::CreateFromTrapData(std::vector<std::string> data, int & count)
{
	m_trapID = stoi(data[count++]);
}

std::vector<std::string> Trap::GetDataForSave()
{
	vector<string> data = NPA::GetDataForSave();

	data.push_back(to_string(m_trapID));

	data.push_back("-");
	return data;
}
