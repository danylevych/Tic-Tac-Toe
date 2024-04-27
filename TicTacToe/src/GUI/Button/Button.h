#pragma once

#include "../Component/Component.h"
#include "../../Tools/ResourceHolder/Holders.h"

#include <memory>
#include <vector>
#include <functional>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


class Button : public Component
{
public:
	enum class State {
		Default,
		Pressed
	};

	using Command = std::function<void()>;
	using Ptr = std::unique_ptr<Button>;

private:
	std::vector<sf::Texture*> textures;
	
	State state;
	sf::Text text;
	sf::Sprite sprite;
	Command action;
	sf::IntRect size;
	
	sf::Time animTime;

	const sf::Time FULL_ANIMATION = sf::seconds(0.3f);

public:
	Button(size_t width, size_t height, const FontHolder& fonts, const TextureHolder& textures, const std::string& string = "");

public: // Overriden section.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void Update(sf::Time deltaTime) override;
	virtual void HandleEvent(const sf::Event& event) override;

public:
	void Call();

public: // Set section. 
	void SetButtonState(const State& state);
	void SetText(const std::string& text);
	void SetWidth(size_t width);
	void SetHeight(size_t height);
	void SetSize(sf::IntRect size);
	void SetSize(size_t width, size_t height);
	void SetCommand(const Command& action);
	void SetFontSize(size_t fontSize);

public: // Get section.
	State GetState() const;
	const std::string& GetText() const;
	size_t GetWidth() const;
	size_t GetHeight() const;
	const Command& GetCommand() const;
	sf::IntRect GetSize() const;
	
private: // Init section.
	void InitTextures(const TextureHolder& textures);
	void InitSprite();
	void InitText(const FontHolder& fonts, const std::string& string);

public: // Overriden default functions.
	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);

private: // Helper functions.
	bool ConsistMouse() const;
};

