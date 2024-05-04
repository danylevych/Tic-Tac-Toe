#pragma once

#include <vector>
#include <functional>


class MinMax
{
private:
	using Cell = char;
	using Board = std::vector<std::vector<Cell>>;

private:
	Cell IAtype;
	Board& board;

	const Cell EMPTY = Cell();

	const Cell PLAYER_X = 'X';
	const Cell PLAYER_O = 'O';

	int MAX_SCORE = 1;
	int DRAW_SCORE = 0;
	int MIN_SCORE = -1;

public:
	MinMax(Board& board, const Cell& type);

public:
	int operator()(int depth, bool isMax);

private:
	Cell GetWinner();
	bool IsDraw() const;
	bool IsPlayerOn(Cell cell) const;
	Cell GetCurrentPlayer();

private:
	int BestScore(int val, int depth, bool isMax, std::function<int(int, int)> func);

};

