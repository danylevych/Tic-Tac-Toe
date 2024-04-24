#pragma once


#include "../Scene/Scene.h"
#include "../../GUI/Button/Button.h"

class GameScene : public Scene
{
public:
	using Ptr = std::unique_ptr<GameScene>;

public:
	GameScene(Context& context, SceneStack* stack);
	GameScene(Context& context, SceneStack* stack, const sf::Texture& texture);

private: // Init section.
	void InitComponetn();

private: // Helper function.
	std::unique_ptr<Button> GetFieldElement(float x, float y);

};

