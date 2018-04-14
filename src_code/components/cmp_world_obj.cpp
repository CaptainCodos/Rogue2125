#include "cmp_world_obj.h"
#include "cmp_skills.h"
#include "../game.h"
//#include "cmp_tilemap.h"

using namespace std;
using namespace DataShapes;

WorldObjComp::WorldObjComp(Entity * p, WorldObj obj) 
	: TextureComponent(p)
{
	m_obj = obj;

	m_useCircle = Circle(36.0f, p->getPosition());

	m_map = _parent->scene->ents.find("TileMap")[0]->GetCompatibleComponent<TileMapComponent>()[0];
}

int WorldObjComp::GetObjID() { return m_obj.GetSecID(); }

void WorldObjComp::UseObj(shared_ptr<ActorStatsComponent> actor)
{
	if (m_useCircle.Intersects(actor->GetCircle()))
	{
		if (FloorChange* change = dynamic_cast<FloorChange*>(&m_obj))
		{
			//std::shared_ptr<TileMapComponent> map = _parent->scene->ents.find("TileMap")[0]->GetCompatibleComponent<TileMapComponent>()[0];
			counter += change->GetDir();
			m_map->GenerateOtherMap(counter);
		}
		else if (Door* door = dynamic_cast<Door*>(&m_obj))
		{
			if (!door->IsLocked())
			{
				door->ToggleOpen();
			}
		}
		else if (AutoShop* shop = dynamic_cast<AutoShop*>(&m_obj))
		{
			// Not implemented due to time constraints. :'(
		}
		else if (SkillLibrary* lib = dynamic_cast<SkillLibrary*>(&m_obj))
		{
			if (actor->GetID() == 0)
			{
				shared_ptr<SkillsComponent> skills = _parent->GetCompatibleComponent<SkillsComponent>()[0];
				skills->AddSkillPoint();
			}
		}
	}
}
