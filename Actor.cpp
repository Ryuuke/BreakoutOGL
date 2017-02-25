#include "Actor.h"

void Actor::Init()
{
	for (auto& component : m_components)
		component.second->VInit();
}

void Actor::Update(const float & deltaTime)
{
	for (auto& component : m_components)
		component.second->VUpdate(deltaTime);
}

void Actor::AddComponent(std::unique_ptr<IActorComponent> component)
{
	m_components[component->VGetComponentId()] = std::move(component);
}
