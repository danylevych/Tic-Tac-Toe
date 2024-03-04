#pragma once

#include "../Component/Component.h"
#include "../../Tools/ResourceHolder/Holders.h"

#include <SFML/Graphics/Text.hpp>


class Label : public Component
{
private:
	sf::Text text;

public:
	Label();
	Label(const std::string string, const FontHolder& font, size_t fontSize);

	virtual ~Label() override = default;

public: // Overriden section.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void Update(sf::Time deltaTime) override;
	virtual void HandleEvent(const sf::Event& event) override;

public: // Get section.
	const std::string& GetText() const;
	size_t GetFontSize() const;

public: // Set section.
	void SetText(const std::string& string);
	void SetFontSize(size_t fontSize);
	void SetFont(const sf::Font& font);

};

