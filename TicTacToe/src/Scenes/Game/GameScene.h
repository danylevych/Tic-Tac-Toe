#pragma once


#include "../Scene/Scene.h"
#include "../../GUI/Button/Button.h"

class GameScene : public Scene
{
public:
	using Ptr = std::unique_ptr<GameScene>;

private:
	std::vector<std::vector<Button::Ptr>> field;

public:
	GameScene(Context& context, SceneStack* stack);
	GameScene(Context& context, SceneStack* stack, const sf::Texture& texture);

public:
	virtual void Update(sf::Time deltaTime) override;
	virtual void HandleEvent(const sf::Event& event) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private: // Init section.
	void InitComponetn();
	void InitAdditionalComponents(const sf::Vector2f& anchor);
	void InitField(const sf::Vector2f& anchor);
	void InitFieldSize();
	void InitFielCells(const sf::Vector2f& anchor);

private: // Helper function.
	std::unique_ptr<Button> GetFieldElement(float x, float y);

};

