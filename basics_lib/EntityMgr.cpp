#include "EntityMgr.h"
#include "RenderSystem.h"

using namespace std;
using namespace sf;

void EntityMgr::Instantiate(shared_ptr<Entity> e)
{
	m_entities.push_back(e);
}

void EntityMgr::Destroy(shared_ptr<Entity> e)
{
	e->SetForDelete();
}
void EntityMgr::DestroyEnts()
{
	m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [](shared_ptr<Entity> e) { return e->ToBeDeleted(); }), m_entities.end());
}

void EntityMgr::UpdateEnts(double dt)
{
	DestroyEnts();

	for (int i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->UpdateMe(dt);
	}
}

void EntityMgr::DrawEnts()
{
	for (int i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->DrawMe();
	}
}
