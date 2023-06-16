#pragma once

#include "Kaiser/Core.h"
#include "UUID.h"





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

		Entity CreateEntity();
		
		Entity GetEntity(UUID uuid);


		std::string GetName() { return mName; }
		
		
		

	private:
		Ref<ECS> mECS;
	};
}
