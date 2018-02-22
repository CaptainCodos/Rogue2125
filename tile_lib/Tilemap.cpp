#include "Tilemap.h"
#include <AllMgrs.h>

using namespace std;
using namespace sf;

TileMap::TileMap(Entity * const e, int sizeX, int sizeY, vector<char> sets) : Component(e)
{
	m_sizeX = sizeX;
	m_sizeY = sizeY;

	static TextureMgr* txrM = TextureMgr::GetInstance();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			Vector2f v = e->GetPos();
			shared_ptr<Entity> ent = make_shared<Entity>();
			ent->SetScale(2.0f);
			ent->SetPos(Vector2f(v.x + 32.0f + (x * 64.0f), v.x + 32.0f + (y * 64.0f)));
			auto tile = ent->AddComponent<Tile>();
			//tile->SetAnimates(true, true);
			tile->ChangeSetIdx(0);
			tile->SetOrigin(Vector2f(0.5f, 0.5f));
			tile->SetColor(Color(160, 230, 255, 255));

			m_allTiles.push_back(ent);
		}
	}
}

shared_ptr<Entity> TileMap::GetEntityAt(Vector2i coords)
{
	return m_allTiles[(coords.y * m_sizeX) + coords.x];
}

std::shared_ptr<Tile> TileMap::GetTileAt(Vector2i coords)
{
	return GetEntityAt(coords)->GetComponent<Tile>();
}

std::vector<std::shared_ptr<Entity>> TileMap::GetAllTileEntities()
{
	return m_allTiles;
}

void TileMap::GenerateMap()
{

}

void TileMap::UpdateMe(double dt)
{

}

void TileMap::DrawMe()
{

}