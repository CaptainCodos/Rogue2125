#include "Entity.h"
#include "RenderSystem.h"
#include "ExtraMaths.h"

#include <typeindex>
#include <memory>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace sf;

bool pleaseWork = true;

// Entity Implementation //
Entity::Entity()
{
	m_components = vector<shared_ptr<Component>>();
	m_pos = Vector2f(0.0f, 0.0f);
	m_rot = 0.0f;
	m_scale = 1.0f;

	m_toBeDeleted = false;
	m_visible = true;
	m_active = true;
}
Entity::~Entity()
{

}

vector<shared_ptr<Component>> &Entity::GetComponents()
{
	return m_components;
}
void Entity::DestoyComps()
{
	m_components.erase(std::remove_if(m_components.begin(), m_components.end(), [](shared_ptr<Component> c) { return c->ToBeDeleted(); }), m_components.end());
}

bool Entity::ToBeDeleted() const
{
	return m_toBeDeleted;
}
bool Entity::IsActive() const
{
	return m_active;
}
bool Entity::IsVisible() const
{
	return m_visible;
}

void Entity::SetForDelete()
{
	m_toBeDeleted = true;
}
void Entity::SetActive(bool val)
{
	m_active = val;
}
void Entity::SetVisibility(bool val)
{
	m_visible = val;
}

const Vector2f &Entity::GetPos() const
{
	return m_pos;
}
float Entity::GetRot() const
{
	return m_rot;
}
float Entity::GetScale() const
{
	return m_scale;
}

void Entity::SetPos(const Vector2f &pos)
{
	m_pos = pos;
}
void Entity::SetRot(float rot)
{
	m_rot = rot;
}
void Entity::SetScale(float scale)
{
	m_scale = scale;
}

string Entity::GetTag()
{
	return m_tag;
}
void Entity::SetTag(string tag)
{
	m_tag = tag;
}

void Entity::UpdateMe(double dt)
{
	if (m_active)
	{
		DestoyComps();

		for (int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->UpdateMe(dt);
		}
	}
}
void Entity::DrawMe()
{
	if (m_visible && m_active)
	{
		for (int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->DrawMe();
		}
	}
}

// Component Implementation //
Component::Component(Entity *const e) : m_parent(e)
{
	m_toBeDeleted = false;
	m_tag = "base";
}
Component::~Component()
{

}

string Component::GetTag()
{
	return m_tag;
}

bool Component::ToBeDeleted() const
{
	return m_toBeDeleted;
}
void Component::SetForDelete()
{
	m_toBeDeleted = true;
}

// Sprite Component Implementation //
SpriteComponent::SpriteComponent(Entity * const e) : Component(e)
{
	m_sprite = Sprite();
	//m_sprite.setPosition(Vector2f(100.0f, 200.0f));

	m_animTime = 1.0f;
	m_animates = false;
	m_randomAnim = false;

	m_tag = "sprite";
}

void SpriteComponent::SetAnimates(bool val, bool isRandom)
{
	m_animates = val;
	m_randomAnim = isRandom;
}
void SpriteComponent::SetSpriteTex(Texture &txr, int frameRes, int fps)
{
	//m_texture = txr;

	m_frameRes = frameRes;
	m_fps = fps;

	m_framesX = txr.getSize().x / frameRes;
	m_framesY = txr.getSize().y / frameRes;

	m_currX = 0;
	m_currY = 0;

	m_animTime = 1.0f;

	m_animRect = IntRect(0, 0, frameRes, frameRes);

	m_sprite.setTexture(txr);
	m_sprite.setTextureRect(m_animRect);
}
void SpriteComponent::SetOrigin(Vector2f vec)
{
	Vector2f origin = Vector2f((m_sprite.getTexture()->getSize().x / m_framesX) * vec.x, (m_sprite.getTexture()->getSize().y / m_framesY) * vec.y);
	m_sprite.setOrigin(origin);
}
void SpriteComponent::SetColor(Color color)
{
	m_sprite.setColor(color);
}
void SpriteComponent::SetFrame(int frame)
{
	m_currX = frame;
	m_animRect.left = m_frameRes * frame;
}
void SpriteComponent::PickSet(int set)
{
	m_currY = set;
	m_animRect.top = m_frameRes * set;
}

void SpriteComponent::UpdateMe(double dt)
{
	//m_toBeDeleted = true;
	m_sprite.setPosition(m_parent->GetPos());
	m_sprite.setRotation(m_parent->GetRot());
	m_sprite.setScale(Vector2f(m_parent->GetScale(), m_parent->GetScale()));

	if (m_animates)
	{
		if (m_randomAnim)
		{
			if (m_animTime <= 0.0f)
			{
				m_animTime = 1.0f;

				int endIdx = m_sprite.getTexture()->getSize().x / m_frameRes;
				int frame = ExtraMaths::GetRandomInt(0, endIdx);

				while (frame >= endIdx && frame == m_currX)
				{
					frame = ExtraMaths::GetRandomInt(0, endIdx);
				}

				SetFrame(frame);
			}
			else
			{
				m_animTime -= dt * m_fps;
			}
		}
		else
		{
			if (m_animTime <= 0.0f)
			{
				m_animTime = 1.0f;
				m_animRect.left += m_frameRes;
				m_currX++;

				if (m_animRect.left >= m_sprite.getTexture()->getSize().x)
				{
					m_animRect.left = 0;
					m_currX = 0;
				}
			}
			else
			{
				m_animTime -= dt * m_fps;
			}
		}
	}

	//Renderer::Queue(&m_sprite);

	//DrawMe();
}
void SpriteComponent::DrawMe()
{
	if (m_sprite.getTexture() != NULL)
	{
		m_sprite.setTextureRect(m_animRect);
		Renderer::Queue(&m_sprite);
	}
}

// Font Component //
FontComponent::FontComponent(Entity * const e) : Component(e)
{
}

void FontComponent::SetText(String str, Font &font, int size)
{
	m_text = Text(str, font, size);
}
void FontComponent::SetOrigin(Vector2f vec)
{
	Vector2f origin = Vector2f(m_text.getLocalBounds().width * vec.x, m_text.getLocalBounds().height * vec.y);
	m_text.setOrigin(origin);
}
void FontComponent::SetColor(Color color)
{
	m_text .setColor(color);
}

void FontComponent::UpdateMe(double dt)
{
	m_text.setPosition(m_parent->GetPos());
	m_text.setRotation(m_parent->GetRot());
	m_text.setScale(Vector2f(m_parent->GetScale(), m_parent->GetScale()));
}
void FontComponent::DrawMe()
{
	if (m_text.getFont() != NULL && m_text.getString().getSize() > 0)
	{
		Renderer::Queue(&m_text);
	}
}