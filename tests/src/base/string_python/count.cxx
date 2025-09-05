/**
 * Copyright (C) 2025 Brandon Zorn <brandonzorn@cock.li>
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

#include <string>
#include <string_view>

#include <doctest/doctest.h>

#include "ztd/detail/string_python.hxx"

TEST_CASE("ztd::count")
{
    SUBCASE("default")
    {
        std::string str;
        std::string find;
        ztd::u64 wanted = 0_u64;

        SUBCASE("count")
        {
            str = "zaaazaaaz";
            find = "a";
            wanted = 6_u64;
        }

        SUBCASE("multichar")
        {
            str = "zaaazaaaz";
            find = "aaa";
            wanted = 2_u64;
        }

        SUBCASE("zero")
        {
            str = "zaaazaaaz";
            find = "w";
            wanted = 0_u64;
        }

        SUBCASE("empty")
        {
            str = "";
            find = "a";
            wanted = 0_u64;
        }

        CHECK_EQ(ztd::count(str, find), wanted);
    }

    SUBCASE("char overload")
    {
        std::string str;
        char find = 0;
        ztd::u64 wanted = 0_u64;

        SUBCASE("char")
        {
            str = "zaaazaaaz";
            find = 'a';
            wanted = 6_u64;
        }

        SUBCASE("zero")
        {
            str = "zaaazaaaz";
            find = 'w';
            wanted = 0_u64;
        }

        SUBCASE("empty")
        {
            str = "";
            find = 'w';
            wanted = 0_u64;
        }

        CHECK_EQ(ztd::count(str, find), wanted);
    }

    SUBCASE("(start, end) overload")
    {
        std::string str;
        std::string find;
        ztd::usize start = 0_usize;
        ztd::usize end = 0_usize;
        ztd::u64 wanted = 0_u64;

        SUBCASE("empty")
        {
            str = "";
            find = "w";
            start = 0_usize;
            end = std::string_view::npos;
            wanted = 0_u64;
        }

        SUBCASE("start/end")
        {
            str = "zaaazaaaz";
            find = "a";
            start = 4_usize;
            end = 15_usize;
            wanted = 3_u64;
        }

        SUBCASE("start/end 2")
        {
            str = "zaaazaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
            find = "a";
            start = 0_usize;
            end = 4_usize;
            wanted = 3_u64;
        }

        SUBCASE("multichar")
        {
            str = "zaaazaaaz";
            find = "aaa";
            start = 4_usize;
            end = 15_usize;
            wanted = 1_u64;
        }

        SUBCASE("zero")
        {
            str = "zaaazaaaz";
            find = "w";
            start = 0_usize;
            end = 15_usize;
            wanted = 0_u64;
        }

        SUBCASE("same")
        {
            str = "aaaa";
            find = "a";
            start = 1_usize;
            end = 1_usize;
            wanted = 0_u64;
        }

        SUBCASE("large start")
        {
            str = "aaaa";
            find = "a";
            start = 3_usize;
            end = 2_usize;
            wanted = 0_u64;
        }

        SUBCASE("large end")
        {
            str = "aaaa";
            find = "a";
            start = 0_usize;
            end = 100_usize;
            wanted = 4_u64;
        }

        CHECK_EQ(ztd::count(str, find, start, end), wanted);
    }

    SUBCASE("(start, end) char overload")
    {
        std::string str;
        char find = 0;
        ztd::usize start = 0_usize;
        ztd::usize end = 0_usize;
        ztd::u64 wanted = 0_u64;

        SUBCASE("empty")
        {
            str = "";
            find = 'w';
            start = 0_usize;
            end = std::string_view::npos;
            wanted = 0_u64;
        }

        SUBCASE("start/end")
        {
            str = "zaaazaaaz";
            find = 'a';
            start = 4_usize;
            end = 15_usize;
            wanted = 3_u64;
        }

        SUBCASE("start/end 2")
        {
            str = "zaaazaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
            find = 'a';
            start = 0_usize;
            end = 4_usize;
            wanted = 3_u64;
        }

        SUBCASE("zero")
        {
            str = "zaaazaaaz";
            find = 'w';
            start = 0_usize;
            end = 15_usize;
            wanted = 0_u64;
        }

        SUBCASE("same")
        {
            str = "aaaa";
            find = 'a';
            start = 1_usize;
            end = 1_usize;
            wanted = 0_u64;
        }

        SUBCASE("large start")
        {
            str = "aaaa";
            find = 'a';
            start = 3_usize;
            end = 2_usize;
            wanted = 0_u64;
        }

        SUBCASE("large end")
        {
            str = "aaaa";
            find = 'a';
            start = 0_usize;
            end = 100_usize;
            wanted = 4_u64;
        }

        CHECK_EQ(ztd::count(str, find, start, end), wanted);
    }
}
