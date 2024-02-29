#include "Component.h"

Component::Component(bool interactiveState)
	: isInteractive(interactiveState)
	, isActive(false)
{	}

void Component::SetInteractive(bool state)
{
	isInteractive = state;
}

bool Component::IsInteractive() const
{
	return isInteractive;
}

void Component::SetActive(bool state)
{
	if (isInteractive)
	{
		isActive = state;
	}
}

bool Component::IsActive() const
{
	return isActive;
}
