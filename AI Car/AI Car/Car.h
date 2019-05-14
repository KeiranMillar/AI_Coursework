#pragma once
#include "Fuzzy.h"
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics\Font.hpp>

class Car
{


public:
	Car();
	~Car();
	int CreateDisplay();
	float UpdateFIS();

	bool isPlaying = false;
	sf::Event Event;
	fl::scalar position = 0;
	fl::scalar direction = 0;
	fl::scalar steerDir = 0;

	Fuzzy FIS;

};
