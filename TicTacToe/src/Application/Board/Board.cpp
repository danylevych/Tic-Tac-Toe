#include "Board.h"

#include "../Context/Context.h"

Board::Board(Context& context, sf::Vector2f anchor, size_t cellSize)
	: context(&context)
{	
	InitBoard(anchor, cellSize);
}

void Board::InitBoard(sf::Vector2f anchor, size_t cellSize)
{
	const int OFFSET = 80;

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
	button->SetCommand([this, rawPtr]() {});

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
	if (currentPlayer == PlayerType::X)
	{
		currentPlayer = PlayerType::O;
	}
	else
	{
		currentPlayer = PlayerType::X;
	}
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
	for (const auto& row : board)
	{
		for (const auto& cell : row)
		{
			cell->HandleEvent(event);
		}
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

Board::PlayerType Board::GetWinner() const
{
	// Checking for rows and columns.
	for (size_t i = 0; i < board.size(); i++)
	{
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
		{
			return GetPlayerTypeFromCell(board[i][0]);
		}
		else if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
		{
			return GetPlayerTypeFromCell(board[0][i]);
		}
	}

	// Checking for diagonals.
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
	{
		return GetPlayerTypeFromCell(board[0][0]);
	}

	if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
	{
		return GetPlayerTypeFromCell(board[0][2]);
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
