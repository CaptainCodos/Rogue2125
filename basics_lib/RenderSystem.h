#pragma once
#include <SFML\Graphics.hpp>

namespace Renderer
{
	void init(sf::RenderWindow &window);
	sf::RenderWindow &getWindow();

	void Shutdown();
	void Update(const double &dt);
	void Queue(sf::Drawable *sprite);
	void Draw();
};