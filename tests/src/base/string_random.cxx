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

TEST_SUITE("ztd::random<std::string>")
{
    TEST_CASE("default length")
    {
        const auto random_string = ztd::random<std::string>();

        REQUIRE(random_string.size() == 10);
    }

    TEST_CASE("basic")
    {
        const std::size_t random_string_size = 200;

        const auto rand_hex_string = ztd::random<std::string>(random_string_size);

        REQUIRE(rand_hex_string.size() == random_string_size);

        CHECK(rand_hex_string.contains('0'));
        CHECK(rand_hex_string.contains('1'));
        CHECK(rand_hex_string.contains('2'));
        CHECK(rand_hex_string.contains('3'));
        CHECK(rand_hex_string.contains('4'));
        CHECK(rand_hex_string.contains('5'));
        CHECK(rand_hex_string.contains('6'));
        CHECK(rand_hex_string.contains('7'));
        CHECK(rand_hex_string.contains('8'));
        CHECK(rand_hex_string.contains('9'));
        CHECK(rand_hex_string.contains('A'));
        CHECK(rand_hex_string.contains('B'));
        CHECK(rand_hex_string.contains('C'));
        CHECK(rand_hex_string.contains('D'));
        CHECK(rand_hex_string.contains('E'));
        CHECK(rand_hex_string.contains('F'));
        // Check only hex chars are used
        CHECK_FALSE(rand_hex_string.contains('G'));
        CHECK_FALSE(rand_hex_string.contains('H'));
        CHECK_FALSE(rand_hex_string.contains('I'));
        CHECK_FALSE(rand_hex_string.contains('J'));
        CHECK_FALSE(rand_hex_string.contains('K'));
        CHECK_FALSE(rand_hex_string.contains('L'));
        CHECK_FALSE(rand_hex_string.contains('M'));
        CHECK_FALSE(rand_hex_string.contains('N'));
        CHECK_FALSE(rand_hex_string.contains('O'));
        CHECK_FALSE(rand_hex_string.contains('P'));
        CHECK_FALSE(rand_hex_string.contains('Q'));
        CHECK_FALSE(rand_hex_string.contains('R'));
        CHECK_FALSE(rand_hex_string.contains('S'));
        CHECK_FALSE(rand_hex_string.contains('T'));
        CHECK_FALSE(rand_hex_string.contains('U'));
        CHECK_FALSE(rand_hex_string.contains('V'));
        CHECK_FALSE(rand_hex_string.contains('W'));
        CHECK_FALSE(rand_hex_string.contains('X'));
        CHECK_FALSE(rand_hex_string.contains('Y'));
        CHECK_FALSE(rand_hex_string.contains('Z'));

        CHECK_FALSE(rand_hex_string.contains('a'));
        CHECK_FALSE(rand_hex_string.contains('b'));
        CHECK_FALSE(rand_hex_string.contains('c'));
        CHECK_FALSE(rand_hex_string.contains('d'));
        CHECK_FALSE(rand_hex_string.contains('e'));
        CHECK_FALSE(rand_hex_string.contains('f'));
        CHECK_FALSE(rand_hex_string.contains('g'));
        CHECK_FALSE(rand_hex_string.contains('h'));
        CHECK_FALSE(rand_hex_string.contains('i'));
        CHECK_FALSE(rand_hex_string.contains('j'));
        CHECK_FALSE(rand_hex_string.contains('k'));
        CHECK_FALSE(rand_hex_string.contains('l'));
        CHECK_FALSE(rand_hex_string.contains('m'));
        CHECK_FALSE(rand_hex_string.contains('n'));
        CHECK_FALSE(rand_hex_string.contains('o'));
        CHECK_FALSE(rand_hex_string.contains('p'));
        CHECK_FALSE(rand_hex_string.contains('q'));
        CHECK_FALSE(rand_hex_string.contains('r'));
        CHECK_FALSE(rand_hex_string.contains('s'));
        CHECK_FALSE(rand_hex_string.contains('t'));
        CHECK_FALSE(rand_hex_string.contains('u'));
        CHECK_FALSE(rand_hex_string.contains('v'));
        CHECK_FALSE(rand_hex_string.contains('w'));
        CHECK_FALSE(rand_hex_string.contains('x'));
        CHECK_FALSE(rand_hex_string.contains('y'));
        CHECK_FALSE(rand_hex_string.contains('z'));
    }
}
