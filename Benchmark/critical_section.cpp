#include "benchmark/benchmark.h"
#ifdef _MSC_VER
#include <windows.h>
#endif
#include <mutex>
using namespace std;

class Counter
{
  static const char* MUTEX_NAME;

  int m_counter;

#ifdef _MSC_VER
  CRITICAL_SECTION m_cs;
  HANDLE handle;
#endif
  std::mutex mtx;

public:
  Counter()
    : m_counter(0)
  {
#ifdef _MSC_VER
    InitializeCriticalSection(&m_cs);

    handle = CreateMutex(nullptr, FALSE, MUTEX_NAME);
    if (handle == nullptr) {
      throw "failed";
    }
#endif
  }

  ~Counter()
  {
#ifdef _MSC_VER
    DeleteCriticalSection(&m_cs);

    CloseHandle(handle);
#endif
  }

#ifdef _MSC_VER
  void ProcessWithWin32CriticalSection()
  {
      EnterCriticalSection(&m_cs);
      ++m_counter;
      LeaveCriticalSection(&m_cs);
  }

  void ProcessWithWin32NativeMutex()
  {
    WaitForSingleObject(handle, INFINITE);
    ++m_counter;
    ReleaseMutex(handle);
  }
#endif
  void ProcessWithStdMutex()
  {
    std::lock_guard<std::mutex> lock(mtx);
    ++m_counter;
  }
};
const char* Counter::MUTEX_NAME = "NATIVE_MUTEX_COUNTER";

#ifdef _MSC_VER
//----CriticalSectionによる保護
static void BM_m_cs_critical_section(benchmark::State& state) {
  Counter counter;
  while (state.KeepRunning()) {
    counter.ProcessWithWin32CriticalSection();
  }
}

// 登録
BENCHMARK(BM_m_cs_critical_section)->Threads(4)->UseRealTime();


//----Win32のMutexによる保護
//const char* MUTEX_NAME = nullptr;
static void BM_m_cs_mutex(benchmark::State& state) {
#if 1
  Counter counter;
  while (state.KeepRunning()) {
    counter.ProcessWithWin32NativeMutex();
  }
#else
  while (state.KeepRunning()) {
    //auto mutex_got = OpenMutex(MUTEX_ALL_ACCESS , FALSE , MUTEX_NAME);
    //WaitForSingleObject(mutex_got, INFINITE);
    WaitForSingleObject(handle, INFINITE);
   ++m_counter;
    //ReleaseMutex(mutex_got);
    ReleaseMutex(handle);
  }

  CloseHandle(handle);
#endif
}

// 登録
BENCHMARK(BM_m_cs_mutex)->Threads(4)->UseRealTime();
#endif

//----std::mutexによる保護
static void BM_m_cs_std_mutex(benchmark::State& state) {
  Counter counter;
  while (state.KeepRunning()) {
    counter.ProcessWithStdMutex();
  }
}

// 登録
BENCHMARK(BM_m_cs_std_mutex)->Threads(4)->UseRealTime();
