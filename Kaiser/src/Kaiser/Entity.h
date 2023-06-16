#pragma once

#include "UUID.h"
#include "entt.hpp"
#include "ECS.h"



namespace Kaiser
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, ECS* ecs);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			//KS_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			T& component = m_ECS->registry->emplace<T>(mId, (UUID)*this, std::forward<Args>(args)...);
			//m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		//template<typename T>
		//T& GetComponent()
		//{
		//	KS_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
		//	return m_ECS->registry.get<T>(mId);
		//}
		
		//template<typename T>
		//bool HasComponent()
		//{
		//	return m_ECS->registry.has<T>(mId);
		//}
		
		//template<typename T>
		//void RemoveComponent()
		//{
		//	KS_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
		//	m_ECS->registry.remove<T>(mId);
		//}

		operator bool() const { return mId != entt::null; }
		operator uint64_t() const { return (uint64_t)mId; }
		operator entt::entity() const { return mId; }
		operator UUID() const { return UUID((uint64_t)mId); }
		
		bool operator==(const Entity& other) const
		{
			return mId == other.mId && m_ECS == other.m_ECS;
		}
		
		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

		const UUID& ID() const { return (UUID)*this; }
		
	private:

		ECS* m_ECS = nullptr;

		EntityID mId{ entt::null };

		
	};
		
	
}
