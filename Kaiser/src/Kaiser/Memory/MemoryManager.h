#pragma once

#include <map>
#include <mutex>
#include "MemoryInfo.h"
#include "Kaiser/Trace.h"

// make Allocator::Shutdown() get called when the program exits. put it in the programs exit function
#define KAISER_SHUTDOWN_AT_EXIT() atexit(Kaiser::Allocator::Shutdown)


namespace Kaiser
{

	namespace Memory
	{
		const Statistics& GetAllocationStats();
	}

	class Allocator
	{
	public:
		static void Shutdown()
		{



			bool hasLeaks = false;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


			std::scoped_lock<std::mutex> lock(s_Data->m_Mutex);

			const int size = (int)s_Data->m_AllocationMap.size();



			Buffer* savedLocations = (Buffer*)_malloca(size * sizeof(Buffer));
			int savedLocationsSize = 0;



			// Get the file name and line number
			for (auto& it : s_Data->m_AllocationMap)
			{
				auto& alloc = it.second;

				if (alloc.caller)
				{
					char fileName[1024]; // file name buffer
					int lineNumber = 0; // line number

					GetSymbols(alloc.caller, fileName, &lineNumber);

					bool ignore = false;

					for (int i = 0; i < IGNORE_LIST_SIZE; i++)
					{
						if (strstr(fileName, ignoreList[i]))
						{
							ignore = true;
							break;
						}
					}

					if (ignore)
						continue;

					bool found = false;

					for (int i = 0; i < savedLocationsSize; i++)
					{
						if (strcmp(savedLocations[i].file, fileName) == 0 && savedLocations[i].line == lineNumber)
						{
							found = true;
							break;
						}
					}

					if (found)
						continue;
					else
					{
						strncpy_s(savedLocations[savedLocationsSize].file, fileName, 1024);
						savedLocations[savedLocationsSize].line = lineNumber;
						savedLocationsSize++;
					}

					if (!hasLeaks)
					{
						// make color white
						SetConsoleTextAttribute(hConsole, 15);
						printf("\nDumping Engine Memory Leaks:\n");
					}

					// make color light red
					SetConsoleTextAttribute(hConsole, 12);

					// Print the file name and line number
					printf("\t[Leak] %zd bytes lost\n", alloc.Size);

					// make color light yellow
					SetConsoleTextAttribute(hConsole, 14);

					printf("\t\tFile: %s\n", fileName);
					printf("\t\tLine: %d\n\n", lineNumber);



					// free the memory
					//free(alloc.Memory);
				}

				// make color white
				SetConsoleTextAttribute(hConsole, 15);
			}

			// free the saved locations
			_freea(savedLocations);
		}
		static void Init();

		static void* Malloc(size_t size);

		static void* Allocate(size_t size, void* caller = nullptr);
		static void* Allocate(size_t size, const char* desc, void* caller = nullptr);
		static void* Allocate(size_t size, const char* file, int line);
		static void Free(void* memory);

		static void GetSymbols(const void* caller, char* fn, int* ln);

		static const StatsMap& GetAllocationStats() { return s_Data->m_AllocationStatsMap; }

	private:
		inline static AllocatorData* s_Data = nullptr;
	};

}

#define KS_TRACK_MEMORY 1

#if KS_TRACK_MEMORY

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new(size_t size);

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new[](size_t size);

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new(size_t size, const char* desc);

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new[](size_t size, const char* desc);

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new(size_t size, const char* file, int line);

_NODISCARD _Ret_notnull_ _Post_writable_byte_size_(size) _VCRT_ALLOCATOR
void* __CRTDECL operator new[](size_t size, const char* file, int line);

void __CRTDECL operator delete(void* memory);
void __CRTDECL operator delete(void* memory, const char* desc);
void __CRTDECL operator delete(void* memory, const char* file, int line);
void __CRTDECL operator delete[](void* memory);
void __CRTDECL operator delete[](void* memory, const char* desc);
void __CRTDECL operator delete[](void* memory, const char* file, int line);

#define knew new(__FILE__, __LINE__)
#define kdelete delete

#else

#define knew new
#define kdelete delete

#endif


