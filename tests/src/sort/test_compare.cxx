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

#include <vector>

#include <algorithm>
#include <ranges>

#include "ztd/ztd.hxx"

TEST(sort, compare)
{
    EXPECT_TRUE(ztd::sort::compare("", "") == 0);
    EXPECT_TRUE(ztd::sort::compare("", "a") < 0);
    EXPECT_TRUE(ztd::sort::compare("a", "") > 0);
    EXPECT_TRUE(ztd::sort::compare("a", "a") == 0);
    EXPECT_TRUE(ztd::sort::compare("", "9") < 0);
    EXPECT_TRUE(ztd::sort::compare("9", "") > 0);
    EXPECT_TRUE(ztd::sort::compare("1", "1") == 0);
    EXPECT_TRUE(ztd::sort::compare("1", "2") < 0);
    EXPECT_TRUE(ztd::sort::compare("3", "2") > 0);
    EXPECT_TRUE(ztd::sort::compare("a1", "a1") == 0);
    EXPECT_TRUE(ztd::sort::compare("a1", "a2") < 0);
    EXPECT_TRUE(ztd::sort::compare("a2", "a1") > 0);
    EXPECT_TRUE(ztd::sort::compare("a1a2", "a1a3") < 0);
    EXPECT_TRUE(ztd::sort::compare("a1a2", "a1a0") > 0);
    EXPECT_TRUE(ztd::sort::compare("134", "122") > 0);
    EXPECT_TRUE(ztd::sort::compare("12a3", "12a3") == 0);
    EXPECT_TRUE(ztd::sort::compare("12a1", "12a0") > 0);
    EXPECT_TRUE(ztd::sort::compare("12a1", "12a2") < 0);
    EXPECT_TRUE(ztd::sort::compare("a", "aa") < 0);
    EXPECT_TRUE(ztd::sort::compare("aaa", "aa") > 0);
    EXPECT_TRUE(ztd::sort::compare("Alpha 2", "Alpha 2") == 0);
    EXPECT_TRUE(ztd::sort::compare("Alpha 2", "Alpha 2A") < 0);
    EXPECT_TRUE(ztd::sort::compare("Alpha 2 B", "Alpha 2") > 0);

    const std::string str = "Alpha 2";
    EXPECT_TRUE(ztd::sort::compare(str, "Alpha 2") == 0);
    EXPECT_TRUE(ztd::sort::compare(str, "Alpha 2A") < 0);
    EXPECT_TRUE(ztd::sort::compare("Alpha 2 B", str) > 0);

    EXPECT_TRUE(ztd::sort::compare(str, strdup("Alpha 2")) == 0);
    EXPECT_TRUE(ztd::sort::compare(str, strdup("Alpha 2A")) < 0);
    EXPECT_TRUE(ztd::sort::compare(strdup("Alpha 2 B"), str) > 0);
}

TEST(sort, compare__vector__single_letter)
{
    std::vector<std::string> vec = {"e", "d", "c", "b", "a"};
    const std::vector<std::string> result_wanted{"a", "b", "c", "d", "e"};

    std::ranges::sort(vec, ztd::sort::compare);

    EXPECT_EQ(vec, result_wanted);
}
