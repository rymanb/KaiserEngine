#include "stdafx.h"
#include "ComponentFactory.h"

namespace Kaiser
{

	template <typename T>
	static Component& CreateComponent(Entity& entity)
	{
		//T& component = entity.Add<T>();

		//return component;
		return T();
	}




	template <typename T>
	static void AddCompoment(ComponentFactory& componentfactory)
	{
		componentfactory.AddComponentCreateFunction(T::TypeName(), CreateComponent<T>);
	}

	void ComponentFactory::Init()
	{
		//AddCompoment<Test>(*this);

	}
	Component& ComponentFactory::Create(std::string_view component, Entity& entity)
	{

		return mComponentMap.at((std::string)component)(entity);
	}

	bool ComponentFactory::Has(std::string_view component) const
	{
		auto c = mComponentMap.find((std::string)component);
		if (c != mComponentMap.end())
		{
			return true;
		}

		return false;
	}


	void ComponentFactory::AddComponentCreateFunction(std::string_view component, std::function<Component& (Entity&)> function)
	{
		mComponentMap.emplace(component, function);
	}

	std::vector<std::string> ComponentFactory::GetNames() const
	{
		std::vector<std::string> names;
		for (auto& component : mComponentMap)
		{
			names.push_back(component.first);
		}

		return names;
	}
}