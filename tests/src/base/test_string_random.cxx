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

    GTEST_ASSERT_TRUE(rand_hex_string.size() == rand_hex_string_size);

    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "0"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "1"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "2"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "3"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "4"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "5"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "6"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "7"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "8"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "9"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "A"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "B"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "C"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "D"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "E"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_hex_string, "F"));
}

TEST(string_random, randstr)
{
    std::srand(std::time(nullptr));

    constexpr std::size_t rand_str_string_size = 1000;

    // With a size this big all chars should be in there at least once
    const std::string rand_str_string = ztd::randstr(rand_str_string_size);

    GTEST_ASSERT_TRUE(rand_str_string.size() == rand_str_string_size);

    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "0"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "1"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "2"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "3"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "4"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "5"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "6"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "7"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "8"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "9"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "0"));

    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "a"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "b"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "c"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "d"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "e"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "f"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "g"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "h"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "i"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "j"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "k"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "l"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "m"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "n"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "o"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "p"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "q"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "r"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "s"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "t"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "u"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "v"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "w"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "x"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "y"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "z"));

    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "A"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "B"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "C"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "D"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "E"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "F"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "G"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "H"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "I"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "J"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "K"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "L"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "M"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "N"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "O"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "P"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "Q"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "R"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "S"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "T"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "U"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "V"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "W"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "X"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "Y"));
    GTEST_ASSERT_TRUE(ztd::contains(rand_str_string, "Z"));
}
