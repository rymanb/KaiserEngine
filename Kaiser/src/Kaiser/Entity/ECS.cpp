#include "stdafx.h"
#include "ECS.h"

#include "Entity.h"
#include "UUID.h"

#include <unordered_map>

#include "Kaiser/Core/Engine.h"
#include "ComponentFactory.h"



typedef entt::registry Registry;

namespace Kaiser
{
	ECS::ECS() : registry(new Registry())
	{
		mEntityMap.reset(new std::unordered_map<UUID, Entity>());
	}
	
	Entity ECS::CreateEntity()
	{
		Entity entity = Entity(registry->create(), this);
		return entity;
	}

	void ECS::AddEntity(Entity entity, UUID uuid)
	{
		mEntityMap->insert(std::make_pair(uuid, entity));
	}

	Entity ECS::GetEntity(UUID uuid)
	{
		return mEntityMap->at(uuid);
	}







	void ECS::Update()
	{

#define ComponentType(x) UpdateComponent<x>();
#include "Components.h"
#undef ComponentType

		
	}

	void ECS::Draw()
	{
#define ComponentType(x) DrawComponent<x>();
#include "Components.h"
#undef ComponentType
	}

}

//template void ECS::AddComponent<Test>(EntityID entity, Test component);