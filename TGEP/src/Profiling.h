#pragma once
#include "windows.h"
#include "TCHAR.h"
#include "pdh.h"
#include "psapi.h"
#include "stdint.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <thread>

#define TGEP_DEBUG_PROFILEING 1

#if TGEP_DEBUG_PROFILEING
#define PROFILE_BEGIN(name, filepath) TGEP::Instrumentor::Get().BeginSession(name, filepath)
#define PROFILE_END() TGEP::Instrumentor::Get().EndSession()
#define PROFILE_SCOPED(name) TGEP::InstrumentationTimer timer##__LINE__(name);
#define PROFILE_FUNCTION() PROFILE_SCOPED(__FUNCSIG__)
#else
#define PROFILE_BEGIN(name, file) 
#define PROFILE_END() 
#define PROFILE_FUNCTION(name) 
#define PROFILE_SCOPED() 
#endif


namespace TGEP
{
    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        uint32_t ThreadID;
    };

    struct InstrumentationSession
    {
        std::string Name;
    };

    class Instrumentor
    {
    private:
        InstrumentationSession* m_CurrentSession;
        std::ofstream m_OutputStream;
        int m_ProfileCount;
    public:
        Instrumentor()
            : m_CurrentSession(nullptr), m_ProfileCount(0)
        {
        }

        void BeginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            m_OutputStream.open(filepath);
            WriteHeader();
            m_CurrentSession = new InstrumentationSession{ name };
        }

        void EndSession()
        {
            WriteFooter();
            m_OutputStream.close();
            delete m_CurrentSession;
            m_CurrentSession = nullptr;
            m_ProfileCount = 0;
        }

        void WriteProfile(const ProfileResult& result)
        {
            if (m_ProfileCount++ > 0)
                m_OutputStream << ",";

            std::string name = result.Name;
            std::replace(name.begin(), name.end(), '"', '\'');

            m_OutputStream << "{";
            m_OutputStream << "\"cat\":\"function\",";
            m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
            m_OutputStream << "\"name\":\"" << name << "\",";
            m_OutputStream << "\"ph\":\"X\",";
            m_OutputStream << "\"pid\":0,";
            m_OutputStream << "\"tid\":" << result.ThreadID << ",";
            m_OutputStream << "\"ts\":" << result.Start;
            m_OutputStream << "}";

            m_OutputStream.flush();
        }

        void WriteHeader()
        {
            m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
            m_OutputStream.flush();
        }

        void WriteFooter()
        {
            m_OutputStream << "]}";
            m_OutputStream.flush();
        }

        static Instrumentor& Get()
        {
            static Instrumentor instance;
            return instance;
        }
    };

    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name)
            : m_Name(name), m_Stopped(false)
        {
            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }

        ~InstrumentationTimer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

            uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
            Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });

            m_Stopped = true;
        }
    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
        bool m_Stopped;
    };

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

        virtual ~Profiling() = default;

        uint64_t get_cpu_cycles()
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