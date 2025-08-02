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

#include "data/div-data.hxx"
#include "ztd/detail/types.hxx"

TEST_SUITE("signed integer<T>" * doctest::description(""))
{
    using namespace ztd::literals::type_literals;

    TEST_CASE_TEMPLATE("checked_abs ",
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
            const auto result = x.checked_abs();

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(0)));
        }

        SUBCASE("positive")
        {
            const auto x = Integer(type(100));
            const auto result = x.checked_abs();

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(100)));
        }

        SUBCASE("negative")
        {
            const auto x = Integer(type(-100));
            const auto result = x.checked_abs();

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(100)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_abs();

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_add ",
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
            const auto result = x.checked_add(Integer(type(1)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer::MAX() - Integer(type(1)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(10));
            const auto result = x.checked_add(x);

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(20)));
        }

        SUBCASE("positive + positive")
        {
            const auto x = Integer(type(5));
            const auto result = x.checked_add(Integer(type(10)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(15)));
        }

        SUBCASE("positive + negative")
        {
            const auto x = Integer(type(5));
            const auto result = x.checked_add(Integer(type(-10)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(-5)));
        }

        SUBCASE("negative + positive")
        {
            const auto x = Integer(type(-5));
            const auto result = x.checked_add(Integer(type(10)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(5)));
        }

        SUBCASE("negative + negative")
        {
            const auto x = Integer(type(-5));
            const auto result = x.checked_add(Integer(type(-10)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(-15)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MAX();
            const auto result = x.checked_add(Integer(type(1)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_add(Integer(type(-1)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_add unsigned overload ",
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
            const auto result = x.checked_add(x.cast_unsigned());

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(20)));
        }

        SUBCASE("positive + positive")
        {
            const auto x = Integer(type(5));
            const auto result = x.checked_add(Integer(type(10)).cast_unsigned());

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(15)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MAX();
            const auto result = x.checked_add(Integer(type(1)).cast_unsigned());

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_sub ",
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
            const auto result = x.checked_sub(Integer(type(1)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(0)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(100));
            const auto result = x.checked_sub(x);

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(0)));
        }

        SUBCASE("positive - positive")
        {
            const auto x = Integer(type(5));
            const auto result = x.checked_sub(Integer(type(10)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(-5)));
        }

        SUBCASE("positive - negative")
        {
            const auto x = Integer(type(5));
            const auto result = x.checked_sub(Integer(type(-10)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(15)));
        }

        SUBCASE("negative - positive")
        {
            const auto x = Integer(type(-5));
            const auto result = x.checked_sub(Integer(type(10)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(-15)));
        }

        SUBCASE("negative - negative")
        {
            const auto x = Integer(type(-5));
            const auto result = x.checked_sub(Integer(type(-10)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(5)));
        }

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_sub(Integer(type(1)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_sub unsigned overload ",
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
            const auto result = x.checked_sub(Integer(type(1)).cast_unsigned());

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(0)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(100));
            const auto result = x.checked_sub(x.cast_unsigned());

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(0)));
        }

        SUBCASE("positive - positive")
        {
            const auto x = Integer(type(5));
            const auto result = x.checked_sub(Integer(type(10)).cast_unsigned());

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(-5)));
        }

        SUBCASE("negative - positive")
        {
            const auto x = Integer(type(-5));
            const auto result = x.checked_sub(Integer(type(10)).cast_unsigned());

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(-15)));
        }

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_sub(Integer(type(1)).cast_unsigned());

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_mul ",
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
            const auto result = x.checked_mul(Integer(type(1)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(5)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(5));
            const auto result = x.checked_mul(x);

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(25)));
        }

        SUBCASE("positive * positive - overflow")
        {
            const auto x = Integer::MAX();
            const auto result = x.checked_mul(Integer(type(2)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }

        SUBCASE("positive * positive - ok")
        {
            const auto x = Integer(type(5));
            const auto result = x.checked_mul(Integer(type(2)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(10)));
        }

        SUBCASE("positive * negative - underflow")
        {
            const auto x = Integer(type(2));
            const auto result =
                x.checked_mul((Integer::MIN() / Integer(type(2))) - Integer(type(1)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }

        SUBCASE("positive * negative - ok")
        {
            const auto x = Integer(type(2));
            const auto result = x.checked_mul(Integer(type(-3)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(-6)));
        }

        SUBCASE("negative * positive - underflow")
        {
            const auto x = (Integer::MIN() / Integer(type(2))) - Integer(type(1));
            const auto result = x.checked_mul(Integer(type(2)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }

        SUBCASE("negative * positive - ok")
        {
            const auto x = Integer(type(-2));
            const auto result = x.checked_mul(Integer(type(3)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(-6)));
        }

        SUBCASE("negative * negative - overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_mul(Integer(type(-2)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }

        SUBCASE("negative * negative - ok")
        {
            const auto x = Integer(type(-2));
            const auto result = x.checked_mul(Integer(type(-3)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(6)));
        }

        SUBCASE("zero * positive")
        {
            const auto x = Integer(type(0));
            const auto result = x.checked_mul(Integer::MAX());

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(0)));
        }

        SUBCASE("positive * zero")
        {
            const auto x = Integer::MAX();
            const auto result = x.checked_mul(Integer(type(0)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(0)));
        }

        SUBCASE("zero * negative")
        {
            const auto x = Integer(type(0));
            const auto result = x.checked_mul(Integer::MIN());

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(0)));
        }

        SUBCASE("negative * zero")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_mul(Integer(type(0)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(0)));
        }
    }

    TEST_CASE_TEMPLATE("checked_div ",
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
                auto result = dividend.checked_div(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, *result, wanted));
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_div(Integer(type(-1)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }

        SUBCASE("division by zero")
        {
            const auto x = Integer(type(1));
            const auto result = x.checked_div(Integer(type(0)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_div_down ",
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
                auto result = dividend.checked_div_down(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, *result, wanted));
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_div_down(Integer(type(-1)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }

        SUBCASE("division by zero")
        {
            const auto x = Integer(type(1));
            const auto result = x.checked_div_down(Integer(type(0)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_div_up ",
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
                auto result = dividend.checked_div_up(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, *result, wanted));
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_div_up(Integer(type(-1)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }

        SUBCASE("division by zero")
        {
            const auto x = Integer(type(1));
            const auto result = x.checked_div_up(Integer(type(0)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_div_floor ",
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

            CHECK(x.checked_div_floor(y) == 2);
            CHECK(x.checked_div_floor(-y) == -3);
            CHECK((-x).checked_div_floor(y) == -3);
            CHECK((-x).checked_div_floor(-y) == 2);
        }

        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] :
                 test::signed_int::div_floor_data<Integer>)
            {
                auto result = dividend.checked_div_floor(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, *result, wanted));
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_div_floor(Integer(type(-1)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }

        SUBCASE("division by zero")
        {
            const auto x = Integer(type(1));
            const auto result = x.checked_div_floor(Integer(type(0)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_div_ceil ",
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

            CHECK(x.checked_div_ceil(y) == 3);
            CHECK(x.checked_div_ceil(-y) == -2);
            CHECK((-x).checked_div_ceil(y) == -2);
            CHECK((-x).checked_div_ceil(-y) == 3);
        }

        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] : test::signed_int::div_ceil_data<Integer>)
            {
                auto result = dividend.checked_div_ceil(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, *result, wanted));
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_div_ceil(Integer(type(-1)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }

        SUBCASE("division by zero")
        {
            const auto x = Integer(type(1));
            const auto result = x.checked_div_ceil(Integer(type(0)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_div_euclid ",
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

            CHECK(x.checked_div_euclid(y) == 1);     // 7 >= 4 * 1
            CHECK(x.checked_div_euclid(-y) == -1);   // 7 >= -4 * -1
            CHECK((-x).checked_div_euclid(y) == -2); // -7 >= 4 * -2
            CHECK((-x).checked_div_euclid(-y) == 2); // -7 >= -4 * 2
        }

        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] :
                 test::signed_int::div_euclid_data<Integer>)
            {
                auto result = dividend.checked_div_euclid(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, *result, wanted));
            }
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_div_euclid(Integer(type(-1)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }

        SUBCASE("division by zero")
        {
            const auto x = Integer(type(1));
            const auto result = x.checked_div_euclid(Integer(type(0)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_rem ",
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
            const auto result1 = Integer(type(5)).checked_rem(Integer(type(2)));
            REQUIRE(result1.has_value());
            CHECK_EQ(result1, Integer(type(1)));

            const auto result2 = Integer(type(-5)).checked_rem(Integer(type(2)));
            REQUIRE(result2.has_value());
            CHECK_EQ(result2, Integer(type(-1)));

            const auto result3 = Integer(type(5)).checked_rem(Integer(type(-2)));
            REQUIRE(result3.has_value());
            CHECK_EQ(result3, Integer(type(1)));

            const auto result4 = Integer(type(-5)).checked_rem(Integer(type(-2)));
            REQUIRE(result4.has_value());
            CHECK_EQ(result4, Integer(type(-1)));
        }

        SUBCASE("basic no remainder")
        {
            const auto x = Integer(type(9));
            const auto result = x.checked_rem(Integer(type(3)));

            REQUIRE(result.has_value());
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive % positive")
        {
            const auto x = Integer(type(10));
            const auto result = x.checked_rem(Integer(type(3)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(1)));
        }

        SUBCASE("positive % negative")
        {
            const auto x = Integer(type(10));
            const auto result = x.checked_rem(Integer(type(-3)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(1)));
        }

        SUBCASE("negative % positive")
        {
            const auto x = Integer(type(-10));
            const auto result = x.checked_rem(Integer(type(3)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(-1)));
        }

        SUBCASE("negative % negative")
        {
            const auto x = Integer(type(-10));
            const auto result = x.checked_rem(Integer(type(-3)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(-1)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_rem(Integer(type(-1)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }

        SUBCASE("division by zero")
        {
            const auto x = Integer(type(5));
            const auto result = x.checked_rem(Integer(type(0)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_rem_euclid ",
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
            const auto result1 = Integer(type(5)).checked_rem_euclid(Integer(type(2)));
            REQUIRE(result1.has_value());
            CHECK_EQ(result1, Integer(type(1)));

            const auto result2 = Integer(type(-5)).checked_rem_euclid(Integer(type(2)));
            REQUIRE(result2.has_value());
            CHECK_EQ(result2, Integer(type(1)));

            const auto result3 = Integer(type(5)).checked_rem_euclid(Integer(type(-2)));
            REQUIRE(result3.has_value());
            CHECK_EQ(result3, Integer(type(1)));

            const auto result4 = Integer(type(-5)).checked_rem_euclid(Integer(type(-2)));
            REQUIRE(result4.has_value());
            CHECK_EQ(result4, Integer(type(1)));
        }

        SUBCASE("basic no remainder")
        {
            const auto x = Integer(type(9));
            const auto result = x.checked_rem_euclid(Integer(type(3)));

            REQUIRE(result.has_value());
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive % positive")
        {
            const auto x = Integer(type(10));
            const auto result = x.checked_rem_euclid(Integer(type(3)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(1)));
        }

        SUBCASE("positive % negative")
        {
            const auto x = Integer(type(10));
            const auto result = x.checked_rem_euclid(Integer(type(-3)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(1)));
        }

        SUBCASE("negative % positive")
        {
            const auto x = Integer(type(-10));
            const auto result = x.checked_rem_euclid(Integer(type(3)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(2)));
        }

        SUBCASE("negative % negative")
        {
            const auto x = Integer(type(-10));
            const auto result = x.checked_rem_euclid(Integer(type(-3)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(2)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_rem_euclid(Integer(type(-1)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }

        SUBCASE("division by zero")
        {
            const auto x = Integer(type(5));
            const auto result = x.checked_rem_euclid(Integer(type(0)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_neg ",
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
            const auto result = x.checked_neg();

            REQUIRE(result.has_value());
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive")
        {
            const auto x = Integer(type(10));
            const auto result = x.checked_neg();

            REQUIRE(result.has_value());
            CHECK_EQ(result, Integer(type(-10)));
        }

        SUBCASE("negative")
        {
            const auto x = Integer(type(-10));
            const auto result = x.checked_neg();

            REQUIRE(result.has_value());
            CHECK_EQ(result, Integer(type(10)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();

            const auto result = x.checked_neg();

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_pow ",
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
            CHECK_EQ(x.checked_pow(0_u32), 0);
            CHECK_EQ(x.checked_pow(1_u32), 0);
            CHECK_EQ(x.checked_pow(2_u32), 0);
            CHECK_EQ(x.checked_pow(3_u32), 0);
            CHECK_EQ(x.checked_pow(4_u32), 0);
            CHECK_EQ(x.checked_pow(5_u32), 0);
            CHECK_EQ(x.checked_pow(6_u32), 0);
        }

        SUBCASE("one")
        {
            auto x = Integer(type(1));
            CHECK_EQ(x.checked_pow(0_u32), 1);
            CHECK_EQ(x.checked_pow(1_u32), 1);
            CHECK_EQ(x.checked_pow(2_u32), 1);
            CHECK_EQ(x.checked_pow(3_u32), 1);
            CHECK_EQ(x.checked_pow(4_u32), 1);
            CHECK_EQ(x.checked_pow(5_u32), 1);
            CHECK_EQ(x.checked_pow(6_u32), 1);
        }

        SUBCASE("two")
        {
            auto x = Integer(type(2));
            CHECK_EQ(x.checked_pow(0_u32), 1);
            CHECK_EQ(x.checked_pow(1_u32), 2);
            CHECK_EQ(x.checked_pow(2_u32), 4);
            CHECK_EQ(x.checked_pow(3_u32), 8);
            CHECK_EQ(x.checked_pow(4_u32), 16);
            CHECK_EQ(x.checked_pow(5_u32), 32);
            CHECK_EQ(x.checked_pow(6_u32), 64);
        }

        SUBCASE("negative two")
        {
            auto x = Integer(type(-2));
            CHECK_EQ(x.checked_pow(0_u32), 1);
            CHECK_EQ(x.checked_pow(1_u32), -2);
            CHECK_EQ(x.checked_pow(2_u32), 4);
            CHECK_EQ(x.checked_pow(3_u32), -8);
            CHECK_EQ(x.checked_pow(4_u32), 16);
            CHECK_EQ(x.checked_pow(5_u32), -32);
            CHECK_EQ(x.checked_pow(6_u32), 64);
        }

        SUBCASE("overflow")
        {
            auto x = Integer(type(2));
            CHECK_EQ(x.checked_pow(100_u32), std::nullopt);
        }
    }
}
