#include "cmp_inventory.h"
#include "../general/equipment.h"

#include <Windows.h>
#include <stdio.h>
#include <memory>
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

InventoryComponent::InventoryComponent(Entity* p) 
	: Component(p)
{
	CreateInventory();

	m_defGun = make_shared<TankGun>();
	m_defGun->GenerateBasic();

	m_defHead = make_shared<TankHead>();
	m_defHead->GenerateBasic();

	m_defBody = make_shared<TankBody>();
	m_defBody->GenerateBasic();

	m_defEngine = make_shared<TankEngine>();
	m_defEngine->GenerateBasic();

	m_eqGun = m_defGun;
	m_eqHead = m_defHead;
	m_eqBody = m_defBody;
	m_eqEngine = m_defEngine;
}

InventoryComponent::~InventoryComponent()
{
	FlushInventory();
}

void InventoryComponent::update(double dt)
{

}

void InventoryComponent::render()
{

}

void InventoryComponent::SaveInventory()
{
	vector<vector<string>> itemChunks = vector<vector<string>>();

	for (int i = 0; i < 7; i++)
	{
		if (m_guns[i] != nullptr)
			itemChunks.push_back(m_guns[i]->GetDataForSave());
	}

	for (int i = 0; i < 7; i++)
	{
		if (m_heads[i] != nullptr)
			itemChunks.push_back(m_heads[i]->GetDataForSave());
	}

	for (int i = 0; i < 7; i++)
	{
		if (m_bodies[i] != nullptr)
			itemChunks.push_back(m_bodies[i]->GetDataForSave());
	}

	for (int i = 0; i < 7; i++)
	{
		if (m_engines[i] != nullptr)
			itemChunks.push_back(m_engines[i]->GetDataForSave());
	}

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (m_useables[j][i] != nullptr)
				itemChunks.push_back(m_useables[j][i]->GetDataForSave());
		}
	}

	string dir = "res/PlayerData/PlayerInv.txt";
	string folder = "res/PlayerData";

	if (CreateDirectory(folder.c_str(), NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		// CopyFile(...)
	}
	else
	{
		// Failed to create directory.
	}

	ofstream out(dir);

	if (out.good())
	{
		string str;
		for (int i = 0; i < itemChunks.size(); i++)
		{
			for (int j = 0; j < itemChunks[i].size(); j++)
			{
				str = itemChunks[i][j];
				out << str << endl;
			}
		}

		out.close();
	}
}

void InventoryComponent::LoadInventory()
{
	string dir = "res/PlayerData/PlayerInv.txt";
	string folder = "res/PlayerData";

	if (CreateDirectory(folder.c_str(), NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		// CopyFile(...)
	}
	else
	{
		// Failed to create directory.
	}

	ifstream out(dir);
	if (out.good())
	{
		vector<string> allData = vector<string>();
		vector<vector<string>> itemChunks = vector<vector<string>>();

		//itemChunks.push_back(vector<string>());
		vector<string> chunk = vector<string>();
		for (string l; std::getline(out, l); )
		{
			if (l != " ")
			{
				chunk.push_back(l);
			}
			else
			{
				itemChunks.push_back(chunk);
				chunk = vector<string>();
			}
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
					//item->CreateFromData(itemChunks[i]);
					
					break;
				case 1:
					item = make_shared<TankHead>();
					//item->CreateFromData(itemChunks[i]);
					break;
				case 2:
					item = make_shared<TankBody>();
					//item->CreateFromData(itemChunks[i]);
					break;
				case 3:
					item = make_shared<TankEngine>();
					//item->CreateFromData(itemChunks[i]);
					break;
				}
				break;
			case 1:
				item = make_shared<Useable>();
				//item->CreateFromData(itemChunks[i]);
				break;
			}

			item->CreateFromData(itemChunks[i]);
			AddItem(item);

			/*for (int h = 0; h < itemChunks[i].size(); h++)
			{
				
			}*/
		}
	}
}

void InventoryComponent::CreateInventory()
{
	for (int i = 0; i < 7; i++)
		m_guns[i] = nullptr;

	for (int i = 0; i < 7; i++)
		m_heads[i] = nullptr;

	for (int i = 0; i < 7; i++)
		m_bodies[i] = nullptr;

	for (int i = 0; i < 7; i++)
		m_engines[i] = nullptr;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			m_useables[j][i] = nullptr;
		}
	}
}

