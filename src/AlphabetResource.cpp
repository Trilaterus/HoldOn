#include "AlphabetResource.h"

AlphabetResource::AlphabetResource()
{
	m_aAlphaLowerCase.at(0).first = "a";
	m_aAlphaLowerCase.at(1).first = "b";
	m_aAlphaLowerCase.at(2).first = "c";
	m_aAlphaLowerCase.at(3).first = "d";
	m_aAlphaLowerCase.at(4).first = "e";
	m_aAlphaLowerCase.at(5).first = "f";
	m_aAlphaLowerCase.at(6).first = "g";
	m_aAlphaLowerCase.at(7).first = "h";
	m_aAlphaLowerCase.at(8).first = "i";
	m_aAlphaLowerCase.at(9).first = "j";
	m_aAlphaLowerCase.at(10).first = "k";
	m_aAlphaLowerCase.at(11).first = "l";
	m_aAlphaLowerCase.at(12).first = "m";
	m_aAlphaLowerCase.at(13).first = "n";
	m_aAlphaLowerCase.at(14).first = "o";
	m_aAlphaLowerCase.at(15).first = "p";
	m_aAlphaLowerCase.at(16).first = "q";
	m_aAlphaLowerCase.at(17).first = "r";
	m_aAlphaLowerCase.at(18).first = "s";
	m_aAlphaLowerCase.at(19).first = "t";
	m_aAlphaLowerCase.at(20).first = "u";
	m_aAlphaLowerCase.at(21).first = "v";
	m_aAlphaLowerCase.at(22).first = "w";
	m_aAlphaLowerCase.at(23).first = "x";
	m_aAlphaLowerCase.at(24).first = "y";
	m_aAlphaLowerCase.at(25).first = "z";

	m_aAlphaLowerCase.at(0).second = sf::Keyboard::A;
	m_aAlphaLowerCase.at(1).second = sf::Keyboard::B;
	m_aAlphaLowerCase.at(2).second = sf::Keyboard::C;
	m_aAlphaLowerCase.at(3).second = sf::Keyboard::D;
	m_aAlphaLowerCase.at(4).second = sf::Keyboard::E;
	m_aAlphaLowerCase.at(5).second = sf::Keyboard::F;
	m_aAlphaLowerCase.at(6).second = sf::Keyboard::G;
	m_aAlphaLowerCase.at(7).second = sf::Keyboard::H;
	m_aAlphaLowerCase.at(8).second = sf::Keyboard::I;
	m_aAlphaLowerCase.at(9).second = sf::Keyboard::J;
	m_aAlphaLowerCase.at(10).second = sf::Keyboard::K;
	m_aAlphaLowerCase.at(11).second = sf::Keyboard::L;
	m_aAlphaLowerCase.at(12).second = sf::Keyboard::M;
	m_aAlphaLowerCase.at(13).second = sf::Keyboard::N;
	m_aAlphaLowerCase.at(14).second = sf::Keyboard::O;
	m_aAlphaLowerCase.at(15).second = sf::Keyboard::P;
	m_aAlphaLowerCase.at(16).second = sf::Keyboard::Q;
	m_aAlphaLowerCase.at(17).second = sf::Keyboard::R;
	m_aAlphaLowerCase.at(18).second = sf::Keyboard::S;
	m_aAlphaLowerCase.at(19).second = sf::Keyboard::T;
	m_aAlphaLowerCase.at(20).second = sf::Keyboard::U;
	m_aAlphaLowerCase.at(21).second = sf::Keyboard::V;
	m_aAlphaLowerCase.at(22).second = sf::Keyboard::W;
	m_aAlphaLowerCase.at(23).second = sf::Keyboard::X;
	m_aAlphaLowerCase.at(24).second = sf::Keyboard::Y;
	m_aAlphaLowerCase.at(25).second = sf::Keyboard::Z;

	m_aAlphaUpperCase.at(0).first = "A";
	m_aAlphaUpperCase.at(1).first = "B";
	m_aAlphaUpperCase.at(2).first = "C";
	m_aAlphaUpperCase.at(3).first = "D";
	m_aAlphaUpperCase.at(4).first = "E";
	m_aAlphaUpperCase.at(5).first = "F";
	m_aAlphaUpperCase.at(6).first = "G";
	m_aAlphaUpperCase.at(7).first = "H";
	m_aAlphaUpperCase.at(8).first = "I";
	m_aAlphaUpperCase.at(9).first = "J";
	m_aAlphaUpperCase.at(10).first = "K";
	m_aAlphaUpperCase.at(11).first = "L";
	m_aAlphaUpperCase.at(12).first = "M";
	m_aAlphaUpperCase.at(13).first = "N";
	m_aAlphaUpperCase.at(14).first = "O";
	m_aAlphaUpperCase.at(15).first = "P";
	m_aAlphaUpperCase.at(16).first = "Q";
	m_aAlphaUpperCase.at(17).first = "R";
	m_aAlphaUpperCase.at(18).first = "S";
	m_aAlphaUpperCase.at(19).first = "T";
	m_aAlphaUpperCase.at(20).first = "U";
	m_aAlphaUpperCase.at(21).first = "V";
	m_aAlphaUpperCase.at(22).first = "W";
	m_aAlphaUpperCase.at(23).first = "X";
	m_aAlphaUpperCase.at(24).first = "Y";
	m_aAlphaUpperCase.at(25).first = "Z";

	m_aAlphaUpperCase.at(0).second = sf::Keyboard::A;
	m_aAlphaUpperCase.at(1).second = sf::Keyboard::B;
	m_aAlphaUpperCase.at(2).second = sf::Keyboard::C;
	m_aAlphaUpperCase.at(3).second = sf::Keyboard::D;
	m_aAlphaUpperCase.at(4).second = sf::Keyboard::E;
	m_aAlphaUpperCase.at(5).second = sf::Keyboard::F;
	m_aAlphaUpperCase.at(6).second = sf::Keyboard::G;
	m_aAlphaUpperCase.at(7).second = sf::Keyboard::H;
	m_aAlphaUpperCase.at(8).second = sf::Keyboard::I;
	m_aAlphaUpperCase.at(9).second = sf::Keyboard::J;
	m_aAlphaUpperCase.at(10).second = sf::Keyboard::K;
	m_aAlphaUpperCase.at(11).second = sf::Keyboard::L;
	m_aAlphaUpperCase.at(12).second = sf::Keyboard::M;
	m_aAlphaUpperCase.at(13).second = sf::Keyboard::N;
	m_aAlphaUpperCase.at(14).second = sf::Keyboard::O;
	m_aAlphaUpperCase.at(15).second = sf::Keyboard::P;
	m_aAlphaUpperCase.at(16).second = sf::Keyboard::Q;
	m_aAlphaUpperCase.at(17).second = sf::Keyboard::R;
	m_aAlphaUpperCase.at(18).second = sf::Keyboard::S;
	m_aAlphaUpperCase.at(19).second = sf::Keyboard::T;
	m_aAlphaUpperCase.at(20).second = sf::Keyboard::U;
	m_aAlphaUpperCase.at(21).second = sf::Keyboard::V;
	m_aAlphaUpperCase.at(22).second = sf::Keyboard::W;
	m_aAlphaUpperCase.at(23).second = sf::Keyboard::X;
	m_aAlphaUpperCase.at(24).second = sf::Keyboard::Y;
	m_aAlphaUpperCase.at(25).second = sf::Keyboard::Z;

	m_aAlphaSFKey.at(0) = sf::Keyboard::A;
	m_aAlphaSFKey.at(1) = sf::Keyboard::B;
	m_aAlphaSFKey.at(2) = sf::Keyboard::C;
	m_aAlphaSFKey.at(3) = sf::Keyboard::D;
	m_aAlphaSFKey.at(4) = sf::Keyboard::E;
	m_aAlphaSFKey.at(5) = sf::Keyboard::F;
	m_aAlphaSFKey.at(6) = sf::Keyboard::G;
	m_aAlphaSFKey.at(7) = sf::Keyboard::H;
	m_aAlphaSFKey.at(8) = sf::Keyboard::I;
	m_aAlphaSFKey.at(9) = sf::Keyboard::J;
	m_aAlphaSFKey.at(10) = sf::Keyboard::K;
	m_aAlphaSFKey.at(11) = sf::Keyboard::L;
	m_aAlphaSFKey.at(12) = sf::Keyboard::M;
	m_aAlphaSFKey.at(13) = sf::Keyboard::N;
	m_aAlphaSFKey.at(14) = sf::Keyboard::O;
	m_aAlphaSFKey.at(15) = sf::Keyboard::P;
	m_aAlphaSFKey.at(16) = sf::Keyboard::Q;
	m_aAlphaSFKey.at(17) = sf::Keyboard::R;
	m_aAlphaSFKey.at(18) = sf::Keyboard::S;
	m_aAlphaSFKey.at(19) = sf::Keyboard::T;
	m_aAlphaSFKey.at(20) = sf::Keyboard::U;
	m_aAlphaSFKey.at(21) = sf::Keyboard::V;
	m_aAlphaSFKey.at(22) = sf::Keyboard::W;
	m_aAlphaSFKey.at(23) = sf::Keyboard::X;
	m_aAlphaSFKey.at(24) = sf::Keyboard::Y;
	m_aAlphaSFKey.at(25) = sf::Keyboard::Z;
}

AlphabetResource& AlphabetResource::getInstance()
{
	static AlphabetResource instance;
	return instance;
}

std::string AlphabetResource::getLowerCase(int iValue)
{
	return m_aAlphaLowerCase.at(iValue).first;
}

std::string AlphabetResource::getUpperCase(int iValue)
{
	return m_aAlphaUpperCase.at(iValue).first;
}

sf::Keyboard::Key AlphabetResource::getSFKey(std::string sLetter)
{
	for (std::array<std::pair<std::string, sf::Keyboard::Key>, 26>::const_iterator it = m_aAlphaLowerCase.begin();
		it != m_aAlphaLowerCase.end();
		++it)
	{
		if (it->first == sLetter)
		{
			return it->second;
		}
	}
}

std::string AlphabetResource::getRandomLower()
{
	// Copied from http://stackoverflow.com/questions/19665818/best-way-to-generate-random-numbers-using-c11-random-library
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 25);
	return m_aAlphaLowerCase.at(dist(mt)).first;
}