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

TEST_CASE("ztd::upper")
{
    std::string lower;
    std::string wanted;

    SUBCASE("empty") {}

    SUBCASE("latin")
    {
        lower = "abcdefghijklmnopqrstuvwxyz1234567890!@$%^&*()_+";
        wanted = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@$%^&*()_+";
    }

    SUBCASE("special")
    {
        lower = "!@$%^&*()_+";
        wanted = "!@$%^&*()_+";
    }

    SUBCASE("mixed special")
    {
        lower = "@a@A@a@";
        wanted = "@A@A@A@";
    }

    SUBCASE("japanese")
    {
        lower = "化粧室はどこですか";
        wanted = "化粧室はどこですか";
    }

    SUBCASE("korean")
    {
        lower = "화장실이 어디야";
        wanted = "화장실이 어디야";
    }

    CHECK_EQ(ztd::upper(lower), wanted);
}
