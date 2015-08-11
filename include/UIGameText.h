#ifndef UIGAMETEXT_H
#define UIGAMETEXT_H

#include "UIText.h"
#include "AlphabetResource.h"
#include "SoundManager.h"

class UIGameText : public UIText
{
private:
	sf::Clock m_sfClock; // clock for checking how long it has been pressed
	int m_iPercentFilled; // tracks how much percent of circle should be filled
	bool m_isReady; // can the circle be safely released?
	int m_iTimeHeld; // how long till it becomes full
	sf::Keyboard::Key m_sfKey; // which key triggers it
	bool m_isPressed; // has the key been pressed?
	sf::Clock m_sfAutoReleaseClock; // the clock tracking the auto release decrease
	bool m_isAutoReleaseClockStarted; // has the clock been restarted only once?
	int m_iTimeAutoRelease; // how long till the full circle becomes empty
	int m_iPercentDrained; // how much should be taken away from percentfilled for autorelease to work
	std::string m_sFunctionName; // name of function to execute when released properly
	sf::Sound m_fxLetterFill; // sound to play while letter is filling

	sf::Texture m_sfFillCircleTexture;
	sf::Color m_sfFillCircleColor;
	sf::Texture m_sfOutline1CircleTexture;
	sf::Texture m_sfOutline2CircleTexture;

	void init();

protected:

public:
	UIGameText();
	UIGameText(int enumPos);
	UIGameText(int enumPos, float fXOffset, float fYOffset);
	UIGameText(int enumPos, float fXOffset, float fYOffset, std::string sTextName);
	UIGameText(int enumPos, float fXOffset, float fYOffset, std::string sTextName, std::string sKey, std::string sFunctionName);

	std::string getFunctionName();

	void setKey(std::string sLetter);
	void setFunctionName(std::string sFunctionName);

	void onPressed(sf::Event sfEvent);
	bool onReleased(sf::Event sfEvent);
	void onReleased(bool bValue);
	void onClicked();
	void onUnclicked();

	virtual void update(const sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // UIGAMETEXT_H