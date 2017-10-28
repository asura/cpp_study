#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "plog/Log.h"

int main(int argc, char *argv[])
{
	plog::init(plog::info, "tester.log");

	LOGI << "START";
	int result = Catch::Session().run(argc, argv);
	LOGI << "END(" << result << ")";

	return (result < 0xff ? result : 0xff);
}
