#include <SFML/Graphics.hpp>

typedef unsigned int uint;

constexpr uint WINDOW_WIDTH = 800;
constexpr uint WINDOW_HEIGHT = 600;


int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Framework Test Application");
	
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		
		window.draw(shape);


		window.display();
	}

	return 0;
}