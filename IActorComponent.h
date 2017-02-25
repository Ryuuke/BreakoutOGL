#pragma once

using ActorComponentId = unsigned long;

class Actor;

class IActorComponent
{
protected:
	Actor* m_owner;
public:
	IActorComponent() = default;
	virtual ~IActorComponent() = default;

	virtual void VInit() {}
	virtual void VUpdate(const float& deltaTime) {}
	virtual ActorComponentId VGetComponentId() const = 0;

	inline void SetOwner(Actor* const owner) { m_owner = owner; }
	inline Actor* const GetOwner() const { return m_owner; }
};
