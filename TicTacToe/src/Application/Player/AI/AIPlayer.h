#pragma once

#include <vector>
#include <set>
#include "../Player.h"
#include "../../../GUI/Button/Button.h"


class AIPlayer : public Player
{
public:

public:
	using Board = std::vector<std::vector<std::string>>;

private:
	Board board;

public:
	AIPlayer(Type type);

	virtual ~AIPlayer() = default;

public:
	virtual Action GetAction(const std::vector<std::vector<Button::Ptr>>& board) override;

private:
	void FillBoard(const std::vector<std::vector<Button::Ptr>>& board);

public:
	static std::string GetPlayer(const Board& board);
	static std::set<Action> Actions(Board& board);
	static std::string GetWinner(const Board& board);
	static int Utility(const Board& board);
	static Action MinMax(Board& board);
	static Board Result(const Board& board, Action action);

};

