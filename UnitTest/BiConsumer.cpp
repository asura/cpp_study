#include "BiConsumer.h"
#include "catch.hpp"

class Foo
{
	int m_i;

public:
	Foo(int i)
		: m_i(i)
	{}

	int value() const { return m_i; }

	void Calc(int x, int y)
	{
		m_i = m_i * x + y;
	}
};

SCENARIO("2引数メソッドをキャプチャし、実行する", "[unit][BiConsumer]") {
	Foo foo(2);
	BiConsumer<int, int> sut([&](int x, int y) {
		foo.Calc(x, y);
	});
	sut(3, 4);
	REQUIRE(foo.value() == 10);
}
