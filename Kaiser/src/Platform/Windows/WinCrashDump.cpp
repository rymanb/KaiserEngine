
#include "stdafx.h"
#include "Kaiser/CrashDump.h"
//#ifdef _DEBUG
#include <DbgHelp.h>

#include "Kaiser/Trace.h"


#pragma comment ( lib, "dbghelp.lib" )

namespace Kaiser
{

	void CrashDump::Init()
	{
		// 16k size
		unsigned long size = 16000;
		SetThreadStackGuarantee(&size);
		//SetUnhandledExceptionFilter(WriteDump);

		KS_CORE_INFO("CrashDump: Initialized Successfully.");
	}



	LONG WINAPI CrashDump::WriteDump(EXCEPTION_POINTERS* pException)
	{
		KS_CORE_FATAL("Crash Detected: Dumping log");
		CrashDump::WriteToFile(pException);

		return EXCEPTION_CONTINUE_SEARCH;
	}

	void CrashDump::WriteToFile(EXCEPTION_POINTERS* pException)
	{

		MINIDUMP_EXCEPTION_INFORMATION mdei;
		mdei.ThreadId = GetCurrentThreadId();
		mdei.ExceptionPointers = pException; // comes from exception
		mdei.ClientPointers = FALSE; // used when writing for a different process

		HANDLE hFile = CreateFile(L"crash.dmp", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		MINIDUMP_TYPE type = MINIDUMP_TYPE(MiniDumpNormal | MiniDumpWithHandleData | MiniDumpWithTokenInformation |
			MiniDumpWithIndirectlyReferencedMemory | MiniDumpWithUnloadedModules | MiniDumpWithFullMemoryInfo | MiniDumpWithThreadInfo);

		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, type, &mdei, NULL, NULL);
	}
	//#endif

}


