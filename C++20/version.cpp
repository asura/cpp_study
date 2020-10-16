#include <catch2/catch.hpp>
#include <version>

TEST_CASE(
    "versionヘッダ",
    "[version]")
{
    SECTION("ライブラリ")
    {
        SECTION("optionalを利用可能")
        {
            CHECK(__cpp_lib_optional == 201606);
        }
    }
}
