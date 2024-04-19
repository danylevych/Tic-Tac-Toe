#include "SceneStack.h"

#include "../Scene/Scene.h"
#include "../../Application/Context/Context.h"


Scene::Ptr GetScene(const SceneStack::SceneType& type, Context* context)
{
	switch (type)
	{
	case SceneStack::SceneType::Main:
		// TODO: Create a bilder class, that will have returned the correct pointer.
	}
}


SceneStack::SceneStack(Context* context)
	: context(context)
{	}

void SceneStack::Push(const SceneType& type)
{
	scenesStack.push(GetScene(type, context));
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
