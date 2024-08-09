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

#include <string_view>

#include <ranges>

#include "ztd/detail/map.hxx"

/**
 * ztd::map
 */

TEST(map, map__i32_string_view)
{
    static constexpr auto map = ztd::map<i32, std::string_view, 10>{{
        {0, "zero"},
        {1, "one"},
        {2, "two"},
        {3, "three"},
        {4, "four"},
        {5, "five"},
        {6, "six"},
        {7, "seven"},
        {8, "eight"},
        {9, "nine"},
    }};

    EXPECT_EQ(map.at(0), "zero");
    EXPECT_EQ(map.at(1), "one");
    EXPECT_EQ(map.at(2), "two");
    EXPECT_EQ(map.at(3), "three");
    EXPECT_EQ(map.at(4), "four");
    EXPECT_EQ(map.at(5), "five");
    EXPECT_EQ(map.at(6), "six");
    EXPECT_EQ(map.at(7), "seven");
    EXPECT_EQ(map.at(8), "eight");
    EXPECT_EQ(map.at(9), "nine");
}

TEST(map, map__string_view_i32)
{
    static constexpr auto map = ztd::map<std::string_view, i32, 10>{{
        {"zero", 0},
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9},
    }};

    EXPECT_EQ(map.at("zero"), 0);
    EXPECT_EQ(map.at("one"), 1);
    EXPECT_EQ(map.at("two"), 2);
    EXPECT_EQ(map.at("three"), 3);
    EXPECT_EQ(map.at("four"), 4);
    EXPECT_EQ(map.at("five"), 5);
    EXPECT_EQ(map.at("six"), 6);
    EXPECT_EQ(map.at("seven"), 7);
    EXPECT_EQ(map.at("eight"), 8);
    EXPECT_EQ(map.at("nine"), 9);
}

TEST(map, map__enum_string_view)
{
    enum class num
    {
        zero,
        one,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
    };

    static constexpr auto map = ztd::map<num, std::string_view, 10>{{
        {num::zero, "zero"},
        {num::one, "one"},
        {num::two, "two"},
        {num::three, "three"},
        {num::four, "four"},
        {num::five, "five"},
        {num::six, "six"},
        {num::seven, "seven"},
        {num::eight, "eight"},
        {num::nine, "nine"},
    }};

    EXPECT_EQ(map.at(num::zero), "zero");
    EXPECT_EQ(map.at(num::one), "one");
    EXPECT_EQ(map.at(num::two), "two");
    EXPECT_EQ(map.at(num::three), "three");
    EXPECT_EQ(map.at(num::four), "four");
    EXPECT_EQ(map.at(num::five), "five");
    EXPECT_EQ(map.at(num::six), "six");
    EXPECT_EQ(map.at(num::seven), "seven");
    EXPECT_EQ(map.at(num::eight), "eight");
    EXPECT_EQ(map.at(num::nine), "nine");
}

TEST(map, map__enum_object)
{
    struct data
    {
        i32 d{};
    };

    enum class num
    {
        zero,
        one,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
    };

    static constexpr auto map = ztd::map<num, data, 10>{{
        {num::zero, {0}},
        {num::one, {1}},
        {num::two, {2}},
        {num::three, {3}},
        {num::four, {4}},
        {num::five, {5}},
        {num::six, {6}},
        {num::seven, {7}},
        {num::eight, {8}},
        {num::nine, {9}},
    }};

    EXPECT_EQ(map.at(num::zero).d, 0);
    EXPECT_EQ(map.at(num::one).d, 1);
    EXPECT_EQ(map.at(num::two).d, 2);
    EXPECT_EQ(map.at(num::three).d, 3);
    EXPECT_EQ(map.at(num::four).d, 4);
    EXPECT_EQ(map.at(num::five).d, 5);
    EXPECT_EQ(map.at(num::six).d, 6);
    EXPECT_EQ(map.at(num::seven).d, 7);
    EXPECT_EQ(map.at(num::eight).d, 8);
    EXPECT_EQ(map.at(num::nine).d, 9);
}

TEST(map, map__iterators)
{
    static constexpr auto map = ztd::map<i32, std::string_view, 10>{{
        {0, "zero"},
        {1, "one"},
        {2, "two"},
        {3, "three"},
        {4, "four"},
        {5, "five"},
        {6, "six"},
        {7, "seven"},
        {8, "eight"},
        {9, "nine"},
    }};

    usize c = 0;
    for (const auto& it : map)
    {
        EXPECT_EQ(it.second, map.at(c));
        c++;
    }

    for (const auto [idx, item] : std::views::enumerate(map))
    {
        EXPECT_EQ(item.second, map.at(idx));
    }
}

TEST(map, map__contains_enum)
{
    enum class letters
    {
        a,
        b,
        c,
        d,
        e,
    };

    static constexpr auto map = ztd::map<letters, i32, 3>{{
        {letters::a, 0},
        {letters::c, 0},
        {letters::e, 0},
    }};

    EXPECT_TRUE(map.contains(letters::a));
    EXPECT_TRUE(map.contains(letters::c));
    EXPECT_TRUE(map.contains(letters::e));

    EXPECT_FALSE(map.contains(letters::b));
    EXPECT_FALSE(map.contains(letters::d));
}

TEST(map, map__contains_string)
{
    static constexpr auto map = ztd::map<std::string_view, i32, 3>{{
        {"a", 0},
        {"c", 0},
        {"e", 0},
    }};

    EXPECT_TRUE(map.contains("a"));
    EXPECT_TRUE(map.contains("c"));
    EXPECT_TRUE(map.contains("e"));

    EXPECT_FALSE(map.contains("b"));
    EXPECT_FALSE(map.contains("d"));
}
