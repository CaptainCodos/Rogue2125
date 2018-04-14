#pragma once
#include "ecm.h"

class MenuComponent : public Component {
public:
	MenuComponent(Entity* p);
	~MenuComponent() = default;

	void LoadButtons();

	void update(double dt) override;
private:
	std::vector<std::shared_ptr<Entity>> buttons;

	std::shared_ptr<Entity> _btn_start_game;
	std::shared_ptr<Entity> _btn_options;
	std::shared_ptr<Entity> _btn_pause;

	// DEBUG
	std::shared_ptr<Entity> _btn_close;
};