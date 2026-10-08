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

#include "ztd/detail/static_map.hxx"
#include "ztd/detail/types.hxx"

TEST_SUITE("ztd::static_map")
{
    TEST_CASE("key: i32, value: string_view")
    {
        static constexpr auto map = ztd::static_map<std::uint32_t, std::string_view, 10>{{
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

        SUBCASE(".at()")
        {
            CHECK(map.at(0) == "zero");
            CHECK(map.at(1) == "one");
            CHECK(map.at(2) == "two");
            CHECK(map.at(3) == "three");
            CHECK(map.at(4) == "four");
            CHECK(map.at(5) == "five");
            CHECK(map.at(6) == "six");
            CHECK(map.at(7) == "seven");
            CHECK(map.at(8) == "eight");
            CHECK(map.at(9) == "nine");
        }

        SUBCASE(".contains()")
        {
            CHECK(map.contains(0));
            CHECK(map.contains(1));
            CHECK(map.contains(2));
            CHECK(map.contains(3));
            CHECK(map.contains(4));
            CHECK(map.contains(5));
            CHECK(map.contains(6));
            CHECK(map.contains(7));
            CHECK(map.contains(8));
            CHECK(map.contains(9));

            CHECK_FALSE(map.contains(11));
            CHECK_FALSE(map.contains(12));
        }

        SUBCASE("iterators")
        {
            std::size_t c = 0;
            for (const auto& it : map)
            {
                CHECK(it.second == map.at(static_cast<std::uint32_t>(c)));
                c++;
            }

            for (const auto [idx, item] : std::views::enumerate(map))
            {
                CHECK(item.second == map.at(static_cast<std::uint32_t>(idx)));
            }
        }
    }

    TEST_CASE("key: string_view, value: i32")
    {
        static constexpr auto map = ztd::static_map<std::string_view, std::uint32_t, 10>{{
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

        SUBCASE(".at()")
        {
            CHECK(map.at("zero") == 0);
            CHECK(map.at("one") == 1);
            CHECK(map.at("two") == 2);
            CHECK(map.at("three") == 3);
            CHECK(map.at("four") == 4);
            CHECK(map.at("five") == 5);
            CHECK(map.at("six") == 6);
            CHECK(map.at("seven") == 7);
            CHECK(map.at("eight") == 8);
            CHECK(map.at("nine") == 9);
        }

        SUBCASE(".contains()")
        {
            CHECK(map.contains("zero"));
            CHECK(map.contains("one"));
            CHECK(map.contains("two"));
            CHECK(map.contains("three"));
            CHECK(map.contains("four"));
            CHECK(map.contains("five"));
            CHECK(map.contains("six"));
            CHECK(map.contains("seven"));
            CHECK(map.contains("eight"));
            CHECK(map.contains("nine"));

            CHECK_FALSE(map.contains("eleven"));
            CHECK_FALSE(map.contains("twelve"));
        }
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
            // Not in map
            eleven,
            twelve,
        };

        static constexpr auto map = ztd::static_map<num, std::string_view, 10>{{
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

        SUBCASE(".at()")
        {
            CHECK(map.at(num::zero) == "zero");
            CHECK(map.at(num::one) == "one");
            CHECK(map.at(num::two) == "two");
            CHECK(map.at(num::three) == "three");
            CHECK(map.at(num::four) == "four");
            CHECK(map.at(num::five) == "five");
            CHECK(map.at(num::six) == "six");
            CHECK(map.at(num::seven) == "seven");
            CHECK(map.at(num::eight) == "eight");
            CHECK(map.at(num::nine) == "nine");
        }

        SUBCASE(".contains()")
        {
            CHECK(map.contains(num::zero));
            CHECK(map.contains(num::one));
            CHECK(map.contains(num::two));
            CHECK(map.contains(num::three));
            CHECK(map.contains(num::four));
            CHECK(map.contains(num::five));
            CHECK(map.contains(num::six));
            CHECK(map.contains(num::seven));
            CHECK(map.contains(num::eight));
            CHECK(map.contains(num::nine));

            CHECK_FALSE(map.contains(num::eleven));
            CHECK_FALSE(map.contains(num::twelve));
        }
    }

    TEST_CASE("key: enum, value: object")
    {
        struct data
        {
            std::uint32_t d{};
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
            // Not in map
            eleven,
            twelve,
        };

        static constexpr auto map = ztd::static_map<num, data, 10>{{
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

        SUBCASE(".at()")
        {
            CHECK(map.at(num::zero).d == 0);
            CHECK(map.at(num::one).d == 1);
            CHECK(map.at(num::two).d == 2);
            CHECK(map.at(num::three).d == 3);
            CHECK(map.at(num::four).d == 4);
            CHECK(map.at(num::five).d == 5);
            CHECK(map.at(num::six).d == 6);
            CHECK(map.at(num::seven).d == 7);
            CHECK(map.at(num::eight).d == 8);
            CHECK(map.at(num::nine).d == 9);
        }

        SUBCASE(".contains()")
        {
            CHECK(map.contains(num::zero));
            CHECK(map.contains(num::one));
            CHECK(map.contains(num::two));
            CHECK(map.contains(num::three));
            CHECK(map.contains(num::four));
            CHECK(map.contains(num::five));
            CHECK(map.contains(num::six));
            CHECK(map.contains(num::seven));
            CHECK(map.contains(num::eight));
            CHECK(map.contains(num::nine));

            CHECK_FALSE(map.contains(num::eleven));
            CHECK_FALSE(map.contains(num::twelve));
        }
    }
}
