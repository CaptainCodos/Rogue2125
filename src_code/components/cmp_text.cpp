#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>

void TextComponent::update(double dt) {}

void TextComponent::render() { Renderer::queue(&_text); }

TextComponent::TextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
  _text.setString(_string);
  _font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
  _text.setFont(*_font);
}

void TextComponent::SetPos(sf::Vector2f& pos) { _text.setPosition(pos); }
void TextComponent::SetFont(sf::Font font) { _text.setFont(font); }
void TextComponent::SetColor(sf::Color color) { _text.setColor(color); }
void TextComponent::SetOrigin(sf::Vector2f &origin)
{
	float oX = _text.getGlobalBounds().width * origin.x;
	float oY = _text.getGlobalBounds().height * origin.y;
	_origin = sf::Vector2f(oX, oY);

	_text.setOrigin(_origin);
}

void TextComponent::SetText(const std::string& str) {
  _string = str;
  _text.setString(_string);
}
