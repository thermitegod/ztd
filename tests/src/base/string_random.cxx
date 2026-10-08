/**
 * Copyright (C) 2024 Brandon Zorn <brandonzorn@cock.li>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <string>

#include <doctest/doctest.h>

#include "ztd/detail/string_random.hxx"

TEST_SUITE("ztd::random_hex")
{
    TEST_CASE("random_hex default string length")
    {
        const auto rand_hex_string = ztd::random_hex();

        REQUIRE(rand_hex_string.size() == 10);
    }

    TEST_CASE("random_hex string")
    {
        const std::size_t rand_hex_string_size = 200;

        // With a size this big all chars should be in there at least once
        const auto rand_hex_string = ztd::random_hex(rand_hex_string_size);

        REQUIRE(rand_hex_string.size() == rand_hex_string_size);

        CHECK(rand_hex_string.contains("0"));
        CHECK(rand_hex_string.contains("1"));
        CHECK(rand_hex_string.contains("2"));
        CHECK(rand_hex_string.contains("3"));
        CHECK(rand_hex_string.contains("4"));
        CHECK(rand_hex_string.contains("5"));
        CHECK(rand_hex_string.contains("6"));
        CHECK(rand_hex_string.contains("7"));
        CHECK(rand_hex_string.contains("8"));
        CHECK(rand_hex_string.contains("9"));
        CHECK(rand_hex_string.contains("A"));
        CHECK(rand_hex_string.contains("B"));
        CHECK(rand_hex_string.contains("C"));
        CHECK(rand_hex_string.contains("D"));
        CHECK(rand_hex_string.contains("E"));
        CHECK(rand_hex_string.contains("F"));
        // Check only hex chars are used
        CHECK_FALSE(rand_hex_string.contains("G"));
        CHECK_FALSE(rand_hex_string.contains("H"));
        CHECK_FALSE(rand_hex_string.contains("I"));
        CHECK_FALSE(rand_hex_string.contains("J"));
        CHECK_FALSE(rand_hex_string.contains("K"));
        CHECK_FALSE(rand_hex_string.contains("L"));
        CHECK_FALSE(rand_hex_string.contains("M"));
        CHECK_FALSE(rand_hex_string.contains("N"));
        CHECK_FALSE(rand_hex_string.contains("O"));
        CHECK_FALSE(rand_hex_string.contains("P"));
        CHECK_FALSE(rand_hex_string.contains("Q"));
        CHECK_FALSE(rand_hex_string.contains("R"));
        CHECK_FALSE(rand_hex_string.contains("S"));
        CHECK_FALSE(rand_hex_string.contains("T"));
        CHECK_FALSE(rand_hex_string.contains("U"));
        CHECK_FALSE(rand_hex_string.contains("V"));
        CHECK_FALSE(rand_hex_string.contains("W"));
        CHECK_FALSE(rand_hex_string.contains("X"));
        CHECK_FALSE(rand_hex_string.contains("Y"));
        CHECK_FALSE(rand_hex_string.contains("Z"));

        CHECK_FALSE(rand_hex_string.contains("a"));
        CHECK_FALSE(rand_hex_string.contains("b"));
        CHECK_FALSE(rand_hex_string.contains("c"));
        CHECK_FALSE(rand_hex_string.contains("d"));
        CHECK_FALSE(rand_hex_string.contains("e"));
        CHECK_FALSE(rand_hex_string.contains("f"));
        CHECK_FALSE(rand_hex_string.contains("g"));
        CHECK_FALSE(rand_hex_string.contains("h"));
        CHECK_FALSE(rand_hex_string.contains("i"));
        CHECK_FALSE(rand_hex_string.contains("j"));
        CHECK_FALSE(rand_hex_string.contains("k"));
        CHECK_FALSE(rand_hex_string.contains("l"));
        CHECK_FALSE(rand_hex_string.contains("m"));
        CHECK_FALSE(rand_hex_string.contains("n"));
        CHECK_FALSE(rand_hex_string.contains("o"));
        CHECK_FALSE(rand_hex_string.contains("p"));
        CHECK_FALSE(rand_hex_string.contains("q"));
        CHECK_FALSE(rand_hex_string.contains("r"));
        CHECK_FALSE(rand_hex_string.contains("s"));
        CHECK_FALSE(rand_hex_string.contains("t"));
        CHECK_FALSE(rand_hex_string.contains("u"));
        CHECK_FALSE(rand_hex_string.contains("v"));
        CHECK_FALSE(rand_hex_string.contains("w"));
        CHECK_FALSE(rand_hex_string.contains("x"));
        CHECK_FALSE(rand_hex_string.contains("y"));
        CHECK_FALSE(rand_hex_string.contains("z"));
    }

    TEST_CASE("random_string default string length")
    {
        const auto rand_str_string = ztd::random_string();

        REQUIRE(rand_str_string.size() == 10);
    }

    TEST_CASE("random_string string")
    {
        const std::size_t rand_str_string_size = 1000;

        // With a size this big all chars should be in there at least once
        const auto rand_str_string = ztd::random_string(rand_str_string_size);

        REQUIRE(rand_str_string.size() == rand_str_string_size);

        CHECK(rand_str_string.contains("0"));
        CHECK(rand_str_string.contains("1"));
        CHECK(rand_str_string.contains("2"));
        CHECK(rand_str_string.contains("3"));
        CHECK(rand_str_string.contains("4"));
        CHECK(rand_str_string.contains("5"));
        CHECK(rand_str_string.contains("6"));
        CHECK(rand_str_string.contains("7"));
        CHECK(rand_str_string.contains("8"));
        CHECK(rand_str_string.contains("9"));
        CHECK(rand_str_string.contains("0"));

        CHECK(rand_str_string.contains("a"));
        CHECK(rand_str_string.contains("b"));
        CHECK(rand_str_string.contains("c"));
        CHECK(rand_str_string.contains("d"));
        CHECK(rand_str_string.contains("e"));
        CHECK(rand_str_string.contains("f"));
        CHECK(rand_str_string.contains("g"));
        CHECK(rand_str_string.contains("h"));
        CHECK(rand_str_string.contains("i"));
        CHECK(rand_str_string.contains("j"));
        CHECK(rand_str_string.contains("k"));
        CHECK(rand_str_string.contains("l"));
        CHECK(rand_str_string.contains("m"));
        CHECK(rand_str_string.contains("n"));
        CHECK(rand_str_string.contains("o"));
        CHECK(rand_str_string.contains("p"));
        CHECK(rand_str_string.contains("q"));
        CHECK(rand_str_string.contains("r"));
        CHECK(rand_str_string.contains("s"));
        CHECK(rand_str_string.contains("t"));
        CHECK(rand_str_string.contains("u"));
        CHECK(rand_str_string.contains("v"));
        CHECK(rand_str_string.contains("w"));
        CHECK(rand_str_string.contains("x"));
        CHECK(rand_str_string.contains("y"));
        CHECK(rand_str_string.contains("z"));

        CHECK(rand_str_string.contains("A"));
        CHECK(rand_str_string.contains("B"));
        CHECK(rand_str_string.contains("C"));
        CHECK(rand_str_string.contains("D"));
        CHECK(rand_str_string.contains("E"));
        CHECK(rand_str_string.contains("F"));
        CHECK(rand_str_string.contains("G"));
        CHECK(rand_str_string.contains("H"));
        CHECK(rand_str_string.contains("I"));
        CHECK(rand_str_string.contains("J"));
        CHECK(rand_str_string.contains("K"));
        CHECK(rand_str_string.contains("L"));
        CHECK(rand_str_string.contains("M"));
        CHECK(rand_str_string.contains("N"));
        CHECK(rand_str_string.contains("O"));
        CHECK(rand_str_string.contains("P"));
        CHECK(rand_str_string.contains("Q"));
        CHECK(rand_str_string.contains("R"));
        CHECK(rand_str_string.contains("S"));
        CHECK(rand_str_string.contains("T"));
        CHECK(rand_str_string.contains("U"));
        CHECK(rand_str_string.contains("V"));
        CHECK(rand_str_string.contains("W"));
        CHECK(rand_str_string.contains("X"));
        CHECK(rand_str_string.contains("Y"));
        CHECK(rand_str_string.contains("Z"));
    }
}
