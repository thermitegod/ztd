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

#include <doctest/doctest.h>

#include "ztd/detail/string_python.hxx"

TEST_CASE("ztd::lower")
{
    std::string upper;
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("latin")
    {
        upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
        wanted = "abcdefghijklmnopqrstuvwxyz1234567890";
    }

    SUBCASE("special")
    {
        upper = "!@$%^&*()_+";
        wanted = "!@$%^&*()_+";
    }

    SUBCASE("mixed special")
    {
        upper = "@A@a@A@";
        wanted = "@a@a@a@";
    }

    SUBCASE("japanese")
    {
        upper = "化粧室はどこですか";
        wanted = "化粧室はどこですか";
    }

    SUBCASE("korean")
    {
        upper = "화장실이 어디야";
        wanted = "화장실이 어디야";
    }

    CHECK_EQ(ztd::lower(upper), wanted);
}
