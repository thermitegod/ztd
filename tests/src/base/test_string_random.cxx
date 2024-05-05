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

#include <gtest/gtest.h>

#include <string>
#include <chrono>
#include <cstdlib>

#include "ztd/detail/string_random.hxx"

/**
 * randhex
 */

TEST(string_random, randhex)
{
    constexpr std::size_t rand_hex_string_size = 200;

    // With a size this big all chars should be in there at least once
    const std::string rand_hex_string = ztd::randhex(rand_hex_string_size);

    EXPECT_EQ(rand_hex_string.size(), rand_hex_string_size);

    EXPECT_TRUE(rand_hex_string.contains("0"));
    EXPECT_TRUE(rand_hex_string.contains("1"));
    EXPECT_TRUE(rand_hex_string.contains("2"));
    EXPECT_TRUE(rand_hex_string.contains("3"));
    EXPECT_TRUE(rand_hex_string.contains("4"));
    EXPECT_TRUE(rand_hex_string.contains("5"));
    EXPECT_TRUE(rand_hex_string.contains("6"));
    EXPECT_TRUE(rand_hex_string.contains("7"));
    EXPECT_TRUE(rand_hex_string.contains("8"));
    EXPECT_TRUE(rand_hex_string.contains("9"));
    EXPECT_TRUE(rand_hex_string.contains("A"));
    EXPECT_TRUE(rand_hex_string.contains("B"));
    EXPECT_TRUE(rand_hex_string.contains("C"));
    EXPECT_TRUE(rand_hex_string.contains("D"));
    EXPECT_TRUE(rand_hex_string.contains("E"));
    EXPECT_TRUE(rand_hex_string.contains("F"));
    // Check only hex chars are used
    EXPECT_FALSE(rand_hex_string.contains("G"));
    EXPECT_FALSE(rand_hex_string.contains("H"));
    EXPECT_FALSE(rand_hex_string.contains("I"));
    EXPECT_FALSE(rand_hex_string.contains("J"));
    EXPECT_FALSE(rand_hex_string.contains("K"));
    EXPECT_FALSE(rand_hex_string.contains("L"));
    EXPECT_FALSE(rand_hex_string.contains("M"));
    EXPECT_FALSE(rand_hex_string.contains("N"));
    EXPECT_FALSE(rand_hex_string.contains("O"));
    EXPECT_FALSE(rand_hex_string.contains("P"));
    EXPECT_FALSE(rand_hex_string.contains("Q"));
    EXPECT_FALSE(rand_hex_string.contains("R"));
    EXPECT_FALSE(rand_hex_string.contains("S"));
    EXPECT_FALSE(rand_hex_string.contains("T"));
    EXPECT_FALSE(rand_hex_string.contains("U"));
    EXPECT_FALSE(rand_hex_string.contains("V"));
    EXPECT_FALSE(rand_hex_string.contains("W"));
    EXPECT_FALSE(rand_hex_string.contains("X"));
    EXPECT_FALSE(rand_hex_string.contains("Y"));
    EXPECT_FALSE(rand_hex_string.contains("Z"));

    EXPECT_FALSE(rand_hex_string.contains("a"));
    EXPECT_FALSE(rand_hex_string.contains("b"));
    EXPECT_FALSE(rand_hex_string.contains("c"));
    EXPECT_FALSE(rand_hex_string.contains("d"));
    EXPECT_FALSE(rand_hex_string.contains("e"));
    EXPECT_FALSE(rand_hex_string.contains("f"));
    EXPECT_FALSE(rand_hex_string.contains("g"));
    EXPECT_FALSE(rand_hex_string.contains("h"));
    EXPECT_FALSE(rand_hex_string.contains("i"));
    EXPECT_FALSE(rand_hex_string.contains("j"));
    EXPECT_FALSE(rand_hex_string.contains("k"));
    EXPECT_FALSE(rand_hex_string.contains("l"));
    EXPECT_FALSE(rand_hex_string.contains("m"));
    EXPECT_FALSE(rand_hex_string.contains("n"));
    EXPECT_FALSE(rand_hex_string.contains("o"));
    EXPECT_FALSE(rand_hex_string.contains("p"));
    EXPECT_FALSE(rand_hex_string.contains("q"));
    EXPECT_FALSE(rand_hex_string.contains("r"));
    EXPECT_FALSE(rand_hex_string.contains("s"));
    EXPECT_FALSE(rand_hex_string.contains("t"));
    EXPECT_FALSE(rand_hex_string.contains("u"));
    EXPECT_FALSE(rand_hex_string.contains("v"));
    EXPECT_FALSE(rand_hex_string.contains("w"));
    EXPECT_FALSE(rand_hex_string.contains("x"));
    EXPECT_FALSE(rand_hex_string.contains("y"));
    EXPECT_FALSE(rand_hex_string.contains("z"));
}

