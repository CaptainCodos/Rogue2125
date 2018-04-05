#include "AllFonts.h"
#include <iostream>
#include <sstream>

FontMgr* FontMgr::m_instance = NULL;

FontMgr::FontMgr()
{
	m_fonts = std::vector<sf::Font>();

	for (int i = 0; i < 3; i++)
	{
		sf::Font font;

		std::stringstream sf;
		sf << "res/fonts/Font" << i << ".ttf";
		std::stringstream se;
		se << "Failed to load Font" << i;

		if (!font.loadFromFile(sf.str()))
			std::cerr << se.str() << std::endl;

		m_fonts.push_back(font);
	}
}

FontMgr* FontMgr::GetInstance()
{
	if (!m_instance)
		m_instance = new FontMgr();

	return m_instance;
}