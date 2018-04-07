
#include "cmp_sprite.h"
#include "system_renderer.h"

using namespace std;
#pragma region SpriteComponent
SpriteComponent::SpriteComponent(Entity* p)
	: Component(p), _sprite(make_shared<sf::Sprite>()) {}

void SpriteComponent::update(double dt) {
	_sprite->setPosition(_parent->getPosition());
	_sprite->setRotation(_parent->getRotation());
}

void SpriteComponent::render() { Renderer::queue(_sprite.get()); }

sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }
#pragma endregion

#pragma region TextureComponent
TextureComponent::TextureComponent(Entity* p)
	: Component(p), m_sprite(make_shared<sf::Sprite>()) 
{
	m_color = sf::Color::White;
	m_tint = sf::Color::White;

	SetColor(m_color);
	SetTint(m_tint);
	//m_srcRect = make_shared<sf::IntRect>(sf::IntRect(0, 0, 32, 32));
	//m_srcRect = new sf::IntRect(0, 0, 32, 32);
}

void TextureComponent::update(double dt) {
	m_sprite->setPosition(_parent->getPosition());
	m_sprite->setRotation(_parent->getRotation());
}

void TextureComponent::render() 
{
	if (m_sprite->getTexture() != nullptr && _parent->isVisible())
	{
		if (m_srcRect != nullptr)
			m_sprite->setTextureRect(*m_srcRect);
		
		Renderer::queue(m_sprite.get());
	}
}

void TextureComponent::SetTexture(sf::Texture& txr, int texRes)
{
	m_sprite->setTexture(txr);
	m_texRes = texRes;
}

void TextureComponent::SetOrigin(sf::Vector2f origin)
{
	if (m_sprite->getTexture() != nullptr)
	{
		sf::Vector2f o = sf::Vector2f(origin.x * m_sprite->getTexture()->getSize().x, origin.y * m_sprite->getTexture()->getSize().y);
		m_sprite->setOrigin(o);
	}
}

void TextureComponent::SetColor(sf::Color color)
{
	m_color = color;
	m_sprite->setColor(m_color * m_tint);
}
void TextureComponent::SetTint(sf::Color tint)
{
	m_tint = tint;
	m_sprite->setColor(m_color * m_tint);
}

void TextureComponent::SetScale(float scale)
{
	m_sprite->setScale(sf::Vector2f(scale, scale));
}

void TextureComponent::SetTextureRect(shared_ptr<sf::IntRect> rect)
{
	m_srcRect = rect;
}
#pragma endregion

#pragma region AnimComponent
AnimComponent::AnimComponent(Entity* p)
	: TextureComponent(p)
{
	m_animates = true;
	m_fps = 30;
	m_texRes = 32;
}

void AnimComponent::SetTexture(sf::Texture& txr, int texRes)
{
	m_sprite->setTexture(txr);
	m_srcRect = make_shared<sf::IntRect>(sf::IntRect(0, 0, texRes, texRes));
	m_texRes = texRes;
	m_sprite->setTextureRect(*m_srcRect);
}

void AnimComponent::SetOrigin(sf::Vector2f origin)
{
	if (m_sprite->getTexture() != nullptr)
	{
		sf::Vector2f o = sf::Vector2f(origin.x * m_texRes, origin.y * m_texRes);
		m_sprite->setOrigin(o);
	}
}

void AnimComponent::SetAnimates(bool animates)
{
	m_animates = animates;
}

void AnimComponent::SetFrame(int frame)
{
	if (m_srcRect != nullptr)
	{
		m_srcRect->left = m_srcRect->width * frame;
	}
}

void AnimComponent::SetState(int state)
{
	if (m_srcRect != nullptr)
	{
		m_srcRect->top = m_srcRect->height * state;
	}
}

void AnimComponent::SetFPS(float fps)
{
	m_fps = fps;
}

void AnimComponent::update(double dt)
{
	TextureComponent::update(dt);

	if (m_animates && m_sprite->getTexture() != nullptr)
	{
		if (m_animTime <= 0.0f)
		{
			m_srcRect->left += m_srcRect->width;
			if (m_srcRect->left >= m_sprite->getTexture()->getSize().x)
				m_srcRect->left = 0;

			m_sprite->setTextureRect(*m_srcRect);

			m_animTime = 1.0f;
		}
		else
		{
			m_animTime -= dt * m_fps;
		}
	}
}
#pragma endregion

#pragma region ShapeComponent
void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p)
	: Component(p), _shape(make_shared<sf::CircleShape>()) {}

void ShapeComponent::update(double dt) {
	_shape->setPosition(_parent->getPosition());
	_shape->setRotation(_parent->getRotation());
}
#pragma endregion