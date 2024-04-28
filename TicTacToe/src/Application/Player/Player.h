#pragma once

#include <string>
#include <memory>
#include <limits>
#include <vector>
#include "../../GUI/Button/Button.h"

class Player
{
public:
	enum class Type {
		X,
		O
	};

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
	Type type;

public:
	Player(Type type);

	virtual ~Player() = default;

public:
	Type GetType() const;
	std::string GetTypeAsString() const;

public:
	virtual Action GetAction(const std::vector<std::vector<Button::Ptr>>& board);

};
