#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>



class Component : public sf::NonCopyable,
				  public sf::Drawable,
				  public sf::Transformable
{
private:
	bool isInteractive;
	bool isActive;

public:
	Component(bool interactiveState = false);

	virtual ~Component() = default;

public: // For overloading.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
	virtual void Update(sf::Time deltaTime) = 0;
	virtual void HandleEvent(const sf::Event& event) = 0;

protected: // For daughter classes.
	void SetInteractive(bool state);
	bool IsInteractive() const;

public:
	void SetActive(bool state);
	bool IsActive() const;
};