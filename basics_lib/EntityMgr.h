#pragma once
#include "RenderSystem.h"
#include "Entity.h"

struct EntityMgr
{
	/*EntityMgr();
	~EntityMgr();*/

	std::vector<std::shared_ptr<Entity>> m_entities;

	void UpdateEnts(double dt);
	void DrawEnts();

	void Destroy(std::shared_ptr<Entity> e);
	void DestroyEnts();
	void Instantiate(std::shared_ptr<Entity> e);
};

