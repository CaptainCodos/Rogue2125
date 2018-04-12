#pragma once

#include "ecm.h"
#include "cmp_sprite.h"
#include "../general/damage_object.h"

class AttackComponent : public AnimComponent
{
public:
	AttackComponent() = delete;
	AttackComponent(Entity* p, DmgData data);
	~AttackComponent() = default;

	void update(double dt) override;
protected:

private:
	DmgData m_data;
};