#include "MainScene.h"
#include "../../GUI/Label/Label.h"
#include "../../GUI/Button/Button.h"
#include "../SceneStack/SceneStack.h"


MainScene::MainScene(Context& context, SceneStack* sceneStack)
	: Scene(context, sceneStack)
{	
	InitComponents();
}

MainScene::MainScene(Context& context, SceneStack* sceneStack, const sf::Texture& texture)
	: Scene(context, sceneStack, texture)
{	
	InitComponents();
}

void MainScene::InitComponents()
{
	sf::Vector2f size = context->window->getDefaultView().getSize();
	float yPosition = size.y / 2.f;

	std::unique_ptr<Label> title{ new Label("Tic Tack Toe", context->fonts, 72) };
	title->setPosition(size.x / 2.f, yPosition - 100); // Position of the screen mid.

	std::unique_ptr<Button> play{ new Button(150, 50, context->fonts, context->textures, "Play") };
	play->setPosition(size.x / 2.f, yPosition);
	play->SetCommand(Button::Command([this]() {
			sceneStack->Push(SceneStack::SceneType::Game);
		}));

	std::unique_ptr<Button> exit{ new Button(150, 50, context->fonts, context->textures, "Exit") };
	exit->setPosition(size.x / 2.f, yPosition + 70);
	exit->SetCommand(Button::Command([this]() {
			sceneStack->Clear();
		}));

	components.push_back(std::move(title));
	components.push_back(std::move(play));
	components.push_back(std::move(exit));
}
