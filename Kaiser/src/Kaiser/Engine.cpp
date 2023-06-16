#include "stdafx.h"
#include "Engine.h"
#include "Module.h"

//------------------------------------------------------------------------------
//
// File Name:	FLEngine.cpp
// Author(s):	Ryman Barnett 
// Class: GAM 200
//
// Copyright ? 2022 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//******************************************************************************//
// Include		  																//
//******************************************************************************//


//******************************************************************************//
// Public Functions																//
//******************************************************************************//




//******************************************************************************//
// Public Functions																//
//******************************************************************************//


//! Initialize FLEngine
void Engine::Init()
{


	// Loads each component
	for (int i = 0; i < Engine::components.size(); i++)
	{
		Engine::components[i].first->Load();
	}

	// Init each component
	for (int i = 0; i < Engine::components.size(); i++)
	{
		Engine::components[i].first->Init();
	}



}

//! Update the FLEngine
//! \param dt delta time
void Engine::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);


	// Update each component
	for (int i = 0; i < Engine::components.size(); i++)
	{
		Engine::components[i].first->Update();
		
	}

}

//! Shutdown FLEngine
void Engine::Shutdown()
{


	// Loads each component
	for (int i = 0; i < Engine::components.size(); i++)
	{
		Engine::components[i].first->Unload();
	}

	// Shutdown each component backwards
	long long i = Engine::components.size() - 1;
	for (i; i >= 0; i--)
	{
		Engine::components[i].first->Shutdown();
	}


}

void Engine::Add(Ref<Module> component, std::string_view id)
{
	component->SetParent(this);
	components.push_back({ component, std::string(id.data()) });
}

Ref<Module> Engine::Get(std::string_view id) const
{
	for (int i = 0; i < components.size(); ++i)
	{
		if (components[i].second == id)
		{
			return components[i].first;
		}
	}
	return nullptr;
}

