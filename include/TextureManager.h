/** \file TextureManager.h
The purpose of the TextureManager class is to store single copies of a texture, so that if
multiple objects need that texture it doesn't need to load a copy for each one (I think...)
*/

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class TextureManager
{
private:
	TextureManager(); //!< Overridden default constructor for Singleton class
	TextureManager(TextureManager const&); //!< Overridden default constructor for Singleton class
	void operator=(TextureManager const&); //!< Overridden default constructor for Singleton class

	std::map<std::string, sf::Texture> m_AllTextures;
	std::map<std::string, sf::Font> m_AllFonts;

protected:


public:
	static TextureManager& getInstance();

	void loadTexture(const std::string& name, const std::string& fileName);
	void loadFont(const std::string& name, const std::string& fileName);
	sf::Texture& getTexRef(const std::string& texture);
	sf::Font& getFontRef(const std::string& font);
};

#endif // TEXTUREMANAGER_H