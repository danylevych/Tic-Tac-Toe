#include "Player.h"

Player::Player(Type type)
	: type(type)
{	}

Player::Type Player::GetType() const
{
	return type;
}

std::string Player::GetTypeAsString() const
{
	switch (type)
	{
	case Player::Type::X:
		return "X";

	case Player::Type::O:
		return "O";
	}
}

Player::Action Player::GetAction(const std::vector<std::vector<Button::Ptr>>& board)
{
	Action action{};
	action.SetInfinit();
	
	return action;
}
