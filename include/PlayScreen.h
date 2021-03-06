#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include "Screen.h"

class PlayScreen : public Screen
{
private:
	bool m_bFirstTime;
	bool m_isCurrentScreen;

protected:

public:
	PlayScreen();
	PlayScreen(std::string sFileName);
	PlayScreen(std::string sFileName, sf::RenderWindow* window);

	virtual std::string handleEvents(sf::Event sfEvent);
	virtual void functionHandler(std::string sFunctionName);

	void gotoClassic();
	void gotoNormal();
	void gotoRapid();
	void gotoBack();
	void gotoTut();

	virtual void update(const sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // PLAYSCREEN_H