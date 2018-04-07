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
	void GenerateMap();

	std::string GetID();
	int GetIntID();
	std::shared_ptr<TileComponent> GetTile(int x, int y);
	std::shared_ptr<Entity> GetEnt(int x, int y);
	std::vector<std::vector<std::shared_ptr<TileComponent>>> GetTiles(sf::IntRect area);
	std::vector<std::vector<std::shared_ptr<TileComponent>>> GetNeighbourTiles(int x, int y);
	std::vector<std::vector<std::shared_ptr<TileComponent>>> GetAllNeighbourTiles(int X, int Y);

	std::vector<std::vector<std::shared_ptr<Entity>>> GetNeightbourEnts(int X, int Y);			// Used to get neighbouring entities to toggle visibility.

	
protected:

private:
	TextureMgr* m_txrMgr;

	std::string m_ID;
	int m_IntID;
	int m_width;
	int m_height;
	bool m_flag;

	char m_roomIDs;
	char m_corridorIDs;

	std::vector<std::vector<std::shared_ptr<Entity>>> m_tileEnts;
	std::vector<std::vector<std::shared_ptr<TileComponent>>> m_tileCmps;
	std::vector<std::vector<std::shared_ptr<TileComponent>>> m_visibleTiles;

	std::vector<sf::IntRect> m_rooms;

	std::vector<int> m_corridorDirs;
	std::vector<std::vector<std::shared_ptr<TileComponent>>> m_corridors;

	char CalculateTileIdx(std::vector<std::vector<std::shared_ptr<TileComponent>>> neighbours);
	bool ToggleTile(std::vector<std::vector<std::shared_ptr<TileComponent>>> tiles);

	sf::IntRect GenerateRoom(sf::IntRect prev);	// Generate new room within bounds of previous.
	std::vector<std::shared_ptr<TileComponent>> GenerateCorridor(sf::IntRect r1, sf::IntRect r2);	// Generate corridor from one room to another.
	//sf::IntRect GenerateLockedRoom();			// Generate new room along corridor that is locked.
	//sf::IntRect GenerateHiddenRoom();			// Generate hidden room on side of normal room.

	void AlterRoomTiles(sf::IntRect room);
	void AlterCorridorTiles(std::vector<std::shared_ptr<TileComponent>> corridor);
	void IterateAcrossTileMap();
};