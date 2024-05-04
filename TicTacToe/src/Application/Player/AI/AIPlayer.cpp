#include "AIPlayer.h"
#include <iostream>
#include "../../Board/Board.h"

AIPlayer::AIPlayer(Board::PlayerType type)
	: Player(type)
	, minMax(board, GetTypeAsString()[0])
{	
	ResizeBorder(3);
}

Player::Action AIPlayer::GetAction(const std::vector<std::vector<Button::Ptr>>&board)
{
	FillBoard(board);

	int bestEval = std::numeric_limits<int>::min();
	Action action;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (this->board[i][j] == char{})
			{
				this->board[i][j] = GetTypeAsString()[0];
				int eval = minMax(0, false);
				this->board[i][j] = char{};

				if (eval > bestEval)
				{
					bestEval = eval;
					action = Action{ i, j };
				}
			}
		}
	}

	return action;
}

void AIPlayer::ResizeBorder(size_t size)
{
	board.resize(size);
	for (auto& row : board)
	{
		row.resize(size);
	}
}

void AIPlayer::FillBoard(const std::vector<std::vector<Button::Ptr>>& board)
{
	for (size_t i = 0; i < board.size(); i++)
	{
		for (size_t j = 0; j < board[i].size(); j++)
		{
			this->board[i][j] = board[i][j]->GetText()[0];
		}
	}
}
