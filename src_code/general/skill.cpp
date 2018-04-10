#include "skill.h"

using namespace std;

Skill::Skill(string name, string sName, int id, int initVal)
{
	m_name = name;
	m_short = sName;

	m_ID = id;
	m_skill = initVal;
}

string Skill::GetName() { return m_name; }
string Skill::GetShortName() { return m_short; }
int Skill::GetID() { return m_ID; }
int Skill::GetVal() { return m_skill; }

void Skill::SetDescription(string desc)
{
	m_descript = desc;
}