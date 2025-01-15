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

#include <filesystem>
#include <string>
#include <vector>

#include <doctest/doctest.h>

#include "ztd/detail/vector_templates.hxx"

TEST_SUITE("std::vector templates" * doctest::description(""))
{
    TEST_CASE("ztd::move")
    {
        std::vector<std::string> vec1{"foo", "bar", "baz"};

        const std::vector<std::string> result_wanted{"bar", "foo", "baz"};
        ztd::move(vec1, 1, 0);

        CHECK_EQ(vec1, result_wanted);
    }

    TEST_CASE("ztd::index")
    {
        const std::vector<std::string> vec1{"foo", "bar", "baz"};

        const std::string bar = "bar";
        const std::size_t index = ztd::index(vec1, bar);

        CHECK_EQ(index, 1);
    }

    TEST_CASE("ztd::merge")
    {
        SUBCASE("vector<string>")
        {
            SUBCASE("2")
            {
                const std::vector<std::string> vec1{"foo", "bar"};
                const std::vector<std::string> vec2{"foo", "baz", "buz"};

                const std::vector<std::string> result_wanted{"foo", "bar", "baz", "buz"};
                const std::vector<std::string> result = ztd::merge(vec1, vec2);

                CHECK_EQ(result, result_wanted);
            }

            SUBCASE("3")
            {
                const std::vector<std::string> vec1{"foo", "bar"};
                const std::vector<std::string> vec2{"foo", "baz", "buz"};
                const std::vector<std::string> vec3{"foo", "baz", "buz", "buk"};

                const std::vector<std::string> result_wanted{"foo", "bar", "baz", "buz", "buk"};
                const std::vector<std::string> result = ztd::merge(vec1, vec2, vec3);

                CHECK_EQ(result, result_wanted);
            }

            SUBCASE("4")
            {
                const std::vector<std::string> vec1{"foo", "bar"};
                const std::vector<std::string> vec2{"foo", "baz", "buz"};
                const std::vector<std::string> vec3{"foo", "baz", "buz", "buk"};
                const std::vector<std::string> vec4{"foo", "baz", "buz", "buk", "bur"};

                const std::vector<std::string> result_wanted{"foo",
                                                             "bar",
                                                             "baz",
                                                             "buz",
                                                             "buk",
                                                             "bur"};
                const std::vector<std::string> result = ztd::merge(vec1, vec2, vec3, vec4);

                CHECK_EQ(result, result_wanted);
            }
        }

        SUBCASE("vector<int>")
        {
            SUBCASE("2")
            {
                const std::vector<int> vec1{1, 2};
                const std::vector<int> vec2{1, 2, 3, 4};

                const std::vector<int> result_wanted{1, 2, 3, 4};
                const std::vector<int> result = ztd::merge(vec1, vec2);

                CHECK_EQ(result, result_wanted);
            }

            SUBCASE("3")
            {
                const std::vector<int> vec1{1, 2};
                const std::vector<int> vec2{1, 2, 3, 4};
                const std::vector<int> vec3{1, 2, 3, 4, 5, 6};

                const std::vector<int> result_wanted{1, 2, 3, 4, 5, 6};
                const std::vector<int> result = ztd::merge(vec1, vec2, vec3);

                CHECK_EQ(result, result_wanted);
            }

            SUBCASE("4")
            {
                const std::vector<int> vec1{1, 2};
                const std::vector<int> vec2{1, 2, 3, 4};
                const std::vector<int> vec3{1, 2, 3, 4, 5, 6};
                const std::vector<int> vec4{1, 2, 3, 4, 5, 6, 7, 8};

                const std::vector<int> result_wanted{1, 2, 3, 4, 5, 6, 7, 8};
                const std::vector<int> result = ztd::merge(vec1, vec2, vec3, vec4);

                CHECK_EQ(result, result_wanted);
            }
        }
    }

    TEST_CASE("ztd::dedup")
    {
        SUBCASE("vector<string>")
        {
            const std::vector<std::string> vec1{"a", "a", "b", "b", "c", "a"};

            const std::vector<std::string> result_wanted{"a", "b", "c"};
            const std::vector<std::string> result = ztd::dedup(vec1);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("vector<int>")
        {
            std::vector<int> vec1{1, 1, 2, 3, 2};

            const std::vector<int> result_wanted{1, 2, 3};
            const std::vector<int> result = ztd::dedup(vec1);

            CHECK_EQ(result, result_wanted);
        }
    }

    TEST_CASE("ztd::prune")
    {
        SUBCASE("vector<string>")
        {
            const std::vector<std::string> vec1{"foo", "bar", "baz"};
            const std::vector<std::string> vec2{"bar", "baz"};

            const std::vector<std::string> result_wanted{"foo"};
            const std::vector<std::string> result = ztd::prune(vec1, vec2);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("vector<filesystem::path>")
        {
            const std::vector<std::filesystem::path> vec1{"/home/user/new1",
                                                          "/home/user/new2",
                                                          "/home/user/new3"};
            const std::vector<std::filesystem::path> vec2{"/home/user/new2", "/home/user/new3"};

            const std::vector<std::filesystem::path> result_wanted{"/home/user/new1"};
            const std::vector<std::filesystem::path> result = ztd::prune(vec1, vec2);

            CHECK_EQ(result, result_wanted);
        }

        SUBCASE("vector<int>")
        {
            const std::vector<int> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9};
            const std::vector<int> vec2{2, 4, 6, 8};

            const std::vector<int> result_wanted{1, 3, 5, 7, 9};
            const std::vector<int> result = ztd::prune(vec1, vec2);

            CHECK_EQ(result, result_wanted);
        }
    }
}
