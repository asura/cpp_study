#include <memory>
#include "catch.hpp"

using namespace std;

SCENARIO("shared_ptrはリソースの所有権を共有する", "[memory][shared_ptr]")
{
    GIVEN("shared_ptrを生成")
    {
        auto var1 = make_shared<int>(1);
        REQUIRE(var1 != nullptr);
        REQUIRE(var1.use_count() == 1);

        WHEN("他の変数に代入")
        {
            auto var2 = var1;

            THEN("同じポインタを指している")
            {
                REQUIRE(var1.get() == var2.get());
            }
            THEN("参照カウンタが2になる")
            {
                REQUIRE(var1.use_count() == 2);
            }
        }
    }
}
