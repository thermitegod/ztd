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

TEST_SUITE("ztd::passwd" * doctest::description(""))
{
    TEST_CASE("constructor name throw")
    {
#if defined(NON_PORTABLE_TESTS)
        const auto pw = ztd::passwd("brandon");

        CHECK_EQ(pw.name(), "brandon");
        CHECK_EQ(pw.password(), "x");
        CHECK_EQ(pw.uid(), 1000);
        CHECK_EQ(pw.gid(), 1000);
        CHECK_EQ(pw.gecos(), "");
        CHECK_EQ(pw.home(), "/home/brandon");
        CHECK_EQ(pw.shell(), "/bin/fish");
#endif
    }

    TEST_CASE("constructor name throw bad user")
    {
        CHECK_THROWS(ztd::passwd("xxx"));
    }

    TEST_CASE("constructor name ec bad user")
    {
        std::error_code ec;
        ztd::passwd("xxx", ec);
        CHECK_EQ(!!ec, true);
    }

    TEST_CASE("constructor name ec")
    {
#if defined(NON_PORTABLE_TESTS)
        std::error_code ec;
        const auto pw = ztd::passwd("brandon", ec);
        EXPECT_FALSE(ec);

        CHECK_EQ(pw.name(), "brandon");
        CHECK_EQ(pw.password(), "x");
        CHECK_EQ(pw.uid(), 1000);
        CHECK_EQ(pw.gid(), 1000);
        CHECK_EQ(pw.gecos(), "");
        CHECK_EQ(pw.home(), "/home/brandon");
        CHECK_EQ(pw.shell(), "/bin/fish");
#endif
    }

    TEST_CASE("constructor uid throw")
    {
#if defined(NON_PORTABLE_TESTS)
        const auto pw = ztd::passwd("brandon");

        CHECK_EQ(pw.name(), "brandon");
        CHECK_EQ(pw.password(), "x");
        CHECK_EQ(pw.uid(), 1000);
        CHECK_EQ(pw.gid(), 1000);
        CHECK_EQ(pw.gecos(), "");
        CHECK_EQ(pw.home(), "/home/brandon");
        CHECK_EQ(pw.shell(), "/bin/fish");
#endif
    }

    TEST_CASE("constructor uid throw bad user")
    {
        CHECK_THROWS(ztd::passwd(500000));
    }

    TEST_CASE("constructor uid ec bad user")
    {
        std::error_code ec;
        ztd::passwd(500000, ec);
        CHECK_EQ(!!ec, true);
    }

    TEST_CASE("constructor uid ec")
    {
#if defined(NON_PORTABLE_TESTS)
        std::error_code ec;
        const auto pw = ztd::passwd("brandon", ec);
        EXPECT_FALSE(ec);

        CHECK_EQ(pw.name(), "brandon");
        CHECK_EQ(pw.password(), "x");
        CHECK_EQ(pw.uid(), 1000);
        CHECK_EQ(pw.gid(), 1000);
        CHECK_EQ(pw.gecos(), "");
        CHECK_EQ(pw.home(), "/home/brandon");
        CHECK_EQ(pw.shell(), "/bin/fish");
#endif
    }
}
