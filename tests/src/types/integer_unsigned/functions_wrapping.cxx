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

    TEST_CASE_TEMPLATE("wrapping_div_down ",
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
                const auto result = dividend.wrapping_div_down(divisor);

                CHECK_EQ(result, wanted);
            }
        }
    }

    TEST_CASE_TEMPLATE("wrapping_div_up ",
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
                const auto result = dividend.wrapping_div_up(divisor);

                CHECK_EQ(result, wanted);
            }
        }
    }

    TEST_CASE_TEMPLATE("wrapping_div_floor ",
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
                const auto result = dividend.wrapping_div_floor(divisor);

                CHECK_EQ(result, wanted);
            }
        }
    }

    TEST_CASE_TEMPLATE("wrapping_div_ceil ",
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
                auto result = dividend.wrapping_div_ceil(divisor);

                CHECK_EQ(result, wanted);
            }
        }
    }

    TEST_CASE_TEMPLATE("wrapping_div_euclid ",
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
            const auto result = x.wrapping_div_euclid(Integer(type(2)));

            CHECK_EQ(result, Integer(type(32)));
        }

        SUBCASE("positive / positive")
        {
            const auto x = Integer(type(100));
            const auto result = x.wrapping_div_euclid(Integer(type(5)));

            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(1));

            CHECK_THROWS_AS((void)x.wrapping_div_euclid(Integer(type(0))), std::runtime_error);
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
            const auto result = Integer(type(5)).wrapping_rem(Integer(type(2)));
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

    TEST_CASE_TEMPLATE("wrapping_rem_euclid ",
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
            const auto result = Integer(type(5)).wrapping_rem_euclid(Integer(type(2)));
            CHECK_EQ(result, Integer(type(1)));
        }

        SUBCASE("basic no remainder")
        {
            const auto x = Integer(type(9));
            const auto result = x.wrapping_rem_euclid(Integer(type(3)));

            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive % positive")
        {
            const auto x = Integer(type(10));
            const auto result = x.wrapping_rem_euclid(Integer(type(3)));

            CHECK_EQ(result, Integer(type(1)));
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(5));

            CHECK_THROWS_AS((void)x.wrapping_rem_euclid(Integer(type(0))), std::runtime_error);
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
}
