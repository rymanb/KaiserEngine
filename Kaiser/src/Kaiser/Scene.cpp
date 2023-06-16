#include "stdafx.h"
#include "Scene.h"


#include "Entity.h"


namespace Kaiser
{

	Scene::Scene(std::string name) : mName(name), mECS(new ECS()) {}

	Scene::~Scene() {}
	

	void Scene::Update()
	{
		mECS->Update();
	}
	
	
	Entity Scene::CreateEntity()
	{
		UUID uuid = UUID();
		Entity entity = mECS->CreateEntity();
		mECS->AddEntity(entity, uuid);
		
		return entity;
	}

	Entity Scene::GetEntity(UUID uuid)
	{
		return mECS->GetEntity(uuid);
	}


}