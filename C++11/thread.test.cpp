#include <catch2/catch.hpp>
#include <future>
#include <utility>

// c++ - Reference to abstract class can't be passed to thread function? - Stack Overflow
//   https://stackoverflow.com/questions/46560195/reference-to-abstract-class-cant-be-passed-to-thread-function

class Interface
{
public:
    virtual ~Interface() = default;

    virtual int x() const = 0;
};

class Concrete : public Interface
{
public:
    int x() const { return 0; }
};

int task(const Interface& interface)
{
    return interface.x();
}

class Foo
{
public:
    int foo(const Interface& interface)
    {
        auto result = std::async(&task,
                                 std::ref(interface));  // std::refを使う必要あり
        return result.get();
    }
};

SCENARIO("thread + インタフェースクラス")
{
    Foo sut;
    auto c = Concrete();

    CHECK(sut.foo(c) == 0);
}
