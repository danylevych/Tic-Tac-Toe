#pragma once


#include "../Scene/Scene.h"
#include "../../Application/Context/Context.h"

//class Context;

class MainScene :  public Scene
{
public:
	using Ptr = std::unique_ptr<MainScene>;

private:
	Context* context;

public:
	MainScene(Context& context);
	MainScene(Context& context, const sf::Texture& texture);
	MainScene(Context& context, const sf::Texture& texture, sf::IntRect rect);

	virtual ~MainScene() override = default;

private: // Helper functions sections.
	void InitComponents();
};

