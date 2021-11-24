#include "json.hpp"

#include "catch.hpp"

TEST_CASE("Test decoding of null values") {
	auto str = R"(
{
	"a": null,
	"b": null
}
)";

	json::Decoder decoder;
	auto value = decoder.decode(str);

	SECTION("Test value validity") {
		REQUIRE(value != nullptr);
	}
	SECTION("Test object validity") {
		REQUIRE(value->tryObject());
	}
	auto object = value->tryObject();
	SECTION("Test object hierarchy") {
		SECTION("Test null member a") {
			REQUIRE(object->lookup("a"));
			auto child = object->lookup("a");
			REQUIRE(child->isNull());
		}
		SECTION("Test null member b") {
			REQUIRE(object->lookup("b"));
			auto child = object->lookup("b");
			REQUIRE(child->isNull());
		}
	}
}
