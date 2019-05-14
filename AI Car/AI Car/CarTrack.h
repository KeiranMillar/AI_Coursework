#pragma once
#include "FuzzyLogic.h"
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics\Font.hpp>

class CarTrack
{


public:
	CarTrack();
	~CarTrack();
	int CreateDisplay();
	float UpdateFIS();

	bool isPlaying = true;
	sf::Event Event;
	fl::scalar position = 0;
	fl::scalar direction = 0;
	fl::scalar steerDir = 0;

	FuzzyLogic FIS;

};
