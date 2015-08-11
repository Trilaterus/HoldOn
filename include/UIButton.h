/** \file UIButton.h
This UIButton class is used to display image buttons on the screen.
The buttons will have a response when clicked on.
The buttons can also have effects for hovering over and on click.
Question is do toggle buttons need to be their own class?
*/

#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "UIObject.h"
#include "TextureManager.h"

class UIButton : public UIObject
{
private:
	int m_iFrames;
	bool m_bIsHovered;

protected:

public:
	UIButton();
	UIButton(int enumPos);
	UIButton(int enumPos, float fXOffset, float fYOffset);
	UIButton(int enumPos, float fXOffset, float fYOffset, sf::Texture texture);

	virtual void update(const sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // UIBUTTON_H