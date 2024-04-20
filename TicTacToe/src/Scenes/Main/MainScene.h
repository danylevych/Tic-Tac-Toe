#pragma once


#include "../Scene/Scene.h"
#include "../../Application/Context/Context.h"

class MainScene :  public Scene
{
public:
	using Ptr = std::unique_ptr<MainScene>;

public:
	MainScene(Context& context, SceneStack* sceneStack);
	MainScene(Context& context, SceneStack* sceneStack, const sf::Texture& texture);

	virtual ~MainScene() override = default;

private: // Helper functions sections.
	void InitComponents();
};

