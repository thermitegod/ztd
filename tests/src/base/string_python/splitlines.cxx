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
#include <vector>

#include <doctest/doctest.h>

#include "ztd/detail/string_python.hxx"

TEST_CASE("ztd::splitlines")
{
    std::string str;
    bool keepends = false;
    std::vector<std::string> wanted;

    SUBCASE("newline keepends")
    {
        str = "foo\nfoo";
        wanted = {"foo", "foo"};
    }

    SUBCASE("python example 1")
    {
        str = "ab c\n\nde fg\rkl\r\n";
        wanted = {"ab c", "", "de fg", "kl"};
    }

    SUBCASE("python example 2")
    {
        str = "ab c\n\nde fg\rkl\r\n";
        keepends = true;
        wanted = {"ab c\n", "\n", "de fg\r", "kl\r\n"};
    }

    CHECK_EQ(ztd::splitlines(str, keepends), wanted);
}
