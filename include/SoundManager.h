#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <map>
#include <SFML/Audio.hpp>
#include <iostream>

class SoundManager
{
private:
	SoundManager();
	SoundManager(SoundManager const&);
	void operator=(SoundManager const&);

	std::map<std::string, sf::SoundBuffer> m_AllEffects;
	std::map<std::string, sf::Music*> m_AllMusic;
	sf::Music* m_CurrentMusic;

protected:

public:
	static SoundManager& getInstance();

	void loadEffect(const std::string& name, const std::string& fileName);
	void loadMusic(const std::string& name, const std::string& fileName);

	sf::SoundBuffer& getEffectRef(const std::string& effect);
	sf::Music* getMusicRef(const std::string& music);

	void playBGMusic(const std::string& musicRef);
	void stopBGMusic();
};

#endif // SOUNDMANAGER_H