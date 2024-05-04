#pragma once

#include <vector>
#include <set>
#include "MinMax/MinMax.h"
#include "../Player.h"
#include "../../../GUI/Button/Button.h"


class AIPlayer : public Player
{
public:

public:
	using InnerBoard = std::vector<std::vector<char>>;

private:
	MinMax minMax;
	InnerBoard board;

public:
	AIPlayer(Board::PlayerType type);

	virtual ~AIPlayer() = default;

public:
	virtual Action GetAction(const std::vector<std::vector<Button::Ptr>>& board) override;

private:
	void ResizeBorder(size_t size);
	void FillBoard(const std::vector<std::vector<Button::Ptr>>& board);
};

