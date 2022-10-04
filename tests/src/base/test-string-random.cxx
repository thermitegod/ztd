/**
 * Copyright (C) 2022 Brandon Zorn <brandonzorn@cock.li>
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

#include <gtest/gtest.h>

#include <string>
#include <chrono>
#include <cstdlib>

#include "ztd/ztd.hxx"

TEST(string_random, randhex)
{
    std::srand(std::time(nullptr));

    constexpr std::size_t rand_hex_string_size = 200;

    // With a size this big all chars should be in there at least once
    const std::string rand_hex_string = ztd::randhex(rand_hex_string_size);

    ASSERT_TRUE(rand_hex_string.size() == rand_hex_string_size);

    ASSERT_TRUE(ztd::contains(rand_hex_string, "0"));
    ASSERT_TRUE(ztd::contains(rand_hex_string, "1"));
    ASSERT_TRUE(ztd::contains(rand_hex_string, "2"));
    ASSERT_TRUE(ztd::contains(rand_hex_string, "3"));
    ASSERT_TRUE(ztd::contains(rand_hex_string, "4"));
    ASSERT_TRUE(ztd::contains(rand_hex_string, "5"));
    ASSERT_TRUE(ztd::contains(rand_hex_string, "6"));
    ASSERT_TRUE(ztd::contains(rand_hex_string, "7"));
    ASSERT_TRUE(ztd::contains(rand_hex_string, "8"));
    ASSERT_TRUE(ztd::contains(rand_hex_string, "9"));
    ASSERT_TRUE(ztd::contains(rand_hex_string, "a"));
    ASSERT_TRUE(ztd::contains(rand_hex_string, "b"));
    ASSERT_TRUE(ztd::contains(rand_hex_string, "c"));
    ASSERT_TRUE(ztd::contains(rand_hex_string, "d"));
    ASSERT_TRUE(ztd::contains(rand_hex_string, "e"));
    ASSERT_TRUE(ztd::contains(rand_hex_string, "f"));
}

TEST(string_random, randstr)
{
    std::srand(std::time(nullptr));

    constexpr std::size_t rand_str_string_size = 1000;

    // With a size this big all chars should be in there at least once
    const std::string rand_str_string = ztd::randstr(rand_str_string_size);

    ASSERT_TRUE(rand_str_string.size() == rand_str_string_size);

    ASSERT_TRUE(ztd::contains(rand_str_string, "0"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "1"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "2"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "3"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "4"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "5"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "6"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "7"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "8"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "9"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "0"));

    ASSERT_TRUE(ztd::contains(rand_str_string, "a"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "b"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "c"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "d"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "e"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "f"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "g"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "h"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "i"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "j"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "k"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "l"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "m"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "n"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "o"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "p"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "q"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "r"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "s"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "t"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "u"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "v"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "w"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "x"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "y"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "z"));

    ASSERT_TRUE(ztd::contains(rand_str_string, "A"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "B"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "C"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "D"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "E"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "F"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "G"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "H"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "I"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "J"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "K"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "L"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "M"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "N"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "O"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "P"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "Q"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "R"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "S"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "T"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "U"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "V"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "W"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "X"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "Y"));
    ASSERT_TRUE(ztd::contains(rand_str_string, "Z"));
}
