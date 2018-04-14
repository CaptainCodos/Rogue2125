#pragma once
#include "ecm.h"

class MenuComponent : public Component {
public:
	MenuComponent(Entity* p);
	~MenuComponent() = default;

	void LoadButtons();

	void update(double dt) override;
	void render() override;
private:
	std::vector<std::shared_ptr<Entity>> buttons;

	std::shared_ptr<Entity> _btn_start_game;
	std::shared_ptr<Entity> _btn_settings;
	std::shared_ptr<Entity> _btn_highscores;
	std::shared_ptr<Entity> _btn_quit;
};