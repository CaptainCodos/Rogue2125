#include "cmp_collision_handler.h"

#include "../src_code/components/cmp_player_movement.h"
#include "../cmp_actor_stats.h"
#include "../src_code/components/cmp_attack.h"
#include "SFML\Graphics.hpp"
#include "maths.h"


using namespace std;
using namespace sf;

ColHandlerComp::ColHandlerComp(Entity* p) 
	: Component(p)
{
	//vector<shared_ptr<Entity>> tileMap = _parent->scene->ents.find("TileMap");
	m_map = _parent->GetCompatibleComponent<TileMapComponent>()[0];
}

void ColHandlerComp::update(double dt)
{
	vector<shared_ptr<Entity>> attacks = _parent->scene->ents.find("Attack");
	vector<shared_ptr<Entity>> actors = _parent->scene->ents.find("Actor");
	vector<shared_ptr<Entity>> player = _parent->scene->ents.find("Player");

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

			if (actorComp->GetID() != attack->GetSenderID() && attack->GetCircle().Intersects(actorComp->GetCircle(), dir))
			{

				cout << "Ouch!\n";
				attacks[i]->setForDelete();
			}
		}
	}
}

void ColHandlerComp::HandleActors(vector<shared_ptr<Entity>> &actors)
{

}

void ColHandlerComp::HandlePlayer(vector<shared_ptr<Entity>> &actors)
{
	for (int i = 0; i < actors.size(); i++)
	{
		shared_ptr<ActorStatsComponent> actor = actors[i]->GetCompatibleComponent<ActorStatsComponent>()[0];
		Vector2i coords = actor->GetCoords();

		vector<vector<shared_ptr<TileComponent>>> tiles = m_map->GetAllNeighbourTiles(coords.x, coords.y);

		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (tiles[y][x] != nullptr)
				{
					Vector2i diff = coords - tiles[y][x]->GetCoords();

					if ((diff.x == tiles[y][x]->GetFreeX() || tiles[y][x]->GetFreeX() == 0) && tiles[y][x]->GetFreeX() != 2
						&& (diff.y == tiles[y][x]->GetFreeY() || tiles[y][x]->GetFreeY() == 0) && tiles[y][x]->GetFreeY() != 2
						&& !tiles[y][x]->GetWalkable())
					{
						float depth;
						int dir;

						if (actor->GetRect().Intersects(tiles[y][x]->GetRect(), depth, dir))
						{
							Vector2f diffTrue = actor->GetTrueCoords() - tiles[y][x]->GetTrueCoords();
							Vector2f v = actor->GetMoveComp()->GetVel();
							float dotV = dot(diffTrue, v);

							if (dotV < 0.0f)
							{
								switch (dir)
								{
								case 0:
									actor->GetMoveComp()->GetVelRef().x = 0.0f;
									break;
								case 1:
									actor->GetMoveComp()->GetVelRef().y = 0.0f;
									break;
								}
							}

							
						}
					}
				}
			}
		}
	}
}