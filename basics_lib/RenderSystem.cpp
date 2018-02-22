#include "RenderSystem.h"
#include <queue>

using namespace std;
using namespace sf;

static queue<const Drawable*> sprites;
static RenderWindow *rw;

void Renderer::init(sf::RenderWindow &window) { rw = &window; }

sf::RenderWindow &Renderer::getWindow() { return *rw; }

void Renderer::Shutdown()
{
	while (!sprites.empty())
		sprites.pop();
}

void Renderer::Update(const double &dt) {}

void Renderer::Draw()
{
	if (rw == nullptr)
	{
		throw("No render window set!");
	}

	while (!sprites.empty())
	{
		rw->draw(*sprites.front());
		sprites.pop();
	}
}

void Renderer::Queue(sf::Drawable *sprite) { sprites.push(sprite); }