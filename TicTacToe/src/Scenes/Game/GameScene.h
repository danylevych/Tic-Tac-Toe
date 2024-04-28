#pragma once


#include "../Scene/Scene.h"
#include "../../GUI/Button/Button.h"
#include "../../Application/Player/Player.h"

class GameScene : public Scene
{
public:
	using Ptr = std::unique_ptr<GameScene>;

private:
	Player::Type currentPlayer;
	Player::Ptr playerX;
	Player::Ptr playerO;
	std::vector<std::vector<Button::Ptr>> field;

public:
	GameScene(Context& context, SceneStack* stack);
	GameScene(Context& context, SceneStack* stack, const sf::Texture& texture);

public:
	virtual void Update(sf::Time deltaTime) override;
	virtual void HandleEvent(const sf::Event& event) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private: // Helper function.
	void HandlePlayerAction();
	Player* GetCurrentPlayer() ;
	std::unique_ptr<Button> GetFieldElement(float x, float y);

private: // Init section.
	void InitPlayers();
	void InitComponetn();
	void InitAdditionalComponents(const sf::Vector2f& anchor);
	void InitField(const sf::Vector2f& anchor);
	void InitFieldSize();
	void InitFielCells(const sf::Vector2f& anchor);


};

