#pragma once

#include "IActorComponent.h"
#include <unordered_map>
#include <memory>

class IActorComponent;

using ActorId = unsigned long;

using ActorComponentMap = std::unordered_map<ActorComponentId, std::unique_ptr<IActorComponent>>;

class Actor
{
private:
	ActorComponentMap m_components;
	ActorId m_id;
public:
	explicit Actor(const ActorId& id) : m_id(id) {}
	~Actor() = default;

	void Init();
	void Update(const float& deltaTime);

	void AddComponent(std::unique_ptr<IActorComponent> component);
	
	template<typename T>
	T* const TGetComponent()
	{
		return dynamic_cast<T* const>(m_components[T::COMPONENT_ID].get());
	}

	inline ActorId GetId() const { return m_id; }
};