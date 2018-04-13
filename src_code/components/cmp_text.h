#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

class TextComponent : public Component {
public:
  TextComponent() = delete;
  explicit TextComponent(Entity* p, const std::string& str = "");
  void update(double dt) override;

  void render() override;

  ~TextComponent() override = default;

  void SetPos(sf::Vector2f pos);
  void SetColor(sf::Color color);
  void SetOrigin(sf::Vector2f origin);	// 0 = top/left, 1 = bottom/right
  void SetFont(sf::Font font);
  void SetText(const std::string& str);

  sf::Text* GetText() { return &_text; }

protected:
  std::shared_ptr<sf::Font> _font;
  std::string _string;
  sf::Text _text;
};
