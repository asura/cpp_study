#include <vector>
#include "benchmark/benchmark.h"
using std::move;
using std::vector;

// 明示的にmoveを指定してvectorを返却する
vector<int> func1(int num)
{
    vector<int> to_be_returned;

    for (int i = 0; i < num; ++i)
    {
        to_be_returned.push_back(i);
    }

    return move(to_be_returned);
}

// 無指定でそのままvectorを返却する
vector<int> func2(int num)
{
    vector<int> to_be_returned;

    for (int i = 0; i < num; ++i)
    {
        to_be_returned.push_back(i);
    }

    return to_be_returned;
}

// 参照渡ししたvectorに値を代入する
void func3(int num, vector<int>& v)
{
    v.clear();

    for (int i = 0; i < num; ++i)
    {
        v.push_back(i);
    }
}

// 参照渡ししたvectorに値を代入する(clearなし)
void func4(int num, vector<int>& v)
{
    for (int i = 0; i < num; ++i)
    {
        v.push_back(i);
    }
}

static void BM_returning_vector_with_move(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        for (int i = 0; i < state.range_x(); ++i)
        {
            auto v = func1(i);
        }
    }
    state.SetItemsProcessed(state.iterations());
}

static void BM_returning_vector_without_move(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        for (int i = 0; i < state.range_x(); ++i)
        {
            auto v = func2(i);
        }
    }
    state.SetItemsProcessed(state.iterations());
}

static void BM_returning_vector_by_arg(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        for (int i = 0; i < state.range_x(); ++i)
        {
            vector<int> v;
            func3(i, v);
        }
    }
    state.SetItemsProcessed(state.iterations());
}

static void BM_returning_vector_by_arg_without_clear(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        for (int i = 0; i < state.range_x(); ++i)
        {
            vector<int> v;
            func4(i, v);
        }
    }
    state.SetItemsProcessed(state.iterations());
}

BENCHMARK(BM_returning_vector_with_move)->Range(1 << 4, 1 << 8);
BENCHMARK(BM_returning_vector_without_move)->Range(1 << 4, 1 << 8);
BENCHMARK(BM_returning_vector_by_arg)->Range(1 << 4, 1 << 8);
BENCHMARK(BM_returning_vector_by_arg_without_clear)->Range(1 << 4, 1 << 8);
