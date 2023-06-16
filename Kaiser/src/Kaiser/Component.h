#pragma once

#include "stdafx.h"
#include <string>
#include <vector>
#include "Kaiser/Core.h"

class Component
{
public:

	//! Constructor
	//! \param type type of component
	Component() 
	{
	}



	Component(const Component& other)
	{
		*this = other;
	}


	//virtual ComponentPtr Clone() const = 0;

	//! Virt deconstructor
	virtual ~Component(void) {};

	//virtual void Read(rapidjson::Value&) {}

	//! Component-specific render code.
	virtual void Update() { }

	//! Component-specific render code.
	virtual void Draw(/*FLEngine* engine*/) const {}

	//! Component-specific render code.
	virtual void Init() {};

	//! Component-specific render code.
	virtual void Shutdown(/*FLEngine* engine*/) {}


	virtual std::string_view Name() const { return ""; }// { return mType;  }

	//virtual Component& Clone() const = 0;






private:

};