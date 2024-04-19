#include "Button.h"
#include "../Utilities.h"
#include "../../Application/Context/Context.h"

#include <SFML/Window/Event.hpp>

#include <iostream>

Button::Button(size_t width, size_t height, const FontHolder& fonts, const TextureHolder& textures, const std::string& string)
	: Component(true)
	, state(State::Default)
	, size(0, 0, width, height)
	, text()
	, transitionNum(0)
{
	InitTextures(textures);
	InitSprite();
	InitText(fonts, string);
}

void Button::InitTextures(const TextureHolder& textures)
{
	this->textures.push_back(textures.Get(TextureID::ButtonDefault).get());
	this->textures.push_back(textures.Get(TextureID::ButtonPressed).get());
}

void Button::InitSprite()
{
	sprite.setTextureRect(size);
	sprite.setTexture(*textures[static_cast<size_t>(state)]);
	Centered(sprite);
}

void Button::InitText(const FontHolder& fonts, const std::string& string)
{
	text.setFont(*fonts.Get(FontID::Button));
	text.setString(string);
	Centered(text);
	auto pos = sprite.getPosition();
	pos.y -= 5;
	text.setPosition(pos);
}

void Button::setPosition(sf::Vector2f pos)
{
	this->setPosition(pos.x, pos.y);
}

void Button::setPosition(float x, float y)
{
	//Transformable::setPosition(x, y);
	sprite.setPosition(x, y);
	auto pos = sprite.getPosition();
	pos.y -= 5;
	text.setPosition(pos);
}



void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(sprite, states);
	target.draw(text, states);
}

void Button::Update(sf::Time deltaTime)
{
	transitionNum--;
		
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (ConsistMouse())
		{
			state = State::Pressed;
			transitionNum = TRANSITION_TO_PRESSED_STATE;
		}
	}
	else if (transitionNum <= TRANSITION_TO_DEFAULT_STATE)
	{
		state = State::Default;
	}

	sprite.setTexture(*textures[static_cast<size_t>(state)]);
	
	if (state == State::Pressed && action)
	{
		action();
	}
}

bool Button::ConsistMouse() const
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*Context::GetInstance()->window);
	sf::Vector2f thisPos = sprite.getPosition();
	sf::FloatRect borders(thisPos.x - size.width/2, thisPos.y - size.height/2, size.width, size.height);

	return borders.contains(mousePos.x, mousePos.y);
}

void Button::HandleEvent(const sf::Event& event)
{
	// EMPTY.
}

void Button::SetButtonState(const State& state)
{
	this->state = state;
}

void Button::SetText(const std::string& text)
{
	this->text.setString(text);
	Centered(this->text);
}

void Button::SetWidth(size_t width)
{
	size.width = width;
}

void Button::SetHeight(size_t height)
{
	size.height = height;
}

void Button::SetSize(sf::IntRect size)
{
	this->size = size;
}

void Button::SetSize(size_t width, size_t height)
{
	SetSize(sf::IntRect(0, 0, width, height));
}

void Button::SetCommand(const Command& action)
{
	this->action = action;
}

void Button::SetFontSize(size_t fontSize)
{
	this->text.setCharacterSize(fontSize);
}

Button::State Button::GetState() const
{
	return state;
}

const std::string& Button::GetText() const
{
	return text.getString();
}

size_t Button::GetWidth() const
{
	return size.width;
}

size_t Button::GetHeight() const
{
	return size.height;
}

const Button::Command& Button::GetCommand() const
{
	return action;
}

sf::IntRect Button::GetSize() const
{
	return size;
}
