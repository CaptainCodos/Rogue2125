#include "cmp_world_obj.h"
#include "cmp_skills.h"
#include "../game.h"
#include <AllMgrs.h>
//#include "cmp_tilemap.h"

using namespace std;
using namespace DataShapes;

WorldObjComp::WorldObjComp(Entity* p, shared_ptr<WorldObj> obj)
	: AnimComponent(p)
{
	m_obj = obj;

	SetTexture(TextureMgr::GetInstance()->sheet_NPA_Textures[m_obj->GetPriID()][m_obj->GetSecID()], 32);
	SetOrigin(Vector2f(0.5f, 0.5f));

	SetAnimates(false);

	if (std::shared_ptr<FloorChange> change = dynamic_pointer_cast<FloorChange>(m_obj))
	{
		SetFrame(change->GetDir() == 1 ? 1 : 0);
	}
	else if (std::shared_ptr<Door> door = dynamic_pointer_cast<Door>(m_obj))
	{
		SetFrame(door->IsOpen() ? 1 : 0);
	}
	else if (std::shared_ptr<AutoShop> shop = dynamic_pointer_cast<AutoShop>(m_obj))
	{
		// Not implemented due to time constraints. :'(
	}
	else if (std::shared_ptr<SkillLibrary> sL = dynamic_pointer_cast<SkillLibrary>(m_obj))
	{

	}

	m_useCircle = Circle(36.0f, p->getPosition());

	m_map = Engine::GetActiveScene()->ents.find("TileMap")[0];
}

int WorldObjComp::GetObjID() { return m_obj->GetSecID(); }

void WorldObjComp::update(double dt)
{
	AnimComponent::update(dt);

	if (std::shared_ptr<Door> door = dynamic_pointer_cast<Door>(m_obj))
	{
		Vector2i v = Vector2i(_parent->getPosition() / 32.0f);
		m_map->GetCompatibleComponent<TileMapComponent>()[0]->GetTile(v)->SetShut(door->IsOpen());
	}
}

void WorldObjComp::UseObj(shared_ptr<ActorStatsComponent> actor)
{
	if (m_useCircle.Intersects(actor->GetCircle()))
	{
		if (std::shared_ptr<FloorChange> change = dynamic_pointer_cast<FloorChange>(m_obj))
		{
			//std::shared_ptr<TileMapComponent> map = Engine::GetActiveScene()->ents.find("TileMap")[0]->GetCompatibleComponent<TileMapComponent>()[0];
			counter += change->GetDir();
			m_map->GetCompatibleComponent<TileMapComponent>()[0]->GenerateOtherMap(counter);
		}
		else if (std::shared_ptr<Door> door = dynamic_pointer_cast<Door>(m_obj))
		{
			if (!door->IsLocked())
			{
				door->ToggleOpen();
			}
		}
		else if (std::shared_ptr<AutoShop> shop = dynamic_pointer_cast<AutoShop>(m_obj))
		{
			// Not implemented due to time constraints. :'(
		}
		else if (std::shared_ptr<SkillLibrary> sL = dynamic_pointer_cast<SkillLibrary>(m_obj))
		{
			if (actor->GetID() == 0)
			{
				shared_ptr<SkillsComponent> skills = _parent->GetCompatibleComponent<SkillsComponent>()[0];
				skills->AddSkillPoint();
			}
		}
	}
}
