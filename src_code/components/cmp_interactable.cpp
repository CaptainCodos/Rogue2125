#include "cmp_interactable.h"
#include "engine.h"

using namespace std;
using namespace sf;
using namespace DataShapes;

InteractComp::InteractComp(Entity * p, std::shared_ptr<Interactable> obj)
	: AnimComponent(p)
{
	m_obj = obj;
	m_useCircle = Circle(20.0f, _parent->getPosition());

	SetTexture(TextureMgr::GetInstance()->sheet_NPA_Textures[m_obj->GetPriID()][m_obj->GetSecID()], 32);
	SetOrigin(Vector2f(0.5f, 0.5f));

	SetAnimates(false);
	SetScale(0.75f);

	if (std::shared_ptr<Trap> trap = dynamic_pointer_cast<Trap>(m_obj))
	{
		SetFrame(trap->GetTrapID() == 0 ? 0 : 1);
	}
}

int InteractComp::GetObjID() { return m_obj->GetSecID(); }

void InteractComp::UseObj(std::shared_ptr<ActorStatsComponent> actor)
{
	if (m_useCircle.Intersects(actor->GetCircle()) && m_obj->GetSecID() == 2)
	{
		
	}
}
