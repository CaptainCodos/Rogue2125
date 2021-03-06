#include "AllTextures.h"
#include <iostream>
#include <sstream>

TextureMgr* TextureMgr::m_instance = NULL;

TextureMgr::TextureMgr()
{
	colors_LiquidTiles = std::vector<sf::Color>();
	colors_LiquidTiles.push_back(sf::Color(255, 150, 30, 255));	// Lava
	colors_LiquidTiles.push_back(sf::Color(180, 255, 0, 255));	// Toxic
	colors_LiquidTiles.push_back(sf::Color(20, 255, 180, 255));	// Acid
	colors_LiquidTiles.push_back(sf::Color(150, 195, 255, 255));// Energized Water
	colors_LiquidTiles.push_back(sf::Color(90, 230, 255, 255));	// Water

	colors_Elements.push_back(sf::Color(255, 240, 180, 255));	// Physical
	colors_Elements.push_back(sf::Color(255, 160, 0, 255));	// Heat
	colors_Elements.push_back(sf::Color(160, 255, 255, 255));	// Electric
	colors_Elements.push_back(sf::Color(50, 195, 50, 255));// Toxic
	colors_Elements.push_back(sf::Color(50, 50, 255, 255));	// Cold
	
	sheet_Items = std::vector<std::vector<sf::Texture>>();
	sheet_Items.push_back(std::vector<sf::Texture>());
	sheet_Items.push_back(std::vector<sf::Texture>());

	sheet_NPA_Textures = std::vector<std::vector<sf::Texture>>();
	sheet_NPA_Textures.push_back(std::vector<sf::Texture>());
	sheet_NPA_Textures.push_back(std::vector<sf::Texture>());
	sheet_NPA_Textures.push_back(std::vector<sf::Texture>());

	// Load texture assets
	LoadTextures("tile sheets/", "GreyScale", sheet_Tiles, 5);
	LoadTextures("tank/", "Tank", sheet_Items[0], 4);
	LoadTextures("interactables/", "interactable", sheet_NPA_Textures[0], 3);
	LoadTextures("interactables/", "interactable", sheet_NPA_Textures[1], 3);
	LoadTextures("world/", "world", sheet_NPA_Textures[2], 4);
	LoadTextures("projectiles/", "Proj", sheet_Projectiles, 1);

	LoadTextures("tile sheets/", "GreyScale", anim_Tiles, 1);

	LoadTextures("UI/general/tmpButtons/", "tmpButton", img_Buttons, 3);

	anim_TilesRect = std::make_shared<sf::IntRect>(sf::IntRect(0, 0, 32, 32));

	anim_LiquidTimer = 1.0f;
}

TextureMgr* TextureMgr::GetInstance()
{
	if (!m_instance)
		m_instance = new TextureMgr();

	return m_instance;
}

void TextureMgr::LoadTextures(std::string path, std::string asset, std::vector<sf::Texture> &vec, int items)
{
	vec = std::vector<sf::Texture>();

	for (int i = 0; i < items; i++)
	{
		sf::Texture txr;

		std::stringstream sf;
		sf << "res/graphics/" << path << asset << i << ".png";
		std::stringstream se;
		se << "Failed to load grey " << asset << i;

		if (!txr.loadFromFile(sf.str()))
			std::cerr << se.str() << std::endl;

		vec.push_back(txr);
	}
}

void TextureMgr::UpdateAnims(double dt)
{
	if (anim_LiquidTimer <= 0.0f)
	{
		anim_TilesRect->left += anim_TilesRect->width;
		if (anim_TilesRect->left >= anim_Tiles[0].getSize().x)
			anim_TilesRect->left = 0;

		anim_LiquidTimer = 1.0f;
	}
	else
	{
		anim_LiquidTimer -= 4.0f * dt;
	}
}