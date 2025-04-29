#include "OsStates.h"

#ifdef PLATFORM_WINDOWS
#include <windows.h>
#include <psapi.h>

size_t OsStates::GetProcessMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    return memInfo.WorkingSetSize;
}

#elif defined(PLATFORM_LINUX) || defined(PLATFORM_MAC)

#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>

size_t OsStates::GetProcessMemoryUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

#ifdef PLATFORM_MAC
    return usage.ru_maxrss;
#else
    return usage.ru_maxrss * 1024;
#endif
}

#endif
