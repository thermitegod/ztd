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
#include <vector>

#include "ztd/ztd.hxx"

TEST(vector_templates, move)
{
    std::vector<std::string> vec1{"foo", "bar", "baz"};

    const std::vector<std::string> result_wanted{"bar", "foo", "baz"};
    ztd::move(vec1, 1, 0);

    EXPECT_EQ(vec1, result_wanted);
}

TEST(vector_templates, index)
{
    const std::vector<std::string> vec1{"foo", "bar", "baz"};

    const std::string bar = "bar";
    const std::size_t index = ztd::index(vec1, bar);

    EXPECT_EQ(index, 1);
}

TEST(vector_templates, contains__vector_T)
{
    const std::vector<std::string> vec1{"foo", "bar", "baz"};

    const std::string bar = "bar";
    const std::string buz = "buz";

    EXPECT_TRUE(ztd::contains(vec1, bar));
    EXPECT_FALSE(ztd::contains(vec1, buz));
}

TEST(vector_templates, remove)
{
    std::vector<std::string> vec1{"foo", "bar", "baz"};

    const std::vector<std::string> result_wanted{"foo", "baz"};
    const std::string bar = "bar";
    ztd::remove(vec1, bar);

    EXPECT_EQ(vec1, result_wanted);
}

TEST(vector_templates, merge__2_string)
{
    const std::vector<std::string> vec1{"foo", "bar"};
    const std::vector<std::string> vec2{"foo", "baz", "buz"};

    const std::vector<std::string> result_wanted{"foo", "bar", "baz", "buz"};
    const std::vector<std::string> result = ztd::merge(vec1, vec2);

    EXPECT_EQ(result, result_wanted);
}

TEST(vector_templates, merge__3_string)
{
    const std::vector<std::string> vec1{"foo", "bar"};
    const std::vector<std::string> vec2{"foo", "baz", "buz"};
    const std::vector<std::string> vec3{"foo", "baz", "buz", "buk"};

    const std::vector<std::string> result_wanted{"foo", "bar", "baz", "buz", "buk"};
    const std::vector<std::string> result = ztd::merge(vec1, vec2, vec3);

    EXPECT_EQ(result, result_wanted);
}

TEST(vector_templates, merge__4_string)
{
    const std::vector<std::string> vec1{"foo", "bar"};
    const std::vector<std::string> vec2{"foo", "baz", "buz"};
    const std::vector<std::string> vec3{"foo", "baz", "buz", "buk"};
    const std::vector<std::string> vec4{"foo", "baz", "buz", "buk", "bur"};

    const std::vector<std::string> result_wanted{"foo", "bar", "baz", "buz", "buk", "bur"};
    const std::vector<std::string> result = ztd::merge(vec1, vec2, vec3, vec4);

    EXPECT_EQ(result, result_wanted);
}

TEST(vector_templates, merge__2_int)
{
    const std::vector<int> vec1{1, 2};
    const std::vector<int> vec2{1, 2, 3, 4};

    const std::vector<int> result_wanted{1, 2, 3, 4};
    const std::vector<int> result = ztd::merge(vec1, vec2);

    EXPECT_EQ(result, result_wanted);
}

TEST(vector_templates, merge__3_int)
{
    const std::vector<int> vec1{1, 2};
    const std::vector<int> vec2{1, 2, 3, 4};
    const std::vector<int> vec3{1, 2, 3, 4, 5, 6};

    const std::vector<int> result_wanted{1, 2, 3, 4, 5, 6};
    const std::vector<int> result = ztd::merge(vec1, vec2, vec3);

    EXPECT_EQ(result, result_wanted);
}

TEST(vector_templates, merge__4_int)
{
    const std::vector<int> vec1{1, 2};
    const std::vector<int> vec2{1, 2, 3, 4};
    const std::vector<int> vec3{1, 2, 3, 4, 5, 6};
    const std::vector<int> vec4{1, 2, 3, 4, 5, 6, 7, 8};

    const std::vector<int> result_wanted{1, 2, 3, 4, 5, 6, 7, 8};
    const std::vector<int> result = ztd::merge(vec1, vec2, vec3, vec4);

    EXPECT_EQ(result, result_wanted);
}

TEST(vector_templates, dedup__string)
{
    const std::vector<std::string> vec1{"a", "a", "b", "b", "c", "a"};

    const std::vector<std::string> result_wanted{"a", "b", "c"};
    const std::vector<std::string> result = ztd::dedup(vec1);

    EXPECT_EQ(result, result_wanted);
}

TEST(vector_templates, dedup__int)
{
    std::vector<int> vec1{1, 1, 2, 3, 2};

    const std::vector<int> result_wanted{1, 2, 3};
    const std::vector<int> result = ztd::dedup(vec1);

    EXPECT_EQ(result, result_wanted);
}

TEST(vector_templates, prune__string)
{
    const std::vector<std::string> vec1{"foo", "bar", "baz"};
    const std::vector<std::string> vec2{"bar", "baz"};

    const std::vector<std::string> result_wanted{"foo"};
    const std::vector<std::string> result = ztd::prune(vec1, vec2);

    EXPECT_EQ(result, result_wanted);
}

TEST(vector_templates, prune__string_filepaths)
{
    const std::vector<std::string> vec1{"/home/user/new1", "/home/user/new2", "/home/user/new3"};
    const std::vector<std::string> vec2{"/home/user/new2", "/home/user/new3"};

    const std::vector<std::string> result_wanted{"/home/user/new1"};
    const std::vector<std::string> result = ztd::prune(vec1, vec2);

    EXPECT_EQ(result, result_wanted);
}

TEST(vector_templates, prune__uint64)
{
    const std::vector<std::uint64_t> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::vector<std::uint64_t> vec2{2, 4, 6, 8};

    const std::vector<std::uint64_t> result_wanted{1, 3, 5, 7, 9};
    const std::vector<std::uint64_t> result = ztd::prune(vec1, vec2);

    EXPECT_EQ(result, result_wanted);
}
