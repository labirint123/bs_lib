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

#ifdef PLATFORM_LINUX
#include <fstream>
#include <string>
#include <sstream>
#endif

size_t OsStates::GetProcessMemoryUsage() {
#ifdef PLATFORM_MAC
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
#else
    std::ifstream stat_stream("/proc/self/status", std::ios_base::in);
    std::string line;
    while (std::getline(stat_stream, line)) {
        if (line.substr(0, 6) == "VmRSS:") {
            std::istringstream iss(line);
            std::string key;
            size_t value_kb;
            std::string unit;
            iss >> key >> value_kb >> unit;
            return value_kb * 1024;
        }
    }
    return 0;
#endif
}

#endif
