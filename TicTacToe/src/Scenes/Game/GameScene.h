#pragma once


#include "../Scene/Scene.h"
#include "../../GUI/Button/Button.h"
#include "../../Tools/Enums/GameType.h"
#include "../../Application/Player/Player.h"

class GameScene : public Scene
{
public:
	using Ptr = std::unique_ptr<GameScene>;

private:
	Board board;

public:
	GameScene(Context& context, SceneStack* stack, GameType type);
	GameScene(Context& context, SceneStack* stack, const sf::Texture& texture, GameType type);

public:
	virtual void Update(sf::Time deltaTime) override;
	virtual void HandleEvent(const sf::Event& event) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private: // Init section.
	void InitComponetns();
	void InitAdditionalComponents(const sf::Vector2f& anchor);
	void InitBoardPlayers(GameType gameType);

private:
	sf::Vector2f GetAnchor();

};
