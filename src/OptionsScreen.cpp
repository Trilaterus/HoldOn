#include "OptionsScreen.h"

OptionsScreen::OptionsScreen()
{

}

OptionsScreen::OptionsScreen(std::string sFileName)
: Screen(sFileName)
{

}

OptionsScreen::OptionsScreen(std::string sFileName, sf::RenderWindow* window)
: Screen(sFileName, window)
{

}

std::string OptionsScreen::handleEvents(sf::Event sfEvent)
{
	std::string s = Screen::handleEvents(sfEvent);
	if (s != "")
	{
		this->functionHandler(s);
	}
	return ""; // not really used for anything...
}

void OptionsScreen::functionHandler(std::string sFunctionName)
{
	if (sFunctionName == "")
	{
		int i = 0;
	}
	else if (sFunctionName == "gotoBack")
	{
		this->gotoBack();
	}
}

void OptionsScreen::gotoBack()
{
	Screen::changeScreen(0, 0);
}

void OptionsScreen::update(const sf::RenderWindow& window)
{
	Screen::update(window);
}

void OptionsScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Screen::draw(target, states);
}