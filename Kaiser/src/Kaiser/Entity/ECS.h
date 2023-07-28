#pragma  once

#include "Kaiser/Core/Core.h"
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

	//ComponentPtr Clone() const;

	virtual void Update()
	{
		std::cout << Name() << std::endl;
	}



	static std::string_view TypeName() { return "Test"; }


	auto operator==(Test const& other) const
	{

		return false;
	}


private:
	std::string_view Name() const override { return TypeName(); }
};

class Transform : public Component
{
public:
	Kaiser::UUID id;
	Transform(Kaiser::UUID id) : Component(), id(id) {}
	Transform() : Component(), id(Kaiser::UUID()) {}

	~Transform() {}

	//ComponentPtr Clone() const;

	virtual void Update()
	{
		std::cout << Name() << std::endl;
	}



	static std::string_view TypeName() { return "Transform"; }


	auto operator==(Test const& other) const
	{

		return false;
	}


private:
	std::string_view Name() const override { return TypeName(); }
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


		template <typename T>
		void UpdateComponent()
		{

			registry->view<T>().each([this](auto entity, auto& test)
				{
					test.Update();
				});
		}

		template <typename T>
		void DrawComponent()
		{

			registry->view<T>().each([this](auto entity, auto& test)
				{
					test.Draw();
				});
		}

		void Update();
		void Draw();

	private:
		Registry* registry;
		EntityMap mEntityMap;


		friend class Entity;

	};

}



