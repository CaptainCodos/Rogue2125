#include "scene_menu.h"
//#include "system_player_controls.h"

#include "../general/equipment.h"
#include "../buttons.h"
#include "ecm.h"

#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_tilemap.h"
#include "../components/cmp_actor_stats.h"
#include "../components/cmp_button.h"
#include "../components/cmp_menu.h"

#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

View view;
float zoom;

void GameplayScene::Load()
{
	/*counter++;
	cout << "Test: " << counter << "\n";*/
	zoom = 1.0f;
	//view = View(FloatRect(0, 0, 1600, 900));
	//Engine::GetWindow().setView(view);
	cout << "Gameplay Load \n";
	{
		auto tm = makeEntity();
		shared_ptr<TileMapComponent> tmC = tm->addComponent<TileMapComponent>(txrMgr, counter);
		tmC->GenerateMapObjs();

		/*auto a = makeEntity();
		auto aC = a->addComponent<ActorStatsComponent>();*/
	}

	//counter++;
	cout << "Test: " << counter << "\n";

	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	setLoaded(true);
}

void GameplayScene::Update(const double& dt) {
	// cout << "Menu Update "<<dt<<"\n";

	txrMgr->UpdateAnims(dt);

	if (sf::Keyboard::isKeyPressed(Keyboard::F3)) {
		counter--;
		Engine::ChangeScene(&menu, "menu");
	}

	Scene::Update(dt);
}