#include <catch2/catch.hpp>

[[nodiscard]] bool must_check() { return false; }
bool maybe_check() { return false; }

TEST_CASE("nodiscard属性ありメソッドは戻り値を無視できない")
{
    SECTION("戻り値を無視してみる")
    {
        must_check();
        // 警告発生 (-Wunused-result、標準でenabled)
    }

    SECTION("戻り値を変数に受けるが何もしない")
    {
        auto result = must_check();
        // 警告発生 (-Wunused-variable、標準でdisabled)
    }

    SECTION("戻り値をチェック")
    {
        CHECK(must_check() == false);
        // 警告なし
    }
}

TEST_CASE("nodiscard属性なしメソッドは戻り値を無視してOK")
{
    SECTION("戻り値を無視してみる")
    {
        maybe_check();
        // 警告なし
    }

    SECTION("戻り値を変数に受けるが何もしない")
    {
        auto result = maybe_check();
        // 警告発生 (-Wunused-variable、標準でdisabled)
    }

    SECTION("戻り値をチェック")
    {
        CHECK(maybe_check() == false);
        // 警告なし
    }
}