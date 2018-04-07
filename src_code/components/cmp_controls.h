#pragma once

#include "ecm.h"

class ControlsComponent : public Component {
protected:
	float speed;
	
public:
	void update(double dt) override;
	void render() override {};
	explicit ControlsComponent(Entity* p);
	ControlsComponent() = delete;
};