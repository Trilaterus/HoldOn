/** \file UIImage.h
The UIImage class is used to display standard images to the screen.
This class should also inherit from an animations class that allows the image to be
fade in or out or spin etc.
*/

#ifndef UIIMAGE_H
#define UIIMAGE_H

#include "UIObject.h"

class UIImage : public UIObject
{
private:

protected:


public:
	UIImage();
	UIImage(int enumPos);
	UIImage(int enumPos, float fXOffset, float fYOffset);
	UIImage(int enumPos, float fXOffset, float fYOffset, sf::Texture texture);

	virtual void update(const sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // UIIMAGE_H