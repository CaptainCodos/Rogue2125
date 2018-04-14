#pragma once

#include "ecm.h"

class ActorMoveComp : public Component
{
public:
	ActorMoveComp() = delete;
	ActorMoveComp(Entity* p);
	~ActorMoveComp() = default;

	void update(double dt) override;
	void render() override;

	void SetMaxSpeed(float speed);
	void SetBaseMaxSpeed(float speed);

	float GetBaseMaxSpeed();
	sf::Vector2f& GetVelRef();
	sf::Vector2f GetVel();
	sf::Vector2f& GetAccel();
protected:

private:
	float m_baseMaxSpeed;
	float m_maxSpeed;

	sf::Vector2f m_vel;
	sf::Vector2f m_accel;
	sf::Vector2f m_drag;

	//float GetMaxSpeed();
	sf::Vector2f CalculateAccel(float max);
};