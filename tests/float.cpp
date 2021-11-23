#include "json.hpp"

#include "catch.hpp"

TEST_CASE("Test decoding of floating point values") {
	auto str = R"(
{
	"floatA": 0.12345,
	"floatB": 2.99e3
}
)";

	json::Decoder decoder;
	auto object = decoder.decode(str);

	SECTION("Test object validity") {
		REQUIRE(object != nullptr);
	}
	SECTION("Test object hierarchy") {
		SECTION("Test regular float member") {
			REQUIRE(object->lookup("floatA"));
			auto child = object->lookup("floatA");
			REQUIRE(child->tryFloat() != nullptr);
			auto real = child->tryFloat();
			REQUIRE(*real == 0.12345);
		}
		SECTION("Test exponent float member") {
			REQUIRE(object->lookup("floatB"));
			auto child = object->lookup("floatB");
			REQUIRE(child->tryFloat() != nullptr);
			auto real = child->tryFloat();
			REQUIRE(*real == 2.99e3);
		}
	}
}

TEST_CASE("Test encoding of floating point values") {
	json::Encoder encoder;
	encoder.startEncoding();
	encoder.insert("floatA", 0.12345);
	encoder.insert("floatB", 2.99e3);
	encoder.stopEncoding();

	SECTION("Test encoded string validity") {
		REQUIRE(encoder.str() == "{\"floatA\":0.123450,\"floatB\":2990.000000}");
	}
}
