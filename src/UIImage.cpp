/** \file UIImage.cpp
-
*/

#include "UIImage.h"

UIImage::UIImage()
{
	if (!m_Texture.loadFromFile("assets\\textures\\ui_textures\\image_texture_test.png"))
	{
		// Error Message
	}

	m_fWidth = m_Texture.getSize().x;
	m_fHeight = m_Texture.getSize().y;
}

UIImage::UIImage(int enumPos)
	: UIObject(enumPos)
{
	m_EnumPos = enumPos;
	m_fXOffset = 0;
	m_fYOffset = 0;

	if (!m_Texture.loadFromFile("assets\\textures\\ui_textures\\image_texture_test.png"))
	{
		// Error Message
	}

	m_fWidth = m_Texture.getSize().x;
	m_fHeight = m_Texture.getSize().y;
}

UIImage::UIImage(int enumPos, float fXOffset, float fYOffset)
	: UIObject(enumPos, fXOffset, fYOffset)
{
	m_EnumPos = enumPos;
	m_fXOffset = fXOffset;
	m_fYOffset = fYOffset;

	if (!m_Texture.loadFromFile("assets\\textures\\ui_textures\\image_texture_test.png"))
	{
		// Error Message
	}

	m_fWidth = m_Texture.getSize().x;
	m_fHeight = m_Texture.getSize().y;
}

UIImage::UIImage(int enumPos, float fXOffset, float fYOffset, sf::Texture texture)
{
	m_EnumPos = enumPos;
	m_fXOffset = fXOffset;
	m_fYOffset = fYOffset;

	m_Texture = texture;

	m_fWidth = m_Texture.getSize().x;
	m_fHeight = m_Texture.getSize().y;
}

void UIImage::update(const sf::RenderWindow& window)
{
	UIObject::update(window);
}

void UIImage::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite sprite;
	sprite.setTexture(m_Texture);
	sprite.setPosition(m_fXPos, m_fYPos);
	//sprite.rotate();
	//sprite.setScale(m_fWidth/objTexture.getSize().x, m_fHeight/objTexture.getSize().y);
	sprite.setOrigin((m_fWidth/2.f)/sprite.getScale().x, (m_fHeight/2.f)/sprite.getScale().y);
	
	target.draw(sprite);
}