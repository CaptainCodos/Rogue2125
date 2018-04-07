#include "cmp_tile.h"

using namespace std;
using namespace sf;

TileComponent::TileComponent(Entity* p, TextureMgr* txrMgr, int x, int y)
	: TextureComponent(p)
{
	m_txrMgr = txrMgr;

	m_coords = Vector2i(x, y);

	m_disguised = false;
	m_walkable = false;

	//m_tileID = 6;
	SetTileID(1);
	m_tileIdx = 0;
	m_liquidID = 0;

	m_terrainMod = 1.0f;

	ResetFreeAreas();

	p->addComponent<PhysicsComponent>(false, Vector2f(1.0f, 1.0f));
}

void TileComponent::update(double dt)
{
	TextureComponent::update(dt);
}

shared_ptr<PhysicsComponent> TileComponent::GetTileBox() { return m_tileBox; }

Vector2i TileComponent::GetCoords() { return m_coords; }

bool TileComponent::GetWalkable() { return m_walkable; }
bool TileComponent::GetDisguised() { return m_disguised; }

char TileComponent::GetID() { return m_tileID; }
char TileComponent::GetIdx() { return m_tileIdx; }
char TileComponent::GetLiquidID() { return m_liquidID; }

float TileComponent::GetTerrainMod() { return m_terrainMod; }

void TileComponent::SetTileID(char ID)
{
	m_tileID = ID;

	int catagory = ID / 5;
	int set = ID % 5;

	if (ID > 14)
	{
		m_liquidID = (ID - 15);
		catagory = 0;
		set = 0;
	}

	switch (catagory)
	{
	case 0:
		m_walkable = true;
		m_disguised = false;

		SetTint(Color::White);
		if (set <= 0)
		{
			SetTexture(m_txrMgr->anim_Tiles[set], 32);
			SetColor(m_txrMgr->colors_LiquidTiles[m_liquidID]);
			SetTextureRect(m_txrMgr->anim_TilesRect);
		}
		else
		{
			SetTexture(m_txrMgr->sheet_Tiles[set], 32);
			SetTextureRect(make_shared<sf::IntRect>(sf::IntRect(0, 0, m_texRes, m_texRes)));
		}
		break;
	case 1:
		m_walkable = false;
		m_disguised = false;

		SetTint(Color(220, 220, 220, 255));

		SetTexture(m_txrMgr->sheet_Tiles[set], 32);
		SetTextureRect(make_shared<sf::IntRect>(sf::IntRect(0, 0, m_texRes, m_texRes)));
		break;
	case 2:
		m_walkable = true;
		m_disguised = true;

		SetTint(Color(220, 220, 220, 255));

		SetTexture(m_txrMgr->sheet_Tiles[set], 32);
		SetTextureRect(make_shared<sf::IntRect>(sf::IntRect(0, 0, m_texRes, m_texRes)));
		break;
	}

	SetOrigin(Vector2f(0.5f, 0.5f));
}

void TileComponent::SetOrigin(Vector2f origin)
{
	if (m_sprite->getTexture() != nullptr)
	{
		int frames = m_sprite->getTexture()->getSize().x / m_texRes;
		sf::Vector2f o = sf::Vector2f(origin.x * (m_sprite->getTexture()->getSize().x / frames), origin.y * m_sprite->getTexture()->getSize().y);
		m_sprite->setOrigin(o);
	}
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