#pragma once

#include "cmp_sprite.h"
#include "../general/world_objs.h"
#include "../general/data_shapes.h"
#include "cmp_actor_stats.h"
#include "cmp_tilemap.h"

class WorldObjComp : public TextureComponent
{
public:
	WorldObjComp() = delete;
	WorldObjComp(Entity* p, WorldObj obj);
	~WorldObjComp() = default;

	int GetObjID();

	void UseObj(std::shared_ptr<ActorStatsComponent> actor);
protected:

private:
	std::shared_ptr<TileMapComponent> m_map;

	WorldObj m_obj;
	DataShapes::Circle m_useCircle;
};