
#define CATCH_CONFIG_MAIN
#include "catch.hpp"


#include "../src/sequence_processor.h"

TEST_CASE("create union processor", "[processors]") {

	auto res = freeling_server::build_union_processor();
	
	REQUIRE(res.get() != nullptr);
}

TEST_CASE("create preposition processor", "[processors]") {

	auto res = freeling_server::build_preposition_processor();
	
	REQUIRE(res.get() != nullptr);
}


TEST_CASE("process out sequence", "[processors]") {

	auto processor = freeling_server::build_preposition_processor();

	freeling_server::sentence_type sequence;

	sequence.emplace_back("мама", "мама", "с");
	sequence.emplace_back("мыла", "мыть", "с");
	sequence.emplace_back("раму", "рама", "с");


	auto res = processor->process(sequence);
	
	REQUIRE(res.size() == 3);
}

TEST_CASE("process preposition sequence", "[processors]") {

	auto processor = freeling_server::build_preposition_processor();

	freeling_server::sentence_type sequence;

	sequence.emplace_back("мама", "мама", "с");
	sequence.emplace_back("мыла", "мыть", "с");
	sequence.emplace_back("раму", "рама", "с");
	sequence.emplace_back("без", "без", "с");
	sequence.emplace_back("ведома", "ведомая", "с");
	sequence.emplace_back("маши", "маша", "с");


	auto res = processor->process(sequence);
	
	REQUIRE(res.size() == 5);
	REQUIRE(res[3].word.compare(L"без ведома") == 0);
}

TEST_CASE("process union sequence", "[processors]") {

	auto processor = freeling_server::build_union_processor();

	freeling_server::sentence_type sequence;

	sequence.emplace_back("мама", "мама", "с");
	sequence.emplace_back("мыла", "мыть", "с");
	sequence.emplace_back("раму", "рама", "с");
	sequence.emplace_back("не", "не", "с");
	sequence.emplace_back("то", "то", "с");
	sequence.emplace_back("чтобы", "чтобы", "с");
	sequence.emplace_back("сильно", "сильно", "с");


	auto res = processor->process(sequence);
	
	REQUIRE(res.size() == 5);
	REQUIRE(res[3].word.compare(L"не то чтобы") == 0);
}
