#include "cmp_actor_stats.h"
#include "cmp_inventory.h"
#include "cmp_skills.h"
#include "cmp_player_movement.h"
#include "cmp_actor_move.h"

#include "cmp_sprite.h"
//#include "cmp_physics.h"

#include "system_physics.h"
#include "cmp_world_obj.h"
#include "cmp_interactable.h"
#include "engine.h"
//#include <Box2D/Dynamics/b2Body.h>

using namespace std;
using namespace sf;

using namespace Physics;
using namespace DataShapes;

ActorStatsComponent::ActorStatsComponent(Entity* p)
	: Component(p)
{
	_parent->addTag("Actor");
	m_moveComp = _parent->addComponent<ActorMoveComp>();

	float s = 20.0f;
	m_circle = Circle(s / 2.0f, p->getPosition());
	m_rect = Rectangle(p->getPosition(), Vector2f(s, s));
	m_rect.SetPosCentre(p->getPosition());
	//m_rect.SetSize(Vector2f(20.0f, 20.0f));

	for (int i = 0; i < 5; i++)
	{
		m_resistances[i] = 0.0f;
	}

	m_isInvincible = false;
	m_isDynamic = true;
	m_isPhysical = true;

	m_hp = 10.0f;
	m_effects = vector<StatusEffect>();

	m_placed = true;
}

int ActorStatsComponent::GetID() { return m_actorID; }
int ActorStatsComponent::GetSecID() { return m_secID; }

bool ActorStatsComponent::IsDynamic() { return m_isDynamic; }
bool ActorStatsComponent::IsPhysical() { return m_isPhysical; }

shared_ptr<ActorMoveComp> ActorStatsComponent::GetMoveComp() { return m_moveComp; }
Circle ActorStatsComponent::GetCircle() { return m_circle; }
Rectangle ActorStatsComponent::GetRect() { return m_rect; }
Vector2i ActorStatsComponent::GetCoords() { return m_actorCoords; }
Vector2f ActorStatsComponent::GetTrueCoords() { return _parent->getPosition(); }

void ActorStatsComponent::SetPosition(Vector2f pos) { _parent->setPosition(pos); }

void ActorStatsComponent::update(double dt)
{
	m_circle.pos = _parent->getPosition();
	m_rect.SetPosCentre(_parent->getPosition());
	Vector2f pPos = _parent->getPosition();
	m_actorCoords = Vector2i(pPos / 32.0f);

	if (m_hp <= 0.0f)
	{
		OnDeath();
		_parent->setForDelete();

		return;
	}
	if (m_placed && m_actorID <= 1)
	{
		/*for (size_t i = 0; i < _components.size(); i++) {
			if (_components[i]->is_fordeletion()) {
				_components.erase(_components.begin() + i);
				--i;
			}
			_components[i]->update(dt);
		}*/
		for (int i = 0; i < m_effects.size(); i++)
		{
			if (m_effects[i].ToBeDeleted())
			{
				m_effects.erase(m_effects.begin() + i);
				--i;
			}
		}
		for (int i = 0; i < m_effects.size(); i++)
		{
			m_effects[i].update(dt);
			GetMoveComp()->SetSpeedMod(m_effects[i].GetSpeedMod());
			float e = 0.0f;

			if (m_effects[i].IsTriggering())
			{
				float dmg = 0.0f;
				m_effects[i].DeliverEffect(dmg, 100.0f, e, e);
				vector<int> type = vector<int>();
				type.push_back(m_effects[i].GetDmgType());
				ApplyDamage(-dmg, type);
			}
				
		}

		if (m_effects.size() <= 0)
		{
			GetMoveComp()->SetSpeedMod(1.0f);
		}

		GetTileEffect();


		/*cout << "HP: " << m_hp << "\n";
		cout << "Effects: " << m_effects.size() << "\n";
		cout << "X: " << m_actorCoords.x << " Y: " << m_actorCoords.y << "\n";*/
	}

	//cout << "HP: " << m_hp << "\n";
	
	m_oldCoords = m_actorCoords;
}

void ActorStatsComponent::render()
{

}

