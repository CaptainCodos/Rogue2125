#pragma once

#include "engine.h"

class HighscoresScene : public Scene {
public:
	HighscoresScene() = default;
	~HighscoresScene() override = default;

	void Load() override;

	void Update(const double& dt) override;
};