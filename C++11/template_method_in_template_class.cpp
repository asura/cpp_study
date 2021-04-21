#include <catch2/catch.hpp>

template <typename T>
class A
{
public:
    template <typename U>
    U foo()
    {
        return U();
    }
};

double hode()
{
    A<int> a;
    return a.foo<double>();
}

template <typename U>
double fuga()
{
    A<int> a;
    return a.foo<U>();
}

template <typename U>
class B
{
    A<int> m_a;

public:
    U bar()
    {
        return m_a.foo<U>();
    }
};

template <typename T>
class C
{
    A<T> m_a;

public:
    double bar()
    {
        return m_a.template foo<double>();  // ★ "template" が必要
    }
};

template <typename T, typename U>
class D
{
    A<T> m_a;

public:
    U bar()
    {
        return m_a.template foo<U>();  // ★ "template" が必要
    }
};

SCENARIO("テンプレートクラス中のテンプレートメソッドをグローバルメソッド内で使う")
{
    CHECK(hode() == 0.0);
}

SCENARIO("テンプレートクラス中のテンプレートメソッドをテンプレートメソッド内で使う")
{
    CHECK(fuga<double>() == 0.0);
}

SCENARIO("テンプレートクラス中のテンプレートメソッドを別テンプレートクラス内で使う")
{
    B<double> b;
    CHECK(b.bar() == 0.0);

    C<int> c;
    CHECK(c.bar() == 0.0);

    D<int, double> d;
    CHECK(d.bar() == 0.0);
}
