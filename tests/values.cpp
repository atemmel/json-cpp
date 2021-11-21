#include "json.hpp"

#include "catch.hpp"

TEST_CASE("Test decoding of values") {
	auto str = R"(
{
	"string": "Hello",
	"integer": 5,
	"list": [1, 2, 3, 4, 5],
	"object": { 
		"string": "Hello", 
		"integer": 5, 
		"list": [1, 2, 3, 4, 5] 
	}
}
)";

	json::Decoder decoder;
	auto object = decoder.decode(str);

	SECTION("Test object validity") {
		REQUIRE(object != nullptr);
	}

	SECTION("Test object hierarchy") {
		SECTION("Test string member") {
			REQUIRE(object->lookup("string") != nullptr);
			auto child = object->lookup("string");
			REQUIRE(child->tryString() != nullptr);
			auto string = child->tryString();
			REQUIRE(string->value == "Hello");
		}
		SECTION("Test integer member") {
			REQUIRE(object->lookup("integer") != nullptr);
			auto child = object->lookup("integer");
			REQUIRE(child->tryInt() != nullptr);
			auto integer = child->tryInt();
			REQUIRE(integer->value == 5);
		}
		SECTION("Test list member") {
			REQUIRE(object->lookup("list") != nullptr);
			auto child = object->lookup("list");
			REQUIRE(child->tryList() != nullptr);
			auto list = child->tryList();
			REQUIRE(list->value.size() == 5);
			for(size_t i = 0; i < list->value.size(); i++) {
				REQUIRE(list->value[i]->tryInt() != nullptr);
				auto integer = list->value[i]->tryInt();
				REQUIRE(integer->value == i + 1);
			}
		}
		SECTION("Test object member") {
			REQUIRE(object->lookup("object") != nullptr);
			auto child = object->lookup("object");
			REQUIRE(child->tryObject() != nullptr);
			auto object = child->tryObject();
			REQUIRE(object->lookup("string") != nullptr);
			child = object->lookup("string");
			REQUIRE(child->tryString());
			auto str = child->tryString();
			REQUIRE(str->value == "Hello");
			REQUIRE(object->lookup("integer"));
			child = object->lookup("integer");
			REQUIRE(child->tryInt());
			auto integer = child->tryInt();
			REQUIRE(integer->value == 5);
			child = object->lookup("list");
			REQUIRE(child->tryList() != nullptr);
			auto list = child->tryList();
			REQUIRE(list->value.size() == 5);
			for(size_t i = 0; i < list->value.size(); i++) {
				REQUIRE(list->value[i]->tryInt() != nullptr);
				auto integer = list->value[i]->tryInt();
				REQUIRE(integer->value == i + 1);
			}
		}
	}
}
