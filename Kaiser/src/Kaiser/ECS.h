#pragma  once

#include "Core.h"
#include <iostream>
#include <entt.hpp>
#include "UUID.h"

#include <unordered_map>
#include "Component.h"


class Test : public Component
{
public:
	Kaiser::UUID id;
	Test(Kaiser::UUID id) : Component(), id(id) {}
	Test() : Component(), id(Kaiser::UUID()) {}

	~Test() {}




	//! Component-specific render code.
	virtual void Draw(/*FLEngine* engine*/) const {}

	//! Component-specific render code.
	virtual void Init() {};

	//! Component-specific render code.
	virtual void Shutdown(/*FLEngine* engine*/) {}



	virtual void Update() { std::cout << "Test::Update(): " << (uint64_t)id << std::endl; }
	virtual std::string_view Name() const { return "Test"; }
};


typedef entt::registry Registry;

typedef std::string Name;

typedef entt::entity EntityID;


namespace Kaiser
{

	class Entity;
	typedef Ref<std::unordered_map<UUID, Entity>> EntityMap;

	class ECS
	{

	public:

		ECS();
		
		~ECS()
		{
			delete registry;
		}

		Entity CreateEntity();

		void AddEntity(Entity entity, UUID uuid);

		Entity GetEntity(UUID uuid);

		//void DestroyEntity(EntityID entity);


		template<typename T, typename... Args>
		void AddComponent(UUID entity, Args... args)
		{

			registry->emplace<T>(entity, T(args...));

		}



		void Update();

	private:
		Registry* registry;
		EntityMap mEntityMap;


		friend class Entity;

	};

}



