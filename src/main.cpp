#include <SFML/Graphics.hpp>
#include "game.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Game of life", sf::Style::Close);

	Game game;
	game.Init(128, 72);
	sf::Clock clock;

	while(window.isOpen())
	{
		sf::Event event;

		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		game.Update();
		game.Render(window);
		float dt = clock.restart().asMilliseconds();
		std::cout << "FPS: " << 1000.0f / dt << std::endl;
	}

	return 0;
}