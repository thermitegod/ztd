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

#include <system_error>
#include <vector>

#include <doctest/doctest.h>

#include "ztd/detail/sys/passwd.hxx"

// enable non portable tests
// #define NON_PORTABLE_TESTS

TEST_SUITE("ztd::passwd")
{
    TEST_CASE("create() user name")
    {
#if defined(NON_PORTABLE_TESTS)
        const auto pw = ztd::passwd::create("brandon");
        REQUIRE(pw.has_value());

        CHECK(pw->name() == "brandon");
        CHECK(pw->password() == "x");
        CHECK(pw->uid() == 1000);
        CHECK(pw->gid() == 1000);
        CHECK(pw->gecos() == "");
        CHECK(pw->home() == "/home/brandon");
        CHECK(pw->shell() == "/bin/fish");
#endif
    }

    TEST_CASE("create() bad user name")
    {
        auto pw = ztd::passwd::create("XXX");
        CHECK(!pw);
        CHECK_FALSE(pw.has_value());
    }

    TEST_CASE("create() user uid")
    {
#if defined(NON_PORTABLE_TESTS)
        const auto pw = ztd::passwd::create(1000);
        REQUIRE(pw.has_value());

        CHECK(pw->name() == "brandon");
        CHECK(pw->password() == "x");
        CHECK(pw->uid() == 1000);
        CHECK(pw->gid() == 1000);
        CHECK(pw->gecos() == "");
        CHECK(pw->home() == "/home/brandon");
        CHECK(pw->shell() == "/bin/fish");
#endif
    }

    TEST_CASE("create() bad user uid")
    {
        auto pw = ztd::passwd::create(500000);
        CHECK(!pw);
        CHECK_FALSE(pw.has_value());
    }
}
