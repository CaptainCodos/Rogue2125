#include "cmp_collision_handler.h"

#include "../src_code/components/cmp_player_movement.h"
#include "../cmp_actor_stats.h"
#include "../src_code/components/cmp_attack.h"
#include "SFML\Graphics.hpp"
#include "maths.h"
#include "engine.h"


using namespace std;
using namespace sf;

using namespace DataShapes;

ColHandlerComp::ColHandlerComp(Entity* p) 
	: Component(p)
{
	//vector<shared_ptr<Entity>> tileMap = Engine::GetActiveScene()->ents.find("TileMap");
	m_map = _parent->GetCompatibleComponent<TileMapComponent>()[0];
}

void ColHandlerComp::update(double dt)
{
	vector<shared_ptr<Entity>> attacks = Engine::GetActiveScene()->ents.find("Attack");
	vector<shared_ptr<Entity>> actors = Engine::GetActiveScene()->ents.find("Actor");
	vector<shared_ptr<Entity>> player = Engine::GetActiveScene()->ents.find("Player");

	HandleAttacks(attacks, actors);
	HandleActors(actors);
	HandlePlayer(player);
}

void ColHandlerComp::render() {}

void ColHandlerComp::HandleAttacks(vector<shared_ptr<Entity>> &attacks, vector<shared_ptr<Entity>> &actors)
{
	for (int i = 0; i < attacks.size(); i++)
	{
		shared_ptr<AttackComponent> attack = attacks[i]->GetCompatibleComponent<AttackComponent>()[0];
		Vector2i coords = Vector2i(attack->GetCircle().pos.x / 32, attack->GetCircle().pos.y / 32);

		shared_ptr<TileComponent> tile = m_map->GetTile(coords.x, coords.y);
		
		if (tile != nullptr)
		{
			if (!tile->GetWalkable())
			{
				attacks[i]->setForDelete();
			}
		}
		else
		{
			attacks[i]->setForDelete();
		}

		for (int j = 0; j < actors.size(); j++)
		{
			shared_ptr<ActorStatsComponent> actorComp = actors[j]->GetCompatibleComponent<ActorStatsComponent>()[0];

			Vector2f dir;
			int d;

			if (actorComp->IsPhysical())
			{
				if (actorComp->GetID() != attack->GetSenderID() && attack->GetCircle().Intersects(actorComp->GetCircle(), dir))
				{
					actorComp->ApplyDamage(attack->GetData().dmg, attack->GetData().types);
					actorComp->GetMoveComp()->GetVelRef() += (attack->GetData().vel * 10.0f);
					cout << "Ouch!\n";
					attacks[i]->setForDelete();
				}
			}
		}
	}
}

void ColHandlerComp::HandleActors(vector<shared_ptr<Entity>> &actors)
{
	for (int i = 0; i < actors.size(); i++)
	{
		shared_ptr<ActorStatsComponent> actor = actors[i]->GetCompatibleComponent<ActorStatsComponent>()[0];
		Vector2i coords = actor->GetCoords();
		Vector2f vel = actor->GetMoveComp()->GetVel();
		Rectangle rect = actor->GetRect();

		vector<vector<shared_ptr<TileComponent>>> tiles = m_map->GetAllNeighbourTiles(coords.x, coords.y);

		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (tiles[y][x] != nullptr)
				{
					Vector2i axis = Vector2i(0, 0);
					float depth = 0.0f;

					if (tiles[y][x]->GetRect().Intersects(rect, depth, axis) && !tiles[y][x]->GetWalkable())
					{
						Vector2i r = coords - tiles[y][x]->GetCoords();

						if ((axis.x == r.x || tiles[y][x]->GetFreeX() == 0) && tiles[y][x]->GetFreeX() != 2)
						{
							if (axis.x * vel.x < 0.0f && tiles[y][x]->GetFreeX() * axis.x >= 0)
							{
								actor->GetMoveComp()->GetVelRef().x = 0.0f;
							}
						}

						if ((axis.y == r.y || tiles[y][x]->GetFreeY() == 0) && tiles[y][x]->GetFreeY() != 2)
						{
							if (axis.y * vel.y < 0.0f && tiles[y][x]->GetFreeY() * axis.y >= 0)
							{
								actor->GetMoveComp()->GetVelRef().y = 0.0f;
							}
						}
					}
				}
			}
		}
	}
}

void ColHandlerComp::HandlePlayer(vector<shared_ptr<Entity>> &actors)
{
	
}