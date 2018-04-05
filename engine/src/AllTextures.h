#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>

class TextureMgr
{
public:
	static TextureMgr* GetInstance();
	// The vectors of textures will be split into three sets. One for sheets, anim textures and single texture sprites.
	// The reason for this is that this allows for simultaneous animation across many objects as they share the texture.
	// This also cuts down on memory usage. vectors will be prefixed with "sheet", "anim" and "img" for quick navigation.

	// All the textures will be loaded on first instance call!

	std::vector<sf::Texture> sheet_Tiles;
	
	std::vector<sf::Color> colors_LiquidTiles; // Liquid colors
	std::vector<sf::Texture> anim_Tiles; // Liquid tile animation textures
	std::shared_ptr<sf::IntRect> anim_TilesRect; // Used to animate the liquid tile frames. This is done by passing the rect as reference.
	float anim_LiquidTimer;

	std::vector<sf::Texture> img_Buttons;



	void UpdateAnims(double dt);
private:
	static TextureMgr* m_instance;
	TextureMgr(); // cannot be called outside class
	~TextureMgr() = default;
	TextureMgr(TextureMgr const&) {}; // private copy constructor
	TextureMgr& operator=(TextureMgr const&) {}; // private assignment

	void LoadTextures(std::string path, std::string asset, std::vector<sf::Texture> &vec, int items); // load textures into vec. Asset is folder desired.
	//void CreateAnimSprites(std::vector<sf::Sprite> &vec);
};