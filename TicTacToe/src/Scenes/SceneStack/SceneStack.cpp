#include "SceneStack.h"

#include "../../Application/Context/Context.h"


SceneStack::SceneStack(Context* context)
	: context(context)
{	}

Scene::Ptr SceneStack::GetSceneInstance(const SceneType type)
{
	return sceneFactory[type]();
}

void SceneStack::RequestPop()
{
	pendings.push_back(PendingChanges{ Action::Pop, SceneType::None });
}

void SceneStack::RequestClear()
{
	pendings.push_back(PendingChanges{ Action::Clear, SceneType::None });
}

void SceneStack::RequestPush(const SceneType& type)
{
	pendings.push_back(PendingChanges{ Action::Push, type });
}

void SceneStack::ApplyPendings()
{
	for (auto& change : pendings)
	{
		switch (change.action)
		{
		case Action::Push:
			Push(change.scene);
			break;

		case Action::Pop:
			Pop();
			break;

		case Action::Clear:
			Clear();
			break;
		}
	}

	pendings.clear();
}

void SceneStack::Push(const SceneType& type)
{
	scenesStack.push(GetSceneInstance(type));
}

void SceneStack::Pop()
{
	scenesStack.pop();
}

void SceneStack::Clear()
{
	while (!scenesStack.empty())
	{
		Pop();
	}
}

bool SceneStack::IsEmpty() const
{
	return scenesStack.empty() && pendings.empty();
}

void SceneStack::Update(sf::Time deltaTime)
{
	if (!scenesStack.empty()) {
		scenesStack.top()->Update(deltaTime);
	}
	
	ApplyPendings();
}

void SceneStack::HandleEvent(const sf::Event& event)
{
	if (!scenesStack.empty()) {
		scenesStack.top()->HandleEvent(event);
	}
	ApplyPendings();
}

void SceneStack::Draw(sf::RenderWindow& window)
{
	window.draw(*scenesStack.top());
}

SceneStack::operator bool() const
{
	return !IsEmpty();
}
