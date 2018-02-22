#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>
#include <EntityLib.h>
#include <iostream>
#include "TestScene.h"

// namespaces
using namespace sf;
using namespace std;

// Define Controls
const Keyboard::Key keys[4] =
{
	Keyboard::W,
	Keyboard::S,
	Keyboard::Up,
	Keyboard::Down
};

// Window size
int wWidth = 1280;
int wHeight = 720;

static SceneMgr* sM;

// Game start up method
void Initialize(RenderWindow &window)
{
	sf::FloatRect area(0, 0, 1920, 1080);
	window.setView(sf::View(area));
	
	Renderer::init(window);
}

// Load sounds, art etc....
void LoadContent()
{
	sM = SceneMgr::GetInstance();
	sM->m_scenes.push_back(make_shared<TestScene>());
	sM->m_activeScene = sM->m_scenes[0];
	sM->m_activeScene->LoadScene();
}

// Update loop
void Update(RenderWindow &window)
{
	static Clock clock;
	float dt = clock.restart().asSeconds();

	Event event;

	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
		window.close();

	sM->UpdateActive(dt);
}

// Draw Game
// Clear window, draw items, then display all
void Draw(RenderWindow &window)
{
	sM->DrawActive();
}

int main()
{
	wWidth = VideoMode::getDesktopMode().width;
	wHeight = VideoMode::getDesktopMode().height;
	RenderWindow window(sf::VideoMode(wWidth, wHeight), "Rogue: 2125", Style::Fullscreen);
	window.setVerticalSyncEnabled(false);

	Initialize(window);
	LoadContent();

	// loop until closed
	while (window.isOpen())
	{
		Update(window);
		Draw(window);
	}

	return 0;
}