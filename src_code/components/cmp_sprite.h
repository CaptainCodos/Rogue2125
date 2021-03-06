#pragma once

#include "ecm.h"
//#include <SFML/Graphics/Shape.hpp>
//#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>

class SpriteComponent : public Component {
protected:
	std::shared_ptr<sf::Sprite> _sprite;

public:
	SpriteComponent() = delete;

	explicit SpriteComponent(Entity* p);
	void update(double dt) override;
	void render() override;

	sf::Sprite& getSprite() const;

	template <typename... Targs> void setSprite(Targs... params) {
		_sprite.reset(new sf::Sprite(params...));
	}
};

class TextureComponent : public Component
{
public:
	TextureComponent() = delete;

	explicit TextureComponent(Entity* p);
	void update(double dt) override;
	void render() override;

	virtual std::shared_ptr<sf::Sprite> GetSprite();
	std::shared_ptr<sf::IntRect> GetTexRect();
	sf::Vector2f GetSpritePos();
	float GetSpriteAng();

	virtual void SetTexture(sf::Texture& txr, int texRes);
	virtual void SetOrigin(sf::Vector2f origin);	// between 0f - 1f, 0f = top/left
	void SetColor(sf::Color color);					// Used to set color of texture. Recommend using Max brightness colors.
	void SetTint(sf::Color tint);					// Allows tinting of the given color of sprite.
	void SetScale(float scale);
	void SetTextureRect(std::shared_ptr<sf::IntRect> rect);

	void SetPosition(sf::Vector2f pos);
	void SetRotation(float ang);
protected:
	std::shared_ptr<sf::Sprite> m_sprite;
	std::shared_ptr<sf::IntRect> m_srcRect;

	sf::Color m_color;
	sf::Color m_tint;
	int m_texRes;
private:

};

class AnimComponent : public TextureComponent
{
public:
	AnimComponent() = delete;
	explicit AnimComponent(Entity* p);
	void update(double dt) override;
	void basicUpdate(double dt);	// Incase you don't necessarily want set to entity transform behavious
	//void render() override;

	void SetTexture(sf::Texture& txr, int texRes);
	void SetOrigin(sf::Vector2f origin);	// between 0f - 1f, 0f = top/left
	void SetAnimates(bool animates);
	void SetFrame(int frame);
	void SetState(int state);			// a sprite sheet can have multiple layers, this plays different animation set.
	void SetFPS(float fps);
protected:

private:
	bool m_animates;

	//sf::IntRect m_srcRect;
	float m_fps;

	float m_animTime;
};

class ShapeComponent : public Component {
protected:
  std::shared_ptr<sf::Shape> _shape;
  // sf::Shape _shape;

public:
  ShapeComponent() = delete;

  explicit ShapeComponent(Entity* p);

  void update(double dt) override;
  void render() override;
  sf::Shape& getShape() const;
  template <typename T, typename... Targs> void setShape(Targs... params) {
    _shape.reset(new T(params...));
  }
};