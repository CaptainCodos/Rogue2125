#include "cmp_pickup.h"
#include "cmp_actor_movement.h"

PickupComponent::PickupComponent(Entity* p) : Component(p) {}

void PickupComponent::update(double dt) {
	for (auto e : _ents) {
		if (length(_parent->getPosition() - e->getPosition()) < 30.0f) {

			auto cp = e->GetCompatibleComponent<ActorMovementComponent>()[0];

			if (cp != nullptr) {
				cp->setSpeed(cp->getSpeed() + 1.0f);
				_parent->setForDelete();
				break;
			}
		}
	}
}

void PickupComponent::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_ents = e;
}