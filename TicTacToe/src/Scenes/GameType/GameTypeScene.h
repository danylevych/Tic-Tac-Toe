#pragma once

#include "../Scene/Scene.h"
#include "../../Tools/Enums/GameType.h"


class GameTypeScene : public Scene
{
public:
	using Ptr = std::unique_ptr<GameTypeScene>;

public:
	GameTypeScene(Context& context, SceneStack* stack);
	GameTypeScene(Context& context, SceneStack* stack, const sf::Texture& texture);

private: // Init section.
	void InitComponetns();

private:
	sf::Vector2f GetAnchor();

};
