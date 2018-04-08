#pragma once

#include "ecm.h"

class System_Player_Controls : public Component {
protected:
	float speed;
	
public:
	explicit System_Player_Controls(Entity* p);
	System_Player_Controls() = delete;
};