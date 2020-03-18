#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

// TCMallocを使ってみる
// (リンク指定のみで、コード上は何も特別なことをしない)
TEST_CASE("tcmalloc")
{
    auto p = new int[1024 * 1024];
    delete p;

    BENCHMARK("new & delete")
    {
        for (int i = 1; i < 100; ++i)
        {
            auto p = new int[1024 * 1024 * i];
            delete p;
        }

        return 0;
    };
}
