#include "Scene.h"

using namespace std;

vector<shared_ptr<Entity>> &Scene::GetEntities()
{
	return m_entMgr.m_entities;
}

void Scene::UpdateScene(double dt)
{
	m_entMgr.UpdateEnts(dt);
}

void Scene::DrawScene()
{

}