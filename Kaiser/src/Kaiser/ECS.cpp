#include "stdafx.h"
#include "ECS.h"

#include "Entity.h"
#include "UUID.h"

#include <unordered_map>


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






	//void ECS::DestroyEntity(EntityID entity)
	//{
	//	registry->destroy(entity);
	//}

	void ECS::Update()
	{
		// get all entities in the registry
		registry->each([this](auto entity)
			{
				// can you get a view of all components in the registry?
				// and then iterate through them?
				
				registry->view<Test>().each([this](auto entity, auto& test)
					{
						test.Update();
					});
				
			});
	}

}

//template void ECS::AddComponent<Test>(EntityID entity, Test component);