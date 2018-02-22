#include "Tile.h"
#include <AllMgrs.h>

using namespace std;
using namespace sf;

Tile::Tile(Entity *const e) : SpriteComponent(e)
{
	m_tag = "tile";

	m_tickTime = 1.0f;
	m_tickTimeMult = 1.0f;

	m_tileIdx = 0;
	m_tileSet = 0;

	m_walkable = true;

	static TextureMgr* txrM = TextureMgr::GetInstance();
	SetSpriteTex(txrM->m_tileSheets[0], 32, 12);
}

vector<shared_ptr<Entity>> Tile::GetOccupants()
{
	return m_occupants;
}

void Tile::AddOccupant(shared_ptr<Entity> e)
{
	m_occupants.push_back(e);
}
void Tile::RemoveOccupant(shared_ptr<Entity> e)
{
	m_occupants.erase(std::remove(m_occupants.begin(), m_occupants.end(), e), m_occupants.end());
}

char Tile::GetTileIdx()
{
	return m_tileIdx;
}
char Tile::GetSetIdx()
{
	return m_tileSet;
}
char Tile::GetAirX()
{
	return m_airX;
}
char Tile::GetAirY()
{
	return m_airY;
}

void Tile::SetTickVars(float tickDmg, float timeMult)
{
	m_tickDmg = tickDmg;
	m_tickTimeMult = timeMult;
}
void Tile::SetTileIdx(char idx)
{
	m_tileIdx = idx;
	SetFrame(idx);
}
void Tile::ChangeSetIdx(char idx)
{
	static TextureMgr* txrM = TextureMgr::GetInstance();

	m_tileSet = idx;
	
	if (idx < 1)
	{
		SetAnimates(true, true);
		SetSpriteTex(txrM->m_tileSheets[idx], 32, 6);
	}
	else
	{
		SetSpriteTex(txrM->m_tileSheets[idx], 32, 0);
	}
}
void Tile::SetAirX(char val)
{
	m_airX = val;
}
void Tile::SetAirY(char val)
{
	m_airY = val;
}
void Tile::SetSpeedMult(float val)
{
	m_speedMult = val;
}

void Tile::UpdateMe(double dt)
{
	// call base update
	SpriteComponent::UpdateMe(dt);

	if (m_occupants.size() > 0)
	{
		if (m_tickTime <= 0.0f)
		{
			for (int i = 0; i < m_occupants.size(); i++)
			{
				string tag = m_occupants[i]->GetTag();
				if (tag == "character" || tag == "monster" || tag == "player")
				{
					// do damage!
				}
			}

			m_tickTime = 1.0f;
		}
		else
		{
			m_tickTime -= dt * m_tickTimeMult;
		}
	}
	else
	{
		m_tickTime -= dt * m_tickTimeMult;
	}
}
void Tile::DrawMe()
{
	SpriteComponent::DrawMe();
}