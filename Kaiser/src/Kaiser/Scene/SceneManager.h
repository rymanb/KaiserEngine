#pragma once


#include "Kaiser/Core/Module.h"
#include "Kaiser/Core/Core.h"

namespace Kaiser
{
	class Scene;
	
	class SceneManager : public Module
	{
	public:

		SceneManager() = default;
		~SceneManager()
		{
			mScenes.clear();
		}

		virtual void Init() override;
		//! Overide Update function
		virtual void Update() override {};
		//! Overide Shutdown function
		virtual void Shutdown() override {}


		static std::string_view Name() { return "SceneManager"; }

		Ref<Scene> GetScene(std::string name);

	private:
		std::vector<Ref<Scene>> mScenes;
	};
}

