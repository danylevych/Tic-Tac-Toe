#include "Scene.h"

Scene::Scene(Context& context, SceneStack* sceneStack)
	: context(&context)
	, sceneStack(sceneStack)
{	}


Scene::Scene(Context& context, SceneStack* sceneStack, const sf::Texture& texture)
	: context(&context)
	, sceneStack(sceneStack)
	, background(texture)
{	
	ResizeBackground();
}

void Scene::ResizeBackground()
{
	sf::Vector2u textureSize = background.getTexture()->getSize();
	sf::Vector2u windowSize = context->window->getSize();

	float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
	float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

	background.setScale(scaleX, scaleY);
}


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
