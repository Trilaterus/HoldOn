/** \file TextureManager.cpp
-
*/

#include "TextureManager.h"

TextureManager::TextureManager()
{
	
}

TextureManager& TextureManager::getInstance()
{
	static TextureManager instance;
	return instance;
}

void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
	sf::Texture texture;
	texture.loadFromFile(filename);

	this->m_AllTextures[name] = texture;
}

void TextureManager::loadFont(const std::string& name, const std::string& filename)
{
	sf::Font font;
	if (!font.loadFromFile(filename))
	{
		// error
	}

	this->m_AllFonts[name] = font;
}

sf::Texture& TextureManager::getTexRef(const std::string& texture)
{
	return this->m_AllTextures.at(texture);
}

sf::Font& TextureManager::getFontRef(const std::string& font)
{
	return this->m_AllFonts.at(font);
}