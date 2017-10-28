#include "thread_safe_queue.h"
#include <cassert>
#include <iostream>
#include "benchmark/benchmark.h"

static void BM_normal_deque(benchmark::State& state)
{
    std::deque<int> sut;

    while (state.KeepRunning())
    {
        for (int i = 0; i < state.range_x(); ++i)
        {
            sut.push_back(i);
        }
    }
    state.SetItemsProcessed(state.iterations());

    assert(sut.size() == state.range(0) * state.max_iterations);
}
static void BM_thread_safe_queue(benchmark::State& state)
{
    ThreadSafeQueue<int> sut;

    while (state.KeepRunning())
    {
        for (int i = 0; i < state.range_x(); ++i)
        {
            sut.push(i);
        }
    }
    state.SetItemsProcessed(state.iterations());

    assert(sut.size() == state.range(0) * state.max_iterations);
}

BENCHMARK(BM_normal_deque)->Range(1 << 4, 1 << 8)->Threads(4);
BENCHMARK(BM_thread_safe_queue)->Range(1 << 4, 1 << 8)->Threads(4);
