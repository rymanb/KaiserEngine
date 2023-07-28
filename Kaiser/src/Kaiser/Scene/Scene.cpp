#include "stdafx.h"
#include "Scene.h"


#include "Kaiser/Entity/Entity.h"


namespace Kaiser
{

	Scene::Scene(std::string name) : mName(name), mECS(new ECS()) {}

	Scene::~Scene() {}
	

	void Scene::Update()
	{
		mECS->Update();
		mECS->Draw();
	}

	void Scene::OnEvent(Event& e)
	{
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