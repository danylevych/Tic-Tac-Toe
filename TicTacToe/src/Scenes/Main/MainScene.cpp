#include "MainScene.h"
#include "../../GUI/Label/Label.h"
#include "../../GUI/Button/Button.h"


MainScene::MainScene(Context& context)
	: Scene()
	, context(&context)
{	
	InitComponents();
}

MainScene::MainScene(Context& context, const sf::Texture& texture)
	: Scene(texture)
	, context(&context)
{	
	InitComponents();
}

MainScene::MainScene(Context& context, const sf::Texture& texture, sf::IntRect rect)
	: Scene(texture, rect)
	, context(&context)
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

	std::unique_ptr<Button> exit{ new Button(150, 50, context->fonts, context->textures, "Exit") };
	exit->setPosition(size.x / 2.f, yPosition + 70);
	exit->SetCommand(Button::Command([this]() {
			context->window->close();
		}));

	components.push_back(std::move(title));
	components.push_back(std::move(play));
	components.push_back(std::move(exit));
}
