#include "NPA.h"
#include <sstream>

using namespace std;
using namespace sf;

NPA::NPA()
{
	m_priID = 0;
	m_secID = 0;

	m_pos = Vector2f(0.0f, 0.0f);
	m_color = Color::White;
}


int NPA::GetPriID() { return m_priID; }
int NPA::GetSecID() { return m_secID; }

Vector2f NPA::GetPos() { return m_pos; }
Color NPA::GetColor() { return m_color; }

void NPA::CreateFromData(std::vector<std::string> data)
{
	int c = 0;
	CreateFromNPAData(data, c);
}

void NPA::CreateFromNPAData(std::vector<std::string> data, int &count)
{
	m_priID = stoi(data[count++]);
	m_secID = stoi(data[count++]);

	m_pos = Vector2f();
	m_pos.x = stof(data[count++]);
	m_pos.y = stof(data[count++]);

	m_color = Color();
	m_color.r = data[count++][0];
	m_color.g = data[count++][0];
	m_color.b = data[count++][0];
}

std::vector<std::string> NPA::GetDataForSave()
{
	vector<string> data = vector<string>();

	data.push_back(to_string(m_priID));
	data.push_back(to_string(m_secID));

	data.push_back(to_string(m_pos.x));
	data.push_back(to_string(m_pos.y));

	stringstream s;
	s << m_color.r; data.push_back(s.str()); s.str(string());
	s << m_color.g; data.push_back(s.str()); s.str(string());
	s << m_color.b; data.push_back(s.str()); s.str(string());

	return data;
}