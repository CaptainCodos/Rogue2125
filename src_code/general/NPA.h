#pragma once

#include <string>
#include <vector>
#include <SFML\Graphics.hpp>

class NPA
{
public:
	NPA();
	~NPA() = default;

	virtual void CreateFromData(std::vector<std::string> data);
	void CreateFromNPAData(std::vector<std::string> data, int &count);
	std::vector<std::string> GetDataForSave();

	int GetPriID();
	int GetSecID();

	sf::Vector2f GetPos();
	sf::Color GetColor();
protected:
	int m_priID;
	int m_secID;
	sf::Vector2f m_pos;
	sf::Color m_color;
private:

};