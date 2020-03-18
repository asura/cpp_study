#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <catch2/catch.hpp>

int main(int the_argc, char** the_argv) noexcept
{
    try
    {
        const int result = Catch::Session().run(the_argc, the_argv);

        return result;
    }
    catch (...)
    {
        return -1;
    }
}
