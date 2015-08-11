#ifndef MAINMENUSCREEN_H
#define MAINMENUSCREEN_H

#include "Screen.h"

class MainMenuScreen : public Screen
{
private:
	bool m_isCurrentScreen;

protected:

public:
	MainMenuScreen();
	MainMenuScreen(std::string sFileName);
	MainMenuScreen(std::string sFileName, sf::RenderWindow* window);

	virtual std::string handleEvents(sf::Event sfEvent);
	virtual void functionHandler(std::string sFunctionName);

	void gotoPlay();
	void gotoOptions();
	void gotoQuit();

	virtual void update(const sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // MAINMENUSCREEN_H