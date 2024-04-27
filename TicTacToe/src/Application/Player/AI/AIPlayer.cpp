#include "AIPlayer.h"

AIPlayer::AIPlayer(Type type, std::vector<std::vector<Button::Ptr>>& field)
	: Player(type)
{	
	InitFieldSize(field.size());
	InitField(field);
}

void AIPlayer::InitFieldSize(size_t size)
{
	field.resize(size);

	for (auto& row : field)
	{
		row.resize(size);
	}
}

void AIPlayer::InitField(std::vector<std::vector<Button::Ptr>>& field)
{
	for (size_t i = 0; i < field.size(); i++)
	{
		for (size_t j = 0; j < field[0].size(); j++)
		{
			this->field[i][j] = field[i][j]->GetText();
		}
	}
}

std::string AIPlayer::GetPlayer(const Board& board)
{
	int numOfX = 0;
	int numOfO = 0;

	for (const auto& row : board)
	{
		numOfX += std::count(row.begin(), row.end(), "X");
		numOfO += std::count(row.begin(), row.end(), "O");
	}

	return ((numOfX + numOfO) % 2 == 0) ? "X" : "O";
}

std::set<AIPlayer::Action> AIPlayer::Actions(Board& board)
{
	std::set<Action> actions;

	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[0].size(); j++)
		{
			std::string cell = board[i][j];
			if (cell != "X" && cell != "O")
			{
				actions.insert(Action{ i, j });
			}
		}
	}

	return actions;
}

std::string AIPlayer::GetWinner(const Board& board)
{
	// Checking for rows and columns.
	for (size_t i = 0; i < board.size(); i++)
	{
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
		{
			return board[i][0];
		}
		else if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
		{
			return board[0][i];
		}
	}

	// Checking for diagonals.
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
	{
		return board[0][0];
	}

	if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
	{
		return board[0][2];
	}
	
	return std::string();
}

int AIPlayer::Utility(const Board& board)
{
	std::string winner = GetWinner(board);
	
	if (!winner.empty())
	{
		return (winner == "X") ? 1 : -1;
	}

	return 0;
}

AIPlayer::Action AIPlayer::MinMax(Board& board)
{
	return Action();
}
