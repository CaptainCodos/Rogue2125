#pragma once
#include "cmp_sprite.h"
#include "cmp_physics.h"
#include "AllMgrs.h"
#include <memory>

class TileComponent : public TextureComponent
{
public:
	TileComponent() = delete;

	explicit TileComponent(Entity* p, TextureMgr* txrMgr);

	void update(double dt) override;

	std::shared_ptr<PhysicsComponent> GetTileBox();

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

	char m_tileID;		// Determines if tile is (traversable and what set) (0 - 4 = traversable) (5 - 9 = non-traversable) (10 - 4 = disguised)
	char m_tileIdx;		// Determines the frame to display for solid tiles. Is not saved as it is generated on load/creation.
	bool m_walkable;	// Flag for traversability
	bool m_disguised;	// Flag to check if tile is disguised as wall

	float m_terrainMod;	// Movement speed modifier of character traversing the tile.

	int m_freeX;		// Helps determine free areas around tile on X axis. -1 = left, 0 = both, 1 = right, 2 = neither.
	int m_freeY;		// Helps determine free areas around tile on Y axis. -1 = top, 0 = both, 1 = bottom, 2 = neither.
};