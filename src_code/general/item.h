#pragma once
#include "skill.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Item
{
public:
	Item();
	~Item() = default;

	bool CheckReqs(std::vector<Skill> skills);
	virtual void GenerateItem();

	virtual void CreateFromData(std::vector<std::string> data) = 0;
	void CreateFromItemData(std::vector<std::string> data, int &count);
	std::vector<std::string> GetDataForSave();

	std::string GetDescription();
	std::string GetName();
	std::string GetShortName();

	sf::Texture GetTexture();
protected:
	int m_absID;	// Determines if item is useable or equipment. 0 = Equipment, 1 = Useable
	int m_secID;	// Determines type of useable or equipment. Used differently for each.

	std::string m_descript;	// Item description.
	std::string m_name;
	std::string m_short;

	std::vector<Skill> m_reqs;	// These are the requirements that must be met to use the item in any way.

	bool m_canStack;	// Determines if more than one can be held in same inventory slot. I got 99 mushrooms but these trends aint one!
	int m_stack;		// How many of the item is stacked. If it cannot stack then it will not exceed 1.

	int m_txrVecIdx;	// Used when loading from file to determine place in texture array.
	sf::Texture m_texture;	// Texture of the item for gui/pickup.
	sf::Color m_color;	// Texture color.
private:
	
};

class Useable : public Item
{
public:
	Useable();
	~Useable() = default;

	void GenerateItem();
	void CreateFromData(std::vector<std::string> data) override;
	void CreateFromUseableData(std::vector<std::string> data, int &count);
	std::vector<std::string> GetDataForSave();

	int GetEffectID();
	float GetEffectPower();

	void UseCharge();	// Tells the item that one has been used from the stack.
protected:

private:
	int m_effectID;			// Determines effect type. 0 = exp, 1 = skill point, 2 = hp, 3 = fuel, 4 = en, 5 = buff, 6 = item
	float m_effectPower;	// Determines how strong the effect is.
};