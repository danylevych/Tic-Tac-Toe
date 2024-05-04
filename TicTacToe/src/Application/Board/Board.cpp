#include "Board.h"
#include <iostream>

#include "../Player/Player.h"
#include "../Player/AI/AIPlayer.h"
#include "../Context/Context.h"

bool operator==(const Board::Cell& left, const Board::Cell& right)
{
	return left->GetText() == right->GetText();
}

Board::Board(Context& context, sf::Vector2f anchor, size_t cellSize, std::unique_ptr<Player> playerX, std::unique_ptr<Player> playerO)
	: context(&context)
	, currentPlayer(PlayerType::X)
	, playerX(nullptr)
	, playerO(nullptr)
{	
	InitBoard(anchor, cellSize);
}

void Board::InitBoard(sf::Vector2f anchor, size_t cellSize)
{
	ResizeBoard(3);
	FillBoard(anchor, cellSize);
}

void Board::ResizeBoard(size_t size)
{
	board.resize(size);
	for (auto& row : board)
	{
		row.resize(size);
	}
}

void Board::FillBoard(sf::Vector2f anchor, size_t cellSize)
{
	const int OFFSET = cellSize + 10;

	for (int offsetY = -OFFSET, i = 0; offsetY <= OFFSET; offsetY += OFFSET, i++)
	{
		for (int offsetX = -OFFSET, j = 0; offsetX <= OFFSET; offsetX += OFFSET, j++)
		{
			board[i][j] = GetFieldElement(anchor.x + offsetX, anchor.y + offsetY, cellSize);
		}
	}
}

std::unique_ptr<Button> Board::GetFieldElement(float x, float y, size_t cellSize)
{
	std::unique_ptr<Button> button(new Button(cellSize, cellSize, context->fonts, context->textures));

	button->setPosition(x, y);

	auto rawPtr = button.get();
	button->SetCommand([this, rawPtr]() {
		std::string cellValue = rawPtr->GetText();

		if (!cellValue.empty()) {
			return;
		}

		rawPtr->SetText(GetCurrentPlayerAsString());
		ChangeCurrentPlayer();
	});

	return std::move(button);
}

Board::PlayerType Board::GetPlayerTypeFrom(const Cell& cell) const
{
	std::string cellValue = cell->GetText();
	return (cellValue.empty()) ? PlayerType::NONE : (cellValue == "X") ? PlayerType::X : PlayerType::O;
}

std::string Board::GetCurrentPlayerAsString() const
{
	return (currentPlayer == PlayerType::NONE) ? "" : (currentPlayer == PlayerType::X) ? "X" : "O";
}

void Board::ChangeCurrentPlayer()
{
	if (currentPlayer == PlayerType::X) {
		currentPlayer = PlayerType::O;
	}
	else {
		currentPlayer = PlayerType::X;
	}
}

bool Board::IsCellNotEmpty(const Cell& cell) const
{
	return !cell->GetText().empty();
}

bool Board::CurrentPlayerIsHuman() 
{
	return dynamic_cast<AIPlayer*>(GetCurrentPlayer()) == nullptr;
}

Player* Board::GetCurrentPlayer()
{
	if (GetCurrentPlayerAsString() == "X") {
		return playerX.get();
	}

	return playerO.get();
}

void Board::Update(sf::Time deltaTime)
{
	for (auto& row : board)
	{
		for (auto& cell : row)
		{
			cell->Update(deltaTime);
		}
	}
}

void Board::HandleEvent(const sf::Event& event)
{
	if (IsFull()) {
		return;
	}

	if (CurrentPlayerIsHuman()) {
		HandleEventForHumanPlayer(event);
	}
	else {
		HandleEventForAIPlayer(event);
	}
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& row : board)
	{
		for (const auto& cell : row)
		{
			target.draw(*cell, states);
		}
	}
}

void Board::HandleEventForHumanPlayer(const sf::Event& event)
{
	for (const auto& row : board)
	{
		for (const auto& cell : row)
		{
			cell->HandleEvent(event);
		}
	}
}

void Board::HandleEventForAIPlayer(const sf::Event& event)
{
	Player::Action action = playerO->GetAction(board);
	board[action.i][action.j]->Press();
}

void Board::SetPlayerX(Player* playerX)
{
	this->playerX.reset(playerX);
}

void Board::SetPlayerO(Player* playerO)
{
	this->playerO.reset(playerO);
}

Board::PlayerType Board::GetWinner() const
{
	// Checking for rows and columns.
	for (size_t i = 0; i < board.size(); i++)
	{
		if (IsCellNotEmpty(board[i][0]) && board[i][0] == board[i][1] && board[i][0] == board[i][2])
		{
			std::cout << "Here is the winner" << std::endl;
			return GetPlayerTypeFrom(board[i][0]);
		}
		else if (IsCellNotEmpty(board[0][i]) && board[0][i] == board[1][i] && board[0][i] == board[2][i])
		{
			return GetPlayerTypeFrom(board[0][i]);
		}
	}

	// Checking for diagonals.
	if (IsCellNotEmpty(board[0][0]) && board[0][0] == board[1][1] && board[0][0] == board[2][2])
	{
		std::cout << "Here is the winner" << std::endl;
		return GetPlayerTypeFrom(board[0][0]);
	}

	if (IsCellNotEmpty(board[0][2]) && board[0][2] == board[1][1] && board[0][2] == board[2][0])
	{
		return GetPlayerTypeFrom(board[0][2]);
	}

	return PlayerType::NONE;
}

bool Board::IsFull() const
{
	for (const auto& row : board)
	{
		for (const auto& cell : row)
		{
			if (cell->GetText().empty())
			{
				return false;
			}
		}
	}

	return true;
}

bool Board::IsDraw() const
{
	return IsFull() && GetWinner() == PlayerType::NONE;
}


