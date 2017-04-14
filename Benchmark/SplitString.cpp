#include "SplitString.h"
#include "benchmark/benchmark.h"

const std::wstring input = L"The quick brown fox jumps over the lazy dog";
const wchar_t delimiter = L' ';

static void BM_SplitString(benchmark::State& state)
{
	while (state.KeepRunning())
	{
		for (int i = 0; i < state.range_x(); ++i)
		{
			SplitString(input, delimiter);
		}
	}
	state.SetItemsProcessed(state.iterations());
}

static void BM_SplitStringNaive(benchmark::State& state)
{
	while (state.KeepRunning())
	{
		for (int i = 0; i < state.range_x(); ++i)
		{
			SplitStringNaive(input, delimiter);
		}
	}
	state.SetItemsProcessed(state.iterations());
}

BENCHMARK(BM_SplitString)->Range(1 << 4, 1 << 8);
BENCHMARK(BM_SplitStringNaive)->Range(1 << 4, 1 << 8);
