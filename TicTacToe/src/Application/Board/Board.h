#pragma once


#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>

#include "../../GUI/Button/Button.h"

class Context;

class Board : public sf::NonCopyable
			, public sf::Drawable
{
public:
	enum class PlayerType {
		NONE,
		X,
		O
	};

	using Cell = Button::Ptr;

private:
	Context* context;
	std::vector<std::vector<Cell>> board;
	PlayerType currentPlayer;

public:
	Board(Context& context, sf::Vector2f anchor, size_t cellSize);

private:
	void InitBoard(sf::Vector2f anchor, size_t cellSize);
	
private:
	std::unique_ptr<Button> GetFieldElement(float x, float y, size_t cellSize);
	PlayerType GetPlayerTypeFrom(const Cell& cell) const;
	std::string GetCurrentPlayerAsString() const;
	void ChangeCurrentPlayer();

public:
	void Update(sf::Time deltaTime);
	void HandleEvent(const sf::Event& event);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	PlayerType GetWinner() const;
	bool IsFull() const;
	bool IsDraw() const;
};
