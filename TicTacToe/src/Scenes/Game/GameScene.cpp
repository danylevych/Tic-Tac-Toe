#include "GameScene.h"

#include <iostream>
#include "../../GUI/Label/Label.h"
#include "../../Scenes/SceneStack/SceneStack.h"
#include "../../Application/Player/AI/AIPlayer.h"


GameScene::GameScene(Context& context, SceneStack* stack, GameType type)
	: Scene(context, stack)
	, board(context, GetAnchor(), 80)
{
	InitBoardPlayers(type);
	InitComponetns();
}

GameScene::GameScene(Context& context, SceneStack* stack, const sf::Texture& texture, GameType type)
	: Scene(context, stack, texture)
	, board(context, GetAnchor(), 80)
{
	InitBoardPlayers(type);
	InitComponetns();
}

void GameScene::Update(sf::Time deltaTime)
{
	Scene::Update(deltaTime);

	Board::PlayerType winner = board.GetWinner();
	if (winner != Board::PlayerType::NONE || board.IsDraw())
	{
		switch (winner)
		{
		case Board::PlayerType::X:
			sceneStack->RequestPush(SceneStack::SceneType::GameOverWinX);
			break;
		case Board::PlayerType::O:
			sceneStack->RequestPush(SceneStack::SceneType::GameOverWinO);
			break;
		default:
			sceneStack->RequestPush(SceneStack::SceneType::GameOverDraw);
			break;
		}
		
		return;
	}

	board.Update(deltaTime);
}

void GameScene::HandleEvent(const sf::Event& event)
{
	Scene::HandleEvent(event);
	board.HandleEvent(event);
}

void GameScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Scene::draw(target, states);
	board.draw(target, states);
}

void GameScene::InitComponetns()
{
	InitAdditionalComponents(GetAnchor());
}

void GameScene::InitAdditionalComponents(const sf::Vector2f& anchor)
{
	sf::Vector2u windowSize = context->window->getSize();

	std::unique_ptr<Label> title{ new Label("Tic Tack Toe", context->fonts, 72) };
	title->setPosition(anchor.x, anchor.y - 250);

	std::unique_ptr<Button> back{ new Button(120, 50, context->fonts, context->textures, "BACK") };
	back->setPosition(80, windowSize.y - 50);

	back->SetCommand([this]() { this->sceneStack->RequestPop(); });

	components.push_back(std::move(title));
	components.push_back(std::move(back));
}

void GameScene::InitBoardPlayers(GameType gameType)
{
	switch (gameType)
	{
	case GameType::AgainstIA:
		board.SetPlayerX(new Player(Board::PlayerType::X));
		board.SetPlayerO(new AIPlayer(Board::PlayerType::O));
		break;
	case GameType::AgainstPlayer:
		board.SetPlayerX(new Player(Board::PlayerType::X));
		board.SetPlayerO(new Player(Board::PlayerType::O));
		break;
	default:
		InitBoardPlayers(GameType::AgainstIA);
		break;
	}
}

sf::Vector2f GameScene::GetAnchor()
{
	sf::Vector2u windowSize = context->window->getSize();
	sf::Vector2f anchor(windowSize.x / 2.f, windowSize.y / 2.f + 30);

	return anchor;
}
