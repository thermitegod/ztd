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

TEST_SUITE("ztd::random_hex" * doctest::description(""))
{
    TEST_CASE("random_hex default string length")
    {
        const auto rand_hex_string = ztd::random_hex();

        REQUIRE_EQ(rand_hex_string.size(), 10);
    }

    TEST_CASE("random_hex string")
    {
        const std::size_t rand_hex_string_size = 200;

        // With a size this big all chars should be in there at least once
        const auto rand_hex_string = ztd::random_hex(rand_hex_string_size);

        REQUIRE_EQ(rand_hex_string.size(), rand_hex_string_size);

        CHECK_EQ(rand_hex_string.contains("0"), true);
        CHECK_EQ(rand_hex_string.contains("1"), true);
        CHECK_EQ(rand_hex_string.contains("2"), true);
        CHECK_EQ(rand_hex_string.contains("3"), true);
        CHECK_EQ(rand_hex_string.contains("4"), true);
        CHECK_EQ(rand_hex_string.contains("5"), true);
        CHECK_EQ(rand_hex_string.contains("6"), true);
        CHECK_EQ(rand_hex_string.contains("7"), true);
        CHECK_EQ(rand_hex_string.contains("8"), true);
        CHECK_EQ(rand_hex_string.contains("9"), true);
        CHECK_EQ(rand_hex_string.contains("A"), true);
        CHECK_EQ(rand_hex_string.contains("B"), true);
        CHECK_EQ(rand_hex_string.contains("C"), true);
        CHECK_EQ(rand_hex_string.contains("D"), true);
        CHECK_EQ(rand_hex_string.contains("E"), true);
        CHECK_EQ(rand_hex_string.contains("F"), true);
        // Check only hex chars are used
        CHECK_EQ(rand_hex_string.contains("G"), false);
        CHECK_EQ(rand_hex_string.contains("H"), false);
        CHECK_EQ(rand_hex_string.contains("I"), false);
        CHECK_EQ(rand_hex_string.contains("J"), false);
        CHECK_EQ(rand_hex_string.contains("K"), false);
        CHECK_EQ(rand_hex_string.contains("L"), false);
        CHECK_EQ(rand_hex_string.contains("M"), false);
        CHECK_EQ(rand_hex_string.contains("N"), false);
        CHECK_EQ(rand_hex_string.contains("O"), false);
        CHECK_EQ(rand_hex_string.contains("P"), false);
        CHECK_EQ(rand_hex_string.contains("Q"), false);
        CHECK_EQ(rand_hex_string.contains("R"), false);
        CHECK_EQ(rand_hex_string.contains("S"), false);
        CHECK_EQ(rand_hex_string.contains("T"), false);
        CHECK_EQ(rand_hex_string.contains("U"), false);
        CHECK_EQ(rand_hex_string.contains("V"), false);
        CHECK_EQ(rand_hex_string.contains("W"), false);
        CHECK_EQ(rand_hex_string.contains("X"), false);
        CHECK_EQ(rand_hex_string.contains("Y"), false);
        CHECK_EQ(rand_hex_string.contains("Z"), false);

        CHECK_EQ(rand_hex_string.contains("a"), false);
        CHECK_EQ(rand_hex_string.contains("b"), false);
        CHECK_EQ(rand_hex_string.contains("c"), false);
        CHECK_EQ(rand_hex_string.contains("d"), false);
        CHECK_EQ(rand_hex_string.contains("e"), false);
        CHECK_EQ(rand_hex_string.contains("f"), false);
        CHECK_EQ(rand_hex_string.contains("g"), false);
        CHECK_EQ(rand_hex_string.contains("h"), false);
        CHECK_EQ(rand_hex_string.contains("i"), false);
        CHECK_EQ(rand_hex_string.contains("j"), false);
        CHECK_EQ(rand_hex_string.contains("k"), false);
        CHECK_EQ(rand_hex_string.contains("l"), false);
        CHECK_EQ(rand_hex_string.contains("m"), false);
        CHECK_EQ(rand_hex_string.contains("n"), false);
        CHECK_EQ(rand_hex_string.contains("o"), false);
        CHECK_EQ(rand_hex_string.contains("p"), false);
        CHECK_EQ(rand_hex_string.contains("q"), false);
        CHECK_EQ(rand_hex_string.contains("r"), false);
        CHECK_EQ(rand_hex_string.contains("s"), false);
        CHECK_EQ(rand_hex_string.contains("t"), false);
        CHECK_EQ(rand_hex_string.contains("u"), false);
        CHECK_EQ(rand_hex_string.contains("v"), false);
        CHECK_EQ(rand_hex_string.contains("w"), false);
        CHECK_EQ(rand_hex_string.contains("x"), false);
        CHECK_EQ(rand_hex_string.contains("y"), false);
        CHECK_EQ(rand_hex_string.contains("z"), false);
    }

    TEST_CASE("random_string default string length")
    {
        const auto rand_str_string = ztd::random_string();

        REQUIRE_EQ(rand_str_string.size(), 10);
    }

    TEST_CASE("random_string string")
    {
        const std::size_t rand_str_string_size = 1000;

        // With a size this big all chars should be in there at least once
        const auto rand_str_string = ztd::random_string(rand_str_string_size);

        REQUIRE_EQ(rand_str_string.size(), rand_str_string_size);

        CHECK_EQ(rand_str_string.contains("0"), true);
        CHECK_EQ(rand_str_string.contains("1"), true);
        CHECK_EQ(rand_str_string.contains("2"), true);
        CHECK_EQ(rand_str_string.contains("3"), true);
        CHECK_EQ(rand_str_string.contains("4"), true);
        CHECK_EQ(rand_str_string.contains("5"), true);
        CHECK_EQ(rand_str_string.contains("6"), true);
        CHECK_EQ(rand_str_string.contains("7"), true);
        CHECK_EQ(rand_str_string.contains("8"), true);
        CHECK_EQ(rand_str_string.contains("9"), true);
        CHECK_EQ(rand_str_string.contains("0"), true);

        CHECK_EQ(rand_str_string.contains("a"), true);
        CHECK_EQ(rand_str_string.contains("b"), true);
        CHECK_EQ(rand_str_string.contains("c"), true);
        CHECK_EQ(rand_str_string.contains("d"), true);
        CHECK_EQ(rand_str_string.contains("e"), true);
        CHECK_EQ(rand_str_string.contains("f"), true);
        CHECK_EQ(rand_str_string.contains("g"), true);
        CHECK_EQ(rand_str_string.contains("h"), true);
        CHECK_EQ(rand_str_string.contains("i"), true);
        CHECK_EQ(rand_str_string.contains("j"), true);
        CHECK_EQ(rand_str_string.contains("k"), true);
        CHECK_EQ(rand_str_string.contains("l"), true);
        CHECK_EQ(rand_str_string.contains("m"), true);
        CHECK_EQ(rand_str_string.contains("n"), true);
        CHECK_EQ(rand_str_string.contains("o"), true);
        CHECK_EQ(rand_str_string.contains("p"), true);
        CHECK_EQ(rand_str_string.contains("q"), true);
        CHECK_EQ(rand_str_string.contains("r"), true);
        CHECK_EQ(rand_str_string.contains("s"), true);
        CHECK_EQ(rand_str_string.contains("t"), true);
        CHECK_EQ(rand_str_string.contains("u"), true);
        CHECK_EQ(rand_str_string.contains("v"), true);
        CHECK_EQ(rand_str_string.contains("w"), true);
        CHECK_EQ(rand_str_string.contains("x"), true);
        CHECK_EQ(rand_str_string.contains("y"), true);
        CHECK_EQ(rand_str_string.contains("z"), true);

        CHECK_EQ(rand_str_string.contains("A"), true);
        CHECK_EQ(rand_str_string.contains("B"), true);
        CHECK_EQ(rand_str_string.contains("C"), true);
        CHECK_EQ(rand_str_string.contains("D"), true);
        CHECK_EQ(rand_str_string.contains("E"), true);
        CHECK_EQ(rand_str_string.contains("F"), true);
        CHECK_EQ(rand_str_string.contains("G"), true);
        CHECK_EQ(rand_str_string.contains("H"), true);
        CHECK_EQ(rand_str_string.contains("I"), true);
        CHECK_EQ(rand_str_string.contains("J"), true);
        CHECK_EQ(rand_str_string.contains("K"), true);
        CHECK_EQ(rand_str_string.contains("L"), true);
        CHECK_EQ(rand_str_string.contains("M"), true);
        CHECK_EQ(rand_str_string.contains("N"), true);
        CHECK_EQ(rand_str_string.contains("O"), true);
        CHECK_EQ(rand_str_string.contains("P"), true);
        CHECK_EQ(rand_str_string.contains("Q"), true);
        CHECK_EQ(rand_str_string.contains("R"), true);
        CHECK_EQ(rand_str_string.contains("S"), true);
        CHECK_EQ(rand_str_string.contains("T"), true);
        CHECK_EQ(rand_str_string.contains("U"), true);
        CHECK_EQ(rand_str_string.contains("V"), true);
        CHECK_EQ(rand_str_string.contains("W"), true);
        CHECK_EQ(rand_str_string.contains("X"), true);
        CHECK_EQ(rand_str_string.contains("Y"), true);
        CHECK_EQ(rand_str_string.contains("Z"), true);
    }
}
