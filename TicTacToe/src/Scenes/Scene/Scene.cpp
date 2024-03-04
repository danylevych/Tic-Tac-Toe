#include "Scene.h"

Scene::Scene(const sf::Texture& texture)
	: background(texture)
{	}

Scene::Scene(const sf::Texture & texture, sf::IntRect rect)
	: background(texture)
{	}

void Scene::Update(sf::Time deltaTime)
{
	for (auto& item : components)
	{
		item->Update(deltaTime);
	}
}

void Scene::HandleEvent(const sf::Event& event)
{
	for (auto& item : components)
	{
		item->HandleEvent(event);
	}
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= background.getTransform();
	target.draw(background, states);

	for (auto& item : components)
	{
		item->draw(target, states);
	}
}
