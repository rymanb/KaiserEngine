#pragma once

#include <map>
#include "Mallocator.h"

namespace Kaiser
{
	// Basic statistics for a single allocation
	struct Statistics
	{
		int TotalAllocations = 0;
		int TotalFrees = 0;
		int DeltaMemory = 0;
	};

	// Data for a single allocation
	struct Allocation
	{
		void* Memory = 0;
		size_t Size = 0;
		const char* Category = 0;
		
		void* caller = nullptr;
	};

	// Map of allocations
	template<typename U, typename T>
	using Map = std::map<U, T, std::less<U>, Mallocator<std::pair<const U, T>>>;

	// Basic definitions for simplicity
	typedef Map<void*, Allocation> AllocationMap;
	typedef Map<const char*, Statistics> StatsMap;

	// Data for the allocator
	struct AllocatorData
	{

		Map<const void*, Allocation> m_AllocationMap;
		Map<const char*, Statistics> m_AllocationStatsMap;

		std::mutex m_Mutex, m_StatsMutex;
	};

#define IGNORE_LIST_SIZE 2
	
	static const char* ignoreList[IGNORE_LIST_SIZE] =
	{
		"MSVC",
		"vendor"
	};

	struct Buffer
	{
		char file[1024];
		int line;
	};
}