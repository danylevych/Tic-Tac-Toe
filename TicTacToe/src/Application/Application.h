#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/NonCopyable.hpp>


class Application : public sf::NonCopyable
{
private:
	sf::RenderWindow window;

public:
	Application();

public: 
	void Run();

private:
	void Update(sf::Time deltaTime);
	void Render();
	void Process();
};

