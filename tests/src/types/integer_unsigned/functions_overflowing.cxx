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
#include "data/sub-data.hxx"
#include "ztd/detail/types.hxx"

TEST_SUITE("unsigned integer<T>" * doctest::description(""))
{
    using namespace ztd::literals::type_literals;

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
            for (const auto& [x, y, wanted] : test::unsigned_int::add_data<Integer>)
            {
                auto [result, overflow] = x.overflowing_add(y);

                CHECK_FALSE(overflow);
                CHECK_MESSAGE(result == wanted,
                              std::format("{} + {} = {} | wanted {}", x, y, result, wanted));
            }
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(10));
            const auto [result, overflow] = x.overflowing_add(x);

            CHECK_FALSE(overflow);
            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MAX();
            const auto [result, overflow] = x.overflowing_add(Integer(type(1)));

            CHECK(overflow);
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

        SUBCASE("basic")
        {
            for (const auto& [x, y, wanted] :
                 test::unsigned_int::add_signed_data<Integer,
                                                     decltype(Integer(type(1)).cast_signed())>)
            {
                auto [result, overflow] = x.overflowing_add(y);

                CHECK_FALSE(overflow);
                CHECK_MESSAGE(result == wanted,
                              std::format("{} + {} = {} | wanted {}", x, y, result, wanted));
            }
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(10));
            const auto [result, overflow] = x.overflowing_add(x.cast_signed());

            CHECK_FALSE(overflow);
            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MAX();
            const auto [result, overflow] = x.overflowing_add(Integer(type(1)).cast_signed());

            CHECK(overflow);
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
            for (const auto& [x, y, wanted] : test::unsigned_int::sub_data<Integer>)
            {
                auto [result, overflow] = x.overflowing_sub(y);

                CHECK_FALSE(overflow);
                CHECK_MESSAGE(result == wanted,
                              std::format("{} - {} = {} | wanted {}", x, y, result, wanted));
            }
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(100));
            const auto [result, overflow] = x.overflowing_sub(x);

            CHECK_FALSE(overflow);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_sub(Integer(type(1)));

            CHECK(overflow);
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

        SUBCASE("basic")
        {
            for (const auto& [x, y, wanted] :
                 test::unsigned_int::sub_signed_data<Integer,
                                                     decltype(Integer(type(1)).cast_signed())>)
            {
                auto [result, overflow] = x.overflowing_sub(y);

                CHECK_FALSE(overflow);
                CHECK_MESSAGE(result == wanted,
                              std::format("{} + {} = {} | wanted {}", x, y, result, wanted));
            }
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(100));
            const auto [result, overflow] = x.overflowing_sub(x.cast_signed());

            CHECK_FALSE(overflow);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("underflow")
        {
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_sub(Integer(type(1)).cast_signed());

            CHECK(overflow);
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

            CHECK_FALSE(overflow);
            CHECK_EQ(result, Integer(type(5)));
        }

        SUBCASE("self")
        {
            const auto x = Integer(type(5));
            const auto [result, overflow] = x.overflowing_mul(x);

            CHECK_FALSE(overflow);
            CHECK_EQ(result, Integer(type(25)));
        }

        SUBCASE("positive * positive - overflow")
        {
#if 0
            // TODO either find a type agnostic way to test overflow
            // or use if constexpr and hardcode overflow tests
            const auto x = Integer::MAX();
            const auto [result, overflow] = x.overflowing_mul(Integer(type(2)));

            CHECK(overflow);
            CHECK_EQ(result, Integer::MAX());
#endif
        }

        SUBCASE("positive * positive - ok")
        {
            const auto x = Integer(type(5));
            const auto [result, overflow] = x.overflowing_mul(Integer(type(2)));

            CHECK_FALSE(overflow);
            CHECK_EQ(result, Integer(type(10)));
        }

        SUBCASE("zero * positive")
        {
            const auto x = Integer(type(0));
            const auto [result, overflow] = x.overflowing_mul(Integer::MAX());

            CHECK_FALSE(overflow);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive * zero")
        {
            const auto x = Integer::MAX();
            const auto [result, overflow] = x.overflowing_mul(Integer(type(0)));

            CHECK_FALSE(overflow);
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
        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] : test::unsigned_int::div_data<Integer>)
            {
                auto [result, overflow] = dividend.overflowing_div(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
                CHECK_FALSE(overflow);
            }
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
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] : test::unsigned_int::div_data<Integer>)
            {
                auto [result, overflow] = dividend.overflowing_div_down(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
                CHECK_FALSE(overflow);
            }
        }
    }

    TEST_CASE_TEMPLATE("overflowing_div_up ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] : test::unsigned_int::div_up_data<Integer>)
            {
                auto [result, overflow] = dividend.overflowing_div_up(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
                CHECK_FALSE(overflow);
            }
        }
    }

    TEST_CASE_TEMPLATE("overflowing_div_floor ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] :
                 test::unsigned_int::div_floor_data<Integer>)
            {
                auto [result, overflow] = dividend.overflowing_div_floor(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
                CHECK_FALSE(overflow);
            }
        }
    }

    TEST_CASE_TEMPLATE("overflowing_div_ceil ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] :
                 test::unsigned_int::div_ceil_data<Integer>)
            {
                auto [result, overflow] = dividend.overflowing_div_ceil(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
                CHECK_FALSE(overflow);
            }
        }
    }

    TEST_CASE_TEMPLATE("overflowing_div_euclid ",
                       Integer,
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] :
                 test::unsigned_int::div_euclid_data<Integer>)
            {
                auto [result, overflow] = dividend.overflowing_div_euclid(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
                CHECK_FALSE(overflow);
            }
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
                       ztd::v2::u8,
                       ztd::v2::u16,
                       ztd::v2::u32,
                       ztd::v2::u64,
                       ztd::v2::usize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("basic remainder")
        {
            const auto [result, overflow] = Integer(type(5)).overflowing_rem(Integer(type(2)));
            CHECK_EQ(result, Integer(type(1)));
            CHECK_FALSE(overflow);
        }

        SUBCASE("basic no remainder")
        {
            const auto x = Integer(type(9));
            const auto [result, overflow] = x.overflowing_rem(Integer(type(3)));

            CHECK_FALSE(overflow);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive % positive")
        {
            const auto x = Integer(type(10));
            const auto [result, overflow] = x.overflowing_rem(Integer(type(3)));

            CHECK_FALSE(overflow);
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

    TEST_CASE_TEMPLATE("overflowing_rem_euclid ",
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
            const auto [result, overflow] =
                Integer(type(5)).overflowing_rem_euclid(Integer(type(2)));
            CHECK_EQ(result, Integer(type(1)));
            CHECK_FALSE(overflow);
        }

        SUBCASE("basic no remainder")
        {
            const auto x = Integer(type(9));
            const auto [result, overflow] = x.overflowing_rem_euclid(Integer(type(3)));

            CHECK_FALSE(overflow);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive % positive")
        {
            const auto x = Integer(type(10));
            const auto [result, overflow] = x.overflowing_rem_euclid(Integer(type(3)));

            CHECK_FALSE(overflow);
            CHECK_EQ(result, Integer(type(1)));
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(5));

            CHECK_THROWS_AS((void)x.overflowing_rem_euclid(Integer(type(0))), std::runtime_error);
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

            CHECK_FALSE(overflow);
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("overflow")
        {
#if 0
            // TODO either find a type agnostic way to test overflow
            // or use if constexpr and hardcode overflow tests
            const auto x = Integer::MIN();
            const auto [result, overflow] = x.overflowing_neg();

            CHECK(overflow);
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
            CHECK(overflow);
        }
    }
}
