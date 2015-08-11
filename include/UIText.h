/** \file UIText.h
This UIText class is used to display text to the screen.
It determines what to display by reading in from a file to allow different
languages and quick changes to be displayed.
*/

#ifndef UITEXT_H
#define UITEXT_H

#include "UIObject.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "TextureManager.h"

class UIText : public UIObject
{
private:
	std::string m_sText;
	std::string m_sFontRef;
	sf::Font m_sfFont;
	sf::Color m_sfColour;
	int m_iCharSize;

	std::string getStringFromFile(std::string sFilePath, std::string sTextName);
protected:

public:
	UIText();
	UIText(int enumPos);
	UIText(int enumPos, float fXOffset, float fYOffset);
	UIText(int enumPos, float fXOffset, float fYOffset, std::string sTextName);

	sf::Text getSFText() const; // Used for UIGameText for positioning the circle indicators
	float getWidth() const;
	float getHeight() const;

	void setColour(sf::Color colour);
	void setFont(std::string sFontRef);
	void setCharSize(int iCharSize);
	void setString(std::string sText); // used for making  UITexts outside of the notepad

	virtual void update(const sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // UITEXT_H