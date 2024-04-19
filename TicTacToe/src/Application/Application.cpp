#include "Application.h"

#include <SFML/Window/Event.hpp>

#include "../Scenes/Main/MainScene.h"


Application::Application()
	: context(Context::GetInstance())
	, sceneStack(context)
{	
	InitContext();
	sceneStack.Push(SceneStack::SceneType::Main);
}

void Application::Run()
{
	const sf::Time FPS = sf::seconds(1.f / 60.f);

	sf::Time time = sf::Time::Zero;
	sf::Clock clock;

	while (context->window->isOpen())
	{
		time += clock.getElapsedTime();

		Process();

		while (time > FPS)
		{
			time -= FPS;
			Update(FPS);
			Process();
		}

		Render();
	}
}

void Application::Update(sf::Time deltaTime)
{
	if (sceneStack)
	{
		sceneStack.Update(deltaTime);
	}
}

void Application::Render()
{
	sf::RenderWindow& window = *context->window;
	window.clear(sf::Color(21, 37, 51));

	if (sceneStack)
	{
		sceneStack.Draw(window);
	}

	window.display();
}

void Application::Process()
{
	sf::RenderWindow& window = *context->window;
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			// TODO: Save user data.
			window.close();
			break;
		}

		if (sceneStack)
		{
			sceneStack.HandleEvent(event);
		}
	}
}

void Application::InitContext()
{
	InitWindow();
	InitFonts();
	InitTextures();
}

void Application::InitFonts()
{
	context->fonts.Load(FontID::Label, "data/Fonts/Madimi One/MadimiOne-Regular.ttf");
	context->fonts.Load(FontID::Button, "data/Fonts/Roboto/Roboto-Bold.ttf");
}

void Application::InitTextures()
{
	context->textures.Load(TextureID::ButtonDefault, "data/Textures/ButtonDefault.png");
	context->textures.Load(TextureID::ButtonPressed, "data/Textures/ButtonPressed.png");
}

void Application::InitWindow()
{
	context->window.reset(new sf::RenderWindow(sf::VideoMode(800, 600), "Tic Tac Toe", sf::Style::Close));
}
