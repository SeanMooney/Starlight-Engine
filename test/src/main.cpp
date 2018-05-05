#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <catch/catch.hpp>
#include <fakeit.hpp>

#include <core/core.hpp>

struct SomeInterface {
    virtual int foo(int) = 0;
    virtual int bar(int, int) = 0;
};

namespace starlight::core{
using namespace fakeit;

TEST_CASE( "life, the universe, everything", "[answer]" ) {
    REQUIRE( Shared::answer == 42 );
}

TEST_CASE("Test MOCKING", "[Mocking]") {
    Mock<SomeInterface> mock;
    // Stub a method to return a value once
    When(Method(mock, foo)(0)).Return(1);
    When(Method(mock, foo)(1)).Return(42);
    SomeInterface& i = mock.get();
    REQUIRE(i.foo(0) == 1);
    REQUIRE(i.foo(1) == 42);
}
}