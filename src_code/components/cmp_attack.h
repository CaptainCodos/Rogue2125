#pragma once

#include "ecm.h"
#include "cmp_sprite.h"
#include "../general/damage_object.h"
#include "../general/data_shapes.h"

class AttackComponent : public AnimComponent
{
public:
	AttackComponent() = delete;
	AttackComponent(Entity* p, DmgData data);
	~AttackComponent() = default;

	int GetSenderID();
	DataShapes::Circle GetCircle();

	void update(double dt) override;
protected:

private:
	DataShapes::Circle m_circle;
	DmgData m_data;
	float m_life;
};