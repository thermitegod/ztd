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

TEST(sort, alphanumeric)
{
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("", "") == 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("", "a") < 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("a", "") > 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("a", "a") == 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("", "9") < 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("9", "") > 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("1", "1") == 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("1", "2") < 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("3", "2") > 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("a1", "a1") == 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("a1", "a2") < 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("a2", "a1") > 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("a1a2", "a1a3") < 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("a1a2", "a1a0") > 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("134", "122") > 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("12a3", "12a3") == 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("12a1", "12a0") > 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("12a1", "12a2") < 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("a", "aa") < 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("aaa", "aa") > 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("Alpha 2", "Alpha 2") == 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("Alpha 2", "Alpha 2A") < 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("Alpha 2 B", "Alpha 2") > 0);

    const std::string str = "Alpha 2";
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric(str, "Alpha 2") == 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric(str, "Alpha 2A") < 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric("Alpha 2 B", str) > 0);

    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric(str, strdup("Alpha 2")) == 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric(str, strdup("Alpha 2A")) < 0);
    GTEST_ASSERT_TRUE(ztd::sort::alphanumeric(strdup("Alpha 2 B"), str) > 0);
}

TEST(sort, alphanumeric__vector__single_letter)
{
    std::vector<std::string> vec = {"e", "d", "c", "b", "a"};
    const std::vector<std::string> result_wanted{"a", "b", "c", "d", "e"};

    std::ranges::sort(vec, ztd::sort::alphanumeric);

    GTEST_ASSERT_EQ(vec, result_wanted);
}

#if 0
TEST(sort,alphanumeric__vector__floating)
{
    std::vector<std::string> vec = {"file10.txt", "file1.5.txt", "file1.txt", "file5.txt"};
    const std::vector<std::string> result_wanted = {"file1.txt", "file1.5.txt", "file5.txt", "file10.txt"};

    std::ranges::sort(vec, ztd::sort::alphanumeric);

    GTEST_ASSERT_EQ(vec , result_wanted);
}
#endif
