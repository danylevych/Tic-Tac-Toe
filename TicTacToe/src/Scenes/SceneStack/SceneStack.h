#pragma once

#include <stack>
#include <functional>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Scene/Scene.h"
#include "../Main/MainScene.h"
#include "../Game/GameScene.h"


class Context;


class SceneStack : sf::NonCopyable
{
public:
	enum class SceneType {
		None,
		Main,
		ChooseType,
		GameAgainstAI,
		GameTwoPlayers,
		GameOverWinX,
		GameOverWinO,
		GameOverDraw
	};

private:
	enum class Action {
		Push,
		Pop,
		Clear
	};

	struct PendingChanges {
		Action action;
		SceneType scene;
	};

private:
	std::vector<PendingChanges> pendings;
	Context* context;
	std::stack<Scene::Ptr> scenesStack;
	std::map<SceneType, std::function<Scene::Ptr()>> sceneFactory;

public:
	SceneStack(Context* context);

public:
	template<typename Type, typename ...Args>
	void RegisterScene(const SceneType type, Args... args);

private:
	Scene::Ptr GetSceneInstance(const SceneType type);

public:
	void RequestPop();
	void RequestClear();
	bool IsEmpty() const;
	void RequestPush(const SceneType& type);

private:
	void ApplyPendings();	
	void Push(const SceneType& type);
	void Pop();
	void Clear();

public:
	void Update(sf::Time deltaTime);
	void HandleEvent(const sf::Event& event);
	void Draw(sf::RenderWindow& window);

public:
	operator bool() const;

};


template<typename Type, typename ...Args>
inline void SceneStack::RegisterScene(const SceneType type, Args ...args)
{
	sceneFactory[type] = [this, args...]() {
		return Scene::Ptr(new Type(*context, this, args...));
	};
}
