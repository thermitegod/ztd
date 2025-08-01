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

#include "../utils.hxx"
#include "ztd/detail/types.hxx"

TEST_SUITE("unsigned integer<T>" * doctest::description(""))
{
    using namespace ztd::literals::type_literals;

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

    TEST_CASE_TEMPLATE("checked_div_down ",
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
            std::vector<div_data<Integer>> test_data{
                // positive / positive
                {
                    .dividend = Integer(type(7)),
                    .divisor = Integer(type(3)),
                    .result = Integer(type(2)),
                },
            };

            for (const auto& [dividend, divisor, wanted] : test_data)
            {
                const auto result = dividend.checked_div_down(divisor);

                CHECK_EQ(result, wanted);
            }
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
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
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
            };

            for (const auto& [dividend, divisor, wanted] : test_data)
            {
                const auto result = dividend.checked_div_up(divisor);

                CHECK_EQ(result, wanted);
            }
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
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
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
            };

            for (const auto& [dividend, divisor, wanted] : test_data)
            {
                const auto result = dividend.checked_div_floor(divisor);

                CHECK_EQ(result, wanted);
            }
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
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
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
            };

            for (const auto& [dividend, divisor, wanted] : test_data)
            {
                auto result = dividend.checked_div_ceil(divisor);

                CHECK_EQ(result, wanted);
            }
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
            const auto result = x.checked_div_euclid(Integer(type(2)));

            REQUIRE(result.has_value());
            CHECK_EQ(result, Integer(type(32)));
        }

        SUBCASE("positive / positive")
        {
            const auto x = Integer(type(100));
            const auto result = x.checked_div_euclid(Integer(type(5)));

            REQUIRE(result.has_value());
            CHECK_EQ(*result, Integer(type(20)));
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
            const auto result = Integer(type(5)).checked_rem(Integer(type(2)));
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

    TEST_CASE_TEMPLATE("checked_rem_euclid ",
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
            const auto result = x.checked_rem_euclid(Integer(type(2)));

            REQUIRE(result.has_value());
            CHECK_EQ(result, Integer(type(1)));
        }

        SUBCASE("basic remainder")
        {
            const auto result = Integer(type(5)).checked_rem_euclid(Integer(type(2)));
            REQUIRE(result.has_value());
            CHECK_EQ(result, Integer(type(1)));
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
}
