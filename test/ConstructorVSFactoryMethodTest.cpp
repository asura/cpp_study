// Constructors or Static Factory Methods? - DZone Java
// https://dzone.com/articles/constructors-or-static-factory-methods

#include <string>

namespace ConstructorVersion
{
    class Color
    {
        const int m_hex;

    public:
        Color(const std::string& rgb)
            : Color(std::stoi(rgb, 0, 16))
        {
        }

        Color(int red, int green, int blue)
            : Color((red << 16) + (green << 8) + blue)
        {
        }

        Color(int hex)
            : m_hex(hex)
        {
        }

        int hex() const { return m_hex; }
    };
}

namespace FactoryMethodVersion
{
    class Color
    {
        const int m_hex;

    public:
        static Color MakeFromRGB(const std::string& rgb)
        {
            return Color(std::stoi(rgb, 0, 16));
        }

        static Color MakeFromPalette(int red, int green, int blue)
        {
            return Color((red << 16) + (green << 8) + blue);
        }

        static Color MakeFromHex(int hex)
        {
            return Color(hex);
        }

        int hex() const { return m_hex; }

    private:
        Color(int hex)
            : m_hex(hex)
        {
        }
    };
}
#include "catch.hpp"

TEST_CASE("コンストラクタを使った構築", "[ConstructorVSFactoruMethod]")
{
    ConstructorVersion::Color c1(0x123456);
    REQUIRE(c1.hex() == 0x123456);

    ConstructorVersion::Color c2(0x12, 0x34, 0x56);
    REQUIRE(c2.hex() == 0x123456);

    ConstructorVersion::Color c3("123456");
    REQUIRE(c3.hex() == 0x123456);
}

TEST_CASE("ファクトリメソッドを使った構築", "[ConstructorVSFactoruMethod]")
{
    auto c1 = FactoryMethodVersion::Color::MakeFromHex(0x123456);
    REQUIRE(c1.hex() == 0x123456);

    auto c2 = FactoryMethodVersion::Color::MakeFromPalette(0x12, 0x34, 0x56);
    REQUIRE(c2.hex() == 0x123456);

    auto c3 = FactoryMethodVersion::Color::MakeFromRGB("123456");
    REQUIRE(c3.hex() == 0x123456);
}
