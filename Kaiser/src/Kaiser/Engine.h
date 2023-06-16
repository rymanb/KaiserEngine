#pragma once

#include "Module.h"


//! FLEngine wrapper class: contains all components
class Engine : public IEngine
{
public:
	void Init() override;           // Initialize FLEngine
	void Update(float dt) override; // Update FLEngine
	void Shutdown() override;       // Shutdown FLEngine

	void Add(Ref<Module> component, std::string_view id) override;

	Ref<Module> Get(std::string_view id) const override;


	static IEngine& Instance()
	{

		static Engine instance;
		return instance;
	}



private:
	Engine() = default;
	//! Vector containing all FLEngine Components
	std::vector<std::pair<Ref<Module>, std::string>> components;



};