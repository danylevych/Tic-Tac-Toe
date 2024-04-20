#pragma once

#include <stack>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Scene/Scene.h"


class Context;

class SceneStack : sf::NonCopyable
{
public:
	enum class SceneType {
		Main,
		Game
	};

private:
	Context* context;
	std::stack<Scene::Ptr> scenesStack;

public:
	SceneStack(Context* context);

public:
	void Push(const SceneType& type);
	void Pop();
	void Clear();
	bool IsEmpty() const;

public:
	void Update(sf::Time deltaTime);
	void HandleEvent(const sf::Event& event);
	void Draw(sf::RenderWindow& window);

public:
	operator bool() const;
};

