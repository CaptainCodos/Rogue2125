#pragma once

#include "cmp_sprite.h"
#include "../general/interactables.h"
#include "../general/data_shapes.h"
#include "cmp_actor_stats.h"
#include "cmp_tilemap.h"

class InteractComp : public AnimComponent
{
public:
	InteractComp() = delete;
	InteractComp(Entity* p, std::shared_ptr<Interactable> obj);
	~InteractComp() = default;

	int GetObjID();

	void UseObj(std::shared_ptr<ActorStatsComponent> actor);
protected:

private:
	std::shared_ptr<Entity> m_map;

	std::shared_ptr<Interactable> m_obj;
	DataShapes::Circle m_useCircle;
};