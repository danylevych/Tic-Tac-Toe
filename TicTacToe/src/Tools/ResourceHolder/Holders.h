#pragma once

#include "ResourceHolder.h"
#include "../Enums/FontID.h"
#include "../Enums/TextureID.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

using FontHolder = ResourceHolder<FontID, sf::Font>;
using TextureHolder = ResourceHolder<TextureID, sf::Texture>;