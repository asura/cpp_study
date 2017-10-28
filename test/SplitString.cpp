#include "SplitString.h"
#include "catch.hpp"

TEST_CASE("SplitString", "[string]")
{
	const std::wstring input = L"The quick brown fox jumps over the lazy dog";
	const wchar_t delimiter = L' ';

	SECTION("SplitString")
	{
		auto result = SplitString(input, delimiter);

		REQUIRE(result.size() == 9);
		CHECK(result[0] == L"The");
		CHECK(result[8] == L"dog");
	}

	SECTION("SplitStringNaive")
	{
		auto result = SplitStringNaive(input, delimiter);

		REQUIRE(result.size() == 9);
		CHECK(result[0] == L"The");
		CHECK(result[8] == L"dog");
	}
}
