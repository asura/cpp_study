#include <catch2/catch.hpp>
#include <memory>

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

SCENARIO("unique_ptr + インタフェースクラス")
{
    std::unique_ptr<Interface> p(new Concrete());

    CHECK(p->x() == 0);
}
