#pragma once

template <typename Type>
inline void Centered(Type& object)
{
	sf::FloatRect boundsRect = object.getLocalBounds();
	object.setOrigin(boundsRect.width / 2.f, boundsRect.height / 2.f);
}
