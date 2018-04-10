#include "equipment.h"
#include "maths.h"
#include <algorithm>

using namespace std;
using namespace sf;

#pragma region Equipment
Equipment::Equipment()
{
	m_buffs = vector<Skill>();

	m_resModOffset = 0.0f;
	m_statModOffset = 0.0f;

	for (int i = 0; i < 5; i++)
		m_resMods[i] = 0.0f;

	for (int i = 0; i < 5; i++)
		m_resMods[i] = 0.0f;
}

void Equipment::GenerateItem()
{
	m_absID = 0;

	int reqs = RandomInt(0, 6);
	int buffs = RandomInt(0, 6);

	vector<int> usedVals = vector<int>();

	for (int i = 0; i < reqs; i++)
	{
		int req = RandomInt(0, 5);

		bool found = find(usedVals.begin(), usedVals.end(), req) != usedVals.end();
		while (found)
		{
			req = RandomInt(0, 5);

			found = find(usedVals.begin(), usedVals.end(), req) != usedVals.end();
		}

		m_reqs.push_back(Skill("name", "short", req, RandomInt(3, 30)));
	}

	usedVals = vector<int>();

	for (int i = 0; i < buffs; i++)
	{
		int req = RandomInt(0, 5);

		bool found = find(usedVals.begin(), usedVals.end(), req) != usedVals.end();
		while (found)
		{
			req = RandomInt(0, 5);

			found = find(usedVals.begin(), usedVals.end(), req) != usedVals.end();
		}

		m_buffs.push_back(Skill("name2", "short2", req, RandomInt(3, 30)));
	}

	for (int i = 0; i < 5; i++)
		m_resMods[i] = RandomFloat(0.0f, 0.9f);

	for (int i = 0; i < 5; i++)
		m_statMods[i] = RandomFloat(0.0f, 0.9f);

	m_statModOffset = RandomFloat(-0.5f, 0.5f);
	m_resModOffset = RandomFloat(-0.5f, 0.5f);
}

void Equipment::CreateFromData(vector<string> data)
{
	int c = 0;
	Item::CreateFromItemData(data, c);
	CreateFromEquipData(data, c);
}

void Equipment::CreateFromEquipData(vector<string> data, int &count)
{
	int buffs = stoi(data[count++]);
	for (int i = 0; i < buffs; i++)
	{
		m_reqs.push_back(Skill("", "", stoi(data[count++]), stoi(data[count++])));
	}

	for (int i = 0; i < 5; i++)
	{
		m_resMods[i] = stof(data[count++]);
	}

	m_resModOffset = stof(data[count++]);

	for (int i = 0; i < 5; i++)
	{
		m_statMods[i] = stof(data[count++]);
	}

	m_statModOffset = stof(data[count++]);
}

vector<string> Equipment::GetDataForSave()
{
	vector<string> data = Item::GetDataForSave();

	data.push_back(to_string(m_buffs.size()));
	for (int i = 0; i < m_buffs.size(); i++)
	{
		data.push_back(to_string(m_buffs[i].GetID()));
		data.push_back(to_string(m_buffs[i].GetVal()));
	}

	for (int i = 0; i < 5; i++)
	{
		data.push_back(to_string(m_resMods[i]));
	}

	data.push_back(to_string(m_resModOffset));

	for (int i = 0; i < 5; i++)
	{
		data.push_back(to_string(m_statMods[i]));
	}

	data.push_back(to_string(m_statModOffset));

	return data;
}
#pragma endregion

#pragma region TankGun
TankGun::TankGun() : Equipment()
{
	m_dmgRange = Vector2f(1.0f, 2.0f);
	m_fireTime = 1.0f;
	m_Sps = 1.0f;
	m_firing = false;
}

void TankGun::GenerateItem()
{
	Equipment::GenerateItem();

	m_EID = 0;
	m_secID = 0;

	m_name = "Nasty Gun";
	m_short = "NG";
	m_descript = "Ouch!";
	
	float min = RandomFloat(1.0f, 3.0f);
	float max = RandomFloat(std::max(min, RandomFloat(2.0f, 5.0f)), RandomFloat(6.0f, 9.0f));

	m_dmgRange = Vector2f(min, max);

	m_Sps = RandomFloat(0.5f, 60.0f);
}

void TankGun::CreateFromData(vector<string> data)
{
	int c = 0;
	Item::CreateFromItemData(data, c);
	Equipment::CreateFromEquipData(data, c);
	CreateFromGunData(data, c);
}

void TankGun::CreateFromGunData(vector<string> data, int &count)
{
	m_dmgRange = Vector2f(0.0f, 0.0f);
	m_dmgRange.x = stof(data[count++]);
	m_dmgRange.y = stof(data[count++]);

	m_Sps = stof(data[count++]);
}

vector<string> TankGun::GetDataForSave()
{
	vector<string> data = Equipment::GetDataForSave();

	data.push_back(to_string(m_dmgRange.x));
	data.push_back(to_string(m_dmgRange.y));

	data.push_back(to_string(m_Sps));

	data.push_back(" ");

	return data;
}
#pragma endregion

#pragma region TankHead
TankHead::TankHead() : Equipment()
{
}

void TankHead::GenerateItem()
{
	Equipment::GenerateItem();

	m_EID = 1;
	m_secID = 1;

	m_name = "Tank Head";
	m_short = "TH";
	m_descript = "Watch the barrel!";
}

void TankHead::CreateFromData(vector<string> data)
{

}

vector<string> TankHead::GetDataForSave()
{
	vector<string> data = Equipment::GetDataForSave();

	data.push_back(" ");

	return data;
}
#pragma endregion

#pragma region TankBody
TankBody::TankBody() : Equipment()
{
}

void TankBody::GenerateItem()
{
	Equipment::GenerateItem();

	m_EID = 2;
	m_secID = 2;

	m_name = "Tank Body";
	m_short = "TB";
	m_descript = "Ping!";
}

void TankBody::CreateFromData(vector<string> data)
{

}

vector<string> TankBody::GetDataForSave()
{
	vector<string> data = Equipment::GetDataForSave();

	data.push_back(" ");

	return data;
}
#pragma endregion

#pragma region TankEngine
TankEngine::TankEngine() : Equipment()
{
}

void TankEngine::GenerateItem()
{
	Equipment::GenerateItem();

	m_EID = 3;
	m_secID = 3;

	m_name = "Tank Engine";
	m_short = "TE";
	m_descript = "Wroooomm! Pua Pua Pua Pua Pua!";
}

void TankEngine::CreateFromData(vector<string> data)
{

}

vector<string> TankEngine::GetDataForSave()
{
	vector<string> data = Equipment::GetDataForSave();

	data.push_back(" ");

	return data;
}
#pragma endregion