TEST(string_random, randhex__api_default_size)
{
    const std::string rand_hex_string = ztd::randhex();

    EXPECT_EQ(rand_hex_string.size(), 10);
}

/**
 * randstr
 */

TEST(string_random, randstr)
{
    constexpr std::size_t rand_str_string_size = 1000;

    // With a size this big all chars should be in there at least once
    const std::string rand_str_string = ztd::randstr(rand_str_string_size);

    EXPECT_EQ(rand_str_string.size(), rand_str_string_size);

    EXPECT_TRUE(rand_str_string.contains("0"));
    EXPECT_TRUE(rand_str_string.contains("1"));
    EXPECT_TRUE(rand_str_string.contains("2"));
    EXPECT_TRUE(rand_str_string.contains("3"));
    EXPECT_TRUE(rand_str_string.contains("4"));
    EXPECT_TRUE(rand_str_string.contains("5"));
    EXPECT_TRUE(rand_str_string.contains("6"));
    EXPECT_TRUE(rand_str_string.contains("7"));
    EXPECT_TRUE(rand_str_string.contains("8"));
    EXPECT_TRUE(rand_str_string.contains("9"));
    EXPECT_TRUE(rand_str_string.contains("0"));

    EXPECT_TRUE(rand_str_string.contains("a"));
    EXPECT_TRUE(rand_str_string.contains("b"));
    EXPECT_TRUE(rand_str_string.contains("c"));
    EXPECT_TRUE(rand_str_string.contains("d"));
    EXPECT_TRUE(rand_str_string.contains("e"));
    EXPECT_TRUE(rand_str_string.contains("f"));
    EXPECT_TRUE(rand_str_string.contains("g"));
    EXPECT_TRUE(rand_str_string.contains("h"));
    EXPECT_TRUE(rand_str_string.contains("i"));
    EXPECT_TRUE(rand_str_string.contains("j"));
    EXPECT_TRUE(rand_str_string.contains("k"));
    EXPECT_TRUE(rand_str_string.contains("l"));
    EXPECT_TRUE(rand_str_string.contains("m"));
    EXPECT_TRUE(rand_str_string.contains("n"));
    EXPECT_TRUE(rand_str_string.contains("o"));
    EXPECT_TRUE(rand_str_string.contains("p"));
    EXPECT_TRUE(rand_str_string.contains("q"));
    EXPECT_TRUE(rand_str_string.contains("r"));
    EXPECT_TRUE(rand_str_string.contains("s"));
    EXPECT_TRUE(rand_str_string.contains("t"));
    EXPECT_TRUE(rand_str_string.contains("u"));
    EXPECT_TRUE(rand_str_string.contains("v"));
    EXPECT_TRUE(rand_str_string.contains("w"));
    EXPECT_TRUE(rand_str_string.contains("x"));
    EXPECT_TRUE(rand_str_string.contains("y"));
    EXPECT_TRUE(rand_str_string.contains("z"));

    EXPECT_TRUE(rand_str_string.contains("A"));
    EXPECT_TRUE(rand_str_string.contains("B"));
    EXPECT_TRUE(rand_str_string.contains("C"));
    EXPECT_TRUE(rand_str_string.contains("D"));
    EXPECT_TRUE(rand_str_string.contains("E"));
    EXPECT_TRUE(rand_str_string.contains("F"));
    EXPECT_TRUE(rand_str_string.contains("G"));
    EXPECT_TRUE(rand_str_string.contains("H"));
    EXPECT_TRUE(rand_str_string.contains("I"));
    EXPECT_TRUE(rand_str_string.contains("J"));
    EXPECT_TRUE(rand_str_string.contains("K"));
    EXPECT_TRUE(rand_str_string.contains("L"));
    EXPECT_TRUE(rand_str_string.contains("M"));
    EXPECT_TRUE(rand_str_string.contains("N"));
    EXPECT_TRUE(rand_str_string.contains("O"));
    EXPECT_TRUE(rand_str_string.contains("P"));
    EXPECT_TRUE(rand_str_string.contains("Q"));
    EXPECT_TRUE(rand_str_string.contains("R"));
    EXPECT_TRUE(rand_str_string.contains("S"));
    EXPECT_TRUE(rand_str_string.contains("T"));
    EXPECT_TRUE(rand_str_string.contains("U"));
    EXPECT_TRUE(rand_str_string.contains("V"));
    EXPECT_TRUE(rand_str_string.contains("W"));
    EXPECT_TRUE(rand_str_string.contains("X"));
    EXPECT_TRUE(rand_str_string.contains("Y"));
    EXPECT_TRUE(rand_str_string.contains("Z"));
}

TEST(string_random, randstr__api_default_size)
{
    const std::string rand_str_string = ztd::randstr();

    EXPECT_EQ(rand_str_string.size(), 10);
}
