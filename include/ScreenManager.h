/** \file ScreenManager.h
The purpose of the ScreenManager class is to manage which screen is currently on
display and to apply effects or transitions between them.
It also manages the size of the window and whether it is fullscreen or not.
*/

#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Screen.h"

class ScreenManager : public sf::Drawable
{
private:
	std::vector<Screen*> m_AllScreens; // add to this list whenever a new screen is made
	Screen* m_CurrentScreen; // for efficiency this could be changed to an int that shows where in the vector the current screen is
	bool m_isFullscreen;
	int m_iScreenWidth;
	int m_iScreenHeight;

protected:


public:
	// Constructors
	ScreenManager();
	ScreenManager(Screen* screen);

	// Getters
	Screen* getCurrentScreen();
	bool isFullscreen();
	int getScreenWidth();
	int getScreenHeight();

	// Setters
	void setIsFullscreen(bool value);
	void setScreenSize(int iWidth, int iHeight);

	// Class Specific
	void addScreen(Screen* screen);
	void changeScreen(int iScreenNumber, int iTransitionNumber); // Starts at 0
	void update(const sf::RenderWindow& window);

	// Inherited
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // SCREENMANAGER_H