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

// Note - can not check overflow/underflow because
//        the basic operators are implimented using
//        functions that will panic

TEST_SUITE("unsigned integer<T>" * doctest::description(""))
{
    TEST_CASE_TEMPLATE("operator+ ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto a = Integer(type(1));
            auto b = Integer(type(2));

            CHECK_EQ(a + a, Integer(type(2)));
            CHECK_EQ(a + b, Integer(type(3)));
            CHECK_EQ(b + a, Integer(type(3)));
            CHECK_EQ(b + b, Integer(type(4)));

            CHECK_EQ((Integer::MAX() - Integer(type(2))) + Integer(type(1)),
                     Integer::MAX() - Integer(type(1)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(10));
            CHECK_EQ(x + x, Integer(type(20)));
            CHECK_EQ(Integer(type(10)) + Integer(type(10)), Integer(type(20)));
        }

        SUBCASE("positive + positive")
        {
            CHECK_EQ(Integer(type(5)) + Integer(type(10)), Integer(type(15)));
        }

        SUBCASE("overflow")
        {
            // CHECK_THROWS_AS(Integer::MAX() + Integer(type(1)), std::runtime_error);
        }
    }

    TEST_CASE_TEMPLATE("operator+= ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto a = Integer(type(1));
            auto b = Integer(type(2));

            CHECK_EQ(a += a, Integer(type(2)));
            CHECK_EQ(a += b, Integer(type(4)));
            CHECK_EQ(b += a, Integer(type(6)));
            CHECK_EQ(b += b, Integer(type(12)));
        }

        SUBCASE("error")
        {
            // auto max = Integer::MAX();
            // CHECK_THROWS_AS(max += Integer(type(1)), std::runtime_error);
        }

        SUBCASE("self")
        {
            auto x = Integer(type(10));
            CHECK_EQ(x += x, Integer(type(20)));
        }

        SUBCASE("positive += positive")
        {
            auto x = Integer(type(5));
            CHECK_EQ(x += Integer(type(10)), Integer(type(15)));
        }

        SUBCASE("overflow")
        {
            // auto x = Integer::MAX();
            // CHECK_THROWS_AS(x += Integer(type(1)), std::runtime_error);
        }
    }

    TEST_CASE_TEMPLATE("operator- ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto big = Integer::MAX();
            auto small = Integer(type(1));

            CHECK_EQ(small - small, Integer(type(0)));
            CHECK_EQ(big - small, Integer::MAX() - Integer(type(1)));
            CHECK_EQ(big - big, Integer(type(0)));

            CHECK_EQ(Integer(type(1)) - Integer(type(1)), Integer(type(0)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(10));
            CHECK_EQ(x - x, Integer(type(0)));
            CHECK_EQ(Integer(type(100)) - Integer(type(100)), Integer(type(0)));
        }

        SUBCASE("positive - positive - ok")
        {
            CHECK_EQ(Integer(type(10)) - Integer(type(5)), Integer(type(5)));
        }

        SUBCASE("positive - positive - underflow")
        {
            // CHECK_THROWS_AS(Integer(type(5)) - Integer(type(10)), std::runtime_error);
        }

        SUBCASE("underflow")
        {
            // CHECK_THROWS_AS(Integer::MIN() - Integer(type(1)), std::runtime_error);
        }
    }

    TEST_CASE_TEMPLATE("operator-= ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto big = Integer(type(100));
            auto small = Integer(type(10));

            CHECK_EQ(big -= small, Integer(type(90)));
        }

        SUBCASE("self")
        {
            auto x = Integer(type(10));
            CHECK_EQ(x -= x, Integer(type(0)));
        }

        SUBCASE("positive -= positive - ok")
        {
            auto x = Integer(type(10));
            CHECK_EQ(x -= Integer(type(5)), Integer(type(5)));
        }

        SUBCASE("positive -= positive - underflow")
        {
            // auto x = Integer(type(5));
            // CHECK_THROWS_AS(x -= Integer(type(10)), std::runtime_error);
        }
        SUBCASE("underflow")
        {
            // auto x = Integer::MIN();
            // CHECK_THROWS_AS(x -= Integer(type(1)), std::runtime_error);
        }
    }

    TEST_CASE_TEMPLATE("operator* ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            const auto val = Integer(type(10));

            CHECK_EQ(val * val, Integer(type(100)));

            const auto zero = Integer(type(0));
            CHECK_EQ(val * zero, zero);
            CHECK_EQ(zero * val, zero);

            const auto one = Integer(type(1));
            CHECK_EQ(val * one, val);
            CHECK_EQ(one * val, val);

            CHECK_EQ(Integer(type(5)) * Integer(type(1)), Integer(type(5)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(5));
            CHECK_EQ(x * x, Integer(type(25)));
            CHECK_EQ(Integer(type(5)) * Integer(type(5)), Integer(type(25)));
        }

        SUBCASE("positive * positive - overflow")
        {
            // CHECK_THROWS_AS(Integer::MAX() * Integer(type(2)), std::runtime_error);
        }

        SUBCASE("positive * positive - ok")
        {
            CHECK_EQ(Integer(type(5)) * Integer(type(2)), Integer(type(10)));
        }

        SUBCASE("zero * positive")
        {
            CHECK_EQ(Integer(type(0)) * Integer::MAX(), Integer(type(0)));
        }

        SUBCASE("positive * zero")
        {
            CHECK_EQ(Integer::MAX() * Integer(type(0)), Integer(type(0)));
        }
    }

    TEST_CASE_TEMPLATE("operator*= ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            const auto val = Integer(type(10));

            CHECK_EQ(val * val, Integer(type(100)));

            auto zero = Integer(type(0));
            CHECK_EQ(zero *= val, zero);

            auto one = Integer(type(1));
            CHECK_EQ(one *= val, val);
        }

        SUBCASE("self")
        {
            auto x = Integer(type(5));
            CHECK_EQ(x *= x, Integer(type(25)));
        }

        SUBCASE("positive *= positive - overflow")
        {
            // auto x = Integer::MAX();
            // CHECK_THROWS_AS(x *= Integer(type(2)), std::runtime_error);
        }

        SUBCASE("positive *= positive - ok")
        {
            auto x = Integer(type(5));
            CHECK_EQ(x *= Integer(type(2)), Integer(type(10)));
        }

        SUBCASE("zero *= positive")
        {
            auto x = Integer(type(0));
            CHECK_EQ(x *= Integer::MAX(), Integer(type(0)));
        }

        SUBCASE("positive *= zero")
        {
            auto x = Integer::MAX();
            CHECK_EQ(x *= Integer(type(0)), Integer(type(0)));
        }
    }

    TEST_CASE_TEMPLATE("operator/ ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            const auto x = Integer(type(100));
            const auto y = Integer(type(10));

            CHECK_EQ(y / y, Integer(type(1)));
            CHECK_EQ(y / x, Integer(type(0)));

            CHECK_EQ(x / x, Integer(type(1)));

            CHECK_EQ(Integer(type(64)) / Integer(type(2)), Integer(type(32)));
        }

        SUBCASE("positive / positive")
        {
            CHECK_EQ(Integer(type(100)) / Integer(type(5)), Integer(type(20)));
        }

        SUBCASE("division by zero")
        {
#if 0
            CHECK_THROWS_AS(Integer(type(1)) / Integer(type(0)), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("operator/= ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            auto x = Integer(type(100));
            auto y = Integer(type(10));

            CHECK_EQ(y /= y, Integer(type(1)));
            CHECK_EQ(y /= x, Integer(type(0)));

            CHECK_EQ(x /= x, Integer(type(1)));
        }

        SUBCASE("positive /= positive")
        {
            auto x = Integer(type(100));
            CHECK_EQ(x /= Integer(type(5)), Integer(type(20)));
        }

        SUBCASE("division by zero")
        {
#if 0
            auto x = Integer(type(1));
            CHECK_THROWS_AS(x /= Integer(type(0)), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("operator% ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic remainder")
        {
            CHECK_EQ(Integer(type(10)) % Integer(type(3)), Integer(type(1)));
        }

        SUBCASE("basic no remainder")
        {
            CHECK_EQ(Integer(type(9)) % Integer(type(3)), Integer(type(0)));
        }

        SUBCASE("positive % positive")
        {
            CHECK_EQ(Integer(type(10)) % Integer(type(3)), Integer(type(1)));
        }

        SUBCASE("division by zero")
        {
#if 0
            CHECK_THROWS_AS(Integer(type(1)) % Integer(type(0)), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("operator%= ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic remainder")
        {
            auto x = Integer(type(10));
            CHECK_EQ(x %= Integer(type(3)), Integer(type(1)));
        }

        SUBCASE("basic no remainder")
        {
            auto x = Integer(type(9));
            CHECK_EQ(x %= Integer(type(3)), Integer(type(0)));
        }

        SUBCASE("positive %= positive")
        {
            auto x = Integer(type(10));
            CHECK_EQ(x %= Integer(type(3)), Integer(type(1)));
        }

        SUBCASE("division by zero")
        {
#if 0
            auto x = Integer(type(1));
            CHECK_THROWS_AS(x %= Integer(type(0)), std::runtime_error);
#endif
        }
    }
}
