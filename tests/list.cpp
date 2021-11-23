#include "json.hpp"

#include "catch.hpp"

TEST_CASE("Test decoding of list values") {
	auto str = R"(
[1, 2, 3, 4, 5]
)";

	json::Decoder decoder;
	auto object = decoder.decode(str);

	SECTION("Test object validity") {
		REQUIRE(object != nullptr);
	}
	SECTION("Test object hierarchy") {
		SECTION("Test list") {
			REQUIRE(object->tryList() != nullptr);
			auto list = object->tryList();
			for(size_t i = 0; i < list->value.size(); i++) {
				auto integer = list->value[i]->tryInt();
				REQUIRE(integer);
				REQUIRE(*integer == i + 1);
			}
		}
	}
}

TEST_CASE("Test encoding of list values") {
	json::Encoder encoder;
	encoder.startEncoding();
	encoder.insert("boolA", false);
	encoder.insert("boolB", true);
	encoder.stopEncoding();

	SECTION("Test encoded string validity") {
		REQUIRE(encoder.str() == "{\"boolA\":false,\"boolB\":true}");
	}
}
