#pragma once

#include "Kaiser/Core/Core.h"
#include "Kaiser/Entity/UUID.h"
#include "Kaiser/Core/Events/Event.h"





namespace Kaiser
{
	class ECS;
	class Entity;


	class Scene
	{
		std::string mName;
	public:
		Scene(std::string name);
		~Scene();

		void Update();

		void OnEvent(Event& e);

		Entity CreateEntity();
		
		Entity GetEntity(UUID uuid);


		std::string GetName() { return mName; }
		
		
		

	private:
		Ref<ECS> mECS;
	};
}
