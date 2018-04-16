#include "scene_gameplay.h"
#include "system_player_controls.h"
#include "../buttons.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_button.h"
#include "../components/cmp_menu.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;
using namespace Input;

void MenuScene::Load()
{
	cout << "Menu Load \n";
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"Platformer\nPress Space to Start");
		t->SetPos(Vector2f(Engine::getWindowSize().x / 2 - 140.0f, Engine::getWindowSize().y / 2 - 200.f));

		// Button loading - method 1 (Component approach)
		auto menu = makeEntity();
		auto m = menu->addComponent<MenuComponent>();

		// Button loading - method 2
		/*shared_ptr<Entity> btn_highscores;
		btn_highscores.reset();
		btn_highscores = new_button("Highscores");
		btn_highscores->setPosition(Vector2f(Engine::getWindowSize().x / 2 - 400.0f, Engine::getWindowSize().y / 2));*/

		sf::View m_camera = View(FloatRect(0, 0, 1600, 900));
		Engine::GetWindow().setView(m_camera);
	}
	setLoaded(true);
}

void MenuScene::Update(const double& dt) {
	// cout << "Gameplay Update "<<dt<<"\n";

	txrMgr->UpdateAnims(dt);

	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		Engine::ChangeScene(&gameplay, "gameplay");
	}

	Scene::Update(dt);
}
