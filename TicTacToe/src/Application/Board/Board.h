#pragma once


#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>


#include "../../GUI/Button/Button.h"

class Context;
class Player;

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
	std::unique_ptr<Player> playerX;
	std::unique_ptr<Player> playerO;

	Context* context;
	std::vector<std::vector<Cell>> board;
	PlayerType currentPlayer;

public:
	Board(Context& context, sf::Vector2f anchor, size_t cellSize, std::unique_ptr<Player> playerX = nullptr, std::unique_ptr<Player> playerO = nullptr);

private:
	void InitBoard(sf::Vector2f anchor, size_t cellSize);
	void ResizeBoard(size_t size);
	void FillBoard(sf::Vector2f anchor, size_t cellSize);
	
private:
	std::unique_ptr<Button> GetFieldElement(float x, float y, size_t cellSize);
	PlayerType GetPlayerTypeFrom(const Cell& cell) const;
	std::string GetCurrentPlayerAsString() const;
	void ChangeCurrentPlayer();
	bool IsCellNotEmpty(const Cell& cell) const;
	bool CurrentPlayerIsHuman();
	Player* GetCurrentPlayer();

public:
	void Update(sf::Time deltaTime);
	void HandleEvent(const sf::Event& event);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void HandleEventForHumanPlayer(const sf::Event& event);
	void HandleEventForAIPlayer(const sf::Event& event);

public:
	void SetPlayerX(Player* playerX);
	void SetPlayerO(Player* playerO);

public:
	PlayerType GetWinner() const;
	bool IsFull() const;
	bool IsDraw() const;

};
