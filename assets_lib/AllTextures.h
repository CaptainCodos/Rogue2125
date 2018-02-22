#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class TextureMgr
{
public:
	static TextureMgr* GetInstance();

	std::vector<sf::Texture> m_tileSheets;
private:
	static TextureMgr* m_instance;
	TextureMgr(); // cannot be called outside class
	~TextureMgr() = default;
	TextureMgr(TextureMgr const&) {}; // private copy constructor
	TextureMgr& operator=(TextureMgr const&) {}; // private assignment
};