void InventoryComponent::FlushInventory()
{
	for (int i = 0; i < 7; i++)
	{
		if (m_guns[i] != nullptr)
		{
			m_guns[i]->~TankGun();
			m_guns[i] = nullptr;
		}
	}

	for (int i = 0; i < 7; i++)
	{
		if (m_heads[i] != nullptr)
		{
			m_heads[i]->~TankHead();
			m_heads[i] = nullptr;
		}
	}

	for (int i = 0; i < 7; i++)
	{
		if (m_bodies[i] != nullptr)
		{
			m_bodies[i]->~TankBody();
			m_bodies[i] = nullptr;
		}
	}

	for (int i = 0; i < 7; i++)
	{
		if (m_engines[i] != nullptr)
		{
			m_engines[i]->~TankEngine();
			m_engines[i] = nullptr;
		}
	}

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (m_useables[j][i] != nullptr)
			{
				m_useables[j][i]->~Useable();
				m_useables[j][i] = nullptr;
			}
			
		}
	}
}

void InventoryComponent::AddItem(shared_ptr<Item> item)
{
	switch (item->GetPriID())
	{
	case 0:
		AddEquipment(static_pointer_cast<Equipment>(item));
		break;
	case 1:
		AddUseable(static_pointer_cast<Useable>(item));
		break;
	}
}

void InventoryComponent::AddEquipment(shared_ptr<Equipment> e)
{
	switch (e->GetSecID())
	{
	case 0:
		for (int i = 0; i < 7; i++)
		{
			if (m_guns[i] == nullptr)
			{
				m_guns[i] = static_pointer_cast<TankGun>(e);
				return;
			}
		}
		break;
	case 1:
		for (int i = 0; i < 7; i++)
		{
			if (m_heads[i] == nullptr)
			{
				m_heads[i] = static_pointer_cast<TankHead>(e);
				return;
			}
		}
		break;
	case 2:
		for (int i = 0; i < 7; i++)
		{
			if (m_bodies[i] == nullptr)
			{
				m_bodies[i] = static_pointer_cast<TankBody>(e);
				return;
			}
		}
		break;
	case 3:
		for (int i = 0; i < 7; i++)
		{
			if (m_engines[i] == nullptr)
			{
				m_engines[i] = static_pointer_cast<TankEngine>(e);
				return;
			}
		}
		break;
	}
}

void InventoryComponent::AddUseable(shared_ptr<Useable> u)
{
	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			if (m_useables[y][x] == nullptr)
			{
				m_useables[y][x] = u;
				return;
			}
		}
	}
}

void InventoryComponent::PrintAllItems()
{
	vector<vector<string>> itemChunks = vector<vector<string>>();

	for (int i = 0; i < 7; i++)
	{
		if (m_guns[i] != nullptr)
			itemChunks.push_back(m_guns[i]->GetDataForSave());
	}

	for (int i = 0; i < 7; i++)
	{
		if (m_heads[i] != nullptr)
			itemChunks.push_back(m_heads[i]->GetDataForSave());
	}

	for (int i = 0; i < 7; i++)
	{
		if (m_bodies[i] != nullptr)
			itemChunks.push_back(m_bodies[i]->GetDataForSave());
	}

	for (int i = 0; i < 7; i++)
	{
		if (m_engines[i] != nullptr)
			itemChunks.push_back(m_engines[i]->GetDataForSave());
	}

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (m_useables[j][i] != nullptr)
				itemChunks.push_back(m_useables[j][i]->GetDataForSave());
		}
	}

	for (int i = 0; i < itemChunks.size(); i++)
	{
		for (int j = 0; j < itemChunks[i].size(); j++)
		{
			cout << itemChunks[i][j] << "\n";
		}
	}
}

vector<shared_ptr<Equipment>> InventoryComponent::GetEquipped()
{
	vector<shared_ptr<Equipment>> vec = vector<shared_ptr<Equipment>>();

	vec.push_back(m_eqGun);
	vec.push_back(m_eqHead);
	vec.push_back(m_eqBody);
	vec.push_back(m_eqEngine);

	return vec;
}