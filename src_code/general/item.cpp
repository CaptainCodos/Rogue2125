#include "item.h"
#include "maths.h"
//#include "../components/cmp_tilemap.h"

using namespace std;
using namespace sf;

Item::Item()
{
	m_reqs = vector<Skill>();

	m_stack = 1;
	m_color = Color::White;
	m_absID = 0;
}

int Item::GetPriID() { return m_absID; }
int Item::GetSecID() { return m_secID; }

string Item::GetDescription() { return m_descript; }
string Item::GetName() { return m_name; }
string Item::GetShortName() { return m_short; }

Color Item::GetColor() { return m_color; }

bool Item::CheckReqs(vector<Skill> skills)
{
	int successes = 0;

	for (int i = 0; i < m_reqs.size(); i++)
	{
		int id = m_reqs[i].GetID();

		if (skills[id].GetVal() >= m_reqs[i].GetVal())
			successes++;
	}

	if (successes >= m_reqs.size())
		return true;
	else
		return false;
}

void Item::GenerateItem()
{
	m_name = "Name";
	m_short = "S";
	m_descript = "Description!";

	m_reqs = vector<Skill>();

	m_stack = 1;
	m_color = Color::White;
	m_absID = 0;
	m_secID = 0;
}

void Item::CreateFromData(vector<string> data)
{
	int c = 0;
	CreateFromItemData(data, c);
}

void Item::CreateFromItemData(vector<string> data, int &count)
{
	m_reqs = vector<Skill>();

	m_absID = stoi(data[count++]);
	m_secID = stoi(data[count++]);

	m_name = data[count++];
	m_short = data[count++];
	m_descript = data[count++];

	m_color = Color();
	m_color.r = data[count++][0];
	m_color.g = data[count++][0];
	m_color.b = data[count++][0];

	int reqs = stoi(data[count++]);
	for (int i = 0; i < reqs; i++)
	{
		m_reqs.push_back(Skill("", "", stoi(data[count++]), stoi(data[count++])));
	}
}

vector<string> Item::GetDataForSave()
{
	vector<string> data = vector<string>();

	data.push_back(to_string(m_absID));
	data.push_back(to_string(m_secID));

	data.push_back(m_name);
	data.push_back(m_short);
	data.push_back(m_descript);

	stringstream s;
	s << m_color.r; data.push_back(s.str()); s.str(string());
	s << m_color.g; data.push_back(s.str()); s.str(string());
	s << m_color.b; data.push_back(s.str()); s.str(string());

	data.push_back(to_string(m_reqs.size()));
	for (int i = 0; i < m_reqs.size(); i++)
	{
		data.push_back(to_string(m_reqs[i].GetID()));
		data.push_back(to_string(m_reqs[i].GetVal()));
	}

	return data;
}

Useable::Useable() : Item()
{
	m_absID = 1;
	m_canStack = true;
	m_effectPower = 0.0f;
}

int Useable::GetEffectID() { return m_effectID; }
float Useable::GetEffectPower() { return m_effectPower; }

void Useable::GenerateItem()
{
	m_absID = 1;

	m_effectID = RandomInt(0, 7);
	m_secID = m_effectID;

	switch (m_effectID)
	{
	case 0:
		m_effectPower = RandomFloat(30.0f, 90.0f);

		m_name = "Combat Program";
		m_short = "Cmb Prgm";
		m_descript = "A combat program that will provide experience when used. Will be corrupted after use.";
		break;
	case 1:
		m_effectPower = 1.1f;

		m_name = "Tutorial Book";
		m_short = "Tut Book";
		m_descript = "A book that will help you learn a skill. Adds one skill point.";
		break;
	case 2:
		m_effectPower = 4.0f;

		m_name = "Nano Paste";
		m_short = "N Pst";
		m_descript = "Will repair the tank for 4 points of HP.";
		break;
	case 3:
		m_effectPower = 4.0f;

		m_name = "Uranium Rods";
		m_short = "Urnm Rods";
		m_descript = "Will provide the tank with 4 points of fuel.";
		break;
	case 4:
		m_effectPower = 4.0f;

		m_name = "1MJ Battery";
		m_short = "MJ Btry";
		m_descript = "Will provide the tank with 4 points of energy.";
		break;
	case 5:
		m_effectPower = 1.0f;
		break;
	case 6:
		m_effectPower = 1.0f;

		m_name = "Mystery Box";
		m_short = "Mysry Bx";
		m_descript = "Will provide an item or status effect. Gamble, Gamble, Gamble.";
		break;
	}
}

void Useable::CreateFromData(std::vector<std::string> data)
{
	int c = 0;
	Item::CreateFromItemData(data, c);
	CreateFromUseableData(data, c);
}

void Useable::CreateFromUseableData(vector<string> data, int &count)
{
	m_effectID = m_secID;
	m_effectPower = stof(data[count++]);
	m_stack = stoi(data[count++]);
}

vector<string> Useable::GetDataForSave()
{
	vector<string> data = Item::GetDataForSave();

	data.push_back(to_string(m_effectPower));
	data.push_back(to_string(m_stack));
	data.push_back(" ");

	return data;
}

void Useable::UseCharge()
{
	m_stack--;

	if (m_stack <= 0)
		Useable::~Useable();
}