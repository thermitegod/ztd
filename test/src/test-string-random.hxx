/**
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

#pragma once

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>

#include <chrono>

#include <cstdlib>

#include "../../src/ztd.hxx"

TEST_CASE("::randhex")
{
    std::srand(std::time(nullptr));

    std::size_t rand_hex_string_size = 200;

    // With a size this big all chars should be in there at least once
    std::string rand_hex_string = ztd::randhex(rand_hex_string_size);

    /////////////////////////////////////////////
    REQUIRE(rand_hex_string.size() == rand_hex_string_size);
    /////////////////////////////////////////////
    REQUIRE(ztd::contains(rand_hex_string, "0"));
    REQUIRE(ztd::contains(rand_hex_string, "1"));
    REQUIRE(ztd::contains(rand_hex_string, "2"));
    REQUIRE(ztd::contains(rand_hex_string, "3"));
    REQUIRE(ztd::contains(rand_hex_string, "4"));
    REQUIRE(ztd::contains(rand_hex_string, "5"));
    REQUIRE(ztd::contains(rand_hex_string, "6"));
    REQUIRE(ztd::contains(rand_hex_string, "7"));
    REQUIRE(ztd::contains(rand_hex_string, "8"));
    REQUIRE(ztd::contains(rand_hex_string, "9"));
    REQUIRE(ztd::contains(rand_hex_string, "a"));
    REQUIRE(ztd::contains(rand_hex_string, "b"));
    REQUIRE(ztd::contains(rand_hex_string, "c"));
    REQUIRE(ztd::contains(rand_hex_string, "d"));
    REQUIRE(ztd::contains(rand_hex_string, "e"));
    REQUIRE(ztd::contains(rand_hex_string, "f"));
}

TEST_CASE("::randstr")
{
    std::srand(std::time(nullptr));

    std::size_t rand_str_string_size = 1000;

    // With a size this big all chars should be in there at least once
    std::string rand_str_string = ztd::randstr(rand_str_string_size);

    /////////////////////////////////////////////
    REQUIRE(rand_str_string.size() == rand_str_string_size);
    /////////////////////////////////////////////
    REQUIRE(ztd::contains(rand_str_string, "0"));
    REQUIRE(ztd::contains(rand_str_string, "1"));
    REQUIRE(ztd::contains(rand_str_string, "2"));
    REQUIRE(ztd::contains(rand_str_string, "3"));
    REQUIRE(ztd::contains(rand_str_string, "4"));
    REQUIRE(ztd::contains(rand_str_string, "5"));
    REQUIRE(ztd::contains(rand_str_string, "6"));
    REQUIRE(ztd::contains(rand_str_string, "7"));
    REQUIRE(ztd::contains(rand_str_string, "8"));
    REQUIRE(ztd::contains(rand_str_string, "9"));
    REQUIRE(ztd::contains(rand_str_string, "0"));
    /////////////////////////////////////////////
    REQUIRE(ztd::contains(rand_str_string, "a"));
    REQUIRE(ztd::contains(rand_str_string, "b"));
    REQUIRE(ztd::contains(rand_str_string, "c"));
    REQUIRE(ztd::contains(rand_str_string, "d"));
    REQUIRE(ztd::contains(rand_str_string, "e"));
    REQUIRE(ztd::contains(rand_str_string, "f"));
    REQUIRE(ztd::contains(rand_str_string, "g"));
    REQUIRE(ztd::contains(rand_str_string, "h"));
    REQUIRE(ztd::contains(rand_str_string, "i"));
    REQUIRE(ztd::contains(rand_str_string, "j"));
    REQUIRE(ztd::contains(rand_str_string, "k"));
    REQUIRE(ztd::contains(rand_str_string, "l"));
    REQUIRE(ztd::contains(rand_str_string, "m"));
    REQUIRE(ztd::contains(rand_str_string, "n"));
    REQUIRE(ztd::contains(rand_str_string, "o"));
    REQUIRE(ztd::contains(rand_str_string, "p"));
    REQUIRE(ztd::contains(rand_str_string, "q"));
    REQUIRE(ztd::contains(rand_str_string, "r"));
    REQUIRE(ztd::contains(rand_str_string, "s"));
    REQUIRE(ztd::contains(rand_str_string, "t"));
    REQUIRE(ztd::contains(rand_str_string, "u"));
    REQUIRE(ztd::contains(rand_str_string, "v"));
    REQUIRE(ztd::contains(rand_str_string, "w"));
    REQUIRE(ztd::contains(rand_str_string, "x"));
    REQUIRE(ztd::contains(rand_str_string, "y"));
    REQUIRE(ztd::contains(rand_str_string, "z"));
    /////////////////////////////////////////////
    REQUIRE(ztd::contains(rand_str_string, "A"));
    REQUIRE(ztd::contains(rand_str_string, "B"));
    REQUIRE(ztd::contains(rand_str_string, "C"));
    REQUIRE(ztd::contains(rand_str_string, "D"));
    REQUIRE(ztd::contains(rand_str_string, "E"));
    REQUIRE(ztd::contains(rand_str_string, "F"));
    REQUIRE(ztd::contains(rand_str_string, "G"));
    REQUIRE(ztd::contains(rand_str_string, "H"));
    REQUIRE(ztd::contains(rand_str_string, "I"));
    REQUIRE(ztd::contains(rand_str_string, "J"));
    REQUIRE(ztd::contains(rand_str_string, "K"));
    REQUIRE(ztd::contains(rand_str_string, "L"));
    REQUIRE(ztd::contains(rand_str_string, "M"));
    REQUIRE(ztd::contains(rand_str_string, "N"));
    REQUIRE(ztd::contains(rand_str_string, "O"));
    REQUIRE(ztd::contains(rand_str_string, "P"));
    REQUIRE(ztd::contains(rand_str_string, "Q"));
    REQUIRE(ztd::contains(rand_str_string, "R"));
    REQUIRE(ztd::contains(rand_str_string, "S"));
    REQUIRE(ztd::contains(rand_str_string, "T"));
    REQUIRE(ztd::contains(rand_str_string, "U"));
    REQUIRE(ztd::contains(rand_str_string, "V"));
    REQUIRE(ztd::contains(rand_str_string, "W"));
    REQUIRE(ztd::contains(rand_str_string, "X"));
    REQUIRE(ztd::contains(rand_str_string, "Y"));
    REQUIRE(ztd::contains(rand_str_string, "Z"));
}
