#include "SoundManager.h"

SoundManager::SoundManager()
{

}

SoundManager& SoundManager::getInstance()
{
	static SoundManager instance;
	return instance;
}

void SoundManager::loadEffect(const std::string& name, const std::string& fileName)
{
	sf::SoundBuffer buffer;
	buffer.loadFromFile(fileName);
	//sf::Sound sound;
	//sound.setBuffer(buffer);
	this->m_AllEffects[name] = buffer;
}

void SoundManager::loadMusic(const std::string& name, const std::string& fileName)
{
	sf::Music* music = new sf::Music;
	music->openFromFile(fileName);
	m_AllMusic[name] = music;
}

sf::SoundBuffer& SoundManager::getEffectRef(const std::string& effect)
{
	return this->m_AllEffects.at(effect);
}

sf::Music* SoundManager::getMusicRef(const std::string& music)
{
	return this->m_AllMusic.at(music);
}

void SoundManager::playBGMusic(const std::string& musicRef)
{
	if (m_CurrentMusic == NULL)
	{
		m_CurrentMusic = m_AllMusic.at(musicRef);
		m_CurrentMusic->setLoop(true);
		m_CurrentMusic->play();
	}
	else if (m_CurrentMusic != m_AllMusic.at(musicRef))
	{
		m_CurrentMusic->stop();
		m_CurrentMusic = m_AllMusic.at(musicRef);
		m_CurrentMusic->setLoop(true);
		m_CurrentMusic->play();
	}
	else // if the track that wants to be played is already being played then do nothing
	{

	}
}

void SoundManager::stopBGMusic()
{
	if (m_CurrentMusic != NULL)
	{
		m_CurrentMusic->stop();
	}
}