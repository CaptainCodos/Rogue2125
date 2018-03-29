#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <memory>
#include <algorithm>
#include <typeindex>
#include <vector>

class Component;

class Entity
{
protected:
	std::vector<std::shared_ptr<Component>> m_components = std::vector<std::shared_ptr<Component>>();

	bool m_active;
	bool m_visible;
	bool m_toBeDeleted;

	sf::Vector2f m_pos;
	float m_rot;
	float m_scale;

	std::string m_tag;
public:
	Entity();
	virtual ~Entity();

	std::vector<std::shared_ptr<Component>> &GetComponents();
	void DestoyComps();

	virtual void UpdateMe(double dt);
	virtual void DrawMe();
	
	bool ToBeDeleted() const;
	void SetForDelete();

	bool IsActive() const;
	void SetActive(bool active);

	bool IsVisible() const;
	void SetVisibility(bool vis);

	const sf::Vector2f &GetPos() const;
	void SetPos(const sf::Vector2f &pos);

	float GetRot() const;
	void SetRot(float rot);

	float GetScale() const;
	void SetScale(float scale);

	std::string GetTag();
	void SetTag(std::string tag);

	template <typename T, typename... Targs>
	std::shared_ptr<T> AddComponent(Targs... params) 
	{
		static_assert(std::is_base_of<Component, T>::value, "Must be a component!");
		std::shared_ptr<T> sp(std::make_shared<T>(this, params...));
		m_components.push_back(sp);
		return sp;
	}

	template <typename T>
	std::shared_ptr<T> GetComponent()
	{
		static_assert(is_base_of<Component, T>::value, "Must be a component!");
		//std::vector<std::shared_ptr<Component>> cs = 
		for (int i = 0; i < m_components.size(); i++)
		{
			bool val = dynamic_pointer_cast<T>(m_components[i]) != NULL;
			if (val)
			{
				return dynamic_pointer_cast<T>(m_components[i]);
				break;
			}
		}

		return nullptr;
	}

	// Will return a component of type T, or anything which is derived from a T component.
	template <typename T>
	const std::vector<std::shared_ptr<T>> GetCompatibleComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "Must be a component!");
		std::vector<std::shared_ptr<T>> ret;
		for (auto c : _components)
		{
			auto dc = dynamic_cast<T*>(&(*c));
			if (dc)
			{
				ret.push_back(std::dynamic_pointer_cast<T>(c));
			}
		}
		return ret;
	}
};

class Component
{
protected:
	std::string m_tag;
	Entity *const m_parent;
	bool m_toBeDeleted;
	explicit Component(Entity *const e);
public:
	std::string GetTag();

	Component() = delete;
	bool ToBeDeleted() const;
	void SetForDelete();

	virtual void UpdateMe(double dt) = 0;
	virtual void DrawMe() = 0;
	virtual ~Component();
};

class SpriteComponent : public Component
{
public:
	SpriteComponent() = delete;
	explicit SpriteComponent(Entity *const e);

	void SetAnimates(bool val, bool isRandom);
	void SetSpriteTex(sf::Texture &txr, int frameRes, int fps);

	/// Use values between 0 and 1. 0 represents origin at top/left.
	void SetOrigin(sf::Vector2f vec);
	void SetColor(sf::Color color);

	void SetFrame(int frame);
	void PickSet(int set);

	void UpdateMe(double dt) override;
	void DrawMe() override;
protected:
	sf::Sprite m_sprite;
	sf::Texture* m_texture;

	sf::IntRect m_animRect;

	bool m_animates;
	bool m_randomAnim; // Pick random frame when animating

	int m_frameRes;
	int m_framesX;
	int m_framesY;

	int m_fps;
	int m_currX;
	int m_currY;
	float m_animTime;
};

class FontComponent : public Component
{
public:
	FontComponent() = delete;
	explicit FontComponent(Entity *const e);

	void SetText(sf::String str, sf::Font &font, int size);
	void SetOrigin(sf::Vector2f vec);
	void SetColor(sf::Color color);

	void UpdateMe(double dt) override;
	void DrawMe() override;
private:
	sf::Text m_text;
};