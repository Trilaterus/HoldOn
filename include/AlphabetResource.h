#ifndef ALPHABETRESOURCE_H
#define ALPHABETRESOURCE_H

#include <SFML/Graphics.hpp>
#include <array>
#include <random>

class AlphabetResource // This is a singleton class, purpose is to be friend classed to classes that need info of the game alphabet
{
private:
	AlphabetResource();
	AlphabetResource(AlphabetResource const&);
	void operator=(AlphabetResource const&);

	std::array<std::pair<std::string, sf::Keyboard::Key>, 26> m_aAlphaLowerCase;
	std::array<std::pair<std::string, sf::Keyboard::Key>, 26> m_aAlphaUpperCase;
	std::array<sf::Keyboard::Key, 26> m_aAlphaSFKey;
	// Need an array<pair> for each letters sound (if needed)
protected:

public:
	static AlphabetResource& getInstance();

	std::string getLowerCase(int iValue); // used for iterating through
	std::string getUpperCase(int iValue); // used for iterating through
	sf::Keyboard::Key getSFKey(std::string sLetter); // used to get sf::Key from a string
	std::string getRandomLower();
};

#endif // ALPHABETRESOURCE_H