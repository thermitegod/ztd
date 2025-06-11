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

TEST_SUITE("signed integer<T>" * doctest::description(""))
{
    using namespace ztd::literals::type_literals;

    TEST_CASE_TEMPLATE("std::formatter ",
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
            const auto x = Integer(type(100));
            CHECK_EQ(std::format("{}", x), "100");
        }

        SUBCASE("padded")
        {
            const auto x = Integer(type(69));

            CHECK_EQ(std::format("{:06}", x), "000069");
        }
    }

    TEST_CASE_TEMPLATE("abs ",
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
            const auto result = x.abs();
            CHECK_EQ(result, Integer(type(0)));
        }

        SUBCASE("positive")
        {
            const auto x = Integer(type(100));
            const auto result = x.abs();
            CHECK_EQ(result, Integer(type(100)));
        }

        SUBCASE("negative")
        {
            const auto x = Integer(type(-100));
            const auto result = x.abs();
            CHECK_EQ(result, Integer(type(100)));
        }

        SUBCASE("overflow")
        {
            // const auto x = Integer::MIN();
            // CHECK_THROWS_AS((void)x.abs(), std::runtime_error);
        }
    }

    TEST_CASE_TEMPLATE("abs_diff ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;
        using utype = typename Integer::sign_conversion;

        CHECK_EQ(Integer(type(100)).abs_diff(Integer(type(80))),
                 ztd::integer<utype>(std::make_unsigned_t<type>(20)));
        CHECK_EQ(Integer(type(100)).abs_diff(Integer(type(110))),
                 ztd::integer<utype>(std::make_unsigned_t<type>(10)));
        CHECK_EQ(Integer(type(-100)).abs_diff(Integer(type(80))),
                 ztd::integer<utype>(std::make_unsigned_t<type>(180)));
        CHECK_EQ(Integer(type(-100)).abs_diff(Integer(type(-120))),
                 ztd::integer<utype>(std::make_unsigned_t<type>(20)));

        CHECK_EQ(Integer::MIN().abs_diff(Integer::MAX()), ztd::integer<utype>::MAX());
    }

    TEST_CASE_TEMPLATE("unsigned_abs ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;
        using utype = typename Integer::sign_conversion;

        SUBCASE("zero")
        {
            const auto x = Integer(type(0));

            CHECK_EQ(x.unsigned_abs(), ztd::integer<utype>(std::make_unsigned_t<type>(0)));
        }

        SUBCASE("positive")
        {
            const auto x = Integer(type(100));

            CHECK_EQ(x.unsigned_abs(), ztd::integer<utype>(std::make_unsigned_t<type>(100)));
        }

        SUBCASE("negative")
        {
            const auto x = Integer(type(-100));

            CHECK_EQ(x.unsigned_abs(), ztd::integer<utype>(std::make_unsigned_t<type>(100)));
        }

        SUBCASE("overflow")
        {
            const auto x = Integer::MIN();

            CHECK_EQ(x.unsigned_abs(),
                     ztd::integer<utype>(std::make_unsigned_t<type>(2))
                         .pow(ztd::integer<utype>::BITS() - 1u));
        }
    }

    TEST_CASE_TEMPLATE("max ",
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
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
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

    TEST_CASE_TEMPLATE("signum ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("positive")
        {
            auto x = Integer(type(100));
            CHECK_EQ(x.signum(), Integer(type(1)));
        }

        SUBCASE("zero")
        {
            auto x = Integer(type(0));
            CHECK_EQ(x.signum(), Integer(type(0)));
        }

        SUBCASE("negative")
        {
            auto x = Integer(type(-100));
            CHECK_EQ(x.signum(), Integer(type(-1)));
        }
    }

    TEST_CASE_TEMPLATE("div_ceil ",
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
            auto x = Integer(type(8));
            auto y = Integer(type(3));

            const auto result1 = x.div_ceil(y);
            CHECK_EQ(result1, Integer(type(3)));

            const auto result2 = x.div_ceil(-y);
            CHECK_EQ(result2, Integer(type(-2)));

            const auto result3 = (-x).div_ceil(y);
            CHECK_EQ(result3, Integer(type(-2)));

            const auto result4 = (-x).div_ceil(-y);
            CHECK_EQ(result4, Integer(type(3)));
        }

        SUBCASE("positive / positive")
        {
            const auto x = Integer(type(100));
            const auto result = x.div_ceil(Integer(type(5)));

            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("positive / negative")
        {
            const auto x = Integer(type(100));
            const auto result = x.div_ceil(Integer(type(-5)));

            CHECK_EQ(result, Integer(type(-20)));
        }

        SUBCASE("negative / positive")
        {
            const auto x = Integer(type(-100));
            const auto result = x.div_ceil(Integer(type(5)));

            CHECK_EQ(result, Integer(type(-20)));
        }

        SUBCASE("negative / negative")
        {
            const auto x = Integer(type(-100));
            const auto result = x.div_ceil(Integer(type(-5)));

            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("overflow")
        {
#if 0
            const auto x = Integer::MIN();
            const auto result = x.div_ceil(Integer(type(-1)));

            CHECK_EQ(result, Integer::MIN());
#endif
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(1));

            CHECK_THROWS_AS((void)x.div_ceil(Integer(type(0))), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("div_floor ",
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
            auto x = Integer(type(8));
            auto y = Integer(type(3));

            const auto result1 = x.div_floor(y);
            CHECK_EQ(result1, Integer(type(2)));

            const auto result2 = x.div_floor(-y);
            CHECK_EQ(result2, Integer(type(-3)));

            const auto result3 = (-x).div_floor(y);
            CHECK_EQ(result3, Integer(type(-3)));

            const auto result4 = (-x).div_floor(-y);
            CHECK_EQ(result4, Integer(type(2)));
        }

        SUBCASE("positive / positive")
        {
            const auto x = Integer(type(100));
            const auto result = x.div_floor(Integer(type(5)));

            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("positive / negative")
        {
            const auto x = Integer(type(100));
            const auto result = x.div_floor(Integer(type(-5)));

            CHECK_EQ(result, Integer(type(-20)));
        }

        SUBCASE("negative / positive")
        {
            const auto x = Integer(type(-100));
            const auto result = x.div_floor(Integer(type(5)));

            CHECK_EQ(result, Integer(type(-20)));
        }

        SUBCASE("negative / negative")
        {
            const auto x = Integer(type(-100));
            const auto result = x.div_floor(Integer(type(-5)));

            CHECK_EQ(result, Integer(type(20)));
        }

        SUBCASE("overflow")
        {
#if 0
            const auto x = Integer::MIN();
            const auto result = x.div_floor(Integer(type(-1)));

            CHECK_EQ(result, Integer::MIN());
#endif
        }

        SUBCASE("division by zero")
        {
#if 0
            const auto x = Integer(type(1));

            CHECK_THROWS_AS((void)x.div_floor(Integer(type(0))), std::runtime_error);
#endif
        }
    }

    TEST_CASE_TEMPLATE("pow ",
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

        SUBCASE("negative two")
        {
            auto x = Integer(type(-2));
            CHECK_EQ(x.pow(0_u32), 1);
            CHECK_EQ(x.pow(1_u32), -2);
            CHECK_EQ(x.pow(2_u32), 4);
            CHECK_EQ(x.pow(3_u32), -8);
            CHECK_EQ(x.pow(4_u32), 16);
            CHECK_EQ(x.pow(5_u32), -32);
            CHECK_EQ(x.pow(6_u32), 64);
        }
    }

    TEST_CASE_TEMPLATE("is_positive ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("positive")
        {
            const auto x = Integer(type(100));

            CHECK_EQ(x.is_positive(), true);
        }

        SUBCASE("negative")
        {
            const auto x = Integer(type(-100));

            CHECK_EQ(x.is_positive(), false);
        }

        SUBCASE("zero")
        {
            const auto x = Integer(type(0));

            CHECK_EQ(x.is_positive(), false);
        }
    }

    TEST_CASE_TEMPLATE("is_negative ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("positive")
        {
            const auto x = Integer(type(100));

            CHECK_EQ(x.is_negative(), false);
        }

        SUBCASE("negative")
        {
            const auto x = Integer(type(-100));

            CHECK_EQ(x.is_negative(), true);
        }

        SUBCASE("zero")
        {
            const auto x = Integer(type(0));

            CHECK_EQ(x.is_negative(), false);
        }
    }

    TEST_CASE_TEMPLATE("is_even ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
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
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
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
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
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
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
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

    TEST_CASE_TEMPLATE("next_multiple_of ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        auto x0 = Integer(type(0));
        auto x1 = Integer(type(1));
        auto x2 = Integer(type(2));
        auto x3 = Integer(type(3));
        auto x4 = Integer(type(4));
        auto x5 = Integer(type(5));
        auto x6 = Integer(type(6));
        auto x7 = Integer(type(7));
        auto x8 = Integer(type(8));
        auto x9 = Integer(type(9));
        auto x10 = Integer(type(10));

        SUBCASE("basic")
        {
            auto x = Integer(type(4));
            auto y = Integer(type(20));

            const auto result1 = x.next_multiple_of(y);
            CHECK_EQ(result1, Integer(type(20)));

            const auto result2 = x.next_multiple_of(-y);
            CHECK_EQ(result2, Integer(type(0)));

            const auto result3 = (-x).next_multiple_of(y);
            CHECK_EQ(result3, Integer(type(0)));

            const auto result4 = (-x).next_multiple_of(-y);
            CHECK_EQ(result4, Integer(type(-20)));
        }

        SUBCASE("positive")
        {
            SUBCASE("1")
            {
                auto z = Integer(type(1));

                CHECK_EQ(x0.next_multiple_of(z), 0);
                CHECK_EQ(x1.next_multiple_of(z), 1);
                CHECK_EQ(x2.next_multiple_of(z), 2);
                CHECK_EQ(x3.next_multiple_of(z), 3);
                CHECK_EQ(x4.next_multiple_of(z), 4);
                CHECK_EQ(x5.next_multiple_of(z), 5);
                CHECK_EQ(x6.next_multiple_of(z), 6);
                CHECK_EQ(x7.next_multiple_of(z), 7);
                CHECK_EQ(x8.next_multiple_of(z), 8);
                CHECK_EQ(x9.next_multiple_of(z), 9);
                CHECK_EQ(x10.next_multiple_of(z), 10);
            }

            SUBCASE("2")
            {
                auto z = Integer(type(2));

                CHECK_EQ(x0.next_multiple_of(z), 0);
                CHECK_EQ(x1.next_multiple_of(z), 2);
                CHECK_EQ(x2.next_multiple_of(z), 2);
                CHECK_EQ(x3.next_multiple_of(z), 4);
                CHECK_EQ(x4.next_multiple_of(z), 4);
                CHECK_EQ(x5.next_multiple_of(z), 6);
                CHECK_EQ(x6.next_multiple_of(z), 6);
                CHECK_EQ(x7.next_multiple_of(z), 8);
                CHECK_EQ(x8.next_multiple_of(z), 8);
                CHECK_EQ(x9.next_multiple_of(z), 10);
                CHECK_EQ(x10.next_multiple_of(z), 10);
            }

            SUBCASE("3")
            {
                auto z = Integer(type(3));

                CHECK_EQ(x0.next_multiple_of(z), 0);
                CHECK_EQ(x1.next_multiple_of(z), 3);
                CHECK_EQ(x2.next_multiple_of(z), 3);
                CHECK_EQ(x3.next_multiple_of(z), 3);
                CHECK_EQ(x4.next_multiple_of(z), 6);
                CHECK_EQ(x5.next_multiple_of(z), 6);
                CHECK_EQ(x6.next_multiple_of(z), 6);
                CHECK_EQ(x7.next_multiple_of(z), 9);
                CHECK_EQ(x8.next_multiple_of(z), 9);
                CHECK_EQ(x9.next_multiple_of(z), 9);
                CHECK_EQ(x10.next_multiple_of(z), 12);
            }
        }

        SUBCASE("negative")
        {
            SUBCASE("1")
            {
                auto z = Integer(type(-1));

                CHECK_EQ((-x0).next_multiple_of(z), 0);
                CHECK_EQ((-x1).next_multiple_of(z), -1);
                CHECK_EQ((-x2).next_multiple_of(z), -2);
                CHECK_EQ((-x3).next_multiple_of(z), -3);
                CHECK_EQ((-x4).next_multiple_of(z), -4);
                CHECK_EQ((-x5).next_multiple_of(z), -5);
                CHECK_EQ((-x6).next_multiple_of(z), -6);
                CHECK_EQ((-x7).next_multiple_of(z), -7);
                CHECK_EQ((-x8).next_multiple_of(z), -8);
                CHECK_EQ((-x9).next_multiple_of(z), -9);
                CHECK_EQ((-x10).next_multiple_of(z), -10);
            }

            SUBCASE("2")
            {
                auto z = Integer(type(-2));

                CHECK_EQ((-x0).next_multiple_of(z), 0);
                CHECK_EQ((-x1).next_multiple_of(z), -2);
                CHECK_EQ((-x2).next_multiple_of(z), -2);
                CHECK_EQ((-x3).next_multiple_of(z), -4);
                CHECK_EQ((-x4).next_multiple_of(z), -4);
                CHECK_EQ((-x5).next_multiple_of(z), -6);
                CHECK_EQ((-x6).next_multiple_of(z), -6);
                CHECK_EQ((-x7).next_multiple_of(z), -8);
                CHECK_EQ((-x8).next_multiple_of(z), -8);
                CHECK_EQ((-x9).next_multiple_of(z), -10);
                CHECK_EQ((-x10).next_multiple_of(z), -10);
            }

            SUBCASE("3")
            {
                auto z = Integer(type(-3));

                CHECK_EQ((-x0).next_multiple_of(z), 0);
                CHECK_EQ((-x1).next_multiple_of(z), -3);
                CHECK_EQ((-x2).next_multiple_of(z), -3);
                CHECK_EQ((-x3).next_multiple_of(z), -3);
                CHECK_EQ((-x4).next_multiple_of(z), -6);
                CHECK_EQ((-x5).next_multiple_of(z), -6);
                CHECK_EQ((-x6).next_multiple_of(z), -6);
                CHECK_EQ((-x7).next_multiple_of(z), -9);
                CHECK_EQ((-x8).next_multiple_of(z), -9);
                CHECK_EQ((-x9).next_multiple_of(z), -9);
                CHECK_EQ((-x10).next_multiple_of(z), -12);
            }
        }
    }

    TEST_CASE_TEMPLATE("checked_next_multiple_of ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        auto x0 = Integer(type(0));
        auto x1 = Integer(type(1));
        auto x2 = Integer(type(2));
        auto x3 = Integer(type(3));
        auto x4 = Integer(type(4));
        auto x5 = Integer(type(5));
        auto x6 = Integer(type(6));
        auto x7 = Integer(type(7));
        auto x8 = Integer(type(8));
        auto x9 = Integer(type(9));
        auto x10 = Integer(type(10));

        SUBCASE("basic")
        {
            auto x = Integer(type(4));
            auto y = Integer(type(20));

            const auto result1 = x.checked_next_multiple_of(y);
            CHECK_EQ(result1, Integer(type(20)));

            const auto result2 = x.checked_next_multiple_of(-y);
            CHECK_EQ(result2, Integer(type(0)));

            const auto result3 = (-x).checked_next_multiple_of(y);
            CHECK_EQ(result3, Integer(type(0)));

            const auto result4 = (-x).checked_next_multiple_of(-y);
            CHECK_EQ(result4, Integer(type(-20)));
        }

        SUBCASE("positive")
        {
            SUBCASE("1")
            {
                auto z = Integer(type(1));

                CHECK_EQ(x0.checked_next_multiple_of(z), 0);
                CHECK_EQ(x1.checked_next_multiple_of(z), 1);
                CHECK_EQ(x2.checked_next_multiple_of(z), 2);
                CHECK_EQ(x3.checked_next_multiple_of(z), 3);
                CHECK_EQ(x4.checked_next_multiple_of(z), 4);
                CHECK_EQ(x5.checked_next_multiple_of(z), 5);
                CHECK_EQ(x6.checked_next_multiple_of(z), 6);
                CHECK_EQ(x7.checked_next_multiple_of(z), 7);
                CHECK_EQ(x8.checked_next_multiple_of(z), 8);
                CHECK_EQ(x9.checked_next_multiple_of(z), 9);
                CHECK_EQ(x10.checked_next_multiple_of(z), 10);
            }

            SUBCASE("2")
            {
                auto z = Integer(type(2));

                CHECK_EQ(x0.checked_next_multiple_of(z), 0);
                CHECK_EQ(x1.checked_next_multiple_of(z), 2);
                CHECK_EQ(x2.checked_next_multiple_of(z), 2);
                CHECK_EQ(x3.checked_next_multiple_of(z), 4);
                CHECK_EQ(x4.checked_next_multiple_of(z), 4);
                CHECK_EQ(x5.checked_next_multiple_of(z), 6);
                CHECK_EQ(x6.checked_next_multiple_of(z), 6);
                CHECK_EQ(x7.checked_next_multiple_of(z), 8);
                CHECK_EQ(x8.checked_next_multiple_of(z), 8);
                CHECK_EQ(x9.checked_next_multiple_of(z), 10);
                CHECK_EQ(x10.checked_next_multiple_of(z), 10);
            }

            SUBCASE("3")
            {
                auto z = Integer(type(3));

                CHECK_EQ(x0.checked_next_multiple_of(z), 0);
                CHECK_EQ(x1.checked_next_multiple_of(z), 3);
                CHECK_EQ(x2.checked_next_multiple_of(z), 3);
                CHECK_EQ(x3.checked_next_multiple_of(z), 3);
                CHECK_EQ(x4.checked_next_multiple_of(z), 6);
                CHECK_EQ(x5.checked_next_multiple_of(z), 6);
                CHECK_EQ(x6.checked_next_multiple_of(z), 6);
                CHECK_EQ(x7.checked_next_multiple_of(z), 9);
                CHECK_EQ(x8.checked_next_multiple_of(z), 9);
                CHECK_EQ(x9.checked_next_multiple_of(z), 9);
                CHECK_EQ(x10.checked_next_multiple_of(z), 12);
            }
        }

        SUBCASE("negative")
        {
            SUBCASE("1")
            {
                auto z = Integer(type(-1));

                CHECK_EQ((-x0).checked_next_multiple_of(z), 0);
                CHECK_EQ((-x1).checked_next_multiple_of(z), -1);
                CHECK_EQ((-x2).checked_next_multiple_of(z), -2);
                CHECK_EQ((-x3).checked_next_multiple_of(z), -3);
                CHECK_EQ((-x4).checked_next_multiple_of(z), -4);
                CHECK_EQ((-x5).checked_next_multiple_of(z), -5);
                CHECK_EQ((-x6).checked_next_multiple_of(z), -6);
                CHECK_EQ((-x7).checked_next_multiple_of(z), -7);
                CHECK_EQ((-x8).checked_next_multiple_of(z), -8);
                CHECK_EQ((-x9).checked_next_multiple_of(z), -9);
                CHECK_EQ((-x10).checked_next_multiple_of(z), -10);
            }

            SUBCASE("2")
            {
                auto z = Integer(type(-2));

                CHECK_EQ((-x0).checked_next_multiple_of(z), 0);
                CHECK_EQ((-x1).checked_next_multiple_of(z), -2);
                CHECK_EQ((-x2).checked_next_multiple_of(z), -2);
                CHECK_EQ((-x3).checked_next_multiple_of(z), -4);
                CHECK_EQ((-x4).checked_next_multiple_of(z), -4);
                CHECK_EQ((-x5).checked_next_multiple_of(z), -6);
                CHECK_EQ((-x6).checked_next_multiple_of(z), -6);
                CHECK_EQ((-x7).checked_next_multiple_of(z), -8);
                CHECK_EQ((-x8).checked_next_multiple_of(z), -8);
                CHECK_EQ((-x9).checked_next_multiple_of(z), -10);
                CHECK_EQ((-x10).checked_next_multiple_of(z), -10);
            }

            SUBCASE("3")
            {
                auto z = Integer(type(-3));

                CHECK_EQ((-x0).checked_next_multiple_of(z), 0);
                CHECK_EQ((-x1).checked_next_multiple_of(z), -3);
                CHECK_EQ((-x2).checked_next_multiple_of(z), -3);
                CHECK_EQ((-x3).checked_next_multiple_of(z), -3);
                CHECK_EQ((-x4).checked_next_multiple_of(z), -6);
                CHECK_EQ((-x5).checked_next_multiple_of(z), -6);
                CHECK_EQ((-x6).checked_next_multiple_of(z), -6);
                CHECK_EQ((-x7).checked_next_multiple_of(z), -9);
                CHECK_EQ((-x8).checked_next_multiple_of(z), -9);
                CHECK_EQ((-x9).checked_next_multiple_of(z), -9);
                CHECK_EQ((-x10).checked_next_multiple_of(z), -12);
            }
        }

        SUBCASE("overflow")
        {
            auto z = Integer(type(2));

            CHECK_EQ(Integer::MAX().checked_next_multiple_of(z), std::nullopt);
        }
    }
}
