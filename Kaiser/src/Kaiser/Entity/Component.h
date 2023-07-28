#pragma once

#include "stdafx.h"
#include <string>
#include <vector>
#include "Kaiser/Core/Core.h"

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

	virtual ~Component(void) {};


	//! Component-specific render code.
	virtual void Update() {  }

	//! Component-specific render code.
	virtual void Draw(/*FLEngine* engine*/) const {}

	//! Component-specific render code.
	virtual void Init() {};

	//! Component-specific render code.
	virtual void Shutdown(/*FLEngine* engine*/) {}



	virtual std::string_view Name() const = 0;// { return mType;  }

	//virtual Component& Clone() const = 0;







private:

};