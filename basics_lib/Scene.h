#pragma once
#include "EntityMgr.h"

#include <vector>
#include <memory>

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void UpdateScene(double dt);
	virtual void DrawScene();
	virtual void LoadScene() = 0;

	std::vector<std::shared_ptr<Entity>> &GetEntities();
protected:
	EntityMgr m_entMgr;
};

