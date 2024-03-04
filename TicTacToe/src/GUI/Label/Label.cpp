#include "Label.h"

#include "../Utilities.h"


Label::Label()
	: Component(false)
	, text()
{	
	Centered(text);
}

Label::Label(const std::string string, const FontHolder& font, size_t fontSize)
	: Component(false)
	, text(string, font.Get(FontID::Label), fontSize)
{	
	Centered(text);
}

void Label::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(text, states);
}

void Label::Update(sf::Time deltaTime)
{
	// EMPTY.
}

void Label::HandleEvent(const sf::Event & event)
{
	// EMPTY.
}

const std::string& Label::GetText() const
{
	return text.getString();
}

size_t Label::GetFontSize() const
{
	return text.getCharacterSize();
}

void Label::SetText(const std::string& string)
{
	text.setString(string);
	Centered(text);
}

void Label::SetFontSize(size_t fontSize)
{
	text.setCharacterSize(fontSize);
	Centered(text);
}

void Label::SetFont(const sf::Font& font)
{
	text.setFont(font);
	Centered(text);
}
