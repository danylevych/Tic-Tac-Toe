#include "MinMax.h"

int Min(int left, int right)
{
	return (left < right) ? left : right;
}

int Max(int left, int right)
{
	return (left > right) ? left : right;
}


MinMax::MinMax(Board& board, const Cell& type)
	: board(board)
	, IAtype(type)
{	}

int MinMax::operator()(int depth, bool isMax)
{
	Cell winner = GetWinner();
	if (winner != EMPTY) {
		return (winner == IAtype) ? MAX_SCORE : MIN_SCORE;
	}

	if (IsDraw()) {
		return DRAW_SCORE;
	}

	if (isMax)
	{
		return BestScore(std::numeric_limits<int>::min(), depth, isMax, Max);
	}
	else
	{
		return BestScore(std::numeric_limits<int>::max(), depth, isMax, Min);
	}
}

MinMax::Cell MinMax::GetWinner()
{
	for (size_t i = 0; i < board.size(); i++)
	{
		if (IsPlayerOn(board[i][0]) && board[i][0] == board[i][1] && board[i][0] == board[i][2])
		{
			return board[i][0];
		}

		if (IsPlayerOn(board[0][i]) && board[0][i] == board[1][i] && board[0][i] == board[2][i])
		{
			return board[0][i];
		}
	}

	if (IsPlayerOn(board[0][0]) && board[0][0] == board[1][1] && board[0][0] == board[2][2])
	{
		return board[0][0];
	}

	if (IsPlayerOn(board[0][2]) && board[0][2] == board[1][1] && board[0][2] == board[2][0])
	{
		return board[0][2];
	}

	return EMPTY;
}

bool MinMax::IsDraw() const
{
	for (const auto& row : board)
	{
		for (const auto& cell : row)
		{
			if (cell == EMPTY)
			{
				return false;
			}
		}
	}

	return true;
}

bool MinMax::IsPlayerOn(Cell cell) const
{
	return (cell == PLAYER_X || cell == PLAYER_O);
}

MinMax::Cell MinMax::GetCurrentPlayer()
{
	int numOfX = 0;
	int numOfO = 0;

	for (const auto& row : board)
	{
		numOfX += std::count(row.begin(), row.end(), PLAYER_X);
		numOfO += std::count(row.begin(), row.end(), PLAYER_O);
	}

	return ((numOfX + numOfO) % 2 == 0) ? PLAYER_X : PLAYER_O;
}

int MinMax::BestScore(int val, int depth, bool isMax, std::function<int(int, int)> func)
{
	int best = val;

	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] == EMPTY)
			{
				board[i][j] = GetCurrentPlayer();
				best = func(best, this->operator()(depth, !isMax));
				board[i][j] = EMPTY;
			}
		}
	}

	return best;
}
