#pragma once
#include "cmp_sprite.h"
#include "cmp_physics.h"
#include "AllMgrs.h"
#include <memory>

class TileComponent : public TextureComponent
{
public:
	TileComponent() = delete;

	explicit TileComponent(Entity* p, TextureMgr* txrMgr, int x, int y);


	void update(double dt) override;

	std::shared_ptr<PhysicsComponent> GetTileBox();
	sf::Vector2i GetCoords();
	bool GetWalkable();
	bool GetDisguised();
	char GetID();
	char GetIdx();
	char GetLiquidID();
	float GetTerrainMod();

	void SetOrigin(sf::Vector2f origin) override;
	void SetTileID(char ID);
	void SetTileIdx(char idx);
	void SetTerrainMod(float mod);

	void ResetFreeAreas();
	void AddFreeX(int x);
	void AddFreeY(int y);
protected:

private:
	TextureMgr* m_txrMgr;

	std::shared_ptr<PhysicsComponent> m_tileBox;	// Used for collision purposes

	sf::Vector2i m_coords;	// Coordinates of the tile.

	char m_tileID;		// Determines if tile is (traversable and what set) (0 - 4 = traversable) (5 - 9 = non-traversable) (10 - 14 = disguised) (15 - 19 = liquid)
	char m_tileIdx;		// Determines the frame to display for solid tiles. Is not saved as it is generated on load/creation.
	char m_liquidID;	// Determines nature of liquid tile (Lava > Toxic > Acid > Energized Water > Water, 0 > 4)

	bool m_walkable;	// Flag for traversability
	bool m_disguised;	// Flag to check if tile is disguised as wall

	float m_terrainMod;	// Movement speed modifier of character traversing the tile.

	int m_freeX;		// Helps determine free areas around tile on X axis. -1 = left, 0 = both, 1 = right, 2 = neither.
	int m_freeY;		// Helps determine free areas around tile on Y axis. -1 = top, 0 = both, 1 = bottom, 2 = neither.
};