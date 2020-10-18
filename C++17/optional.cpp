#include <catch2/catch.hpp>
#include <optional>

TEST_CASE(
    "optional::has_value",
    "[optional")
{
    GIVEN("optionalに有効値を設定")
    {
        const double VALUE = 1.23;

        std::optional<double> sut(VALUE);

        WHEN("has_valueを実行")
        {
            THEN("trueが返る")
            {
                CHECK(sut.has_value() == true);
            }
        }
    }

    GIVEN("optionalに無効値を設定")
    {
        std::optional<double> sut;

        WHEN("has_valueを実行")
        {
            THEN("falseが返る")
            {
                CHECK(sut.has_value() == false);
            }
        }
    }
}

TEST_CASE(
    "optional::operator bool",
    "[optional")
{
    GIVEN("optionalに有効値を設定")
    {
        const double VALUE = 1.23;

        std::optional<double> sut(VALUE);

        WHEN("op boolを実行")
        {
            THEN("trueが返る")
            {
                CHECK(static_cast<bool>(sut) == true);
            }
        }
    }

    GIVEN("optionalに無効値を設定")
    {
        std::optional<double> sut;

        WHEN("op boolを実行")
        {
            THEN("falseが返る")
            {
                CHECK(static_cast<bool>(sut) == false);
            }
        }
    }
}

TEST_CASE(
    "optional::value",
    "[optional")
{
    GIVEN("optionalに有効値を設定")
    {
        const double VALUE = 1.23;

        std::optional<double> sut(VALUE);

        WHEN("valueで取得")
        {
            THEN("設定した値を取得できる")
            {
                CHECK(sut.value() == VALUE);
            }
        }
    }

    GIVEN("optionalに無効値を設定")
    {
        std::optional<double> sut;

        WHEN("valueで取得")
        {
            THEN("例外bad_optional_accessが発生")
            {
                REQUIRE_THROWS_AS(sut.value(), std::bad_optional_access);
            }
        }
    }
}

TEST_CASE(
    "optional::operator*",
    "[optional")
{
    GIVEN("optionalに有効値を設定")
    {
        const double VALUE = 1.23;

        std::optional<double> sut(VALUE);

        WHEN("op*で取得")
        {
            THEN("設定した値を取得できる")
            {
                CHECK(*sut == VALUE);
            }
        }
    }

    // 無効値時の挙動は未定義
}
