#include "thread_safe_queue.h"
#include "catch.hpp"

SCENARIO("構築した時点ではemptyがtrueを返す", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<int> sut;
	REQUIRE(sut.empty());
}

SCENARIO("pushするとemptyはfalseを返す", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<int> sut;
	sut.push(1);
	REQUIRE(! sut.empty());
}

SCENARIO("pushした値はfrontで取得できる", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<int> sut;
	sut.push(1);
	auto value = sut.front();
	REQUIRE(value == 1);
}

SCENARIO("pushするとsizeで取得できる値が+1になる", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<int> sut;
	REQUIRE(sut.size() == 0);

	sut.push(1);
	REQUIRE(sut.size() == 1);

	sut.push(2);
	REQUIRE(sut.size() == 2);
}

SCENARIO("構築直後にpopすると例外発生", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<int> sut;
	REQUIRE_THROWS(sut.pop());
}

SCENARIO("push→popによりsizeが減少", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<int> sut;

	sut.push(1);
	sut.pop();
	REQUIRE(sut.size() == 0);
}

struct Foo
{
	static std::vector<std::string> log;

	Foo()
	{
		log.push_back("constructor");
	}

	Foo(const std::string&)
	{
		log.push_back("constructor with string");
	}

	Foo(const Foo&)
	{
		log.push_back("copy constructor");
	}

	Foo(Foo&&)
	{
		log.push_back("move constructor");
	}

	Foo& operator=(const Foo&)
	{
		log.push_back("copy operator");
	}

	Foo& operator=(Foo&&)
	{
		log.push_back("move operator");
	}
};

std::vector<std::string> Foo::log;

TEST_CASE("通常のpushはコピーコンストラクタが動く", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<Foo> sut;
	Foo::log.clear();

	Foo foo;
	sut.push(foo);

	REQUIRE(Foo::log.size() == 2);
	CHECK(Foo::log[0] == "constructor");
	CHECK(Foo::log[1] == "copy constructor");
}

TEST_CASE("ムーブ版のpushはムーブコンストラクタが動く", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<Foo> sut;
	Foo::log.clear();

	sut.push(Foo());

	REQUIRE(Foo::log.size() == 2);
	CHECK(Foo::log[0] == "constructor");
	CHECK(Foo::log[1] == "move constructor");
}

TEST_CASE("emplaceはコピーされない", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<Foo> sut;
	Foo::log.clear();

	sut.emplace(std::string("abc"));

	REQUIRE(Foo::log.size() == 1);
	CHECK(Foo::log[0] == "constructor with string");
}
