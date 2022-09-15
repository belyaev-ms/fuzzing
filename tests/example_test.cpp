#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE example_test
#include <boost/test/unit_test.hpp>

#include "example.h"

BOOST_AUTO_TEST_CASE(example_test1)
{
    uint8_t buffer[] = { 'F', 'U', 'Z', 'Z' };
    BOOST_REQUIRE(fuzz_me(buffer, 4));
}

BOOST_AUTO_TEST_CASE(example_test2)
{
    uint8_t buffer[] = { 'F', 'U', 'Z', 'X' };
    BOOST_REQUIRE(!fuzz_me(buffer, 4));
}

#if 1
BOOST_AUTO_TEST_CASE(example_test3)
{
    uint8_t buffer[] = { 'F', 'U', 'Z', 'Z' };
    BOOST_REQUIRE(fuzz_me_too(buffer, 4, 0));
}

BOOST_AUTO_TEST_CASE(example_test4)
{
    uint8_t buffer[] = { 'F', 'U', 'Z', 'X' };
    BOOST_REQUIRE(!fuzz_me_too(buffer, 4, 0));
}

BOOST_AUTO_TEST_CASE(example_test5)
{
    uint8_t buffer[] = { 'F', 'U', 'Z', 'X' };
    BOOST_REQUIRE(!fuzz_me_too(buffer, 4, '!'));
}
#endif
