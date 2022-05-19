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

#include "../../src/ztd.hxx"

TEST(vector_templates, move)
{
    std::vector<std::string> vec1{"foo", "bar", "baz"};

    std::vector<std::string> result_wanted{"bar", "foo", "baz"};
    ztd::move(vec1, 1, 0);

    ASSERT_TRUE(vec1 == result_wanted);
}

TEST(vector_templates, index)
{
    std::vector<std::string> vec1{"foo", "bar", "baz"};

    std::string bar = "bar";
    std::size_t index = ztd::index(vec1, bar);

    ASSERT_TRUE(index == 1);
}

TEST(vector_templates, contains__vector_T)
{
    std::vector<std::string> vec1{"foo", "bar", "baz"};

    std::string bar = "bar";
    std::string buz = "buz";

    ASSERT_TRUE(ztd::contains(vec1, bar));
    ASSERT_FALSE(ztd::contains(vec1, buz));
}

TEST(vector_templates, remove)
{
    std::vector<std::string> vec1{"foo", "bar", "baz"};

    std::vector<std::string> result_wanted{"foo", "baz"};
    std::string bar = "bar";
    ztd::remove(vec1, bar);

    ASSERT_TRUE(vec1 == result_wanted);
}

TEST(vector_templates, merge__2_string)
{
    std::vector<std::string> vec1{"foo", "bar"};
    std::vector<std::string> vec2{"foo", "baz", "buz"};

    std::vector<std::string> result_wanted{"foo", "bar", "baz", "buz"};
    std::vector<std::string> result = ztd::merge(vec1, vec2);

    ASSERT_TRUE(result == result_wanted);
}

TEST(vector_templates, merge__3_string)
{
    std::vector<std::string> vec1{"foo", "bar"};
    std::vector<std::string> vec2{"foo", "baz", "buz"};
    std::vector<std::string> vec3{"foo", "baz", "buz", "buk"};

    std::vector<std::string> result_wanted{"foo", "bar", "baz", "buz", "buk"};
    std::vector<std::string> result = ztd::merge(vec1, vec2, vec3);

    ASSERT_TRUE(result == result_wanted);
}

TEST(vector_templates, merge__4_string)
{
    std::vector<std::string> vec1{"foo", "bar"};
    std::vector<std::string> vec2{"foo", "baz", "buz"};
    std::vector<std::string> vec3{"foo", "baz", "buz", "buk"};
    std::vector<std::string> vec4{"foo", "baz", "buz", "buk", "bur"};

    std::vector<std::string> result_wanted{"foo", "bar", "baz", "buz", "buk", "bur"};
    std::vector<std::string> result = ztd::merge(vec1, vec2, vec3, vec4);

    ASSERT_TRUE(result == result_wanted);
}

TEST(vector_templates, merge__2_int)
{
    std::vector<int> vec1{1, 2};
    std::vector<int> vec2{1, 2, 3, 4};

    std::vector<int> result_wanted{1, 2, 3, 4};
    std::vector<int> result = ztd::merge(vec1, vec2);

    ASSERT_TRUE(result == result_wanted);
}

TEST(vector_templates, merge__3_int)
{
    std::vector<int> vec1{1, 2};
    std::vector<int> vec2{1, 2, 3, 4};
    std::vector<int> vec3{1, 2, 3, 4, 5, 6};

    std::vector<int> result_wanted{1, 2, 3, 4, 5, 6};
    std::vector<int> result = ztd::merge(vec1, vec2, vec3);

    ASSERT_TRUE(result == result_wanted);
}

TEST(vector_templates, merge__4_int)
{
    std::vector<int> vec1{1, 2};
    std::vector<int> vec2{1, 2, 3, 4};
    std::vector<int> vec3{1, 2, 3, 4, 5, 6};
    std::vector<int> vec4{1, 2, 3, 4, 5, 6, 7, 8};

    std::vector<int> result_wanted{1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> result = ztd::merge(vec1, vec2, vec3, vec4);

    ASSERT_TRUE(result == result_wanted);
}

TEST(vector_templates, dedup__string)
{
    std::vector<std::string> vec1{"a", "a", "b", "b", "c", "a"};

    std::vector<std::string> result_wanted{"a", "b", "c"};
    std::vector<std::string> result = ztd::dedup(vec1);

    ASSERT_TRUE(result == result_wanted);
}

TEST(vector_templates, dedup__int)
{
    std::vector<int> vec1{1, 1, 2, 3, 2};

    std::vector<int> result_wanted{1, 2, 3};
    std::vector<int> result = ztd::dedup(vec1);

    ASSERT_TRUE(result == result_wanted);
}

TEST(vector_templates, prune__string)
{
    std::vector<std::string> vec1{"foo", "bar", "baz"};
    std::vector<std::string> vec2{"bar", "baz"};

    std::vector<std::string> result_wanted{"foo"};
    ztd::prune(vec1, vec2);

    ASSERT_TRUE(vec1 == result_wanted);
}

TEST(vector_templates, prune__string_filepaths)
{
    std::vector<std::string> vec1{"/home/user/new1", "/home/user/new2", "/home/user/new3"};
    std::vector<std::string> vec2{"/home/user/new2", "/home/user/new3"};

    std::vector<std::string> result_wanted{"/home/user/new1"};
    ztd::prune(vec1, vec2);

    ASSERT_TRUE(vec1 == result_wanted);
}

TEST(vector_templates, prune__uint64)
{
    std::vector<std::uint64_t> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<std::uint64_t> vec2{2, 4, 6, 8};

    std::vector<std::uint64_t> result_wanted{1, 3, 5, 7, 9};
    ztd::prune(vec1, vec2);

    ASSERT_TRUE(vec1 == result_wanted);
}
