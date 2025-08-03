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
#include "data/mul-data.hxx"
#include "data/pow-data.hxx"
#include "data/rem-data.hxx"
#include "data/sub-data.hxx"
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
            for (const auto& [x, y, wanted] : test::signed_int::add_data<Integer>)
            {
                auto result = x.checked_add(y);

                REQUIRE(result.has_value());
                CHECK_MESSAGE(result == wanted,
                              std::format("{} + {} = {} | wanted {}", x, y, *result, wanted));
            }
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(10));
            const auto result = x.checked_add(x);

            REQUIRE(result.has_value());
            CHECK_EQ(result, Integer(type(20)));
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

        SUBCASE("basic")
        {
            for (const auto& [x, y, wanted] :
                 test::signed_int::add_unsigned_data<Integer,
                                                     decltype(Integer(type(1)).cast_unsigned())>)
            {
                auto result = x.checked_add(y);

                REQUIRE(result.has_value());
                CHECK_MESSAGE(result == wanted,
                              std::format("{} + {} = {} | wanted {}", x, y, *result, wanted));
            }
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(10));
            const auto result = x.checked_add(x.cast_unsigned());

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(20)));
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
            for (const auto& [x, y, wanted] : test::signed_int::sub_data<Integer>)
            {
                auto result = x.checked_sub(y);

                REQUIRE(result.has_value());
                CHECK_MESSAGE(result == wanted,
                              std::format("{} - {} = {} | wanted {}", x, y, *result, wanted));
            }
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(100));
            const auto result = x.checked_sub(x);

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(0)));
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
            for (const auto& [x, y, wanted] :
                 test::signed_int::sub_unsigned_data<Integer,
                                                     decltype(Integer(type(1)).cast_unsigned())>)
            {
                auto result = x.checked_sub(y);

                REQUIRE(result.has_value());
                CHECK_MESSAGE(result == wanted,
                              std::format("{} + {} = {} | wanted {}", x, y, *result, wanted));
            }
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(100));
            const auto result = x.checked_sub(x.cast_unsigned());

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(0)));
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
            for (const auto& [x, y, wanted] : test::signed_int::mul_data<Integer>)
            {
                auto result = x.checked_mul(y);

                REQUIRE(result.has_value());
                CHECK_MESSAGE(result == wanted,
                              std::format("{} * {} = {} | wanted {}", x, y, *result, wanted));
            }
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(5));
            const auto result = x.checked_mul(x);

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(25)));
        }

        SUBCASE("overflow")
        {
            // positive * positive
            CHECK_EQ(Integer::MAX().checked_mul(Integer::MAX()), std::nullopt);

            // positive * negative
            CHECK_EQ(Integer::MAX().checked_mul(Integer::MIN()), std::nullopt);

            // negative * positive
            CHECK_EQ(Integer::MIN().checked_mul(Integer::MAX()), std::nullopt);

            // negative * negative
            CHECK_EQ(Integer::MIN().checked_mul(Integer::MIN()), std::nullopt);
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

        SUBCASE("basic")
        {
            for (const auto& [x, y, wanted] : test::signed_int::rem_data<Integer>)
            {
                auto result = x.checked_rem(y);

                CHECK_MESSAGE(result == wanted,
                              std::format("{} % {} = {} | wanted {}", x, y, *result, wanted));
            }
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

        SUBCASE("basic")
        {
            for (const auto& [x, y, wanted] : test::signed_int::rem_euclid_data<Integer>)
            {
                auto result = x.checked_rem_euclid(y);

                CHECK_MESSAGE(result == wanted,
                              std::format("{} % {} = {} | wanted {}", x, y, *result, wanted));
            }
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

        SUBCASE("basic")
        {
            for (const auto& [x, e, wanted] : test::signed_int::pow_data<Integer>)
            {
                auto result = x.checked_pow(e);

                REQUIRE(result.has_value());
                CHECK_MESSAGE(result == wanted,
                              std::format("{} ^ {} = {} | wanted {}", x, e, *result, wanted));
            }
        }

        SUBCASE("overflow")
        {
            auto x = Integer(type(2));
            CHECK_EQ(x.checked_pow(100_u32), std::nullopt);
        }
    }
}
