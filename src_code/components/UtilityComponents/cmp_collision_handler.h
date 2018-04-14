#pragma once

#include "ecm.h"
#include "../src_code/components/cmp_tilemap.h"

class ColHandlerComp : public Component
{
public:
	ColHandlerComp() = delete;
	ColHandlerComp(Entity* p);
	~ColHandlerComp() = default;

	void update(double dt) override;
	void render() override;
protected:

private:
	std::shared_ptr<TileMapComponent> m_map;
	void HandleAttacks(std::vector<std::shared_ptr<Entity>> &attacks, std::vector<std::shared_ptr<Entity>> &actors);	// Check if attacks collide with actors and chick if tile is a wall
	void HandleActors(std::vector<std::shared_ptr<Entity>> &actors);	// Collision between all kinds of actors including the player
	void HandlePlayer(std::vector<std::shared_ptr<Entity>> &actors);	// Alter player's velocity if they hit a wall
};