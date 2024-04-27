#pragma once

#include <string>

class Player
{
public:
	enum class Type {
		X,
		O
	};

private:
	Type type;

public:
	Player(Type type);

	virtual ~Player() = default;

public:
	Type GetType() const;
	std::string GetTypeAsString() const;
};
