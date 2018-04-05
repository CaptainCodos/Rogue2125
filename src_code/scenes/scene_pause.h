#pragma once

#include "engine.h"

class PauseScene : public Scene {
public:
	PauseScene() = default;
	~PauseScene() override = default;

	void Load() override;

	void Update(const double& dt) override;
};