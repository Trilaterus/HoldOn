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
	this->m_AllEffects[name] = buffer;
}

void SoundManager::loadMusic(const std::string& name, const std::string& fileName)
{
	sf::Music* music = new sf::Music;
	music->openFromFile(fileName);
	music->setVolume(50); // tmp
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
		if (m_CurrentMusic->getStatus() != sf::Sound::Status::Playing)
		{
			m_CurrentMusic->play();
		}
	}
}

void SoundManager::stopBGMusic()
{
	if (m_CurrentMusic != NULL)
	{
		m_CurrentMusic->stop();
	}
}

void SoundManager::playSound(const std::string& ref)
{
	if (m_AllSounds.size() >= 100) // if sound list reaches over 50 iterate through and delete non playing sounds
	{
		for (std::vector<sf::Sound>::iterator it = m_AllSounds.begin(); it != m_AllSounds.end();)
		{
			sf::Sound::Status stat = it->getStatus();
			if (it->getStatus() != sf::Sound::Status::Playing)
			{
				it = m_AllSounds.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	sf::Sound* sound = new sf::Sound;
	sound->setBuffer(m_AllEffects.at(ref));
	this->m_AllSounds.push_back(*sound);
	this->m_AllSounds.back().setVolume(50); // tmp
	this->m_AllSounds.back().play();
	delete sound;
}