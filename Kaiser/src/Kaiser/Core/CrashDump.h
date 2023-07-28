#pragma once


#include "Core.h"



namespace Kaiser
{
	class CrashDump
	{
	public:
		static void Init();
		static void WriteToFile(EXCEPTION_POINTERS* pException);
		static LONG WINAPI WriteDump(EXCEPTION_POINTERS* pException);
	};
}
