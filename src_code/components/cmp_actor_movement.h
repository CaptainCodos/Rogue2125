#pragma once
#include <ecm.h>

class ActorMovementComponent : public Component {
protected:
  bool validMove(const sf::Vector2f&);
  float _speed;

public:
  void update(double dt) override;
  void move(const sf::Vector2f&);
  void move(float x, float y);
  void render() override {}
  float getSpeed() const;
  void setSpeed(float _speed);
  explicit ActorMovementComponent(Entity* p);
  ActorMovementComponent() = delete;
};
