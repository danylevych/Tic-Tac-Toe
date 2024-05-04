#include "GameOverScene.h"
#include "../SceneStack/SceneStack.h"
#include "../../GUI/Label/Label.h"
#include "../../GUI/Button/Button.h"


GameOverScene::GameOverScene(Context& context, SceneStack* sceneStack, const std::string& finalText)
	: Scene(context, sceneStack)
	, finalText(finalText)
{
	InitComponents();
}

GameOverScene::GameOverScene(Context& context, SceneStack* sceneStack, const sf::Texture& texture, const std::string& finalText)
	: Scene(context, sceneStack, texture)
	, finalText(finalText)
{
	InitComponents();
}

void GameOverScene::InitComponents()
{
	auto& fonts = context->fonts;
	auto& textures = context->textures;
	sf::Vector2f anchor = GetAnchor();

	std::unique_ptr<Label> title{ new Label(finalText, fonts, 72) };
	title->setPosition(anchor.x, anchor.y - 100);

	std::unique_ptr<Button> back{ new Button(120, 50, context->fonts, context->textures, "BACK") };
	back->setPosition(anchor.x, anchor.y);

	back->SetCommand([this]() {
		sceneStack->RequestClear();
		sceneStack->RequestPush(SceneStack::SceneType::Main);
	});

	components.push_back(std::move(title));
	components.push_back(std::move(back));
}

sf::Vector2f GameOverScene::GetAnchor()
{
	sf::Vector2u windowSize = context->window->getSize();
	sf::Vector2f anchor(windowSize.x / 2.f, windowSize.y / 2.f + 30);

	return anchor;
}