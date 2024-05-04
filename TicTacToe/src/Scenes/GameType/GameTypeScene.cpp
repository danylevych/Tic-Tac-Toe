#include "GameTypeScene.h"
#include "../../GUI/Label/Label.h"
#include "../../GUI/Button/Button.h"
#include "../SceneStack/SceneStack.h"
#include "../../Tools/Enums/GameType.h"


GameTypeScene::GameTypeScene(Context& context, SceneStack* stack)
	: Scene(context, stack)
{
	InitComponetns();
}

GameTypeScene::GameTypeScene(Context & context, SceneStack * stack, const sf::Texture & texture)
	: Scene(context, stack, texture)
{	
	InitComponetns();
}

void GameTypeScene::InitComponetns()
{
	const size_t WIDTH = 230;
	const size_t HEIGHT = 50;
	const size_t SPACE = 150;

	auto& fonts = context->fonts;
	auto& textures = context->textures;
	sf::Vector2f anchor = GetAnchor();

	std::unique_ptr<Label> title{ new Label("Select Game Type",fonts, 72) };
	title->setPosition(anchor.x, anchor.y - 100);

	std::unique_ptr<Button> againstIA{ new Button(WIDTH, HEIGHT, fonts, textures, "Against IA") };
	againstIA->setPosition(anchor.x - SPACE, anchor.y);
	againstIA->SetCommand([this]() {
			sceneStack->RequestPush(SceneStack::SceneType::GameAgainstAI);
		});

	std::unique_ptr<Button> twoPlayers{ new Button(WIDTH, HEIGHT, fonts, textures, "Two players") };
	twoPlayers->setPosition(anchor.x + SPACE, anchor.y);
	twoPlayers->SetCommand([this]() {
			sceneStack->RequestPush(SceneStack::SceneType::GameTwoPlayers);
		});
	components.push_back(std::move(title));
	components.push_back(std::move(againstIA));
	components.push_back(std::move(twoPlayers));
}

sf::Vector2f GameTypeScene::GetAnchor()
{
	sf::Vector2u windowSize = context->window->getSize();
	sf::Vector2f anchor(windowSize.x / 2.f, windowSize.y / 2.f);

	return anchor;
}


