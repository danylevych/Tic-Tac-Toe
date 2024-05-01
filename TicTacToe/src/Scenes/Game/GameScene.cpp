#include "GameScene.h"

#include <iostream>
#include "../../GUI/Label/Label.h"
#include "../../Scenes/SceneStack/SceneStack.h"
#include "../../Application/Player/AI/AIPlayer.h"


GameScene::GameScene(Context& context, SceneStack* stack)
	: Scene(context, stack)
	, currentPlayer(Player::Type::X)
{
	InitPlayers();
	InitComponetn();
}

GameScene::GameScene(Context& context, SceneStack* stack, const sf::Texture& texture)
	: Scene(context, stack, texture)
	, currentPlayer(Player::Type::X)
{
	InitPlayers();
	InitComponetn();
}


void GameScene::Update(sf::Time deltaTime)
{
	Scene::Update(deltaTime);

	HandlePlayerAction();

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

	/*for (auto& row : field)
	{
		for (auto& cell : row)
		{
			cell->HandleEvent(event);
		}
	}*/
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


void GameScene::HandlePlayerAction()
{
	Player* currentPlayer = GetCurrentPlayer();

	if (dynamic_cast<AIPlayer*>(currentPlayer) == nullptr) {
		std::cout << "Next move is for AI" << std::endl;
		return;
	}

	Player::Action action = currentPlayer->GetAction(field);

	field[action.i][action.j]->Call();
}

Player* GameScene::GetCurrentPlayer()
{
	/*int numOfFullCells = 0;

	for (auto& row : field)
	{
		numOfFullCells += std::count_if(row.begin(), row.end(), [](const Button::Ptr& item) {
			std::cout << item->GetText() << std::endl;
			if (item->GetText() == "X" || item->GetText() == "O") {
				return true;
			}
			return false;
		});
	}

	std::cout << "num: " << numOfFullCells << std::endl;

	std::cout << (numOfFullCells % 2 == 0) << std::endl;

	currentPlayer = (numOfFullCells % 2 == 0) ? Player::Type::X : Player::Type::O;*/

	if (playerX->GetType() == currentPlayer) {
		return playerX.get();
	}
	else if (playerO->GetType() == currentPlayer) {
		return playerO.get();
	}
}

void GameScene::InitPlayers()
{
	// TODO: Make the posiability to play tic tac toe beetween two person.
	playerX = std::move(Player::Ptr(new Player(Player::Type::X)));
	playerO = std::move(Player::Ptr(new AIPlayer(Player::Type::O)));
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

	back->SetCommand([this]() { this->sceneStack->Pop(); });

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
	
	auto rawPtr = button.get();
	button->SetCommand([this, rawPtr]() {
		std::string cellValue = rawPtr->GetText();

		if (!cellValue.empty()) {
			return;
		}
		
		rawPtr->SetText(GetCurrentPlayer()->GetTypeAsString());
		currentPlayer = (currentPlayer == Player::Type::X) ? Player::Type::O : Player::Type::X;
	});

	return std::move(button);
}
