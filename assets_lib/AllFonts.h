#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class FontMgr
{
public:
	static FontMgr* GetInstance();

	std::vector<sf::Font> m_fonts;
private:
	static FontMgr* m_instance;
	FontMgr(); // cannot be called outside class
	~FontMgr() = default;
	FontMgr(FontMgr const&) {}; // private copy constructor
	FontMgr& operator=(FontMgr const&) {}; // private assignment
};