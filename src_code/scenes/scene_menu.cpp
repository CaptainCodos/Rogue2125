#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_tilemap.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

View view;
float zoom;

void MenuScene::Load() 
{
	zoom = 1.0f;
	view = View(FloatRect(0, 0, 1920, 1080));
	Engine::GetWindow().setView(view);
	cout << "Menu Load \n";
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>(
			"Platformer\nPress Space to Start");
		
		auto tm = makeEntity();
		auto tmC = tm->addComponent<TileMapComponent>(txrMgr, 0);
	}
	setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

	txrMgr->UpdateAnims(dt);

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
	  Engine::ChangeScene(&gameplay);
  }

  if (sf::Keyboard::isKeyPressed(Keyboard::S)) {
	  view.move(0, dt * 300.0f);
  }
  if (sf::Keyboard::isKeyPressed(Keyboard::W)) {
	  view.move(0, -dt * 300.0f);
  }

  if (sf::Keyboard::isKeyPressed(Keyboard::A)) {
	  view.move(-dt * 300.0f, 0);
  }
  if (sf::Keyboard::isKeyPressed(Keyboard::D)) {
	  view.move(dt * 300.0f, 0);
  }

  if (sf::Keyboard::isKeyPressed(Keyboard::Q)) {
	  zoom += dt;
  }
  if (sf::Keyboard::isKeyPressed(Keyboard::E)) {
	  zoom -= dt;
  }

  view.zoom(zoom);

  zoom = 1.0f;
  Engine::GetWindow().setView(view);

  Scene::Update(dt);
}
