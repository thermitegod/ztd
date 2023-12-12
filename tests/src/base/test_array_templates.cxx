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

#if (ZTD_VERSION == 1)

#include <gtest/gtest.h>

#include <string>
#include <string_view>

#include <array>

#include "ztd/ztd.hxx"

/**
 * array contains Template
 */
TEST(array_templates, contains__template_string)
{
    const std::array<const char*, 3> arr{"foo", "bar", "baz"};

    const char* bar = "bar";
    const char* buz = "buz";

    EXPECT_TRUE(ztd::contains(arr, bar));
    EXPECT_FALSE(ztd::contains(arr, buz));
}

TEST(array_templates, contains__template_int)
{
    const std::array<int, 5> arr{1, 2, 3, 4, 5};

    int five = 5;
    int nine = 9;

    EXPECT_TRUE(ztd::contains(arr, five));
    EXPECT_FALSE(ztd::contains(arr, nine));
}

TEST(array_templates, contains__template_double)
{
    const std::array<double, 5> arr{1.0, 2.0, 3.0, 4.0, 5.0};

    double five = 5.0;
    double nine = 9.0;

    EXPECT_TRUE(ztd::contains(arr, five));
    EXPECT_FALSE(ztd::contains(arr, nine));
}

#endif
