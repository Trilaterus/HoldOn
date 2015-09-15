/** \file Screen.h
The purpose of the Screen class is to provide a layout in which other ui objects can reside.
*/

#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include "UIObject.h"
#include "UIImage.h"
#include "UIText.h"
#include "TextureManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "UIGameText.h"
#include "ScoreController.h"
#include "BackgroundController.h"

class Screen : public sf::Drawable
{
private:
	std::vector<UIObject*> m_AllUIObjects;
	bool m_needsChange; // checks does the screen need to change? (checks in ScreenManager::update())
	std::array<int, 2> m_aScreenChange;
	float m_animViewZoom; // used for animations
	bool m_isAnimating; // Is the current screen in the middle of an animation? Also used to one time start clocks
	bool m_isClockTransitionReset;
	sf::Clock m_clockScreenTransitions; // clock used in screen transition animations

	int convertToEnum(std::string name);
	void init(std::string sFileName);
	bool screenAnimation(int iTransitionNum);

protected:
	sf::RenderWindow* m_sfWindow;

public:
	Screen();
	Screen(std::string sFilePath);
	Screen(std::string sFilePath, sf::RenderWindow* window);

	bool getNeedChange(); // check if the screen needs changing
	std::array<int, 2> getScreenChange(); // gets info on the screen change

	void setNeedChange(bool bValue);

	void addUIObjects(std::string sFilePath);
	void addUIObjects(UIObject* uiObject);
	const std::vector<UIObject*>& getAllUIObjects();
	bool changeScreen(int iScreenNum, int iTransitionNum);

	virtual std::string handleEvents(sf::Event sfEvent);
	virtual void functionHandler(std::string sFunctionName) = 0;

	virtual void update(const sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // SCREEN_H