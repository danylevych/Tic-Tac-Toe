#include "Label.h"

Label::Label()
	: Component(false)
	, text()
{	}

Label::Label(const std::string string, const sf::Font & font, size_t fontSize)
	: Component(false)
	, text(string, font, fontSize)
{	}

void Label::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(text, states);
}

void Label::Update(sf::Time deltaTime)
{	}

void Label::HandleEvent(const sf::Event & event)
{	}
