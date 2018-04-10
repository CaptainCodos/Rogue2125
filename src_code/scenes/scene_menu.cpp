#include "scene_menu.h"
#include "system_player_controls.h"

#include "../general/equipment.h"

#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_tilemap.h"
#include "../components/cmp_actor_stats.h"
#include "../components/cmp_inventory.h"

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

		auto a = makeEntity();
		auto aC = a->addComponent<ActorStatsComponent>();
	}

	counter++;
	cout << "Test: " << counter << "\n";

	shared_ptr<Useable> gA = make_shared<Useable>(Useable());
	gA->GenerateItem();

	shared_ptr<Useable> gB = make_shared<Useable>(Useable());
	gB->GenerateItem();

	shared_ptr<Useable> gC = make_shared<Useable>(Useable());
	gC->GenerateItem();

	shared_ptr<Useable> gD = make_shared<Useable>(Useable());
	gD->GenerateItem();

	shared_ptr<TankGun> eD = make_shared<TankGun>(TankGun());
	eD->GenerateItem();

	auto i = makeEntity();
	auto iC = i->addComponent<InventoryComponent>();

	iC->AddItem(gA);
	iC->AddItem(gB);
	iC->AddItem(gC);
	iC->AddItem(gD);
	iC->AddItem(eD);

	//iC->SaveInventory();
	iC->FlushInventory();
	iC->LoadInventory();
	iC->PrintAllItems();

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

	txrMgr->UpdateAnims(dt);
	CheckCameraInput(view, zoom, dt);
	GetMouseClick();
	GetMousePos();

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
	  Engine::ChangeScene(&menu);
  }

  Scene::Update(dt);
}
