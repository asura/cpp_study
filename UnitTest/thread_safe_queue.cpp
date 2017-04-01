#include "thread_safe_queue.h"
#include "catch.hpp"

SCENARIO("�\�z�������_�ł�empty��true��Ԃ�", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<int> sut;
	REQUIRE(sut.empty());
}

SCENARIO("push�����empty��false��Ԃ�", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<int> sut;
	sut.push(1);
	REQUIRE(! sut.empty());
}

SCENARIO("push�����l��front�Ŏ擾�ł���", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<int> sut;
	sut.push(1);
	auto value = sut.front();
	REQUIRE(value == 1);
}

SCENARIO("push�����size�Ŏ擾�ł���l��+1�ɂȂ�", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<int> sut;
	REQUIRE(sut.size() == 0);

	sut.push(1);
	REQUIRE(sut.size() == 1);

	sut.push(2);
	REQUIRE(sut.size() == 2);
}

SCENARIO("�\�z�����pop����Ɨ�O����", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<int> sut;
	REQUIRE_THROWS(sut.pop());
}

SCENARIO("push��pop�ɂ��size������", "[unit][ThreadSafeQueue]") {
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

TEST_CASE("�ʏ��push�̓R�s�[�R���X�g���N�^������", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<Foo> sut;
	Foo::log.clear();

	Foo foo;
	sut.push(foo);

	REQUIRE(Foo::log.size() == 2);
	CHECK(Foo::log[0] == "constructor");
	CHECK(Foo::log[1] == "copy constructor");
}

TEST_CASE("���[�u�ł�push�̓��[�u�R���X�g���N�^������", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<Foo> sut;
	Foo::log.clear();

	sut.push(Foo());

	REQUIRE(Foo::log.size() == 2);
	CHECK(Foo::log[0] == "constructor");
	CHECK(Foo::log[1] == "move constructor");
}

TEST_CASE("emplace�̓R�s�[����Ȃ�", "[unit][ThreadSafeQueue]") {
	ThreadSafeQueue<Foo> sut;
	Foo::log.clear();

	sut.emplace(std::string("abc"));

	REQUIRE(Foo::log.size() == 1);
	CHECK(Foo::log[0] == "constructor with string");
}
