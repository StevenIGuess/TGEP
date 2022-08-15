#pragma once
#include "windows.h"
#include "TCHAR.h"
#include "pdh.h"
#include "psapi.h"

//to do
//implement system agnostic porifiling


namespace TGEP
{
    class Profiling
    {
    public:
        Profiling()
        {
            SYSTEM_INFO sysInfo;
            FILETIME ftime, fsys, fuser;

            GetSystemInfo(&sysInfo);
            numProcessors = sysInfo.dwNumberOfProcessors;

            GetSystemTimeAsFileTime(&ftime);
            memcpy(&lastCPU, &ftime, sizeof(FILETIME));

            self = GetCurrentProcess();
            GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
            memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
            memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
        }
        virtual ~Profiling() {}

        uint64_t get_cpu_cycles()  // just because inline asm is cool!
        {
            uint64_t t = __rdtsc();
            return t;
        }

        DWORDLONG get_total_vmem()
        {
            MEMORYSTATUSEX memInfo;
            memInfo.dwLength = sizeof(MEMORYSTATUSEX);
            GlobalMemoryStatusEx(&memInfo);
            DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
            return totalVirtualMem;
        }

        DWORDLONG get_used_vmem()
        {
            PROCESS_MEMORY_COUNTERS_EX pmc;
            GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
            SIZE_T virtualMemUsed = pmc.PrivateUsage;
            return virtualMemUsed;
        }

        DWORDLONG get_total_ram()
        {
            MEMORYSTATUSEX memInfo;
            memInfo.dwLength = sizeof(MEMORYSTATUSEX);
            GlobalMemoryStatusEx(&memInfo);
            DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
            return totalPhysMem;
        }

        DWORDLONG get_used_ram()
        {
            PROCESS_MEMORY_COUNTERS_EX pmc;
            GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
            SIZE_T physMemUsed = pmc.WorkingSetSize;
            return physMemUsed;
        }

        double get_used_cpu()
        {
            FILETIME ftime, fsys, fuser;
            ULARGE_INTEGER now, sys, user;
            double percent;

            GetSystemTimeAsFileTime(&ftime);
            memcpy(&now, &ftime, sizeof(FILETIME));

            GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
            memcpy(&sys, &fsys, sizeof(FILETIME));
            memcpy(&user, &fuser, sizeof(FILETIME));
            percent = (sys.QuadPart - lastSysCPU.QuadPart) +
                (user.QuadPart - lastUserCPU.QuadPart);
            percent /= (now.QuadPart - lastCPU.QuadPart);
            percent /= numProcessors;
            lastCPU = now;
            lastUserCPU = user;
            lastSysCPU = sys;

            return percent * 100;
        }

        int get_num_processors()
        {
            return numProcessors;
        }

    private:
        bool m_CpuProfilerInitialized = false;

        ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
        int numProcessors;
        HANDLE self;
    };
}