void ActorStatsComponent::ApplyDamage(float dmg, vector<int> dmgTypes)
{
	if (m_isInvincible)
		return;

	if (m_actorID == 0)
	{
		for (int i = 0; i < dmgTypes.size(); i++)
		{
			float iDmg = dmg / dmgTypes.size();

			vector<shared_ptr<Equipment>> eq = _parent->GetCompatibleComponent<InventoryComponent>()[0]->GetEquipped();
			float totalRes = 0.0f;
			for (int k = 0; k < eq.size(); k++)
			{
				totalRes += (m_resistances[dmgTypes[i]] * (1.0f + (0.04f * _parent->GetCompatibleComponent<SkillsComponent>()[0]->GetTotalSkill(eq, 5 + dmgTypes[i])))) + eq[k]->GetResistMod(dmgTypes[i]);
			}

			if (totalRes > 0.8f)
				totalRes = 0.8f;
			else if (totalRes < -0.5f)
				totalRes = -0.5f;

			m_hp -= iDmg * (1.0f - totalRes);
		}
	}
	else
	{
		for (int i = 0; i < dmgTypes.size(); i++)
		{
			float iDmg = dmg / dmgTypes.size();

			float totalRes = m_resistances[dmgTypes[i]];

			m_hp -= iDmg * (1.0f - totalRes);
		}
	}

	if (m_hp <= 0.0f)
	{
		OnDeath();
		_parent->setForDelete();
	}
}

void ActorStatsComponent::GenerateStats(int ID)
{
	m_actorID = ID;

	

	//int secID = 0;

	switch (ID)
	{
	case 0:
		GeneratePlayerStats();
		break;
	case 1:
		_parent->addTag("Enemy");

		m_secID = RandomInt(0, 3);
		break;
	case 2:
		GenerateInteractable();
		break;
	case 3:
		GenerateWObjStats();
		break;
	}
}

void ActorStatsComponent::GeneratePlayerStats()
{
	m_placed = true;
	m_resistances[0] = 0.15f;
	m_resistances[1] = 0.1f;
	m_resistances[2] = 0.05f;
	m_resistances[3] = 0.0f;
	m_resistances[4] = 0.1f;

	m_hp = 1000.0f;

	shared_ptr<SkillsComponent> a = _parent->addComponent<SkillsComponent>();
	shared_ptr<InventoryComponent> b = _parent->addComponent<InventoryComponent>();
	shared_ptr<PlayerMoveComp> c = _parent->addComponent<PlayerMoveComp>(m_moveComp, b, a);

	_parent->addTag("Player");
}

void ActorStatsComponent::GenerateEnemyStats()
{
	m_placed = true;

}

void ActorStatsComponent::GenerateInteractable()
{
	m_placed = true;
	_parent->addTag("Interactable");

	m_secID = RandomInt(0, 3);

	switch (m_secID)
	{
	case 0:
		_parent->addComponent<InteractComp>(make_shared<Barrel>());
		break;
	case 1:
		_parent->addComponent<InteractComp>(make_shared<Crate>());
		break;
	case 2:
		m_isDynamic = false;
		m_isPhysical = false;
		_parent->addComponent<InteractComp>(make_shared<Trap>());
		break;
	}
}

void ActorStatsComponent::GenerateWObjStats()
{
	m_placed = true;
	_parent->addTag("World");

	m_isInvincible = true;
	m_isDynamic = false;

	m_secID = 3;

	switch (m_secID)
	{
	case 0:
		m_isPhysical = false;
		break;
	case 1:
		m_isInvincible = false;
		m_hp = 1000.0f;
		break;
	case 2:

		break;
	case 3:
		_parent->addComponent<WorldObjComp>(make_shared<SkillLibrary>());
		break;
	}
}

void ActorStatsComponent::GenerateDoor(int dir)
{
	m_placed = true;
	_parent->addTag("World");

	m_secID = 1;
	m_actorID = 3;

	if (dir == 0)
		_parent->setRotation(0.0f);
	else
		_parent->setRotation(90.0f);

	_parent->addComponent<WorldObjComp>(make_shared<Door>());
}

void ActorStatsComponent::GenerateFloorChange(int dir)
{
	m_placed = true;
	_parent->addTag("World");

	m_secID = 0;
	m_actorID = 3;

	m_isPhysical = false;

	/*shared_ptr<FloorChange> change = make_shared<FloorChange>();
	change->GenerateData(dir);*/

	_parent->addComponent<WorldObjComp>(make_shared<FloorChange>(dir));
}

void ActorStatsComponent::GetTileEffect()
{
	std::shared_ptr<TileComponent> tile = Engine::GetActiveScene()->ents.find("TileMap")[0]->GetCompatibleComponent<TileMapComponent>()[0]->GetTile(m_actorCoords.x, m_actorCoords.y);

	if (tile != nullptr)
	{
		if (tile->GetEffectID() != 10)
		{
			bool found = false;
			for (int i = 0; i < m_effects.size(); i++)
			{
				if (tile->GetEffectID() == m_effects[i].GetEffectID())
				{
					if (m_effects[i].GetStacks() <= 0)
					{
						m_effects[i].AddStack();
					}
					
					found = true;
					return;
				}
			}

			if (!found)
			{
				m_effects.push_back(StatusEffect(tile->GetEffectID()));
			}
			
		}
	}
}

void ActorStatsComponent::OnDeath()
{

}