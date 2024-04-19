#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../Tools/ResourceHolder/Holders.h"


class Context
{
private:
	static std::unique_ptr<Context> instance;

public:
	std::unique_ptr<sf::RenderWindow> window;
	TextureHolder textures;
	FontHolder fonts;

private:
	Context() = default;

public:
	~Context() = default;

public:
	static Context* GetInstance()
	{
		if (!instance)
		{
			instance = std::move(std::unique_ptr<Context>(new Context()));
		}

		return instance.get();
	}
};