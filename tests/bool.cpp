#include "json.hpp"

#include "catch.hpp"

TEST_CASE("Test decoding of boolean values") {
	auto str = R"(
{
	"boolA": false,
	"boolB": true
}
)";

	json::Decoder decoder;
	auto object = decoder.decode(str);

	SECTION("Test object validity") {
		REQUIRE(object != nullptr);
	}
	SECTION("Test object hierarchy") {
		SECTION("Test false member") {
			REQUIRE(object->lookup("boolA"));
			auto child = object->lookup("boolA");
			REQUIRE(child->tryBool() != nullptr);
			auto boolean = child->tryBool();
			REQUIRE(*boolean == false);
		}
		SECTION("Test true member") {
			REQUIRE(object->lookup("boolB"));
			auto child = object->lookup("boolB");
			REQUIRE(child->tryBool() != nullptr);
			auto boolean = child->tryBool();
			REQUIRE(*boolean == true);
		}
	}
}

TEST_CASE("Test encoding of boolean values") {
	json::Encoder encoder;
	encoder.startEncoding();
	encoder.insert("boolA", false);
	encoder.insert("boolB", true);
	encoder.stopEncoding();

	SECTION("Test encoded string validity") {
		REQUIRE(encoder.str() == "{\"boolA\":false,\"boolB\":true}");
	}
}
