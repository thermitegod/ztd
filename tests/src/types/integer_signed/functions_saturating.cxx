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

#include "data/add-data.hxx"
#include "data/div-data.hxx"
#include "ztd/detail/types.hxx"

TEST_SUITE("signed integer<T>" * doctest::description(""))
{
    using namespace ztd::literals::type_literals;

    TEST_CASE_TEMPLATE("saturating_abs ",
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
            const auto result = x.saturating_abs();

            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive")
        {
            const auto x = Integer(type(100));
            const auto result = x.saturating_abs();

            CHECK_EQ(result, Integer(type(100)));
        }

        SUBCASE("negative")
        {
            const auto x = Integer(type(-100));
            const auto result = x.saturating_abs();

            CHECK_EQ(result, Integer(type(100)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.saturating_abs();

            CHECK_EQ(result, Integer::MAX());
        }
    }

    TEST_CASE_TEMPLATE("saturating_add ",
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
            for (const auto& [x, y, wanted] : test::signed_int::add_data<Integer>)
            {
                auto result = x.saturating_add(y);

                CHECK_MESSAGE(result == wanted,
                              std::format("{} + {} = {} | wanted {}", x, y, result, wanted));
            }
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(10));
            const auto result = x.saturating_add(x);

            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MAX();
            const auto result = x.saturating_add(Integer(type(1)));

            CHECK_EQ(result, Integer::MAX());
        }

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.saturating_add(Integer(type(-1)));

            CHECK_EQ(result, Integer::MIN());
        }
    }

    TEST_CASE_TEMPLATE("saturating_sub ",
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
            const auto result = x.saturating_sub(Integer(type(1)));

            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(100));
            const auto result = x.saturating_sub(x);

            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive - positive")
        {
            const auto x = Integer(type(5));
            const auto result = x.saturating_sub(Integer(type(10)));

            CHECK_EQ(result, Integer(type(-5)));
        }

        SUBCASE("positive - negative")
        {
            const auto x = Integer(type(5));
            const auto result = x.saturating_sub(Integer(type(-10)));

            CHECK_EQ(result, Integer(type(15)));
        }

        SUBCASE("negative - positive")
        {
            const auto x = Integer(type(-5));
            const auto result = x.saturating_sub(Integer(type(10)));

            CHECK_EQ(result, Integer(type(-15)));
        }

        SUBCASE("negative - negative")
        {
            const auto x = Integer(type(-5));
            const auto result = x.saturating_sub(Integer(type(-10)));

            CHECK_EQ(result, Integer(type(5)));
        }

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.saturating_sub(Integer(type(1)));

            CHECK_EQ(result, Integer::MIN());
        }
    }

    TEST_CASE_TEMPLATE("saturating_mul ",
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
            const auto result = x.saturating_mul(Integer(type(1)));

            CHECK_EQ(result, Integer(type(5)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(5));
            const auto result = x.saturating_mul(x);

            CHECK_EQ(result, Integer(type(25)));
        }

        SUBCASE("positive * positive - overflow")
        {
            const auto x = Integer::MAX();
            const auto result = x.saturating_mul(Integer(type(2)));

            CHECK_EQ(result, Integer::MAX());
        }

        SUBCASE("positive * positive - ok")
        {
            const auto x = Integer(type(5));
            const auto result = x.saturating_mul(Integer(type(2)));

            CHECK_EQ(result, Integer(type(10)));
        }

        SUBCASE("positive * negative - underflow")
        {
            const auto x = Integer(type(2));
            const auto result =
                x.saturating_mul((Integer::MIN() / Integer(type(2))) - Integer(type(1)));

            CHECK_EQ(result, Integer::MIN());
        }

        SUBCASE("positive * negative - ok")
        {
            const auto x = Integer(type(2));
            const auto result = x.saturating_mul(Integer(type(-3)));

            CHECK_EQ(result, Integer(type(-6)));
        }

        SUBCASE("negative * positive - underflow")
        {
            const auto x = (Integer::MIN() / Integer(type(2))) - Integer(type(1));
            const auto result = x.saturating_mul(Integer(type(2)));

            CHECK_EQ(result, Integer::MIN());
        }

        SUBCASE("negative * positive - ok")
        {
            const auto x = Integer(type(-2));
            const auto result = x.saturating_mul(Integer(type(3)));

            CHECK_EQ(result, Integer(type(-6)));
        }

        SUBCASE("negative * negative - overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.saturating_mul(Integer(type(-2)));

            CHECK_EQ(result, Integer::MAX());
        }

        SUBCASE("negative * negative - ok")
        {
            const auto x = Integer(type(-2));
            const auto result = x.saturating_mul(Integer(type(-3)));

            CHECK_EQ(result, Integer(type(6)));
        }

        SUBCASE("zero * positive")
        {
            const auto x = Integer(type(0));
            const auto result = x.saturating_mul(Integer::MAX());

            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive * zero")
        {
            const auto x = Integer::MAX();
            const auto result = x.saturating_mul(Integer(type(0)));

            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("zero * negative")
        {
            const auto x = Integer(type(0));
            const auto result = x.saturating_mul(Integer::MIN());

            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("negative * zero")
        {
            const auto x = Integer::MIN();
            const auto result = x.saturating_mul(Integer(type(0)));

            CHECK_EQ(result, Integer(type(0)));
        }
    }

    TEST_CASE_TEMPLATE("saturating_div ",
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
            for (const auto& [dividend, divisor, wanted] : test::signed_int::div_data<Integer>)
            {
                auto result = dividend.saturating_div(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.saturating_div(Integer(type(-1)));

            CHECK_EQ(result, Integer::MAX());
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(1));

            CHECK_THROWS_AS((void)x.saturating_div(Integer(type(0))), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("saturating_div_down ",
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
            for (const auto& [dividend, divisor, wanted] : test::signed_int::div_data<Integer>)
            {
                auto result = dividend.saturating_div_down(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.saturating_div_down(Integer(type(-1)));

            CHECK_EQ(result, Integer::MAX());
        }
    }

    TEST_CASE_TEMPLATE("saturating_div_up ",
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
            for (const auto& [dividend, divisor, wanted] : test::signed_int::div_up_data<Integer>)
            {
                auto result = dividend.saturating_div_up(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.saturating_div_up(Integer(type(-1)));

            CHECK_EQ(result, Integer::MAX());
        }
    }

    TEST_CASE_TEMPLATE("saturating_div_floor ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("example")
        {
            auto x = Integer(type(8));
            auto y = Integer(type(3));

            CHECK(x.saturating_div_floor(y) == 2);
            CHECK(x.saturating_div_floor(-y) == -3);
            CHECK((-x).saturating_div_floor(y) == -3);
            CHECK((-x).saturating_div_floor(-y) == 2);
        }

        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] :
                 test::signed_int::div_floor_data<Integer>)
            {
                auto result = dividend.saturating_div_floor(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.saturating_div_floor(Integer(type(-1)));

            CHECK_EQ(result, Integer::MAX());
        }
    }

    TEST_CASE_TEMPLATE("saturating_div_ceil ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("example")
        {
            auto x = Integer(type(8));
            auto y = Integer(type(3));

            CHECK(x.saturating_div_ceil(y) == 3);
            CHECK(x.saturating_div_ceil(-y) == -2);
            CHECK((-x).saturating_div_ceil(y) == -2);
            CHECK((-x).saturating_div_ceil(-y) == 3);
        }

        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] : test::signed_int::div_ceil_data<Integer>)
            {
                auto result = dividend.saturating_div_ceil(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.saturating_div_ceil(Integer(type(-1)));

            CHECK_EQ(result, Integer::MAX());
        }
    }

    TEST_CASE_TEMPLATE("saturating_div_euclid ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("example")
        {
            auto x = Integer(type(7));
            auto y = Integer(type(4));

            CHECK(x.saturating_div_euclid(y) == 1);     // 7 >= 4 * 1
            CHECK(x.saturating_div_euclid(-y) == -1);   // 7 >= -4 * -1
            CHECK((-x).saturating_div_euclid(y) == -2); // -7 >= 4 * -2
            CHECK((-x).saturating_div_euclid(-y) == 2); // -7 >= -4 * 2
        }

        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] :
                 test::signed_int::div_euclid_data<Integer>)
            {
                auto result = dividend.saturating_div_euclid(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.saturating_div_euclid(Integer(type(-1)));

            CHECK_EQ(result, Integer::MAX());
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(1));

            CHECK_THROWS_AS((void)x.saturating_div_euclid(Integer(type(0))), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("saturating_neg ",
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
            const auto result = x.saturating_neg();

            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive")
        {
            const auto x = Integer(type(10));
            const auto result = x.saturating_neg();

            CHECK_EQ(result, Integer(type(-10)));
        }

        SUBCASE("negative")
        {
            const auto x = Integer(type(-10));
            const auto result = x.saturating_neg();

            CHECK_EQ(result, Integer(type(10)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.saturating_neg();

            CHECK_EQ(result, Integer::MAX());
        }
    }

    TEST_CASE_TEMPLATE("saturating_pow ",
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
            CHECK_EQ(x.saturating_pow(0_u32), 0);
            CHECK_EQ(x.saturating_pow(1_u32), 0);
            CHECK_EQ(x.saturating_pow(2_u32), 0);
            CHECK_EQ(x.saturating_pow(3_u32), 0);
            CHECK_EQ(x.saturating_pow(4_u32), 0);
            CHECK_EQ(x.saturating_pow(5_u32), 0);
            CHECK_EQ(x.saturating_pow(6_u32), 0);
        }

        SUBCASE("one")
        {
            auto x = Integer(type(1));
            CHECK_EQ(x.saturating_pow(0_u32), 1);
            CHECK_EQ(x.saturating_pow(1_u32), 1);
            CHECK_EQ(x.saturating_pow(2_u32), 1);
            CHECK_EQ(x.saturating_pow(3_u32), 1);
            CHECK_EQ(x.saturating_pow(4_u32), 1);
            CHECK_EQ(x.saturating_pow(5_u32), 1);
            CHECK_EQ(x.saturating_pow(6_u32), 1);
        }

        SUBCASE("two")
        {
            auto x = Integer(type(2));
            CHECK_EQ(x.saturating_pow(0_u32), 1);
            CHECK_EQ(x.saturating_pow(1_u32), 2);
            CHECK_EQ(x.saturating_pow(2_u32), 4);
            CHECK_EQ(x.saturating_pow(3_u32), 8);
            CHECK_EQ(x.saturating_pow(4_u32), 16);
            CHECK_EQ(x.saturating_pow(5_u32), 32);
            CHECK_EQ(x.saturating_pow(6_u32), 64);
        }

        SUBCASE("negative two")
        {
            auto x = Integer(type(-2));
            CHECK_EQ(x.saturating_pow(0_u32), 1);
            CHECK_EQ(x.saturating_pow(1_u32), -2);
            CHECK_EQ(x.saturating_pow(2_u32), 4);
            CHECK_EQ(x.saturating_pow(3_u32), -8);
            CHECK_EQ(x.saturating_pow(4_u32), 16);
            CHECK_EQ(x.saturating_pow(5_u32), -32);
            CHECK_EQ(x.saturating_pow(6_u32), 64);
        }

        SUBCASE("overflow")
        {
            auto x = Integer(type(2));
            CHECK_EQ(x.saturating_pow(100_u32), Integer::MAX());
        }
    }
}
