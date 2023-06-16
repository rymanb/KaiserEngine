#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"

namespace Kaiser
{

	void SceneManager::Init()
	{
		mScenes.emplace_back(new Scene("test"));
	}

	Ref<Scene> Kaiser::SceneManager::GetScene(std::string name)
	{
		for (auto& scene : mScenes)
		{
			if (scene->GetName() == name)
			{
				return scene;
			}
		}
	}

}