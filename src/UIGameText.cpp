#include "UIGameText.h"

/* CONSTRUCTORS */

UIGameText::UIGameText()
: UIText()
{
	init();
}

UIGameText::UIGameText(int enumPos)
: UIText(enumPos)
{
	init();
}

UIGameText::UIGameText(int enumPos, float fXOffset, float fYOffset)
: UIText(enumPos, fXOffset, fYOffset)
{
	init();
}

UIGameText::UIGameText(int enumPos, float fXOffset, float fYOffset, std::string sTextName)
: UIText(enumPos, fXOffset, fYOffset, sTextName)
{
	init();
}

UIGameText::UIGameText(int enumPos, float fXOffset, float fYOffset, std::string sTextName, std::string sKey, std::string sFunctionName)
{
	init();
	m_sfKey = AlphabetResource::getInstance().getSFKey(sKey);
	m_sFunctionName = sFunctionName;
}

void UIGameText::init()
{
	m_sfFillCircleColor = sf::Color(255, 0, 0, 255);
	m_sfFillCircleTexture = TextureManager::getInstance().getTexRef("FillCircle");
	m_sfOutline1CircleTexture = TextureManager::getInstance().getTexRef("FillCircleOutline1");
	m_sfOutline2CircleTexture = TextureManager::getInstance().getTexRef("FillCircleOutline2");
	m_iPercentFilled = 0;
	m_isPressed = false;
	m_iTimeHeld = 750; // 0.75 Seconds
	m_iTimeAutoRelease = 1500; // 1.5 second
	m_sfKey = sf::Keyboard::A;
	m_isReady = false;
	m_isAutoReleaseClockStarted = false;
	m_iPercentDrained = 0;
	m_sFunctionName = "";
	//m_fxLetterFill.setBuffer(SoundManager::getInstance().getEffectRef("LetterFill_1s"));
}

/* GETTERS */

std::string UIGameText::getFunctionName()
{
	return m_sFunctionName;
}

/* SETTERS */

void UIGameText::setKey(std::string sLetter)
{
	m_sfKey = AlphabetResource::getInstance().getSFKey(sLetter);
}

void UIGameText::setFunctionName(std::string sFunctionName)
{
	m_sFunctionName = sFunctionName;
}

/* CLASS SPECIFIC */

void UIGameText::onPressed(sf::Event sfEvent)
{
	if (sfEvent.key.code == m_sfKey)
	{
		if (!m_isPressed)
		{
			m_sfClock.restart();
			m_isPressed = true;
			//m_fxLetterFill.play();
			SoundManager::getInstance().playSound("LetterFill_1s");
		}
	}
}

bool UIGameText::onReleased(sf::Event sfEvent)
{
	if (sfEvent.key.code == m_sfKey)
	{
		if (m_isReady)
		{
			m_isPressed = false;
			m_iPercentFilled = 0;
			m_isReady = false;
			m_iPercentDrained = 0;
			m_isAutoReleaseClockStarted = false;
			//m_fxLetterFill.stop();
			return true;
		}
		else
		{
			m_isPressed = false;
			m_iPercentFilled = 0;
			m_isReady = false;
			m_iPercentDrained = 0;
			m_isAutoReleaseClockStarted = false;
			//m_fxLetterFill.stop();
			return false;
		}
	}
	return false;
}

void UIGameText::onReleased(bool bValue)
{
	if (bValue)
	{
		m_isPressed = false;
		m_iPercentFilled = 0;
		m_isReady = false;
		m_iPercentDrained = 0;
		m_isAutoReleaseClockStarted = false;
	}
}

void UIGameText::onClicked()
{
	m_isReady = true;
	m_iPercentFilled = 100;
	m_iPercentDrained = 0;
	m_sfFillCircleColor = sf::Color(0, 255, 0, 255);
}

void UIGameText::onUnclicked()
{
	m_isReady = false;
	m_iPercentFilled = 0;
	m_sfFillCircleColor = sf::Color(255, 0, 0, 255);
}

