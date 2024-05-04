#pragma once

#include <string>
#include <memory>
#include <limits>
#include <vector>
#include "../../GUI/Button/Button.h"

#include "../Board/Board.h"

class Player
{
public:
	struct Action {
		int i;
		int j;

		void SetInfinit() {
			j = i = std::numeric_limits<int>::max();
		}

		bool IsUndefined() {
			int maxVal = std::numeric_limits<int>::max();

			if (i == maxVal && j == maxVal) {
				return true;
			}

			return false;
		}

		bool operator<(const Action& other) const {
			return i > other.i && j > other.j;
		}
	};

public:
	using Ptr = std::unique_ptr<Player>;

private:
	Board::PlayerType type;

public:
	Player(Board::PlayerType type);

	virtual ~Player() = default;

public:
	Board::PlayerType GetType() const;
	std::string GetTypeAsString() const;

public:
	virtual Action GetAction(const std::vector<std::vector<Button::Ptr>>& board);

};
