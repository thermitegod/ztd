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
#include <array>

#include "../../src/ztd.hxx"

TEST(array_templates, contains__string)
{
    const std::vector<std::string> arr1{"foo", "bar", "baz"};

    const std::string bar = "bar";
    const std::string buz = "buz";

    ASSERT_TRUE(ztd::contains(arr1, bar));
    ASSERT_FALSE(ztd::contains(arr1, buz));
}

TEST(array_templates, contains__int)
{
    const std::vector<int> arr2{1, 2, 3, 4, 5};

    int five = 5;
    int nine = 9;

    ASSERT_TRUE(ztd::contains(arr2, five));
    ASSERT_FALSE(ztd::contains(arr2, nine));
}
