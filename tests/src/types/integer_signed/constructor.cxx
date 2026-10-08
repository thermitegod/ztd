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

#include <doctest/doctest.h>

#include "ztd/detail/types.hxx"

TEST_SUITE("signed integer<T>")
{
    TEST_CASE_TEMPLATE("constructor ",
                       TestType,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using Integer = TestType;

        using type = typename Integer::integer_type;

        SUBCASE("default init value")
        {
            const Integer x;
            CHECK(x == Integer(type(0)));
        }

        SUBCASE("basic")
        {
            const auto x = Integer(type(100));
            const auto y = x;

            CHECK(x == y);
            CHECK(Integer(x) == y);
            CHECK(x == Integer(type(100)));
        }

        SUBCASE("checked_create()")
        {
            SUBCASE("zero")
            {
                const auto x = Integer::checked_create(0);

                REQUIRE(x.has_value());
                CHECK(x.value() == Integer(type(0)));
            }

            SUBCASE("basic")
            {
                const auto x = Integer::checked_create(100);

                REQUIRE(x.has_value());
                CHECK(x.value() == Integer(type(100)));
            }

            SUBCASE("negative")
            {
                const auto x = Integer::checked_create(-100);

                REQUIRE(x.has_value());
                CHECK(x.value() == Integer(type(-100)));
            }
        }

        SUBCASE("unchecked_create()")
        {
            SUBCASE("zero")
            {
                const auto x = Integer::unchecked_create(0);

                CHECK(x == Integer(type(0)));
            }

            SUBCASE("basic")
            {
                const auto x = Integer::unchecked_create(100);

                CHECK(x == Integer(type(100)));
            }

            SUBCASE("negative")
            {
                const auto x = Integer::unchecked_create(-100);

                CHECK(x == Integer(type(-100)));
            }
        }

        SUBCASE("saturating_create()")
        {
            SUBCASE("zero")
            {
                const auto x = Integer::saturating_create(0);

                CHECK(x == Integer(type(0)));
            }

            SUBCASE("basic")
            {
                const auto x = Integer::saturating_create(100);

                CHECK(x == Integer(type(100)));
            }

            SUBCASE("negative")
            {
                const auto x = Integer::saturating_create(-100);

                CHECK(x == Integer(type(-100)));
            }
        }

        SUBCASE("create() string")
        {
            SUBCASE("zero")
            {
                const auto x = Integer::create("0");

                REQUIRE(x.has_value());
                CHECK(x.value() == Integer(type(0)));
            }

            SUBCASE("positive")
            {
                const auto x = Integer::create("100");

                REQUIRE(x.has_value());
                CHECK(x.value() == Integer(type(100)));
            }

            SUBCASE("negative")
            {
                const auto x = Integer::create("-100");

                REQUIRE(x.has_value());
                CHECK(x.value() == Integer(type(-100)));
            }

            SUBCASE("error")
            {
                const auto x = Integer::create("100z");

                CHECK(x == std::nullopt);
            }
        }
    }
}
