#pragma once
#include "Entity.h"
#include <cmath>

class Tile : public SpriteComponent
{
public:
	Tile() = delete;
	explicit Tile(Entity *const e);

	std::vector<std::shared_ptr<Entity>> GetOccupants();
	void AddOccupant(std::shared_ptr<Entity> e);
	void RemoveOccupant(std::shared_ptr<Entity> e);

	char GetTileIdx();
	char GetSetIdx();
	char GetAirX();
	char GetAirY();

	void SetTickVars(float tickDmg, float timeMult);
	void SetTileIdx(char idx);
	void ChangeSetIdx(char idx);
	void SetAirX(char val);
	void SetAirY(char val);
	void SetSpeedMult(float val);

	void UpdateMe(double dt) override;
	void DrawMe() override;
private:
	bool m_walkable;
	std::vector<std::shared_ptr<Entity>> m_occupants;
	
	char m_tileIdx;
	char m_tileSet;

	char m_airX;
	char m_airY;

	float m_tickDmg;
	float m_tickTimeMult;
	float m_tickTime;

	float m_speedMult;
};