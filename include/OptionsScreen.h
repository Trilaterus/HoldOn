#ifndef OPTIONSCREEN_H
#define OPTIONSSCREEN_H

#include "Screen.h"

class OptionsScreen : public Screen
{
private:

protected:

public:
	OptionsScreen();
	OptionsScreen(std::string sFileName);
	OptionsScreen(std::string sFileName, sf::RenderWindow* window);

	virtual std::string handleEvents(sf::Event sfEvent);
	virtual void functionHandler(std::string sFunctionName);

	void gotoBack();

	virtual void update(const sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // OPTIONSSCREEN_H