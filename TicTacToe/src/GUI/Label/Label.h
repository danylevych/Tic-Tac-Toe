#pragma once

#include "../Component/Component.h"

#include <SFML/Graphics/Text.hpp>


class Label : public Component
{
private:
	sf::Text text;

public:
	Label();
	Label(const std::string string, const sf::Font& font, size_t fontSize);

	virtual ~Label() override = default;

public: // Overriden section.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void Update(sf::Time deltaTime) override;
	virtual void HandleEvent(const sf::Event& event) override;

public:

};

