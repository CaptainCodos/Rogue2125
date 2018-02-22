#pragma once
#include "Tile.h"

class TileMap : public Component 
{
public:
	TileMap(Entity * const e, int sizeX, int sizeY, std::vector<char> sets);

	std::shared_ptr<Entity> GetEntityAt(sf::Vector2i coords);
	std::shared_ptr<Tile> GetTileAt(sf::Vector2i coords);

	std::vector<std::shared_ptr<Entity>> GetAllTileEntities();

	void GenerateMap();

	void UpdateMe(double dt) override;
	void DrawMe() override;
private:
	std::vector<std::shared_ptr<Entity>> m_allTiles;

	int m_sizeX;
	int m_sizeY;


};