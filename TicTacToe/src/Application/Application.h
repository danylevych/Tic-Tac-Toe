#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "Context/Context.h"
#include "../Scenes/SceneStack/SceneStack.h"


class Application : public sf::NonCopyable
{
private:
	Context* context;
	SceneStack sceneStack;

public:
	Application();

public: 
	void Run();

private:
	void Update(sf::Time deltaTime);
	void Render();
	void Process();

private:
	void InitSceneFactory();
	void InitContext();
	void InitFonts();
	void InitTextures();
	void InitWindow();
};

