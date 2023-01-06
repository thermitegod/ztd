/**
 * Copyright (C) 2023 Brandon Zorn <brandonzorn@cock.li>
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

/**
 * randhex
 */

TEST(string_random, randhex)
{
    constexpr std::size_t rand_hex_string_size = 200;

    // With a size this big all chars should be in there at least once
    const std::string rand_hex_string = ztd::randhex(rand_hex_string_size);

    EXPECT_TRUE(rand_hex_string.size() == rand_hex_string_size);

    EXPECT_TRUE(ztd::contains(rand_hex_string, "0"));
    EXPECT_TRUE(ztd::contains(rand_hex_string, "1"));
    EXPECT_TRUE(ztd::contains(rand_hex_string, "2"));
    EXPECT_TRUE(ztd::contains(rand_hex_string, "3"));
    EXPECT_TRUE(ztd::contains(rand_hex_string, "4"));
    EXPECT_TRUE(ztd::contains(rand_hex_string, "5"));
    EXPECT_TRUE(ztd::contains(rand_hex_string, "6"));
    EXPECT_TRUE(ztd::contains(rand_hex_string, "7"));
    EXPECT_TRUE(ztd::contains(rand_hex_string, "8"));
    EXPECT_TRUE(ztd::contains(rand_hex_string, "9"));
    EXPECT_TRUE(ztd::contains(rand_hex_string, "A"));
    EXPECT_TRUE(ztd::contains(rand_hex_string, "B"));
    EXPECT_TRUE(ztd::contains(rand_hex_string, "C"));
    EXPECT_TRUE(ztd::contains(rand_hex_string, "D"));
    EXPECT_TRUE(ztd::contains(rand_hex_string, "E"));
    EXPECT_TRUE(ztd::contains(rand_hex_string, "F"));
    // Check only hex chars are used
    EXPECT_FALSE(ztd::contains(rand_hex_string, "G"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "H"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "I"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "J"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "K"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "L"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "M"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "N"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "O"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "P"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "Q"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "R"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "S"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "T"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "U"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "V"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "W"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "X"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "Y"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "Z"));

    EXPECT_FALSE(ztd::contains(rand_hex_string, "a"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "b"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "c"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "d"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "e"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "f"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "g"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "h"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "i"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "j"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "k"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "l"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "m"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "n"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "o"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "p"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "q"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "r"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "s"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "t"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "u"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "v"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "w"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "x"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "y"));
    EXPECT_FALSE(ztd::contains(rand_hex_string, "z"));
}

TEST(string_random, randhex__api_default_size)
{
    const std::string rand_hex_string = ztd::randhex();

    EXPECT_TRUE(rand_hex_string.size() == 10);
}

/**
 * randstr
 */

TEST(string_random, randstr)
{
    constexpr std::size_t rand_str_string_size = 1000;

    // With a size this big all chars should be in there at least once
    const std::string rand_str_string = ztd::randstr(rand_str_string_size);

    EXPECT_TRUE(rand_str_string.size() == rand_str_string_size);

    EXPECT_TRUE(ztd::contains(rand_str_string, "0"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "1"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "2"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "3"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "4"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "5"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "6"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "7"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "8"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "9"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "0"));

    EXPECT_TRUE(ztd::contains(rand_str_string, "a"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "b"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "c"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "d"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "e"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "f"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "g"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "h"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "i"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "j"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "k"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "l"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "m"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "n"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "o"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "p"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "q"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "r"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "s"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "t"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "u"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "v"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "w"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "x"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "y"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "z"));

    EXPECT_TRUE(ztd::contains(rand_str_string, "A"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "B"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "C"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "D"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "E"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "F"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "G"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "H"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "I"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "J"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "K"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "L"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "M"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "N"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "O"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "P"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "Q"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "R"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "S"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "T"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "U"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "V"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "W"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "X"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "Y"));
    EXPECT_TRUE(ztd::contains(rand_str_string, "Z"));
}

TEST(string_random, randstr__api_default_size)
{
    const std::string rand_str_string = ztd::randstr();

    EXPECT_TRUE(rand_str_string.size() == 10);
}
