#pragma once

#include "engine.h"

class MenuScene : public Scene {
public:
  MenuScene() = default;
  ~MenuScene() override = default;

  void Load() override;

  void Update(const double& dt) override;

private:
	std::vector<std::shared_ptr<Entity>> buttons;

	std::shared_ptr<Entity> _btn_start_game;
	std::shared_ptr<Entity> _btn_options;
	std::shared_ptr<Entity> _btn_pause;

	// DEBUG
	std::shared_ptr<Entity> _btn_close;
};
