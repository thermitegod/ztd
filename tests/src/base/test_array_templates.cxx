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
#include <string_view>

#include <array>

#include "ztd/ztd.hxx"

/**
 * array contains string
 */
TEST(array_templates, contains__string)
{
    const std::array<std::string, 3> arr{"foo", "bar", "baz"};

    const std::string bar = "bar";
    const std::string buz = "buz";

    GTEST_ASSERT_TRUE(ztd::contains(arr, bar));
    GTEST_ASSERT_FALSE(ztd::contains(arr, buz));
}

/**
 * array contains string_view
 */
TEST(array_templates, contains__string_view)
{
    using namespace std::literals::string_view_literals;

    static constexpr std::array<std::string_view, 3> arr{"foo"sv, "bar"sv, "baz"sv};

    static constexpr std::string_view bar = "bar"sv;
    static constexpr std::string_view buz = "buz"sv;

    GTEST_ASSERT_TRUE(ztd::contains(arr, bar));
    GTEST_ASSERT_FALSE(ztd::contains(arr, buz));
}

/**
 * array contains Template
 */
TEST(array_templates, contains__template_string)
{
    const std::array<const char*, 3> arr{"foo", "bar", "baz"};

    const char* bar = "bar";
    const char* buz = "buz";

    GTEST_ASSERT_TRUE(ztd::contains(arr, bar));
    GTEST_ASSERT_FALSE(ztd::contains(arr, buz));
}

TEST(array_templates, contains__template_int)
{
    const std::array<int, 5> arr{1, 2, 3, 4, 5};

    int five = 5;
    int nine = 9;

    GTEST_ASSERT_TRUE(ztd::contains(arr, five));
    GTEST_ASSERT_FALSE(ztd::contains(arr, nine));
}

TEST(array_templates, contains__template_double)
{
    const std::array<double, 5> arr{1.0, 2.0, 3.0, 4.0, 5.0};

    double five = 5.0;
    double nine = 9.0;

    GTEST_ASSERT_TRUE(ztd::contains(arr, five));
    GTEST_ASSERT_FALSE(ztd::contains(arr, nine));
}