/* INHERITED */

void UIGameText::update(const sf::RenderWindow& window)
{
	if (m_isPressed)
	{
		if (!m_isReady)
		{
			float i = m_sfClock.getElapsedTime().asMilliseconds();
			float l = i / m_iTimeHeld;
			m_iPercentFilled = 100 * l;
			if (m_iPercentFilled >= 100)
			{
				m_iPercentFilled = 100;
				m_isReady = true;
			}
			else if (m_iPercentFilled <= 50)
			{
				float j = m_iPercentFilled * 2;
				float k = j / 100;
				float l = k * 255;
				m_sfFillCircleColor = sf::Color(255, l, 0, 255);
			}
			else if (m_iPercentFilled > 50)
			{
				float j = m_iPercentFilled * 2 - 100;
				float k = j / 100;
				float l = k * 255;
				m_sfFillCircleColor = sf::Color(255 - l, 255, 0, 255);
			}
		}
		else if (m_isReady)
		{
			if (!m_isAutoReleaseClockStarted)
			{
				SoundManager::getInstance().playSound("ReleaseTrue");
				m_sfAutoReleaseClock.restart();
				m_isAutoReleaseClockStarted = true;
			}
			float i = m_sfAutoReleaseClock.getElapsedTime().asMilliseconds();
			float l = i / m_iTimeAutoRelease;
			m_iPercentDrained = 100 * l;
			m_iPercentFilled = 100 - m_iPercentDrained;
			if (m_iPercentFilled <= 0)
			{
				this->onReleased(true);
			}
		}
	}
	UIText::update(window);
}

void UIGameText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// For smoother (and potentially more efficient) result we need to save the positions as ints not floats
	// Could make this more efficient since some of these are unnessary
	sf::Vector2i halfCharSize(this->getSFText().getCharacterSize() / 2, this->getSFText().getCharacterSize() / 2);
	sf::Vector2i origin1(m_sfFillCircleTexture.getSize().x / 2, m_sfFillCircleTexture.getSize().y / 2);
	sf::Vector2i origin2(m_sfOutline1CircleTexture.getSize().x / 2, m_sfOutline1CircleTexture.getSize().y / 2);
	sf::Vector2i origin3(m_sfOutline2CircleTexture.getSize().x / 2, m_sfOutline2CircleTexture.getSize().y / 2);
	sf::Vector2i firstChar(this->getSFText().findCharacterPos(0));

	sf::Vector2f fhalfCharSize(halfCharSize);
	sf::Vector2f fOrigin1(origin1);
	sf::Vector2f fOrigin2(origin2);
	sf::Vector2f fOrigin3(origin3);
	sf::Vector2f fFirstChar(firstChar);

	// draw circle fill
	sf::Sprite sprite1;
	sprite1.setTexture(m_sfFillCircleTexture);
	sprite1.setColor(m_sfFillCircleColor);
	sprite1.setOrigin(fOrigin1);
	sprite1.setPosition(fFirstChar);
	sprite1.move(fhalfCharSize);
	sprite1.setTextureRect(sf::IntRect(0, 0, 100, m_iPercentFilled));
	sprite1.rotate(180);
	target.draw(sprite1);

	// draw first outline
	sf::Sprite sprite2;
	sprite2.setTexture(m_sfOutline1CircleTexture);
	sprite2.setOrigin(fOrigin2);
	sprite2.setPosition(fFirstChar);
	sprite2.move(fhalfCharSize);
	target.draw(sprite2);

	// draw second outline
	if (m_isReady)
	{
		sf::Sprite sprite3;
		sprite3.setTexture(m_sfOutline2CircleTexture);
		sprite3.setOrigin(fOrigin3);
		sprite3.setPosition(fFirstChar);
		sprite3.move(fhalfCharSize);
		target.draw(sprite3);
	}

	UIText::draw(target, states);
}