#include "SceneStack.h"

#include "../Scene/Scene.h"
#include "../Main/MainScene.h"
#include "../../Application/Context/Context.h"


Scene::Ptr GetScene(const SceneStack::SceneType& type, Context& context, SceneStack* stack)
{
	switch (type)
	{
	case SceneStack::SceneType::Main:
		return Scene::Ptr(new MainScene(context, stack));

	default:
		return Scene::Ptr(new MainScene(context, stack));
	}
}


SceneStack::SceneStack(Context* context)
	: context(context)
{	}

void SceneStack::Push(const SceneType& type)
{
	scenesStack.push(GetScene(type, *context, this));
}

void SceneStack::Pop()
{
	scenesStack.pop();
}

void SceneStack::Clear()
{
	while (!IsEmpty())
	{
		scenesStack.pop();
	}
}

bool SceneStack::IsEmpty() const
{
	return scenesStack.empty();
}

void SceneStack::Update(sf::Time deltaTime)
{
	scenesStack.top()->Update(deltaTime);
}

void SceneStack::HandleEvent(const sf::Event& event)
{
	scenesStack.top()->HandleEvent(event);
}

void SceneStack::Draw(sf::RenderWindow& window)
{
	window.draw(*scenesStack.top());
}

SceneStack::operator bool() const
{
	return !IsEmpty();
}
