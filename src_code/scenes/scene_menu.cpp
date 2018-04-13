#include "scene_menu.h"
//#include "system_player_controls.h"

#include "../general/equipment.h"
#include "../buttons.h"
#include "ecm.h"

#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_tilemap.h"
#include "../components/cmp_actor_stats.h"

#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;
using namespace controls;

View view;
float zoom;

void MenuScene::Load() 
{
	/*counter++;
	cout << "Test: " << counter << "\n";*/
	zoom = 1.0f;
	//view = View(FloatRect(0, 0, 1600, 900));
	//Engine::GetWindow().setView(view);
	cout << "Menu Load \n";
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"Platformer\nPress Space to Start");
		
		auto tm = makeEntity();
		auto tmC = tm->addComponent<TileMapComponent>(txrMgr, counter);

		auto a = makeEntity();
		auto aC = a->addComponent<ActorStatsComponent>();


	}

	// Button loading
	buttons.clear();
	_btn_start_game.reset();
	_btn_start_game = new_button("Start");
	buttons.push_back(_btn_start_game);

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->setPosition({ (float)Engine::GetWindow().getSize().x / 2, (70.0f * i) + 200.0f });
	}

	//counter++;
	cout << "Test: " << counter << "\n";

	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

	txrMgr->UpdateAnims(dt);

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
	  counter++;
	  Engine::ChangeScene(&menu);
  }
  if (sf::Keyboard::isKeyPressed(Keyboard::V)) {
	  counter--;
	  Engine::ChangeScene(&menu);
  }

  Scene::Update(dt);
}
