#include <experimental/optional>
#include "catch.hpp"

struct Hoge
{
  int value;

  Hoge(int v)
    : value(v)
  {}
}
TEST_CASE("optional", "[unit][optional]")
{
  SECTION("int型")
  {
    std::experimental::optional<int> sut_true(1);
    std::experimental::optional<int> sut_false;

    SECTION("値が格納されているか確認できる")
    {
      //REQUIRE(sut.has_value()); //Clangではコンパイルできなかった(メソッド定義なし)
      CHECK(sut_true);
      CHECK(! sut_false);
    }
    SECTION("値を参照できる")
    {
      CHECK(*sut_true == 1);
      //CHECK(sut_true.value() == 1);  //Clangではコンパイルできなかった(原因不明)
    }
  }
  SECTION("struct")
  {
    std::experimental::optional<Hoge> sut_true(1);
    std::experimental::optional<Hoge> sut_false;

    SECTION("値が格納されているか確認できる")
    {
      //REQUIRE(sut.has_value()); //Clangではコンパイルできなかった(メソッド定義なし)
      CHECK(sut_true);
      CHECK(! sut_false);
    }
    SECTION("値を参照できる")
    {
      CHECK(sut_true->value == 1);
      CHECK(sut_true.value() == 1);  //Clangではコンパイルできなかった(原因不明)
    }
  }
}