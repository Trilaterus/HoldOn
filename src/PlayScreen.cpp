#include "PlayScreen.h"

PlayScreen::PlayScreen()
{

}

PlayScreen::PlayScreen(std::string sFileName)
: Screen(sFileName)
{

}

PlayScreen::PlayScreen(std::string sFileName, sf::RenderWindow* window)
: Screen(sFileName, window)
{

}

std::string PlayScreen::handleEvents(sf::Event sfEvent)
{
	std::string s = Screen::handleEvents(sfEvent);
	if (s != "")
	{
		this->functionHandler(s);
	}
	return ""; // not really used for anything...
}

void PlayScreen::functionHandler(std::string sFunctionName)
{
	if (sFunctionName == "")
	{
		int i = 0;
	}
	else if (sFunctionName == "gotoClassic")
	{
		this->gotoClassic();
	}
	else if (sFunctionName == "gotoNormal")
	{
		this->gotoNormal();
	}
	else if (sFunctionName == "gotoRapid")
	{
		this->gotoRapid();
	}
	else if (sFunctionName == "gotoBack")
	{
		this->gotoBack();
	}
}

void PlayScreen::gotoClassic()
{
	Screen::changeScreen(3, 0);
}

void PlayScreen::gotoNormal()
{

}

void PlayScreen::gotoRapid()
{

}

void PlayScreen::gotoBack()
{
	Screen::changeScreen(0, 0);
}

void PlayScreen::update(const sf::RenderWindow& window)
{
	Screen::update(window);
}

void PlayScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Screen::draw(target, states);
}