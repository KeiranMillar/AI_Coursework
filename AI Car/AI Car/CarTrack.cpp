#include "CarTrack.h"

CarTrack::CarTrack()
{
}

CarTrack::~CarTrack()
{

}

int CarTrack::CreateDisplay()
{
	float distanceFromLine = 0;
	float velocity = 0;
	float acceleration = 0;
	float time = 0;

	sf::RectangleShape carShape;
	carShape.setFillColor(sf::Color::Black);
	carShape.setOutlineColor(sf::Color::Blue);
	carShape.setSize(sf::Vector2f(50.0f, 50.0f));
	carShape.setPosition(400.0f, 300.0f);
	sf::Vector2f lastPos;

	sf::RectangleShape line;
	line.setFillColor(sf::Color::Red);
	line.setOutlineColor(sf::Color::Red);
	line.setSize(sf::Vector2f(20.0f, 900.0f));
	line.setPosition(400.0f, 0.0f);

	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Networking");
	window.setTitle("Racing Line");

	sf::Clock clock;
	FIS.InitEngine();

	while (isPlaying)
	{
		float deltaTime = clock.restart().asSeconds();
		lastPos = carShape.getPosition();

		sf::Event Event;
		window.pollEvent(Event);

		switch (Event.type)
		{
		case sf::Event::KeyPressed:
			if (Event.key.code == sf::Keyboard::Space)
				isPlaying = true;
			if (Event.key.code == sf::Keyboard::Escape)
			{
				window.close();
				isPlaying = false;
			}
				
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				line.move((-400.0f * deltaTime), 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				line.move((400.0f * deltaTime), 0);
			}
			break;
		}

		time += deltaTime;

		distanceFromLine = line.getPosition().x - carShape.getPosition().x;
		std::cout << "dis:" << distanceFromLine << std::endl;

		acceleration = FIS.Update(distanceFromLine , velocity * 4);
		std::cout << "steer:" << acceleration << std::endl;
		velocity += acceleration * deltaTime;

		carShape.move(-velocity * 2 , 0);
		window.draw(line);
		window.draw(carShape);
		window.display();
		window.clear(sf::Color::White);
	}

	return 0;
}

float CarTrack::UpdateFIS()
{
	return 0;
}