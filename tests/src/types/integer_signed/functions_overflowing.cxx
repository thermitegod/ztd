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

#include <vector>

#include <doctest/doctest.h>

#include "../utils.hxx"
#include "ztd/detail/types.hxx"

TEST_SUITE("signed integer<T>" * doctest::description(""))
{
    using namespace ztd::literals::type_literals;

    TEST_CASE_TEMPLATE("overflowing_abs ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("zero")
        {
            const auto x = Integer(type(0));
            const auto [result, overflow] = x.overflowing_abs();

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive")
        {
            const auto x = Integer(type(100));
            const auto [result, overflow] = x.overflowing_abs();

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(100)));
        }

        SUBCASE("negative")
        {
            const auto x = Integer(type(-100));
            const auto [result, overflow] = x.overflowing_abs();

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(100)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_abs();

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MIN());
        }
    }

    TEST_CASE_TEMPLATE("overflowing_add ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            const auto x = Integer::MAX() - Integer(type(2));
            const auto [result, overflow] = x.overflowing_add(Integer(type(1)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer::MAX() - Integer(type(1)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(10));
            const auto [result, overflow] = x.overflowing_add(x);

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("positive + positive")
        {
            const auto x = Integer(type(5));
            const auto [result, overflow] = x.overflowing_add(Integer(type(10)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(15)));
        }

        SUBCASE("positive + negative")
        {
            const auto x = Integer(type(5));
            const auto [result, overflow] = x.overflowing_add(Integer(type(-10)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(-5)));
        }

        SUBCASE("negative + positive")
        {
            const auto x = Integer(type(-5));
            const auto [result, overflow] = x.overflowing_add(Integer(type(10)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(5)));
        }

        SUBCASE("negative + negative")
        {
            const auto x = Integer(type(-5));
            const auto [result, overflow] = x.overflowing_add(Integer(type(-10)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(-15)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MAX();
            const auto [result, overflow] = x.overflowing_add(Integer(type(1)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MIN());
        }

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_add(Integer(type(-1)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MAX());
        }
    }

    TEST_CASE_TEMPLATE("overflowing_add unsigned overload ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("self")
        {
            const auto x = Integer(type(10));
            const auto [result, overflow] = x.overflowing_add(x.cast_unsigned());

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("positive + positive")
        {
            const auto x = Integer(type(5));
            const auto [result, overflow] = x.overflowing_add(Integer(type(10)).cast_unsigned());

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(15)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MAX();
            const auto [result, overflow] = x.overflowing_add(Integer(type(1)).cast_unsigned());

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MIN());
        }
    }

    TEST_CASE_TEMPLATE("overflowing_sub ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            const auto x = Integer(type(1));
            const auto [result, overflow] = x.overflowing_sub(Integer(type(1)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(100));
            const auto [result, overflow] = x.overflowing_sub(x);

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive - positive")
        {
            const auto x = Integer(type(5));
            const auto [result, overflow] = x.overflowing_sub(Integer(type(10)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(-5)));
        }

        SUBCASE("positive - negative")
        {
            const auto x = Integer(type(5));
            const auto [result, overflow] = x.overflowing_sub(Integer(type(-10)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(15)));
        }

        SUBCASE("negative - positive")
        {
            const auto x = Integer(type(-5));
            const auto [result, overflow] = x.overflowing_sub(Integer(type(10)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(-15)));
        }

        SUBCASE("negative - negative")
        {
            const auto x = Integer(type(-5));
            const auto [result, overflow] = x.overflowing_sub(Integer(type(-10)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(5)));
        }

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_sub(Integer(type(1)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MAX());
        }
    }

    TEST_CASE_TEMPLATE("overflowing_sub unsigned overload",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("self")
        {
            const auto x = Integer(type(100));
            const auto [result, overflow] = x.overflowing_sub(x.cast_unsigned());

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive - positive")
        {
            const auto x = Integer(type(5));
            const auto [result, overflow] = x.overflowing_sub(Integer(type(10)).cast_unsigned());

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(-5)));
        }

        SUBCASE("negative - positive")
        {
            const auto x = Integer(type(-5));
            const auto [result, overflow] = x.overflowing_sub(Integer(type(10)).cast_unsigned());

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(-15)));
        }

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_sub(Integer(type(1)).cast_unsigned());

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MAX());
        }
    }

    TEST_CASE_TEMPLATE("overflowing_mul ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            const auto x = Integer(type(5));
            const auto [result, overflow] = x.overflowing_mul(Integer(type(1)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(5)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(5));
            const auto [result, overflow] = x.overflowing_mul(x);

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(25)));
        }

        SUBCASE("positive * positive - overflow")
        {
#if 0
            // TODO either find a type agnostic way to test overflow
            // or use if constexpr and hardcode overflow tests
            const auto x = Integer::MAX();
            const auto [result, overflow] = x.overflowing_mul(Integer(type(2)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MAX());
#endif
        }

        SUBCASE("positive * positive - ok")
        {
            const auto x = Integer(type(5));
            const auto [result, overflow] = x.overflowing_mul(Integer(type(2)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(10)));
        }

        SUBCASE("positive * negative - underflow")
        {
#if 0
            // TODO either find a type agnostic way to test overflow
            // or use if constexpr and hardcode overflow tests
            const auto x = Integer(type(2));
            const auto [result, overflow] =
                x.overflowing_mul((Integer::MIN() / Integer(type(2))) - Integer(type(1)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MIN());
#endif
        }

        SUBCASE("positive * negative - ok")
        {
            const auto x = Integer(type(2));
            const auto [result, overflow] = x.overflowing_mul(Integer(type(-3)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(-6)));
        }

        SUBCASE("negative * positive - underflow")
        {
#if 0
            // TODO either find a type agnostic way to test overflow
            // or use if constexpr and hardcode overflow tests
            const auto x = (Integer::MIN() / Integer(type(2))) - Integer(type(1));
            const auto [result, overflow] = x.overflowing_mul(Integer(type(2)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MIN());
#endif
        }

        SUBCASE("negative * positive - ok")
        {
            const auto x = Integer(type(-2));
            const auto [result, overflow] = x.overflowing_mul(Integer(type(3)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(-6)));
        }

        SUBCASE("negative * negative - overflow")
        {
#if 0
            // TODO either find a type agnostic way to test overflow
            // or use if constexpr and hardcode overflow tests
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_mul(Integer(type(-2)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MAX());
#endif
        }

        SUBCASE("negative * negative - ok")
        {
            const auto x = Integer(type(-2));
            const auto [result, overflow] = x.overflowing_mul(Integer(type(-3)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(6)));
        }

        SUBCASE("zero * positive")
        {
            const auto x = Integer(type(0));
            const auto [result, overflow] = x.overflowing_mul(Integer::MAX());

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive * zero")
        {
            const auto x = Integer::MAX();
            const auto [result, overflow] = x.overflowing_mul(Integer(type(0)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("zero * negative")
        {
            const auto x = Integer(type(0));
            const auto [result, overflow] = x.overflowing_mul(Integer::MIN());

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("negative * zero")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_mul(Integer(type(0)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(0)));
        }
    }

    TEST_CASE_TEMPLATE("overflowing_div ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            const auto [result1, overflow1] = Integer(type(5)).overflowing_div(Integer(type(2)));
            CHECK_EQ(result1, Integer(type(2)));
            CHECK_EQ(overflow1, false);

            const auto [result2, overflow2] = Integer(type(-5)).overflowing_div(Integer(type(2)));
            CHECK_EQ(result2, Integer(type(-2)));
            CHECK_EQ(overflow2, false);

            const auto [result3, overflow3] = Integer(type(5)).overflowing_div(Integer(type(-2)));
            CHECK_EQ(result3, Integer(type(-2)));
            CHECK_EQ(overflow3, false);

            const auto [result4, overflow4] = Integer(type(-5)).overflowing_div(Integer(type(-2)));
            CHECK_EQ(result4, Integer(type(2)));
            CHECK_EQ(overflow4, false);
        }

        SUBCASE("positive / positive")
        {
            const auto x = Integer(type(100));
            const auto [result, overflow] = x.overflowing_div(Integer(type(5)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("positive / negative")
        {
            const auto x = Integer(type(100));
            const auto [result, overflow] = x.overflowing_div(Integer(type(-5)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(-20)));
        }

        SUBCASE("negative / positive")
        {
            const auto x = Integer(type(-100));
            const auto [result, overflow] = x.overflowing_div(Integer(type(5)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(-20)));
        }

        SUBCASE("negative / negative")
        {
            const auto x = Integer(type(-100));
            const auto [result, overflow] = x.overflowing_div(Integer(type(-5)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_div(Integer(type(-1)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MIN());
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(1));

            CHECK_THROWS_AS((void)x.overflowing_div(Integer(type(0))), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("overflowing_div_down ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            std::vector<div_data<Integer>> test_data{
                // positive / positive
                {
                    .dividend = Integer(type(7)),
                    .divisor = Integer(type(3)),
                    .result = Integer(type(2)),
                },

                // positive / negative
                {
                    .dividend = Integer(type(7)),
                    .divisor = Integer(type(-3)),
                    .result = Integer(type(-2)),
                },

                // negative / positive
                {
                    .dividend = Integer(type(-7)),
                    .divisor = Integer(type(3)),
                    .result = Integer(type(-2)),
                },

                // negative / negative
                {
                    .dividend = Integer(type(-7)),
                    .divisor = Integer(type(-3)),
                    .result = Integer(type(2)),
                },
            };

            for (const auto& [dividend, divisor, wanted] : test_data)
            {
                auto [result, overflow] = dividend.overflowing_div_down(divisor);

                CHECK_EQ(result, wanted);
                CHECK_EQ(overflow, false);
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_div_down(Integer(type(-1)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MIN());
        }
    }

    TEST_CASE_TEMPLATE("overflowing_div_up ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            std::vector<div_data<Integer>> test_data{
                // positive / positive
                {
                    .dividend = Integer(type(7)),
                    .divisor = Integer(type(3)),
                    .result = Integer(type(3)),
                },

                // positive / negative
                {
                    .dividend = Integer(type(7)),
                    .divisor = Integer(type(-3)),
                    .result = Integer(type(-3)),
                },

                // negative / positive
                {
                    .dividend = Integer(type(-7)),
                    .divisor = Integer(type(3)),
                    .result = Integer(type(-3)),
                },

                // negative / negative
                {
                    .dividend = Integer(type(-7)),
                    .divisor = Integer(type(-3)),
                    .result = Integer(type(3)),
                },
            };

            for (const auto& [dividend, divisor, wanted] : test_data)
            {
                auto [result, overflow] = dividend.overflowing_div_up(divisor);

                CHECK_EQ(result, wanted);
                CHECK_EQ(overflow, false);
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_div_up(Integer(type(-1)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MIN());
        }
    }

    TEST_CASE_TEMPLATE("overflowing_div_floor ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            std::vector<div_data<Integer>> test_data{
                // positive / positive
                {
                    .dividend = Integer(type(7)),
                    .divisor = Integer(type(3)),
                    .result = Integer(type(2)),
                },

                // positive / negative
                {
                    .dividend = Integer(type(7)),
                    .divisor = Integer(type(-3)),
                    .result = Integer(type(-3)),
                },

                // negative / positive
                {
                    .dividend = Integer(type(-7)),
                    .divisor = Integer(type(3)),
                    .result = Integer(type(-3)),
                },

                // negative / negative
                {
                    .dividend = Integer(type(-7)),
                    .divisor = Integer(type(-3)),
                    .result = Integer(type(2)),
                },
            };

            for (const auto& [dividend, divisor, wanted] : test_data)
            {
                auto [result, overflow] = dividend.overflowing_div_floor(divisor);

                CHECK_EQ(result, wanted);
                CHECK_EQ(overflow, false);
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_div_floor(Integer(type(-1)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MIN());
        }
    }

    TEST_CASE_TEMPLATE("overflowing_div_ceil ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            std::vector<div_data<Integer>> test_data{
                // positive / positive
                {
                    .dividend = Integer(type(7)),
                    .divisor = Integer(type(3)),
                    .result = Integer(type(3)),
                },

                // positive / negative
                {
                    .dividend = Integer(type(7)),
                    .divisor = Integer(type(-3)),
                    .result = Integer(type(-2)),
                },

                // negative / positive
                {
                    .dividend = Integer(type(-7)),
                    .divisor = Integer(type(3)),
                    .result = Integer(type(-2)),
                },

                // negative / negative
                {
                    .dividend = Integer(type(-7)),
                    .divisor = Integer(type(-3)),
                    .result = Integer(type(3)),
                },
            };

            for (const auto& [dividend, divisor, wanted] : test_data)
            {
                auto [result, overflow] = dividend.overflowing_div_ceil(divisor);

                CHECK_EQ(result, wanted);
                CHECK_EQ(overflow, false);
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_div_ceil(Integer(type(-1)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MIN());
        }
    }

    TEST_CASE_TEMPLATE("overflowing_div_euclid ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic")
        {
            const auto [result1, overflow1] =
                Integer(type(5)).overflowing_div_euclid(Integer(type(2)));
            CHECK_EQ(result1, Integer(type(2)));
            CHECK_EQ(overflow1, false);

            const auto [result2, overflow2] =
                Integer(type(-5)).overflowing_div_euclid(Integer(type(2)));
            CHECK_EQ(result2, Integer(type(-3)));
            CHECK_EQ(overflow2, false);

            const auto [result3, overflow3] =
                Integer(type(5)).overflowing_div_euclid(Integer(type(-2)));
            CHECK_EQ(result3, Integer(type(-2)));
            CHECK_EQ(overflow3, false);

            const auto [result4, overflow4] =
                Integer(type(-5)).overflowing_div_euclid(Integer(type(-2)));
            CHECK_EQ(result4, Integer(type(3)));
            CHECK_EQ(overflow4, false);
        }

        SUBCASE("positive / positive")
        {
            const auto x = Integer(type(100));
            const auto [result, overflow] = x.overflowing_div_euclid(Integer(type(5)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("positive / negative")
        {
            const auto x = Integer(type(100));
            const auto [result, overflow] = x.overflowing_div_euclid(Integer(type(-5)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(-20)));
        }

        SUBCASE("negative / positive")
        {
            const auto x = Integer(type(-100));
            const auto [result, overflow] = x.overflowing_div_euclid(Integer(type(5)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(-20)));
        }

        SUBCASE("negative / negative")
        {
            const auto x = Integer(type(-100));
            const auto [result, overflow] = x.overflowing_div_euclid(Integer(type(-5)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_div_euclid(Integer(type(-1)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MIN());
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(1));

            CHECK_THROWS_AS((void)x.overflowing_div_euclid(Integer(type(0))), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("overflowing_rem ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic remainder")
        {
            const auto [result1, overflow1] = Integer(type(5)).overflowing_rem(Integer(type(2)));
            CHECK_EQ(result1, Integer(type(1)));
            CHECK_EQ(overflow1, false);

            const auto [result2, overflow2] = Integer(type(-5)).overflowing_rem(Integer(type(2)));
            CHECK_EQ(result2, Integer(type(-1)));
            CHECK_EQ(overflow2, false);

            const auto [result3, overflow3] = Integer(type(5)).overflowing_rem(Integer(type(-2)));
            CHECK_EQ(result3, Integer(type(1)));
            CHECK_EQ(overflow3, false);

            const auto [result4, overflow4] = Integer(type(-5)).overflowing_rem(Integer(type(-2)));
            CHECK_EQ(result4, Integer(type(-1)));
            CHECK_EQ(overflow4, false);
        }

        SUBCASE("basic no remainder")
        {
            const auto x = Integer(type(9));
            const auto [result, overflow] = x.overflowing_rem(Integer(type(3)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive % positive")
        {
            const auto x = Integer(type(10));
            const auto [result, overflow] = x.overflowing_rem(Integer(type(3)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(1)));
        }

        SUBCASE("positive % negative")
        {
            const auto x = Integer(type(10));
            const auto [result, overflow] = x.overflowing_rem(Integer(type(-3)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(1)));
        }

        SUBCASE("negative % positive")
        {
            const auto x = Integer(type(-10));
            const auto [result, overflow] = x.overflowing_rem(Integer(type(3)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(-1)));
        }

        SUBCASE("negative % negative")
        {
            const auto x = Integer(type(-10));
            const auto [result, overflow] = x.overflowing_rem(Integer(type(-3)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(-1)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_rem(Integer(type(-1)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(5));

            CHECK_THROWS_AS((void)x.overflowing_rem(Integer(type(0))), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("overflowing_rem_euclid ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic remainder")
        {
            const auto [result1, overflow1] =
                Integer(type(5)).overflowing_rem_euclid(Integer(type(2)));
            CHECK_EQ(result1, Integer(type(1)));
            CHECK_EQ(overflow1, false);

            const auto [result2, overflow2] =
                Integer(type(-5)).overflowing_rem_euclid(Integer(type(2)));
            CHECK_EQ(result2, Integer(type(1)));
            CHECK_EQ(overflow2, false);

            const auto [result3, overflow3] =
                Integer(type(5)).overflowing_rem_euclid(Integer(type(-2)));
            CHECK_EQ(result3, Integer(type(1)));
            CHECK_EQ(overflow3, false);

            const auto [result4, overflow4] =
                Integer(type(-5)).overflowing_rem_euclid(Integer(type(-2)));
            CHECK_EQ(result4, Integer(type(1)));
            CHECK_EQ(overflow4, false);
        }

        SUBCASE("basic no remainder")
        {
            const auto x = Integer(type(9));
            const auto [result, overflow] = x.overflowing_rem_euclid(Integer(type(3)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive % positive")
        {
            const auto x = Integer(type(10));
            const auto [result, overflow] = x.overflowing_rem_euclid(Integer(type(3)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(1)));
        }

        SUBCASE("positive % negative")
        {
            const auto x = Integer(type(10));
            const auto [result, overflow] = x.overflowing_rem_euclid(Integer(type(-3)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(1)));
        }

        SUBCASE("negative % positive")
        {
            const auto x = Integer(type(-10));
            const auto [result, overflow] = x.overflowing_rem_euclid(Integer(type(3)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(2)));
        }

        SUBCASE("negative % negative")
        {
            const auto x = Integer(type(-10));
            const auto [result, overflow] = x.overflowing_rem_euclid(Integer(type(-3)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(2)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_rem_euclid(Integer(type(-1)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(5));

            CHECK_THROWS_AS((void)x.overflowing_rem(Integer(type(0))), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("overflowing_neg ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("zero")
        {
            const auto x = Integer(type(0));
            const auto [result, overflow] = x.overflowing_neg();

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive")
        {
            const auto x = Integer(type(10));
            const auto [result, overflow] = x.overflowing_neg();

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(-10)));
        }

        SUBCASE("negative")
        {
            const auto x = Integer(type(-10));
            const auto [result, overflow] = x.overflowing_neg();

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(10)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_neg();

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MIN());
        }
    }

    TEST_CASE_TEMPLATE("overflowing_pow ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("zero")
        {
            auto x = Integer(type(0));
            CHECK_EQ(x.overflowing_pow(0_u32), std::make_tuple(Integer(type(0)), false));
            CHECK_EQ(x.overflowing_pow(1_u32), std::make_tuple(Integer(type(0)), false));
            CHECK_EQ(x.overflowing_pow(2_u32), std::make_tuple(Integer(type(0)), false));
            CHECK_EQ(x.overflowing_pow(3_u32), std::make_tuple(Integer(type(0)), false));
            CHECK_EQ(x.overflowing_pow(4_u32), std::make_tuple(Integer(type(0)), false));
            CHECK_EQ(x.overflowing_pow(5_u32), std::make_tuple(Integer(type(0)), false));
            CHECK_EQ(x.overflowing_pow(6_u32), std::make_tuple(Integer(type(0)), false));
        }

        SUBCASE("one")
        {
            auto x = Integer(type(1));
            CHECK_EQ(x.overflowing_pow(0_u32), std::make_tuple(Integer(type(1)), false));
            CHECK_EQ(x.overflowing_pow(1_u32), std::make_tuple(Integer(type(1)), false));
            CHECK_EQ(x.overflowing_pow(2_u32), std::make_tuple(Integer(type(1)), false));
            CHECK_EQ(x.overflowing_pow(3_u32), std::make_tuple(Integer(type(1)), false));
            CHECK_EQ(x.overflowing_pow(4_u32), std::make_tuple(Integer(type(1)), false));
            CHECK_EQ(x.overflowing_pow(5_u32), std::make_tuple(Integer(type(1)), false));
            CHECK_EQ(x.overflowing_pow(6_u32), std::make_tuple(Integer(type(1)), false));
        }

        SUBCASE("two")
        {
            auto x = Integer(type(2));
            CHECK_EQ(x.overflowing_pow(0_u32), std::make_tuple(Integer(type(1)), false));
            CHECK_EQ(x.overflowing_pow(1_u32), std::make_tuple(Integer(type(2)), false));
            CHECK_EQ(x.overflowing_pow(2_u32), std::make_tuple(Integer(type(4)), false));
            CHECK_EQ(x.overflowing_pow(3_u32), std::make_tuple(Integer(type(8)), false));
            CHECK_EQ(x.overflowing_pow(4_u32), std::make_tuple(Integer(type(16)), false));
            CHECK_EQ(x.overflowing_pow(5_u32), std::make_tuple(Integer(type(32)), false));
            CHECK_EQ(x.overflowing_pow(6_u32), std::make_tuple(Integer(type(64)), false));
        }

        SUBCASE("negative two")
        {
            auto x = Integer(type(-2));
            CHECK_EQ(x.overflowing_pow(0_u32), std::make_tuple(Integer(type(1)), false));
            CHECK_EQ(x.overflowing_pow(1_u32), std::make_tuple(Integer(type(-2)), false));
            CHECK_EQ(x.overflowing_pow(2_u32), std::make_tuple(Integer(type(4)), false));
            CHECK_EQ(x.overflowing_pow(3_u32), std::make_tuple(Integer(type(-8)), false));
            CHECK_EQ(x.overflowing_pow(4_u32), std::make_tuple(Integer(type(16)), false));
            CHECK_EQ(x.overflowing_pow(5_u32), std::make_tuple(Integer(type(-32)), false));
            CHECK_EQ(x.overflowing_pow(6_u32), std::make_tuple(Integer(type(64)), false));
        }

        SUBCASE("overflow")
        {
            auto x = Integer(type(2));
            [[maybe_unused]] auto [result, overflow] = x.overflowing_pow(100_u32);
            CHECK_EQ(overflow, true);
        }
    }
}
