/** \file UIButton.cpp
-
*/

#include "UIButton.h"

UIButton::UIButton()
{
	m_iFrames = 3;
	m_bIsHovered = false;
	TextureManager::getInstance().getTexRef("ButtonDefault");
}

void UIButton::update(const sf::RenderWindow& window)
{
	UIObject::update(window);
}

void UIButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//UIObject::draw(target, states);
}