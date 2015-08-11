/** \file UIObject.h
The UIObject class is an abstract class that is the base for all the various UI
elements present in the game, such as buttons, images and image buttons.
It currently holds a texture for that object.
*/

#ifndef UIOBJECT_H
#define UIOBJECT_H

#include <SFML/Graphics.hpp>

class UIObject : public sf::Drawable
{
private:
	

protected:
	std::string m_sName;
	float m_fXPos;
	float m_fYPos;
	int m_EnumPos;
	float m_fXOffset;
	float m_fYOffset;
	float m_fWidth;
	float m_fHeight;
	sf::Texture m_Texture;
	UIObject* m_UIParent;
	UIObject* m_UIChild;

public:
	enum Positions {TOP_LEFT, TOP_RIGHT, BOT_LEFT, BOT_RIGHT, CENTRE, TOP_CENTRE, LEFT_CENTRE, RIGHT_CENTRE, BOT_CENTRE};
	
	UIObject();
	UIObject(int enumPos);
	UIObject(int enumPos, float fXOffset, float fYOffset);
	UIObject(int enumPos, float fXOffset, float fYOffset, sf::Texture texture);

	float getXPos() const;
	float getYPos() const;
	float getWidth() const;
	float getHeight() const;
	std::string getName() const;

	void setPosition(int enumPos);
	void setPosition(int enumPos, float fXOffset, float fYOffset);
	void setRelativePosition(float fXPos, float fYPos);
	void setParent(UIObject* uiObject);
	void setChild(UIObject* uiObject);
	void setTexture(std::string sTextureName);
	void setName(std::string sName);

	virtual void update(const sf::RenderWindow& window) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

};

#endif // UIIMAGE_h