#pragma once
#include <AllMgrs.h>
#include "ecm.h"
#include "../general/data_shapes.h"
#include "cmp_actor_move.h"

class ActorStatsComponent : public Component 
{
public:
	ActorStatsComponent() = delete;

	explicit ActorStatsComponent(Entity* p);

	void update(double dt) override;
	void render() override;

	int GetID();
	std::shared_ptr<ActorMoveComp> GetMoveComp();
	DataShapes::Circle GetCircle();
	DataShapes::Rectangle GetRect();
	sf::Vector2f GetTrueCoords();
	sf::Vector2i GetCoords();

	void SetPosition(sf::Vector2f pos);
	void ApplyDamage(float dmg, std::vector<int> dmgTypes /* Add attack parameter here. This will be some projectile component or something. */);	// Apply damage to actor. dmgTypes is used to apply to resistance.
	void GenerateStats(int ID);	// Used to generate stats according to actor type. Actor may be world object like box, an enemy or player.
protected:

private:
	std::shared_ptr<ActorMoveComp> m_moveComp;

	DataShapes::Circle m_circle;
	DataShapes::Rectangle m_rect;

	std::string m_name;
	int m_actorID;
	bool m_isInvincible;	// Checks if actor can be damaged

	float m_hp;		// Actor's hp.
	float m_en;		// Actor's energy value.

	float m_maxHP;
	float m_maxEn;

	sf::Vector2i m_actorCoords;	// Coords of the actor in the world.
	sf::Vector2i m_oldCoords;
	//std::shared_ptr<TileMapComponent> m_tileMap;
	int m_map;					// Map the actor exists on.

	float m_baseArmour;		// Base armour value to determine resistances.

	float m_resistances[5];	// 0 = physical, 1 = heat, 2 = electric, 3 = toxic, 4 = cold
	float m_stats[3];
	float m_maxStats[3];

	void GeneratePlayerStats();
	void GenerateEnemyStats();
	void GenerateWObjStats();

	void OnDeath();			// Determines death behaviour. It may spawn an effect or drop item etc...
};