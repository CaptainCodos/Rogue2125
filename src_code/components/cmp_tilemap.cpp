#include "cmp_tilemap.h"
#include "system_physics.h"

using namespace std;
using namespace sf;

TileMapComponent::TileMapComponent(Entity* p, TextureMgr* txrMgr, int currMap)
	: Component(p)
{
	m_txrMgr = txrMgr;

	m_width = 100 + ((1 + currMap) * 3);
	m_height = 100 + ((1 + currMap) * 3);

	m_ID = "map" + currMap;

	m_tileEnts = vector<vector<shared_ptr<Entity>>>();
	m_tileCmps = vector<vector<shared_ptr<TileComponent>>>();

	m_rooms = vector<IntRect>();
	m_corridors = vector<IntRect>();
	bool b = true;
	if (!b)
	{

	}
	else
	{
		for (int y = 0; y < m_height; y++)
		{
			m_tileEnts.push_back(vector<shared_ptr<Entity>>());
			m_tileCmps.push_back(vector<shared_ptr<TileComponent>>());
		}

		for (int y = 0; y < m_tileEnts.size(); y++)
		{
			for (int x = 0; x < m_width; x++)
			{
				shared_ptr<Entity> ent = make_shared<Entity>(nullptr);
				ent->setPosition(Vector2f(16.0f + (32.0f * x), 16.0f + (32.0f * y)));
				
				shared_ptr<TileComponent> cmpT = ent->addComponent<TileComponent>(txrMgr);
				cmpT->SetTileID(0);
				//cmpT->SetColor(m_txrMgr->colors_LiquidTiles[4]);
				cmpT->update(1.0f);

				//shared_ptr<PhysicsComponent> pC = ent->GetCompatibleComponent<PhysicsComponent>()[0];
				//cout << "PosX: " << pC->getBody()->GetPosition().x;

				m_tileEnts[y].push_back(ent);
				m_tileCmps[y].push_back(cmpT);
			}
		}
	}
}

void TileMapComponent::update(double dt)
{

}

void TileMapComponent::render()
{
	for (int y = 0; y < m_tileEnts.size(); y++)
	{
		for (int x = 0; x < m_tileEnts[y].size(); x++)
		{
			m_tileEnts[y][x]->render();
		}
	}
}

string TileMapComponent::GetID() { return m_ID; }

shared_ptr<TileComponent> TileMapComponent::GetTile(int x, int y)
{
	return m_tileCmps[y][x];
}

//vector<vector<shared_ptr<TileComponent>>> TileMapComponent::GetTiles(IntRect area)
//{
//
//}
//vector<vector<shared_ptr<TileComponent>>> TileMapComponent::GetNeighbourTiles(int x, int y)
//{
//
//}

bool TileMapComponent::LoadMap()
{
	return false;
}
//void TileMapComponent::SaveMap()
//{
//
//}
//
//void TileMapComponent::GenerateMap()
//{
//
//}