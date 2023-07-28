#include "stdafx.h"
#include "Time.h"

#include <GLFW/glfw3.h>

float Kaiser::Time::sDeltaTime = 0.0f;
float Kaiser::Time::sTimeScale = 1.0f;
float Kaiser::Time::sFPS = 0.0f;
float Kaiser::Time::sFrameTime = 0.0f;
float Kaiser::Time::sFrameCount = 0.0f;


static float lastFrame = 0.0f;

void Kaiser::Time::Update()
{
	float time = (float)glfwGetTime();
	

	sDeltaTime = time - lastFrame;

	lastFrame = time;

	// update fps
	sFrameTime += sDeltaTime;
	sFrameCount++;
	if (sFrameTime >= 1.0f)
	{
		sFPS = sFrameCount;
		sFrameTime = 0.0f;
		sFrameCount = 0.0f;
	}
	
	
}

float Kaiser::Time::DeltaTime()
{
	return sDeltaTime * sTimeScale;
}

float& Kaiser::Time::GetTimeScale()
{

	return sTimeScale;
}
