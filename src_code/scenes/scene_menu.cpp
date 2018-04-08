#include "scene_menu.h"
#include "system_player_controls.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_tilemap.h"
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
	view = View(FloatRect(0, 0, 1920, 1080));
	Engine::GetWindow().setView(view);
	cout << "Menu Load \n";
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"Platformer\nPress Space to Start");
		
		auto tm = makeEntity();
		auto tmC = tm->addComponent<TileMapComponent>(txrMgr, counter);
	}

	counter++;
	cout << "Test: " << counter << "\n";

	setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

	txrMgr->UpdateAnims(dt);
	CheckCameraInput(view, zoom, dt);

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
	  Engine::ChangeScene(&menu);
  }

  Scene::Update(dt);
}
