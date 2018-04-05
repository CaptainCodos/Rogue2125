#pragma once

#include "engine.h"

class GameplayScene : public Scene {
public:
	GameplayScene() = default;
	~GameplayScene() override = default;

	void Load() override;

	void Update(const double& dt) override;
};