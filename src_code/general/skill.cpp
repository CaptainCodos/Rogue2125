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

void Skill::AutoGenSkill()
{
	switch (m_ID)
	{
	case 0:
		m_name = "Sharp Shooting";
		m_short = "Shrp Shtng";
		m_descript = "Increase weapon ";
		break;
	case 1:
		m_name = "Spin Up";
		m_short = "Spn Up";
		m_descript = "";
		break;
	case 2:
		m_name = "Structural Integrity";
		m_short = "Struct Integrity.";
		m_descript = "Increase tank HP by 2 per point.";
		break;
	case 3:
		m_name = "Power Supply";
		m_short = "Pwr Sply";
		m_descript = "Increase tank energy reserves by 2 per point.";
		break;
	case 4:
		m_name = "Engine Operation";
		m_short = "Engine Op.";
		m_descript = "Increase tank speed by 0.2 tiles per second.";
		break;
	case 5:
		m_name = "Armour Plating";
		m_short = "Ar. Plates";
		m_descript = "Increase tank physical damage reduction by 4%.";
		break;
	case 6:
		m_name = "Heat Resistant Plating";
		m_short = "Ar. Heat";
		m_descript = "Increase tank heat damage reduction by 4%.";
		break;
	case 7:
		m_name = "High Ohm Plating";
		m_short = "Ar. Electric";
		m_descript = "Increase tank electric damage reduction by 4%.";
		break;
	case 8:
		m_name = "Hazmat Plating";
		m_short = "Ar. Toxin";
		m_descript = "Increase tank toxic damage reduction by 4%.";
		break;
	case 9:
		m_name = "Insulated Armour Plates";
		m_short = "Ar. Cold";
		m_descript = "Increase tank cold damage reduction by 4%.";
		break;
	}
}