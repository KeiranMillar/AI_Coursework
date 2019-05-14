#include "Car.h"

Car::Car()
{
}

Car::~Car()
{

}

int Car::CreateDisplay()
{
	float distanceFromLine = NULL;
	float directionOfCar = NULL;
	float carMovement = NULL;

	sf::Font font;
	if (!font.loadFromFile("../resources/sansation.ttf"))
		return EXIT_FAILURE;

	// Initialize the pause message
	sf::Text pauseMessage;
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(40);
	pauseMessage.setPosition(170.f, 150.f);
	pauseMessage.setFillColor(sf::Color::White);
	pauseMessage.setString("Welcome to my AI coursework!\nUse Left and Right arrows to control the line\nPress Space to continue");

	sf::RectangleShape carShape;
	carShape.setFillColor(sf::Color::Black);
	carShape.setOutlineColor(sf::Color::Blue);
	carShape.setSize(sf::Vector2f(5.0f, 5.0f));
	sf::Vector2f lastPos;

	sf::RectangleShape line;
	carShape.setFillColor(sf::Color::White);
	carShape.setOutlineColor(sf::Color::White);
	line.setSize(sf::Vector2f(300.0f, 2.0f));

	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Networking");
	window.setTitle("Racing Line");

	sf::Clock clock;

	window.draw(pauseMessage);

	while (isPlaying == false)
	{
		sf::Event Event;
		window.pollEvent(Event);
		switch (Event.type)
		{
		case sf::Event::KeyPressed:
			if (Event.key.code == sf::Keyboard::Space)
				isPlaying = true;
			break;
		}
	}

	while (isPlaying)
	{
		float deltaTime = clock.restart().asSeconds();
		sf::Event Event;
		window.pollEvent(Event);

		lastPos = carShape.getPosition();

		switch (Event.type)
		{
		case sf::Event::KeyPressed:
			if (Event.key.code == sf::Keyboard::Space)
				isPlaying = true;
			if (Event.key.code == sf::Keyboard::Escape)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				sf::Vector2f pos = line.getPosition();
				pos.x += 5.0f * deltaTime;
				line.setPosition(pos);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				sf::Vector2f pos = line.getPosition();
				pos.x -= 5.0f * deltaTime;
				line.setPosition(pos);
			}
			break;
		}

		distanceFromLine = line.getPosition().x - carShape.getPosition().x;
		directionOfCar = lastPos.x - carShape.getPosition().x;
		carMovement = FIS.Update(distanceFromLine, directionOfCar);
		sf::Vector2f newPos = carShape.getPosition();
		newPos.x += carMovement;
		line.setPosition(newPos);
	}

	return 0;
}

float Car::UpdateFIS()
{
	return 0;
}