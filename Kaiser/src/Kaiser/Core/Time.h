#pragma once

namespace Kaiser
{
	class Time
	{
		static float sDeltaTime;
		static float sTimeScale;
		
		static float sFPS;
		static float sFrameTime;
		static float sFrameCount;
		
	public:

		
		static void Update();
		static float DeltaTime();
		static float FPS() { return sFPS; }
		static float& GetTimeScale();
		
		
	
	};
}

