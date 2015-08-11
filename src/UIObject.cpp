/** \file UIObject.cpp
-
*/

#include "UIObject.h"

UIObject::UIObject()
{

}

UIObject::UIObject(int enumPos)
{

}

UIObject::UIObject(int enumPos, float fXOffset, float fYOffset)
{

}

UIObject::UIObject(int enumPos, float fXOffset, float fYOffset, sf::Texture texture)
{

}

float UIObject::getXPos() const
{
	return m_fXPos;
}

float UIObject::getYPos() const
{
	return m_fYPos;
}

float UIObject::getWidth() const
{
	return m_fWidth;
}

float UIObject::getHeight() const
{
	return m_fHeight;
}

std::string UIObject::getName() const
{
	return m_sName;
}

void UIObject::setPosition(int enumPos)
{

}

void UIObject::setPosition(int enumPos, float fXOffset, float fYOffset)
{

}

void UIObject::setRelativePosition(float fXPos, float fYPos)
{
	m_EnumPos = this->m_UIParent->m_EnumPos;
	m_fXOffset = this->m_UIParent->m_fXOffset + fXPos;
	m_fYOffset = this->m_UIParent->m_fYOffset + fYPos;
}

void UIObject::setParent(UIObject* uiObject)
{
	m_UIParent = uiObject;
	if (uiObject->m_UIChild == nullptr)
	{
		uiObject->setChild(this);
	}
}

void UIObject::setChild(UIObject* uiObject)
{
	m_UIChild = uiObject;
	if (uiObject->m_UIParent == nullptr)
	{
		uiObject->setParent(this);
	}
}

void UIObject::setName(std::string sName)
{
	m_sName = sName;
}

void UIObject::update(const sf::RenderWindow& window)
{
	if (m_EnumPos == UIObject::TOP_LEFT)
	{
		m_fXPos = 0 + m_fXOffset;
		m_fYPos = 0 + m_fYOffset;
	}
	else if (m_EnumPos == UIObject::TOP_RIGHT)
	{
		m_fXPos = window.getSize().x + m_fXOffset;
		m_fYPos = 0 + m_fYOffset;
	}
	else if (m_EnumPos == UIObject::BOT_LEFT)
	{
		m_fXPos = 0 + m_fXOffset;
		m_fYPos = window.getSize().y + m_fYOffset;
	}
	else if (m_EnumPos == UIObject::BOT_RIGHT)
	{
		m_fXPos = window.getSize().x + m_fXOffset;
		m_fYPos = window.getSize().y + m_fYOffset;
	}
	else if (m_EnumPos == UIObject::CENTRE)
	{
		m_fXPos = window.getSize().x / 2 + m_fXOffset;
		m_fYPos = window.getSize().y / 2 + m_fYOffset;
	}
	else if (m_EnumPos == UIObject::TOP_CENTRE)
	{
		m_fXPos = window.getSize().x / 2 + m_fXOffset;
		m_fYPos = 0 + m_fYOffset;
	}
	else if (m_EnumPos == UIObject::LEFT_CENTRE)
	{
		m_fXPos = 0 + m_fXOffset;
		m_fYPos = window.getSize().y / 2 + m_fYOffset;
	}
	else if (m_EnumPos == UIObject::RIGHT_CENTRE)
	{
		m_fXPos = window.getSize().x + m_fXOffset;
		m_fYPos = window.getSize().y / 2 + m_fYOffset;
	}
	else if (m_EnumPos == UIObject::BOT_CENTRE)
	{
		m_fXPos = window.getSize().x / 2 + m_fXOffset;
		m_fYPos = window.getSize().y + m_fYOffset;
	}
	else // set pos to centre
	{
		m_fXPos = window.getSize().x / 2 + m_fXOffset;
		m_fYPos = window.getSize().y / 2 + m_fYOffset;
	}
}