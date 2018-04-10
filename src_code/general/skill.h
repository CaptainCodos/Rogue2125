#pragma once
#include <string>

class Skill
{
public:
	Skill() = delete;
	Skill(std::string name, std::string sName, int id, int initVal);

	~Skill() = default;

	std::string GetName();
	std::string GetShortName();
	int GetID();
	int GetVal();

	void SetDescription(std::string desc);
protected:

private:
	std::string m_name;
	std::string m_short;

	std::string m_descript;

	int m_ID;
	int m_skill;
};