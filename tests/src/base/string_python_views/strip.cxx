/**
 * Copyright (C) 2026 Brandon Zorn <brandonzorn@cock.li>
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

#include <string_view>

#include <doctest/doctest.h>

#include "ztd/detail/string_python_views.hxx"

TEST_CASE("ztd::views::lstrip")
{
    std::string_view str;
    std::string_view chars = " \r\n\t";
    std::string_view wanted;

    SUBCASE("empty") {}

    SUBCASE("lstrip")
    {
        str = "  a  ";
        wanted = "a  ";
    }

    SUBCASE("chars")
    {
        str = "z a z";
        chars = "z";
        wanted = " a z";
    }

    CHECK(ztd::views::lstrip(str, chars) == wanted);
}

TEST_CASE("ztd::views::rstrip")
{
    std::string_view str;
    std::string_view chars = " \r\n\t";
    std::string_view wanted;

    SUBCASE("empty") {}

    SUBCASE("rstrip")
    {
        str = "  a  ";
        wanted = "  a";
    }

    SUBCASE("chars")
    {
        str = "z a z";
        chars = "z";
        wanted = "z a ";
    }

    CHECK(ztd::views::rstrip(str, chars) == wanted);
}

TEST_CASE("ztd::views::strip")
{
    std::string_view str;
    std::string_view chars = " \r\n\t";
    std::string_view wanted;

    SUBCASE("empty") {}

    SUBCASE("strip")
    {
        str = "  a  ";
        wanted = "a";
    }

    SUBCASE("chars")
    {
        str = "z a z";
        chars = "z";
        wanted = " a ";
    }

    CHECK(ztd::views::strip(str, chars) == wanted);
}
