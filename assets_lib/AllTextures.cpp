#include "AllTextures.h"
#include <iostream>
#include <sstream>

TextureMgr* TextureMgr::m_instance = NULL;

TextureMgr::TextureMgr()
{
	m_tileSheets = std::vector<sf::Texture>();

	for (int i = 0; i < 5; i++)
	{
		sf::Texture txr;

		std::stringstream sf;
		sf << "res/graphics/tile sheets/GreyScale" << i << ".png";
		std::stringstream se;
		se << "Failed to load grey tile sheet" << i;

		if (!txr.loadFromFile(sf.str()))
			std::cerr << se.str() << std::endl;

		m_tileSheets.push_back(txr);
	}
}

TextureMgr* TextureMgr::GetInstance()
{
	if (!m_instance)
		m_instance = new TextureMgr();

	return m_instance;
}