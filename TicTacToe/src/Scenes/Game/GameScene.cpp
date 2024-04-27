#include "GameScene.h"
#include <iostream>
#include "../../GUI/Label/Label.h"


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

void GameScene::Update(sf::Time deltaTime)
{
	Scene::Update(deltaTime);

	for (auto& row : field)
	{
		for (auto& cell : row)
		{
			cell->Update(deltaTime);
		}
	}
}

void GameScene::HandleEvent(const sf::Event& event)
{
	Scene::HandleEvent(event);

	for (auto& row : field)
	{
		for (auto& cell : row)
		{
			cell->HandleEvent(event);
		}
	}
}

void GameScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Scene::draw(target, states);

	for (auto& row : field)
	{
		for (auto& cell : row)
		{
			cell->draw(target, states);
		}
	}
}

void GameScene::InitComponetn()
{
	sf::Vector2u windowSize = context->window->getSize();
	sf::Vector2f anchor(windowSize.x / 2.f, windowSize.y / 2.f + 30);

	InitAdditionalComponents(anchor);
	InitField(anchor);
}

void GameScene::InitAdditionalComponents(const sf::Vector2f& anchor)
{
	sf::Vector2u windowSize = context->window->getSize();

	std::unique_ptr<Label> title{ new Label("Tic Tack Toe", context->fonts, 72) };
	title->setPosition(anchor.x, anchor.y - 250);

	std::unique_ptr<Button> back{ new Button(120, 50, context->fonts, context->textures, "BACK") };
	back->setPosition(80, windowSize.y - 50);

	components.push_back(std::move(title));
	components.push_back(std::move(back));
}

void GameScene::InitField(const sf::Vector2f& anchor)
{
	InitFieldSize();
	InitFielCells(anchor);	
}

void GameScene::InitFieldSize()
{
	const size_t SIZE = 3;

	field.resize(SIZE);

	for (auto& row : field)
	{
		row.resize(SIZE);
	}
}

void GameScene::InitFielCells(const sf::Vector2f& anchor)
{
	const int OFFSET = 80;

	for (int offsetY = -OFFSET, i = 0; offsetY <= OFFSET; offsetY += OFFSET, i++)
	{
		for (int offsetX = -OFFSET, j = 0; offsetX <= OFFSET; offsetX += OFFSET, j++)
		{
			field[i][j] = GetFieldElement(anchor.x + offsetX, anchor.y + offsetY);
		}
	}
}

std::unique_ptr<Button> GameScene::GetFieldElement(float x, float y)
{
	const int SIZE = 70;

	std::unique_ptr<Button> button(new Button(SIZE, SIZE, context->fonts, context->textures));

	button->setPosition(x, y);
	// TODO: Set the action.

	return std::move(button);
}
