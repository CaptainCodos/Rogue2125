#pragma once
#include "ecm.h"

class PickupComponent : public Component {
protected:
	std::vector<std::shared_ptr<Entity>> _ents;

public:
	PickupComponent() = delete;
	explicit PickupComponent(Entity* p);

	void render() override {}
	void update(double dt) override;
	void setEntities(std::vector<std::shared_ptr<Entity>>& e);
};