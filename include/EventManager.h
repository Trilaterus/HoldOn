/** \file EventManager.h
This class handles the event passed in from the standard sfml loop.
It checks which screen is currently displayed and which UIObject is
is in question to output the correct reaction.
It is also a singleton class.
*/

#ifndef EVENTMANAGER_H
#define EVENTMANGER_H

#include <SFML\Graphics.hpp>
#include "ScreenManager.h"

class EventManager
{
private:
	EventManager();
	EventManager(EventManager const&);
	void operator=(EventManager const&);

	sf::Event m_Event;
protected:

public:
	static EventManager& getInstance();

	void handleEvents(sf::Event eEvent, sf::RenderWindow* window, ScreenManager& screenManager);
};

#endif // EVENTMANAGER_H