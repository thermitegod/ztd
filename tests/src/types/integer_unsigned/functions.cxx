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

#include <format>
#include <ranges>

#include <doctest/doctest.h>

#include "ztd/detail/types.hxx"

// Note - can not check division/modulo by zero because
//        they will panic

TEST_SUITE("unsigned integer<T>" * doctest::description(""))
{
    using namespace ztd::literals::type_literals;

    TEST_CASE_TEMPLATE("std::formatter ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        const auto x = Integer(type(100));
        const auto result = std::format("{}", x);
        CHECK_EQ(result, "100");
    }

    TEST_CASE_TEMPLATE("checked_add ",
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

        SUBCASE("overflow")
        {
            const auto x = Integer::MAX();
            const auto result = x.checked_add(Integer(type(1)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_add signed overload ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("self")
        {
            const auto x = Integer(type(10));
            const auto result = x.checked_add(x.cast_signed());

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(20)));
        }

        SUBCASE("positive + positive")
        {
            const auto x = Integer(type(5));
            const auto result = x.checked_add(Integer(type(10)).cast_signed());

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(15)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MAX();
            const auto result = x.checked_add(Integer(type(1)).cast_signed());

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_sub ",
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

        SUBCASE("positive - positive - ok")
        {
            const auto x = Integer(type(10));
            const auto result = x.checked_sub(Integer(type(5)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(5)));
        }

        SUBCASE("positive - positive - underflow")
        {
            const auto x = Integer(type(5));
            const auto result = x.checked_sub(Integer(type(10)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_sub(Integer(type(1)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_sub signed overload ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("self")
        {
            const auto x = Integer(type(100));
            const auto result = x.checked_sub(x.cast_signed());

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(0)));
        }

        SUBCASE("positive - positive - ok")
        {
            const auto x = Integer(type(10));
            const auto result = x.checked_sub(Integer(type(5)).cast_signed());

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(5)));
        }

        SUBCASE("positive - positive - underflow")
        {
            const auto x = Integer(type(5));
            const auto result = x.checked_sub(Integer(type(10)).cast_signed());

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.checked_sub(Integer(type(1)).cast_signed());

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_mul ",
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
    }

    TEST_CASE_TEMPLATE("checked_div ",
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
            const auto x = Integer(type(64));
            const auto result = x.checked_div(Integer(type(2)));

            REQUIRE(result.has_value());
            CHECK_EQ(result, Integer(type(32)));
        }

        SUBCASE("positive / positive")
        {
            const auto x = Integer(type(100));
            const auto result = x.checked_div(Integer(type(5)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(20)));
        }

        SUBCASE("division by zero")
        {
            const auto x = Integer(type(1));
            const auto result = x.checked_div(Integer(type(0)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_rem ",
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
            const auto x = Integer(type(5));
            const auto result = x.checked_rem(Integer(type(2)));

            REQUIRE(result.has_value());
            CHECK_EQ(result, Integer(type(1)));
        }

        SUBCASE("basic remainder")
        {
            const auto x = Integer(type(10));
            const auto result = x.checked_rem(Integer(type(3)));

            REQUIRE(result.has_value());
            CHECK_EQ(result, Integer(type(1)));
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

        SUBCASE("division by zero")
        {
            const auto x = Integer(type(5));
            const auto result = x.checked_rem(Integer(type(0)));

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_neg ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("zero")
        {
            const auto x = Integer(type(0));
            const auto result = x.checked_neg();

            REQUIRE(result.has_value());
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("overflow")
        {
            Integer x;

            SUBCASE("basic")
            {
                x = Integer(type(1));
            }

            SUBCASE("max")
            {
                x = Integer::MAX();
            }

            const auto result = x.checked_neg();

            REQUIRE(!result.has_value());
            CHECK_EQ(result, std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_pow ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
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

        SUBCASE("overflow")
        {
            auto x = Integer(type(2));
            CHECK_EQ(x.checked_pow(100_u32), std::nullopt);
        }
    }
    TEST_CASE_TEMPLATE("saturating_add ",
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
            const auto x = Integer::MAX() - Integer(type(2));
            const auto result = x.saturating_add(Integer(type(1)));

            CHECK_EQ(result, Integer::MAX() - Integer(type(1)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(10));
            const auto result = x.saturating_add(x);

            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("positive + positive")
        {
            const auto x = Integer(type(5));
            const auto result = x.saturating_add(Integer(type(10)));

            CHECK_EQ(result, Integer(type(15)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MAX();
            const auto result = x.saturating_add(Integer(type(1)));

            CHECK_EQ(result, Integer::MAX());
        }
    }

    TEST_CASE_TEMPLATE("saturating_sub ",
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

        SUBCASE("positive - positive - ok")
        {
            const auto x = Integer(type(10));
            const auto result = x.saturating_sub(Integer(type(5)));

            CHECK_EQ(result, Integer(type(5)));
        }

        SUBCASE("positive - positive - underflow")
        {
            const auto x = Integer(type(5));
            const auto result = x.saturating_sub(Integer(type(10)));

            CHECK_EQ(result, Integer::MIN());
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
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
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
    }

    TEST_CASE_TEMPLATE("saturating_div ",
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
            const auto x = Integer(type(64));
            const auto result = x.saturating_div(Integer(type(2)));

            CHECK_EQ(result, Integer(type(32)));
        }

        SUBCASE("positive / positive")
        {
            const auto x = Integer(type(100));
            const auto result = x.saturating_div(Integer(type(5)));

            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(1));

            CHECK_THROWS_AS((void)x.saturating_div(Integer(type(0))), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("saturating_pow ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
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

        SUBCASE("overflow")
        {
            auto x = Integer(type(2));
            CHECK_EQ(x.saturating_pow(100_u32), Integer::MAX());
        }
    }

    TEST_CASE_TEMPLATE("overflowing_add ",
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

        SUBCASE("overflow")
        {
            const auto x = Integer::MAX();
            const auto [result, overflow] = x.overflowing_add(Integer(type(1)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MIN());
        }
    }

    TEST_CASE_TEMPLATE("overflowing_add signed overload ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("self")
        {
            const auto x = Integer(type(10));
            const auto [result, overflow] = x.overflowing_add(x.cast_signed());

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("positive + positive")
        {
            const auto x = Integer(type(5));
            const auto [result, overflow] = x.overflowing_add(Integer(type(10)).cast_signed());

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(15)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MAX();
            const auto [result, overflow] = x.overflowing_add(Integer(type(1)).cast_signed());

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MIN());
        }
    }

    TEST_CASE_TEMPLATE("overflowing_sub ",
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

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_sub(Integer(type(1)));

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MAX());
        }
    }

    TEST_CASE_TEMPLATE("overflowing_sub signed overload ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("self")
        {
            const auto x = Integer(type(100));
            const auto [result, overflow] = x.overflowing_sub(x.cast_signed());

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_sub(Integer(type(1)).cast_signed());

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MAX());
        }
    }

    TEST_CASE_TEMPLATE("overflowing_mul ",
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
    }

    TEST_CASE_TEMPLATE("overflowing_div ",
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
            const auto x = Integer(type(64));
            const auto [result, overflow] = x.overflowing_div(Integer(type(2)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(32)));
        }

        SUBCASE("positive / positive")
        {
            const auto x = Integer(type(100));
            const auto [result, overflow] = x.overflowing_div(Integer(type(5)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(1));

            CHECK_THROWS_AS((void)x.overflowing_div(Integer(type(0))), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("overflowing_rem ",
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
            const auto x = Integer(type(10));
            const auto [result, overflow] = x.overflowing_rem(Integer(type(3)));

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(1)));
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
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("zero")
        {
            const auto x = Integer(type(0));
            const auto [result, overflow] = x.overflowing_neg();

            CHECK_EQ(overflow, false);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("overflow")
        {
#if 0
            // TODO either find a type agnostic way to test overflow
            // or use if constexpr and hardcode overflow tests
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_neg();

            CHECK_EQ(overflow, true);
            CHECK_EQ(result, Integer::MIN());
#endif
        }
    }

    TEST_CASE_TEMPLATE("overflowing_pow ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
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

        SUBCASE("overflow")
        {
            auto x = Integer(type(2));
            [[maybe_unused]] auto [result, overflow] = x.overflowing_pow(100_u32);
            CHECK_EQ(overflow, true);
        }
    }
    TEST_CASE_TEMPLATE("wrapping_add ",
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
            const auto x = Integer::MAX() - Integer(type(2));
            const auto result = x.wrapping_add(Integer(type(1)));

            CHECK_EQ(result, Integer::MAX() - Integer(type(1)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(10));
            const auto result = x.wrapping_add(x);

            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("positive + positive")
        {
            const auto x = Integer(type(5));
            const auto result = x.wrapping_add(Integer(type(10)));

            CHECK_EQ(result, Integer(type(15)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MAX();
            const auto result = x.wrapping_add(Integer(type(1)));

            CHECK_EQ(result, Integer::MIN());
        }
    }

    TEST_CASE_TEMPLATE("wrapping_add signed overload ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("self")
        {
            const auto x = Integer(type(10));
            const auto result = x.wrapping_add(x.cast_signed());

            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("positive + positive")
        {
            const auto x = Integer(type(5));
            const auto result = x.wrapping_add(Integer(type(10)).cast_signed());

            CHECK_EQ(result, Integer(type(15)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MAX();
            const auto result = x.wrapping_add(Integer(type(1)).cast_signed());

            CHECK_EQ(result, Integer::MIN());
        }
    }

    TEST_CASE_TEMPLATE("wrapping_sub ",
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
            const auto x = Integer(type(1));
            const auto result = x.wrapping_sub(Integer(type(1)));

            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(100));
            const auto result = x.wrapping_sub(x);

            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.wrapping_sub(Integer(type(1)));

            CHECK_EQ(result, Integer::MAX());
        }
    }

    TEST_CASE_TEMPLATE("wrapping_sub signed overload ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("self")
        {
            const auto x = Integer(type(100));
            const auto result = x.wrapping_sub(x.cast_signed());

            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto result = x.wrapping_sub(Integer(type(1)).cast_signed());

            CHECK_EQ(result, Integer::MAX());
        }
    }

    TEST_CASE_TEMPLATE("wrapping_mul ",
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
            const auto x = Integer(type(5));
            const auto result = x.wrapping_mul(Integer(type(1)));

            CHECK_EQ(result, Integer(type(5)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(5));
            const auto result = x.wrapping_mul(x);

            CHECK_EQ(result, Integer(type(25)));
        }

        SUBCASE("positive * positive - overflow")
        {
#if 0
            // TODO either find a type agnostic way to test overflow
            // or use if constexpr and hardcode overflow tests
            const auto x = Integer::MAX();
            const auto result = x.wrapping_mul(Integer(type(2)));

            CHECK_EQ(result, Integer::MAX());
#endif
        }

        SUBCASE("positive * positive - ok")
        {
            const auto x = Integer(type(5));
            const auto result = x.wrapping_mul(Integer(type(2)));

            CHECK_EQ(result, Integer(type(10)));
        }

        SUBCASE("zero * positive")
        {
            const auto x = Integer(type(0));
            const auto result = x.wrapping_mul(Integer::MAX());

            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive * zero")
        {
            const auto x = Integer::MAX();
            const auto result = x.wrapping_mul(Integer(type(0)));

            CHECK_EQ(result, Integer(type(0)));
        }
    }

    TEST_CASE_TEMPLATE("wrapping_div ",
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
            const auto x = Integer(type(64));
            const auto result = x.wrapping_div(Integer(type(2)));

            CHECK_EQ(result, Integer(type(32)));
        }

        SUBCASE("positive / positive")
        {
            const auto x = Integer(type(100));
            const auto result = x.wrapping_div(Integer(type(5)));

            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(1));

            CHECK_THROWS_AS((void)x.wrapping_div(Integer(type(0))), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("wrapping_rem ",
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
            const auto x = Integer(type(10));
            const auto result = x.wrapping_rem(Integer(type(3)));

            CHECK_EQ(result, Integer(type(1)));
        }

        SUBCASE("basic no remainder")
        {
            const auto x = Integer(type(9));
            const auto result = x.wrapping_rem(Integer(type(3)));

            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive % positive")
        {
            const auto x = Integer(type(10));
            const auto result = x.wrapping_rem(Integer(type(3)));

            CHECK_EQ(result, Integer(type(1)));
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(5));

            CHECK_THROWS_AS((void)x.wrapping_rem(Integer(type(0))), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("wrapping_neg ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("zero")
        {
            const auto x = Integer(type(0));
            const auto result = x.wrapping_neg();

            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("overflow")
        {
#if 0
            // TODO either find a type agnostic way to test overflow
            // or use if constexpr and hardcode overflow tests
            const auto x = Integer::MIN();
            const auto result = x.wrapping_neg();

            CHECK_EQ(result, Integer::MIN());
#endif
        }
    }

    TEST_CASE_TEMPLATE("wrapping_pow ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("zero")
        {
            auto x = Integer(type(0));
            CHECK_EQ(x.wrapping_pow(0_u32), 0);
            CHECK_EQ(x.wrapping_pow(1_u32), 0);
            CHECK_EQ(x.wrapping_pow(2_u32), 0);
            CHECK_EQ(x.wrapping_pow(3_u32), 0);
            CHECK_EQ(x.wrapping_pow(4_u32), 0);
            CHECK_EQ(x.wrapping_pow(5_u32), 0);
            CHECK_EQ(x.wrapping_pow(6_u32), 0);
        }

        SUBCASE("one")
        {
            auto x = Integer(type(1));
            CHECK_EQ(x.wrapping_pow(0_u32), 1);
            CHECK_EQ(x.wrapping_pow(1_u32), 1);
            CHECK_EQ(x.wrapping_pow(2_u32), 1);
            CHECK_EQ(x.wrapping_pow(3_u32), 1);
            CHECK_EQ(x.wrapping_pow(4_u32), 1);
            CHECK_EQ(x.wrapping_pow(5_u32), 1);
            CHECK_EQ(x.wrapping_pow(6_u32), 1);
        }

        SUBCASE("two")
        {
            auto x = Integer(type(2));
            CHECK_EQ(x.wrapping_pow(0_u32), 1);
            CHECK_EQ(x.wrapping_pow(1_u32), 2);
            CHECK_EQ(x.wrapping_pow(2_u32), 4);
            CHECK_EQ(x.wrapping_pow(3_u32), 8);
            CHECK_EQ(x.wrapping_pow(4_u32), 16);
            CHECK_EQ(x.wrapping_pow(5_u32), 32);
            CHECK_EQ(x.wrapping_pow(6_u32), 64);
        }
    }
    TEST_CASE_TEMPLATE("abs_diff ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        CHECK_EQ((Integer(type(100))).abs_diff(Integer(type(80))), Integer(type(20)));
        CHECK_EQ((Integer(type(100))).abs_diff(Integer(type(10))), Integer(type(90)));

        CHECK_EQ((Integer(type(80))).abs_diff(Integer(type(100))), Integer(type(20)));
        CHECK_EQ((Integer(type(10))).abs_diff(Integer(type(100))), Integer(type(90)));
    }

    TEST_CASE_TEMPLATE("max ",
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
            const auto a = Integer(type(5));
            const auto b = Integer(type(10));
            CHECK_EQ(a.max(b), b);
        }

        SUBCASE("self")
        {
            const auto a = Integer(type(10));
            CHECK_EQ(a.max(a), a);
        }

        SUBCASE("eq")
        {
            const auto a = Integer(type(10));
            const auto b = Integer(type(10));

            CHECK_EQ(a.max(b), a);
            CHECK_EQ(a.max(b), b);

            CHECK_EQ(b.max(a), a);
            CHECK_EQ(b.max(a), b);
        }
    }

    TEST_CASE_TEMPLATE("min ",
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
            const auto a = Integer(type(5));
            const auto b = Integer(type(10));
            CHECK_EQ(a.min(b), a);
        }

        SUBCASE("self")
        {
            const auto a = Integer(type(10));
            CHECK_EQ(a.min(a), a);
        }

        SUBCASE("eq")
        {
            const auto a = Integer(type(10));
            const auto b = Integer(type(10));

            CHECK_EQ(a.min(b), a);
            CHECK_EQ(a.min(b), b);

            CHECK_EQ(b.min(a), a);
            CHECK_EQ(b.min(a), b);
        }
    }

    TEST_CASE_TEMPLATE("pow ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("zero")
        {
            auto x = Integer(type(0));
            CHECK_EQ(x.pow(0_u32), 0);
            CHECK_EQ(x.pow(1_u32), 0);
            CHECK_EQ(x.pow(2_u32), 0);
            CHECK_EQ(x.pow(3_u32), 0);
            CHECK_EQ(x.pow(4_u32), 0);
            CHECK_EQ(x.pow(5_u32), 0);
            CHECK_EQ(x.pow(6_u32), 0);
        }

        SUBCASE("one")
        {
            auto x = Integer(type(1));
            CHECK_EQ(x.pow(0_u32), 1);
            CHECK_EQ(x.pow(1_u32), 1);
            CHECK_EQ(x.pow(2_u32), 1);
            CHECK_EQ(x.pow(3_u32), 1);
            CHECK_EQ(x.pow(4_u32), 1);
            CHECK_EQ(x.pow(5_u32), 1);
            CHECK_EQ(x.pow(6_u32), 1);
        }

        SUBCASE("two")
        {
            auto x = Integer(type(2));
            CHECK_EQ(x.pow(0_u32), 1);
            CHECK_EQ(x.pow(1_u32), 2);
            CHECK_EQ(x.pow(2_u32), 4);
            CHECK_EQ(x.pow(3_u32), 8);
            CHECK_EQ(x.pow(4_u32), 16);
            CHECK_EQ(x.pow(5_u32), 32);
            CHECK_EQ(x.pow(6_u32), 64);
        }
    }

    TEST_CASE_TEMPLATE("is_even ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("even numbers")
        {
            CHECK_EQ(Integer(type(0)).is_even(), true);
            CHECK_EQ(Integer(type(2)).is_even(), true);
            CHECK_EQ(Integer(type(4)).is_even(), true);
            CHECK_EQ(Integer(type(6)).is_even(), true);
            CHECK_EQ(Integer(type(8)).is_even(), true);
            CHECK_EQ(Integer(type(10)).is_even(), true);
            CHECK_EQ(Integer(type(12)).is_even(), true);
            CHECK_EQ(Integer(type(14)).is_even(), true);
            CHECK_EQ(Integer(type(16)).is_even(), true);
            CHECK_EQ(Integer(type(18)).is_even(), true);
            CHECK_EQ(Integer(type(20)).is_even(), true);
            CHECK_EQ(Integer(type(22)).is_even(), true);
            CHECK_EQ(Integer(type(24)).is_even(), true);
            CHECK_EQ(Integer(type(26)).is_even(), true);
            CHECK_EQ(Integer(type(28)).is_even(), true);
            CHECK_EQ(Integer(type(30)).is_even(), true);
        }

        SUBCASE("odd numbers")
        {
            CHECK_EQ(Integer(type(1)).is_even(), false);
            CHECK_EQ(Integer(type(3)).is_even(), false);
            CHECK_EQ(Integer(type(5)).is_even(), false);
            CHECK_EQ(Integer(type(7)).is_even(), false);
            CHECK_EQ(Integer(type(9)).is_even(), false);
            CHECK_EQ(Integer(type(11)).is_even(), false);
            CHECK_EQ(Integer(type(13)).is_even(), false);
            CHECK_EQ(Integer(type(15)).is_even(), false);
            CHECK_EQ(Integer(type(17)).is_even(), false);
            CHECK_EQ(Integer(type(19)).is_even(), false);
            CHECK_EQ(Integer(type(21)).is_even(), false);
            CHECK_EQ(Integer(type(23)).is_even(), false);
            CHECK_EQ(Integer(type(25)).is_even(), false);
            CHECK_EQ(Integer(type(27)).is_even(), false);
            CHECK_EQ(Integer(type(29)).is_even(), false);
        }
    }

    TEST_CASE_TEMPLATE("is_odd ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("even numbers")
        {
            CHECK_EQ(Integer(type(0)).is_odd(), false);
            CHECK_EQ(Integer(type(2)).is_odd(), false);
            CHECK_EQ(Integer(type(4)).is_odd(), false);
            CHECK_EQ(Integer(type(6)).is_odd(), false);
            CHECK_EQ(Integer(type(8)).is_odd(), false);
            CHECK_EQ(Integer(type(10)).is_odd(), false);
            CHECK_EQ(Integer(type(12)).is_odd(), false);
            CHECK_EQ(Integer(type(14)).is_odd(), false);
            CHECK_EQ(Integer(type(16)).is_odd(), false);
            CHECK_EQ(Integer(type(18)).is_odd(), false);
            CHECK_EQ(Integer(type(20)).is_odd(), false);
            CHECK_EQ(Integer(type(22)).is_odd(), false);
            CHECK_EQ(Integer(type(24)).is_odd(), false);
            CHECK_EQ(Integer(type(26)).is_odd(), false);
            CHECK_EQ(Integer(type(28)).is_odd(), false);
            CHECK_EQ(Integer(type(30)).is_odd(), false);
        }

        SUBCASE("odd numbers")
        {
            CHECK_EQ(Integer(type(1)).is_odd(), true);
            CHECK_EQ(Integer(type(3)).is_odd(), true);
            CHECK_EQ(Integer(type(5)).is_odd(), true);
            CHECK_EQ(Integer(type(7)).is_odd(), true);
            CHECK_EQ(Integer(type(9)).is_odd(), true);
            CHECK_EQ(Integer(type(11)).is_odd(), true);
            CHECK_EQ(Integer(type(13)).is_odd(), true);
            CHECK_EQ(Integer(type(15)).is_odd(), true);
            CHECK_EQ(Integer(type(17)).is_odd(), true);
            CHECK_EQ(Integer(type(19)).is_odd(), true);
            CHECK_EQ(Integer(type(21)).is_odd(), true);
            CHECK_EQ(Integer(type(23)).is_odd(), true);
            CHECK_EQ(Integer(type(25)).is_odd(), true);
            CHECK_EQ(Integer(type(27)).is_odd(), true);
            CHECK_EQ(Integer(type(29)).is_odd(), true);
        }
    }

    TEST_CASE_TEMPLATE("divmod ",
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
            const auto [q, r] = x.divmod(Integer(type(10)));
            CHECK_EQ(q, Integer(type(10)));
            CHECK_EQ(r, Integer(type(0)));
        }

        SUBCASE("rem")
        {
            const auto x = Integer(type(10));
            const auto [q, r] = x.divmod(Integer(type(3)));
            CHECK_EQ(q, Integer(type(3)));
            CHECK_EQ(r, Integer(type(1)));
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(101));

            CHECK_THROWS_AS((void)x.divmod(Integer(type(0))), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("random ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("small range")
        {
            const auto min = Integer(type(1));
            const auto max = Integer(type(100));

            for (auto _ : std::views::iota(0, 100))
            {
                const auto value = Integer::random(min, max);
                CHECK(value >= min);
                CHECK(value <= max);
            }
        }

        SUBCASE("whole range")
        {
            const auto min = Integer::MIN();
            const auto max = Integer::MAX();

            for (auto _ : std::views::iota(0, 100))
            {
                const auto value = Integer::random(min, max);
                CHECK(value >= min);
                CHECK(value <= max);
            }
        }

        SUBCASE("zero range")
        {
            const auto min = Integer(type(69));
            const auto max = Integer(type(69));

            for (auto _ : std::views::iota(0, 10))
            {
                const auto value = Integer::random(min, max);
                CHECK(value == min);
            }
        }
    }
}
