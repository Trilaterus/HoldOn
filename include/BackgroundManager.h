#ifndef BACKGROUNDMANAGER_H
#define BACKGROUNDMANAGER_H

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "RandomResource.h"

class BackgroundManager : public sf::Drawable
{
private:
	std::vector<sf::Sprite> m_AllStars;
	sf::Texture* m_texStar;
	sf::RenderWindow* m_sfWindow;
	RandomResource m_RandGen;
	sf::Clock m_spawnClock;
	sf::Clock m_updateClock;
	float m_fFPS;
	int m_iStarSpeed; // larger is slower
	sf::Color m_altStarColour;
	bool m_shouldSpawn;

protected:

public:
	BackgroundManager(sf::RenderWindow* window);

	void addStar();
	void addStar(float xPos, float yPos);
	int getMoveSpeed();
	void changeMoveSpeed(int iValue); // default is 200, lower is faster higher is slower
	void clearStars();
	void stopSpawning();
	void startSpawning();

	void update(const sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // BACKGROUNDMANAGER_H