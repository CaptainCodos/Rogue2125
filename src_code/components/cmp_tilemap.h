#pragma once

#include "cmp_tile.h"
#include "AllMgrs.h"
#include <SFML/Graphics/Rect.hpp>
#include <vector>

class TileMapComponent : public Component
{
public:
	TileMapComponent() = delete;

	explicit TileMapComponent(Entity* p, TextureMgr* txrMgr, int currMap);

	void update(double dt) override;
	void render() override;

	bool LoadMap();
	//void SaveMap();
	//void GenerateMap();

	std::string GetID();
	std::shared_ptr<TileComponent> GetTile(int x, int y);
	//std::vector<std::vector<std::shared_ptr<TileComponent>>> GetTiles(sf::IntRect area);
	//std::vector<std::vector<std::shared_ptr<TileComponent>>> GetNeighbourTiles(int x, int y);
protected:

private:
	TextureMgr* m_txrMgr;

	std::string m_ID;
	int m_width;
	int m_height;

	std::vector<std::vector<std::shared_ptr<Entity>>> m_tileEnts;
	std::vector<std::vector<std::shared_ptr<TileComponent>>> m_tileCmps;

	std::vector<sf::IntRect> m_rooms;
	std::vector<sf::IntRect> m_corridors;
	//sf::IntRect GenerateRoom(sf::IntRect prev);	// Generate new room within bounds of previous.
	//sf::IntRect GenerateLockedRoom();			// Generate new room along corridor that is locked.
	//sf::IntRect GenerateHiddenRoom();			// Generate hidden room on side of normal room.
};