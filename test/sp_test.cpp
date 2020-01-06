
#define CATCH_CONFIG_MAIN
#include "catch.hpp"


#include "../src/sequence_processor.h"

TEST_CASE("create union processor", "[processors]") {

	auto res = freeling_server::build_union_processor();
	
	REQUIRE(res.get() != nullptr);
}
