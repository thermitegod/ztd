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

#include "ztd/detail/sys/group.hxx"

// enable non portable tests
// #define NON_PORTABLE_TESTS

TEST_SUITE("ztd::group")
{
    TEST_CASE("create() group name")
    {
#if defined(NON_PORTABLE_TESTS)
        const auto gr = ztd::group::create("wheel");
        REQUIRE(gr.has_value());

        CHECK(gr->name() == "wheel");
        CHECK(gr->password() == "x");
        CHECK(gr->gid() == 10);
        std::vector<std::string> members{"root", "brandon"};
        CHECK(gr->members() == members);
#endif
    }

    TEST_CASE("create() bad group name")
    {
        auto gr = ztd::group::create("XXX");
        CHECK(!gr);
        CHECK_FALSE(gr.has_value());
    }

    TEST_CASE("create() group gid")
    {
#if defined(NON_PORTABLE_TESTS)
        const auto gr = ztd::group::create("wheel");
        REQUIRE(gr.has_value());

        CHECK(gr->name() == "wheel");
        CHECK(gr->password() == "x");
        CHECK(gr->gid() == 10);
        std::vector<std::string> members{"root", "brandon"};
        CHECK(gr->members() == members);
#endif
    }

    TEST_CASE("create() bad group gid")
    {
        auto gr = ztd::group::create(500000);
        CHECK(!gr);
        CHECK_FALSE(gr.has_value());
    }
}
