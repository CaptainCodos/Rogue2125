#include "cmp_tile.h"

using namespace std;
using namespace sf;

TileComponent::TileComponent(Entity* p, TextureMgr* txrMgr)
	: TextureComponent(p)
{
	m_txrMgr = txrMgr;

	m_disguised = false;
	m_walkable = false;

	m_tileID = 0;
	m_tileIdx = 0;

	m_terrainMod = 1.0f;

	ResetFreeAreas();

	p->addComponent<PhysicsComponent>(false, Vector2f(1.0f, 1.0f));
}

void TileComponent::update(double dt)
{
	TextureComponent::update(dt);
}

shared_ptr<PhysicsComponent> TileComponent::GetTileBox() { return m_tileBox; }

void TileComponent::SetTileID(char ID)
{
	m_tileID = ID;

	int catagory = ID / 6;
	int set = ID % 6;

	switch (catagory)
	{
	case 0:
		m_walkable = true;
		m_disguised = false;

		if (set <= 0)
		{
			SetTexture(m_txrMgr->anim_Tiles[set], 32);
			SetTextureRect(m_txrMgr->anim_TilesRect);
		}
		else if (set < 4)
		{
			SetTexture(m_txrMgr->sheet_Tiles[set], 32);
		}
		else
		{
			SetTexture(m_txrMgr->sheet_Tiles[set], 32);
		}
		break;
	case 1:
		m_walkable = false;
		m_disguised = false;

		if (set <= 0)
		{
			SetTexture(m_txrMgr->anim_Tiles[set], 32);
			SetTextureRect(m_txrMgr->anim_TilesRect);
		}
		else if (set < 4)
		{
			SetTexture(m_txrMgr->sheet_Tiles[set], 32);
		}
		else
		{
			SetTexture(m_txrMgr->sheet_Tiles[set], 32);
		}
		break;
	case 2:
		m_walkable = true;
		m_disguised = true;

		if (set <= 0)
		{
			SetTexture(m_txrMgr->anim_Tiles[set], 32);
			SetTextureRect(m_txrMgr->anim_TilesRect);
		}
		else if (set < 4)
		{
			SetTexture(m_txrMgr->sheet_Tiles[set], 32);
		}
		else
		{
			SetTexture(m_txrMgr->sheet_Tiles[set], 32);
		}
		break;
	}

	SetOrigin(Vector2f(0.5f, 0.5f));
}

void TileComponent::SetTileIdx(char idx)
{
	m_tileIdx = idx;

	m_srcRect->left = m_texRes * idx;
}

void TileComponent::SetTerrainMod(float mod)
{
	m_terrainMod = mod;
}

void TileComponent::ResetFreeAreas()
{
	m_freeX = 2;
	m_freeY = 2;
}

void TileComponent::AddFreeX(int x)
{
	m_freeX += x;
}
void TileComponent::AddFreeY(int y)
{
	m_freeY += y;
}