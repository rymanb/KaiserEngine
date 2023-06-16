#pragma once

#include "Module.h"
#include "Component.h"
#include "ECS.h"


namespace Kaiser
{
	class ComponentFactory : public Module
	{
	public:
		void Init() override;

		void Update()
		{}

		void Shutdown()
		{}

		Component& Create(std::string_view, Entity& entity);

		//void write(std::string component, Writer* write, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, EntityID id, EntityID arch = 0);

		void AddComponentCreateFunction(std::string_view component, std::function < Component& (Entity&)> function);

		//void AddComponentWriteFunction(std::string_view component, std::function<void(Writer* write, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, EntityID id, EntityID arch)> function);

		static std::string_view Name() { return "FLComponentFactory"; }



		bool Has(std::string_view component) const;
		std::vector<std::string> GetNames() const;

	private:

		std::unordered_map<std::string, std::function<Component& (Entity&)> > mComponentMap{};
		//std::unordered_map<std::string, std::function<void(Writer* write, rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, EntityID id, EntityID arch)> > mWriterMap {};

	};
}
