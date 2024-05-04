#pragma once

#include "../Scene/Scene.h"


class GameOverScene : public Scene
{
public:
	using Ptr = std::unique_ptr<GameOverScene>;

private:
	std::string finalText;

public:
	GameOverScene(Context& context, SceneStack* sceneStack, const std::string& finalText);
	GameOverScene(Context& context, SceneStack* sceneStack, const sf::Texture& texture, const std::string& finalText);

	virtual ~GameOverScene() override = default;

private:
	void InitComponents();

private:
	sf::Vector2f GetAnchor();
};
