#include "stdafx.h"
#include "MemoryManager.h"

#include "Kaiser/Trace.h"

#include <Windows.h>
#include <DbgHelp.h>


namespace Kaiser {

	static Kaiser::Statistics s_GlobalStats; // global stats

	static bool s_InInit = false; // have we initialized yet?

	void Allocator::Init()
	{
		KAISER_SHUTDOWN_AT_EXIT();

		SymInitialize(GetCurrentProcess(), NULL, true);
		SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES);
		
		if (s_Data)
			return;

		s_InInit = true;
		AllocatorData* data = (AllocatorData*)Allocator::Malloc(sizeof(AllocatorData));
		new(data) AllocatorData();
		s_Data = data;
		s_InInit = false;
	}

	void* Allocator::Malloc(size_t size)
	{
		return malloc(size);
	}

	void* Allocator::Allocate(size_t size, void* caller)
	{
		if (s_InInit)
			return Malloc(size);

		if (!s_Data)
			Init();

		void* memory = malloc(size);

		{
			std::scoped_lock<std::mutex> lock(s_Data->m_Mutex);
			Allocation& alloc = s_Data->m_AllocationMap[memory];
			alloc.Memory = memory;
			alloc.Size = size;
			alloc.caller = caller;

			

			s_GlobalStats.TotalAllocations += (int)size;
		}

		return memory;
	}

	void* Allocator::Allocate(size_t size, const char* desc, void* caller)
	{
		if (!s_Data)
			Init();

		void* memory = malloc(size);

		{
			std::scoped_lock<std::mutex> lock(s_Data->m_Mutex);
			Allocation& alloc = s_Data->m_AllocationMap[memory];
			alloc.Memory = memory;
			alloc.Size = size;
			alloc.Category = desc;
			alloc.caller = caller;

			s_GlobalStats.TotalAllocations += (int)size;
			if (desc)
				s_Data->m_AllocationStatsMap[desc].TotalAllocations += (int)size;
		}

		return memory;
	}

	void* Allocator::Allocate(size_t size, const char* file, int line)
	{
		if (!s_Data)
			Init();

		void* memory = malloc(size);

		{
			std::scoped_lock<std::mutex> lock(s_Data->m_Mutex);
			Allocation& alloc = s_Data->m_AllocationMap[memory];
			alloc.Memory = memory;
			alloc.Size = size;
			alloc.Category = file;

			s_GlobalStats.TotalAllocations += (int)size;
			s_Data->m_AllocationStatsMap[file].TotalAllocations += (int)size;
		}

		return memory;
	}

	void Allocator::Free(void* memory)
	{
		if (memory == nullptr)
			return;

		{
			bool found = false;
			{
				std::scoped_lock<std::mutex> lock(s_Data->m_Mutex);
				auto allocMapIt = s_Data->m_AllocationMap.find(memory);
				found = allocMapIt != s_Data->m_AllocationMap.end();
				if (found)
				{
					const Allocation& alloc = allocMapIt->second;
					s_GlobalStats.TotalFrees += (int)alloc.Size;
					if (alloc.Category)
						s_Data->m_AllocationStatsMap[alloc.Category].TotalFrees += (int)alloc.Size;

					s_Data->m_AllocationMap.erase(memory);
				}
			}

#ifndef HZ_DIST
			if (!found)
				KS_CORE_WARN("Memory", "Memory block {0} not present in alloc map", memory);
#endif
		}

		free(memory);
	}

	void Allocator::GetSymbols(const void* caller, char* fn, int* ln)
	{
		if (caller == nullptr)
		{
			return;
		}

		// Get the symbol
		SymSetOptions(SYMOPT_LOAD_LINES);
		DWORD  dwDisplacement;
		IMAGEHLP_LINE64 line;
		line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

		SymGetLineFromAddr64(GetCurrentProcess(), (DWORD64)caller, &dwDisplacement, &line);

		*ln = line.LineNumber;
		if (line.FileName != nullptr)
		{
			strcpy_s(fn, 1024, line.FileName);
		}
		else
		{
			strcpy_s(fn, 1024, "Unknown");
		}
	}

	namespace Memory {

		const Statistics& GetAllocationStats() { return s_GlobalStats; }
	}
}

#if KS_TRACK_MEMORY

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new(size_t size)
{
	return Kaiser::Allocator::Allocate(size, _ReturnAddress());
}

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new[](size_t size)
{
	return Kaiser::Allocator::Allocate(size, _ReturnAddress());
}

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new(size_t size, const char* desc)
{
	return Kaiser::Allocator::Allocate(size, desc, _ReturnAddress());
}

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new[](size_t size, const char* desc)
{
	return Kaiser::Allocator::Allocate(size, desc, _ReturnAddress());
}

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new(size_t size, const char* file, int line)
{
	return Kaiser::Allocator::Allocate(size, file, line);
}

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new[](size_t size, const char* file, int line)
{
	return Kaiser::Allocator::Allocate(size, file, line);
}

void __CRTDECL operator delete(void* memory)
{
	return Kaiser::Allocator::Free(memory);
}

void __CRTDECL operator delete(void* memory, const char* desc)
{
	return Kaiser::Allocator::Free(memory);
}

void __CRTDECL operator delete(void* memory, const char* file, int line)
{
	return Kaiser::Allocator::Free(memory);
}

void __CRTDECL operator delete[](void* memory)
{
	return Kaiser::Allocator::Free(memory);
}

void __CRTDECL operator delete[](void* memory, const char* desc)
{
	return Kaiser::Allocator::Free(memory);
}

void __CRTDECL operator delete[](void* memory, const char* file, int line)
{
	return Kaiser::Allocator::Free(memory);
}

#endif