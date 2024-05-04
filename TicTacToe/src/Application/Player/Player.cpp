#include "Player.h"


Player::Player(Board::PlayerType type)
	: type(type)
{	}

Board::PlayerType Player::GetType() const
{
	return type;
}

std::string Player::GetTypeAsString() const
{
	switch (type)
	{
	case Board::PlayerType::X:
		return "X";

	case Board::PlayerType::O:
		return "O";
	}
}

Player::Action Player::GetAction(const std::vector<std::vector<Button::Ptr>>& board)
{
	Action action{};
	action.SetInfinit();
	
	return action;
}
