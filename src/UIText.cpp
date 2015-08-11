/** \file UIText.cpp
-
*/

#include "UIText.h"

UIText::UIText() // Width and height never set for UIText altho positions at centre cuz it works it out at draw time
{
	m_sText = "default";
	m_sFontRef = "default";
	m_sfFont = TextureManager::getInstance().getFontRef(m_sFontRef);
	m_sfColour = sf::Color(sf::Color::Red);
	m_iCharSize = 30;
}

UIText::UIText(int enumPos)
	: UIObject(enumPos)
{
	m_sText = "default";
	m_sFontRef = "default";
	m_sfFont = TextureManager::getInstance().getFontRef(m_sFontRef);
	m_sfColour = sf::Color(sf::Color::Red);
	m_iCharSize = 30;
	m_EnumPos = enumPos;
	m_fXOffset = 0;
	m_fYOffset = 0;
}

UIText::UIText(int enumPos, float fXOffset, float fYOffset)
	: UIObject (enumPos, fXOffset, fYOffset)
{
	m_sText = "default";
	m_sFontRef = "default";
	m_sfFont = TextureManager::getInstance().getFontRef(m_sFontRef);
	m_sfColour = sf::Color(sf::Color::Red);
	m_iCharSize = 30;
	m_EnumPos = enumPos;
	m_fXOffset = fXOffset;
	m_fYOffset = fYOffset;
}

UIText::UIText(int enumPos, float fXOffset, float fYOffset, std::string sTextName)
{
	m_sFontRef = "default";
	m_sfFont = TextureManager::getInstance().getFontRef(m_sFontRef);
	m_sfColour = sf::Color(sf::Color::Red);
	m_iCharSize = 30;
	m_EnumPos = enumPos;
	m_fXOffset = fXOffset;
	m_fYOffset = fYOffset;

	m_sText = this->getStringFromFile("assets\\localisation\\english.txt", sTextName);
}

// function that allows specification of font

std::string UIText::getStringFromFile(std::string sFilePath, std::string sTextName)
{
	std::ifstream file(sFilePath, std::ifstream::ios_base::in);
	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			std::string s;
			std::istringstream is(line);

			is >> s;

			if (s == sTextName)
			{
				std::string param;
				char c = '-';
				std::vector<std::string> sentence;
				bool isReadingSentence = false;

				while (is >> param)
				{
					if (param.back() == c) // if the last char is a '-' then push current on, concatonate all strings then push
					{
						sentence.push_back(param);
						param = "";
						isReadingSentence = false;
						for (std::vector<std::string>::iterator it = sentence.begin(); it != sentence.end(); ++it)
						{
							param = param + " " + (*it);
						}
						param.erase(std::remove(param.begin(), param.end(), '-'), param.end()); // Removes '-' from the string... All of em probably... Also is adding a space at the beginning of the string! >:(
						param.erase(0, 1); // should remove extra space at start of strings
						return param;
					}
					else if (isReadingSentence || param.front() == c) // if first char is '-'
					{
						sentence.push_back(param);
						isReadingSentence = true;
					}
					else
					{
						return param;
					}
				}
			}
		}
	}
}

sf::Text UIText::getSFText() const
{
	sf::Text text;
	text.setFont(m_sfFont);
	text.setString(m_sText);
	text.setPosition(m_fXPos, m_fYPos);
	text.setColor(m_sfColour);
	text.setCharacterSize(m_iCharSize);
	text.setOrigin((text.getLocalBounds().width / 2.f) / text.getScale().x, (text.getLocalBounds().height / 2.f) / text.getScale().y);
	return text;
}

float UIText::getWidth() const
{
	float i = this->getSFText().getLocalBounds().width;
	return i;
}

float UIText::getHeight() const
{
	float i = this->getSFText().getLocalBounds().height;
	return i;
}

void UIText::setFont(std::string sFontRef)
{
	m_sfFont = TextureManager::getInstance().getFontRef(sFontRef);
}

void UIText::setColour(sf::Color colour)
{
	m_sfColour = sf::Color(colour);
}

void UIText::setCharSize(int iCharSize)
{
	m_iCharSize = iCharSize;
}

void UIText::setString(std::string sText)
{
	m_sText = sText;
}

void UIText::update(const sf::RenderWindow& window)
{
	UIObject::update(window);
}

void UIText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Text text;
	text.setFont(m_sfFont);
	text.setString(m_sText);
	text.setPosition(m_fXPos, m_fYPos);
	text.setColor(m_sfColour);
	text.setCharacterSize(m_iCharSize);
	text.setOrigin((text.getLocalBounds().width / 2.f) / text.getScale().x, (text.getLocalBounds().height / 2.f) / text.getScale().y);

	target.draw(text);
}