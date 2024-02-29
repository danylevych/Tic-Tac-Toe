#include "Application.h"


Application::Application()
	: window(sf::VideoMode(800, 600), "Tic Tac Toe", sf::Style::Close)
{	}

void Application::Run()
{
	const sf::Time FPS = sf::seconds(1.f / 60.f);

	sf::Time time = sf::Time::Zero;
	sf::Clock clock;

	while (window.isOpen())
	{
		time += clock.getElapsedTime();

		Process();

		while (time > FPS)
		{
			Update(FPS);
			Process();
		}

		Render();
	}
}
