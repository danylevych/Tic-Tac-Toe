#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../../GUI/Component/Component.h"
#include "../../Application/Context/Context.h"


class SceneStack;

class Scene : public sf::NonCopyable
			, public sf::Drawable
{
public:
	using Ptr = std::unique_ptr<Scene>;

protected:
	Context* context;
	SceneStack* sceneStack;
	sf::Sprite background;
	std::vector<std::unique_ptr<Component>> components;

protected:
	Scene(Context& context, SceneStack* sceneStack);
	Scene(Context& context, SceneStack* sceneStack, const sf::Texture& texture);

public:
	virtual ~Scene() = default;

public: // Overriding section.
	virtual void Update(sf::Time deltaTime);
	virtual void HandleEvent(const sf::Event& event);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private: // Helper functions.
	void ResizeBackground();

};
