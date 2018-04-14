#include "world_objs.h"

using namespace std;
using namespace sf;

WorldObj::WorldObj() : NPA()
{
	m_priID = 2;
}

void WorldObj::GenerateData()
{
	m_priID = 2;
}

FloorChange::FloorChange(int dir)
{
	m_secID = 0;

	GenerateData(dir);
}

void FloorChange::GenerateData(int dir)
{
	WorldObj::GenerateData();

	m_secID = 0;

	m_dir = dir;
	m_outCoords = Vector2i(0, 0);
}

void FloorChange::CreateFromData(std::vector<std::string> data)
{
	int c = 0;
	NPA::CreateFromNPAData(data, c);
	CreateFromFloorChangeData(data, c);
}

void FloorChange::CreateFromFloorChangeData(std::vector<std::string> data, int &count)
{
	m_dir = stoi(data[count++]);

	Vector2i outC = Vector2i(0, 0);
	outC.x = stoi(data[count++]);
	outC.y = stoi(data[count++]);
}

std::vector<std::string> FloorChange::GetDataForSave()
{
	vector<string> data = NPA::GetDataForSave();

	data.push_back(to_string(m_dir));
	data.push_back(to_string(m_outCoords.x));
	data.push_back(to_string(m_outCoords.y));

	data.push_back("-");

	return data;
}

int FloorChange::GetDir() { return m_dir; }

sf::Vector2i FloorChange::GetOutPos() { return m_outCoords; }

Door::Door()
{
	m_secID = 1;

	GenerateData(false);
}

void Door::GenerateData(bool locked)
{
	m_secID = 1;

	m_open = false;
	m_locked = locked;
}

void Door::CreateFromData(std::vector<std::string> data)
{
	int c = 0;
	NPA::CreateFromNPAData(data, c);
	CreateFromDoorData(data, c);
}

void Door::CreateFromDoorData(std::vector<std::string> data, int &count)
{
	m_open = (data[count++] == "true" ? true : false);
	m_locked = (data[count++] == "true" ? true : false);
}

std::vector<std::string> Door::GetDataForSave()
{
	vector<string> data = NPA::GetDataForSave();

	data.push_back(m_open ? "true" : "false");
	data.push_back(m_locked ? "true" : "false");

	data.push_back("-");

	return data;
}

bool Door::IsLocked() { return m_locked; }
bool Door::IsOpen() { return m_open; }

void Door::ToggleOpen()
{
	m_open = !m_open;
}

void Door::Unlock()
{
	m_locked = false;
}

AutoShop::AutoShop()
{
	m_secID = 2;

	GenerateData();
}

void AutoShop::GenerateData()
{
	m_secID = 2;

	m_gunItem = make_shared<TankGun>();
	m_gunItem->GenerateItem();

	m_headItem = make_shared<TankHead>();
	m_headItem->GenerateItem();

	m_bodyItem = make_shared<TankBody>();
	m_bodyItem->GenerateItem();

	m_engineItem = make_shared<TankEngine>();
	m_engineItem->GenerateItem();

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			m_useables[y][x] = make_shared<Useable>();
			m_useables[y][x]->GenerateItem();
		}
	}
}

void AutoShop::CreateFromData(std::vector<std::string> data)
{
	int c = 0;
	NPA::CreateFromNPAData(data, c);
	CreateFromShopData(data, c);
}

void AutoShop::CreateFromShopData(std::vector<std::string> data, int &count)
{
	/*vector<vector<string>> itemChunks = vector<vector<string>>();

	vector<string> chunk = vector<string>();
	for (int i = count; i < data.size(); i++)
	{
		if (data[i] != " ")
		{
			chunk.push_back(data[i]);
		}
		else
		{
			itemChunks.push_back(chunk);
			chunk = vector<string>();
		}
		count++;
	}

	for (int i = 0; i < itemChunks.size(); i++)
	{
		int IDa = stoi(itemChunks[i][0]);
		int IDb = stoi(itemChunks[i][1]);

		std::shared_ptr<Item> item;

		switch (IDa)
		{
		case 0:
			switch (IDb)
			{
			case 0:
				item = make_shared<TankGun>();
				item->CreateFromData(itemChunks[i]);
				m_gunItem = item;
				break;
			case 1:
				item = make_shared<TankHead>();
				item->CreateFromData(itemChunks[i]);
				m_headItem = item;
				break;
			case 2:
				item = make_shared<TankBody>();
				item->CreateFromData(itemChunks[i]);
				m_bodyItem = item;
				break;
			case 3:
				item = make_shared<TankEngine>();
				item->CreateFromData(itemChunks[i]);
				m_engineItem = item;
				break;
			}
			break;
		case 1:
			item = make_shared<Useable>();
			item->CreateFromData(itemChunks[i]);

			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					if (m_useables[y][x] == nullptr)
					{
						m_useables[y][x] = item;
					}
				}
			}
			break;
		}
	}*/
}

std::vector<std::string> AutoShop::GetDataForSave()
{
	vector<string> data = NPA::GetDataForSave();

	if (m_gunItem != nullptr)
	{
		vector<string> iData = m_gunItem->GetDataForSave();

		data.insert(std::end(data), std::begin(iData), std::end(iData));
	}
	if (m_headItem != nullptr)
	{
		vector<string> iData = m_headItem->GetDataForSave();

		data.insert(std::end(data), std::begin(iData), std::end(iData));
	}
	if (m_bodyItem != nullptr)
	{
		vector<string> iData = m_bodyItem->GetDataForSave();

		data.insert(std::end(data), std::begin(iData), std::end(iData));
	}
	if (m_engineItem != nullptr)
	{
		vector<string> iData = m_engineItem->GetDataForSave();

		data.insert(std::end(data), std::begin(iData), std::end(iData));
	}

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (m_useables[y][x] != nullptr)
			{
				vector<string> iData = m_useables[y][x]->GetDataForSave();

				data.insert(std::end(data), std::begin(iData), std::end(iData));
			}
		}
	}

	data.push_back("-");

	return data;
}

SkillLibrary::SkillLibrary()
{
	m_secID = 3;
}

void SkillLibrary::GenerateData()
{
	m_secID = 3;
}

void SkillLibrary::CreateFromData(std::vector<std::string> data)
{
	int c = 0;
	CreateFromNPAData(data, c);
}

void SkillLibrary::CreateFromLibraryData(std::vector<std::string> data, int &count)
{

}

std::vector<std::string> SkillLibrary::GetDataForSave()
{
	vector<string> data = NPA::GetDataForSave();

	data.push_back("-");

	return data;
}
