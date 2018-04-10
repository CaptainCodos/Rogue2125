#include "cmp_inventory.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

InventoryComponent::InventoryComponent(Entity* p) 
	: Component(p)
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

void InventoryComponent::SaveInventory()
{

}

void InventoryComponent::LoadInventory()
{
	string dir = "res/PlayerData/PlayerInv.txt";

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
					item->CreateFromData(itemChunks[i]);
					
					break;
				case 1:
					item = make_shared<TankHead>();
					item->CreateFromData(itemChunks[i]);
					break;
				case 2:
					item = make_shared<TankBody>();
					item->CreateFromData(itemChunks[i]);
					break;
				case 3:
					item = make_shared<TankEngine>();
					item->CreateFromData(itemChunks[i]);
					break;
				}
				break;
			case 1:
				item = make_shared<Useable>();
				item->CreateFromData(itemChunks[i]);
				break;
			}

			for (int h = 0; h < itemChunks[i].size(); h++)
			{
				
			}
		}
	}
}