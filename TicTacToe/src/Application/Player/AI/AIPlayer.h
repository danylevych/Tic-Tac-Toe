#pragma once

#include <vector>
#include <set>
#include "../Player.h"
#include "../../../GUI/Button/Button.h"


class AIPlayer : public Player
{
public:
	struct Action
	{
		int i;
		int j;
	};

public:
	using Board = std::vector<std::vector<std::string>>;

private:
	Board field;

public:
	AIPlayer(Type type, std::vector<std::vector<Button::Ptr>>& field);

	virtual ~AIPlayer() = default;

private:
	void InitFieldSize(size_t size);
	void InitField(std::vector<std::vector<Button::Ptr>>& field);

public:
	static std::string GetPlayer(const Board& board);
	static std::set<Action> Actions(Board& board);
	static std::string GetWinner(const Board& board);
	static int Utility(const Board& board);
	static Action MinMax(Board& board);

};

