#include "GameScene.h"
#include <iostream>


GameScene::GameScene(Context& context, SceneStack* stack)
	: Scene(context, stack)
{
	InitComponetn();
}

GameScene::GameScene(Context& context, SceneStack* stack, const sf::Texture& texture)
	: Scene(context, stack, texture)
{
	InitComponetn();
}

void GameScene::InitComponetn()
{
	sf::Vector2u windowSize = context->window->getSize();
	sf::Vector2f centerPos(windowSize.x / 2.f, windowSize.y / 2.f);

	int offset = 80;

	for (int offsetX = -offset; offsetX <= offset; offsetX += offset)
	{
		std::cout << "first loop" << std::endl;
		for (int offsetY = -offset; offsetY <= offset; offsetY += offset)
		{
			components.push_back(GetFieldElement(centerPos.x + offsetX, centerPos.y + offsetY));
			std::cout << "1" << std::endl;
		}
	}
}

std::unique_ptr<Button> GameScene::GetFieldElement(float x, float y)
{
	std::unique_ptr<Button> button(new Button(70, 70, context->fonts, context->textures));

	button->setPosition(x, y);
	// TODO: Set the action.

	return std::move(button);
}
