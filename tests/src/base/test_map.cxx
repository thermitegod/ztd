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

#include <ranges>
#include <string_view>

#include <doctest/doctest.h>

#include "ztd/detail/map.hxx"
#include "ztd/detail/types.hxx"

TEST_SUITE("ztd::map" * doctest::description(""))
{
    TEST_CASE("key: i32, value: string_view")
    {
        static constexpr auto map = ztd::map<u32, std::string_view, 10>{{
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

        CHECK_EQ(map.at(0), "zero");
        CHECK_EQ(map.at(1), "one");
        CHECK_EQ(map.at(2), "two");
        CHECK_EQ(map.at(3), "three");
        CHECK_EQ(map.at(4), "four");
        CHECK_EQ(map.at(5), "five");
        CHECK_EQ(map.at(6), "six");
        CHECK_EQ(map.at(7), "seven");
        CHECK_EQ(map.at(8), "eight");
        CHECK_EQ(map.at(9), "nine");
    }

    TEST_CASE("key: string_view, value: i32")
    {
        static constexpr auto map = ztd::map<std::string_view, u32, 10>{{
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

        CHECK_EQ(map.at("zero"), 0);
        CHECK_EQ(map.at("one"), 1);
        CHECK_EQ(map.at("two"), 2);
        CHECK_EQ(map.at("three"), 3);
        CHECK_EQ(map.at("four"), 4);
        CHECK_EQ(map.at("five"), 5);
        CHECK_EQ(map.at("six"), 6);
        CHECK_EQ(map.at("seven"), 7);
        CHECK_EQ(map.at("eight"), 8);
        CHECK_EQ(map.at("nine"), 9);
    }

    TEST_CASE("key: enum, value: string_view")
    {
        enum class num : std::uint8_t
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

        CHECK_EQ(map.at(num::zero), "zero");
        CHECK_EQ(map.at(num::one), "one");
        CHECK_EQ(map.at(num::two), "two");
        CHECK_EQ(map.at(num::three), "three");
        CHECK_EQ(map.at(num::four), "four");
        CHECK_EQ(map.at(num::five), "five");
        CHECK_EQ(map.at(num::six), "six");
        CHECK_EQ(map.at(num::seven), "seven");
        CHECK_EQ(map.at(num::eight), "eight");
        CHECK_EQ(map.at(num::nine), "nine");
    }

    TEST_CASE("key: enum, value: object")
    {
        struct data
        {
            u32 d{};
        };

        enum class num : std::uint8_t
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

        CHECK_EQ(map.at(num::zero).d, 0);
        CHECK_EQ(map.at(num::one).d, 1);
        CHECK_EQ(map.at(num::two).d, 2);
        CHECK_EQ(map.at(num::three).d, 3);
        CHECK_EQ(map.at(num::four).d, 4);
        CHECK_EQ(map.at(num::five).d, 5);
        CHECK_EQ(map.at(num::six).d, 6);
        CHECK_EQ(map.at(num::seven).d, 7);
        CHECK_EQ(map.at(num::eight).d, 8);
        CHECK_EQ(map.at(num::nine).d, 9);
    }

    TEST_CASE("iterators")
    {
        static constexpr auto map = ztd::map<u32, std::string_view, 10>{{
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
            CHECK_EQ(it.second, map.at(static_cast<u32>(c)));
            c++;
        }

        for (const auto [idx, item] : std::views::enumerate(map))
        {
            CHECK_EQ(item.second, map.at(static_cast<u32>(idx)));
        }
    }

    TEST_CASE(".contains() enum")
    {
        enum class letters : std::uint8_t
        {
            a,
            b,
            c,
            d,
            e,
        };

        static constexpr auto map = ztd::map<letters, u32, 3>{{
            {letters::a, 0},
            {letters::c, 0},
            {letters::e, 0},
        }};

        CHECK_EQ(map.contains(letters::a), true);
        CHECK_EQ(map.contains(letters::c), true);
        CHECK_EQ(map.contains(letters::e), true);

        CHECK_EQ(map.contains(letters::b), false);
        CHECK_EQ(map.contains(letters::d), false);
    }

    TEST_CASE(".contains() string")
    {
        static constexpr auto map = ztd::map<std::string_view, u32, 3>{{
            {"a", 0},
            {"c", 0},
            {"e", 0},
        }};

        CHECK_EQ(map.contains("a"), true);
        CHECK_EQ(map.contains("c"), true);
        CHECK_EQ(map.contains("e"), true);

        CHECK_EQ(map.contains("b"), false);
        CHECK_EQ(map.contains("d"), false);
    }
}
