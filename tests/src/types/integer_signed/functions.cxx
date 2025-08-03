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
#include <optional>

#include <doctest/doctest.h>

#include "data/add-data.hxx"
#include "data/div-data.hxx"
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

    TEST_CASE_TEMPLATE("div_down ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] : test::signed_int::div_data<Integer>)
            {
                auto result = dividend.div_down(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
            }
        }
    }

    TEST_CASE_TEMPLATE("div_up ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] : test::signed_int::div_up_data<Integer>)
            {
                auto result = dividend.div_up(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
            }
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

        SUBCASE("example")
        {
            auto x = Integer(type(8));
            auto y = Integer(type(3));

            CHECK(x.div_floor(y) == 2);
            CHECK(x.div_floor(-y) == -3);
            CHECK((-x).div_floor(y) == -3);
            CHECK((-x).div_floor(-y) == 2);
        }
        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] :
                 test::signed_int::div_floor_data<Integer>)
            {
                auto result = dividend.div_floor(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
            }
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

        SUBCASE("example")
        {
            auto x = Integer(type(8));
            auto y = Integer(type(3));

            CHECK(x.div_ceil(y) == 3);
            CHECK(x.div_ceil(-y) == -2);
            CHECK((-x).div_ceil(y) == -2);
            CHECK((-x).div_ceil(-y) == 3);
        }

        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] : test::signed_int::div_ceil_data<Integer>)
            {
                auto result = dividend.div_ceil(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
            }
        }
    }

    TEST_CASE_TEMPLATE("div_euclid ",
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

            CHECK(x.div_euclid(y) == 1);     // 7 >= 4 * 1
            CHECK(x.div_euclid(-y) == -1);   // 7 >= -4 * -1
            CHECK((-x).div_euclid(y) == -2); // -7 >= 4 * -2
            CHECK((-x).div_euclid(-y) == 2); // -7 >= -4 * 2
        }

        SUBCASE("basic")
        {
            for (const auto& [dividend, divisor, wanted] :
                 test::signed_int::div_euclid_data<Integer>)
            {
                auto result = dividend.div_euclid(divisor);

                CHECK_MESSAGE(
                    result == wanted,
                    std::format("{} / {} = {} | wanted {}", dividend, divisor, result, wanted));
            }
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

    TEST_CASE_TEMPLATE("ilog ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("base")
        {
            for (auto v : std::views::iota(2, 100))
            {
                CHECK_EQ(Integer(type(v)).ilog(Integer(type(v))), 1_u32);
            }
        }
    }

    TEST_CASE_TEMPLATE("ilog2 ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        CHECK_EQ(Integer(type(2)).ilog2(), 1_u32);
        CHECK_EQ(Integer(type(3)).ilog2(), 1_u32);
        CHECK_EQ(Integer(type(4)).ilog2(), 2_u32);
        CHECK_EQ(Integer(type(5)).ilog2(), 2_u32);
        CHECK_EQ(Integer(type(6)).ilog2(), 2_u32);
        CHECK_EQ(Integer(type(7)).ilog2(), 2_u32);
        CHECK_EQ(Integer(type(8)).ilog2(), 3_u32);
        CHECK_EQ(Integer(type(9)).ilog2(), 3_u32);
        CHECK_EQ(Integer(type(10)).ilog2(), 3_u32);
        CHECK_EQ(Integer(type(11)).ilog2(), 3_u32);
        CHECK_EQ(Integer(type(12)).ilog2(), 3_u32);
        CHECK_EQ(Integer(type(13)).ilog2(), 3_u32);
        CHECK_EQ(Integer(type(14)).ilog2(), 3_u32);
        CHECK_EQ(Integer(type(15)).ilog2(), 3_u32);
        CHECK_EQ(Integer(type(16)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(17)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(18)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(19)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(20)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(21)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(22)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(23)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(24)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(25)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(26)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(27)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(28)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(29)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(30)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(31)).ilog2(), 4_u32);
        CHECK_EQ(Integer(type(32)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(33)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(34)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(35)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(36)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(37)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(38)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(39)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(40)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(41)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(42)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(43)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(44)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(45)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(46)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(47)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(48)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(49)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(50)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(51)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(52)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(53)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(54)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(55)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(56)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(57)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(58)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(59)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(60)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(61)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(62)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(63)).ilog2(), 5_u32);
        CHECK_EQ(Integer(type(64)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(65)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(66)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(67)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(68)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(69)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(70)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(71)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(72)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(73)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(74)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(75)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(76)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(77)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(78)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(79)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(80)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(81)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(82)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(83)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(84)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(85)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(86)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(87)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(88)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(89)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(90)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(91)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(92)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(93)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(94)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(95)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(96)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(97)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(98)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(99)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(100)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(101)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(102)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(103)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(104)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(105)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(106)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(107)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(108)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(109)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(110)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(111)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(112)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(113)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(114)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(115)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(116)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(117)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(118)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(119)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(120)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(121)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(122)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(123)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(124)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(125)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(126)).ilog2(), 6_u32);
        CHECK_EQ(Integer(type(127)).ilog2(), 6_u32);
    }

    TEST_CASE_TEMPLATE("ilog10 ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        CHECK_EQ(Integer(type(2)).ilog10(), 0_u32);
        CHECK_EQ(Integer(type(3)).ilog10(), 0_u32);
        CHECK_EQ(Integer(type(4)).ilog10(), 0_u32);
        CHECK_EQ(Integer(type(5)).ilog10(), 0_u32);
        CHECK_EQ(Integer(type(6)).ilog10(), 0_u32);
        CHECK_EQ(Integer(type(7)).ilog10(), 0_u32);
        CHECK_EQ(Integer(type(8)).ilog10(), 0_u32);
        CHECK_EQ(Integer(type(9)).ilog10(), 0_u32);
        CHECK_EQ(Integer(type(10)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(11)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(12)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(13)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(14)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(15)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(16)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(17)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(18)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(19)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(20)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(21)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(22)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(23)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(24)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(25)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(26)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(27)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(28)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(29)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(30)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(31)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(32)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(33)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(34)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(35)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(36)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(37)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(38)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(39)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(40)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(41)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(42)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(43)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(44)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(45)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(46)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(47)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(48)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(49)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(50)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(51)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(52)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(53)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(54)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(55)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(56)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(57)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(58)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(59)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(60)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(61)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(62)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(63)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(64)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(65)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(66)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(67)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(68)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(69)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(70)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(71)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(72)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(73)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(74)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(75)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(76)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(77)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(78)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(79)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(80)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(81)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(82)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(83)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(84)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(85)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(86)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(87)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(88)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(89)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(90)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(91)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(92)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(93)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(94)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(95)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(96)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(97)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(98)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(99)).ilog10(), 1_u32);
        CHECK_EQ(Integer(type(100)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(101)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(102)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(103)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(104)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(105)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(106)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(107)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(108)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(109)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(110)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(111)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(112)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(113)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(114)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(115)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(116)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(117)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(118)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(119)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(120)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(121)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(122)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(123)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(124)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(125)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(126)).ilog10(), 2_u32);
        CHECK_EQ(Integer(type(127)).ilog10(), 2_u32);
    }

    TEST_CASE_TEMPLATE("checked_ilog ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("base")
        {
            for (auto v : std::views::iota(2, 100))
            {
                CHECK_EQ(Integer(type(v)).checked_ilog(Integer(type(v))), 1_u32);
            }
        }

        SUBCASE("negative")
        {
            CHECK_EQ(Integer(type(-2)).checked_ilog(Integer(type(2))), std::nullopt);
            CHECK_EQ(Integer(type(2)).checked_ilog(Integer(type(-2))), std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_ilog2 ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("negative")
        {
            CHECK_EQ(Integer(type(-2)).checked_ilog2(), std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("checked_ilog10 ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        SUBCASE("negative")
        {
            CHECK_EQ(Integer(type(-2)).checked_ilog10(), std::nullopt);
        }
    }

    TEST_CASE_TEMPLATE("isqrt ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        CHECK_EQ(Integer(type(0)).isqrt(), Integer(type(0)));
        CHECK_EQ(Integer(type(1)).isqrt(), Integer(type(1)));
        CHECK_EQ(Integer(type(2)).isqrt(), Integer(type(1)));
        CHECK_EQ(Integer(type(3)).isqrt(), Integer(type(1)));
        CHECK_EQ(Integer(type(4)).isqrt(), Integer(type(2)));
        CHECK_EQ(Integer(type(5)).isqrt(), Integer(type(2)));
        CHECK_EQ(Integer(type(6)).isqrt(), Integer(type(2)));
        CHECK_EQ(Integer(type(7)).isqrt(), Integer(type(2)));
        CHECK_EQ(Integer(type(8)).isqrt(), Integer(type(2)));
        CHECK_EQ(Integer(type(9)).isqrt(), Integer(type(3)));
        CHECK_EQ(Integer(type(10)).isqrt(), Integer(type(3)));
        CHECK_EQ(Integer(type(11)).isqrt(), Integer(type(3)));
        CHECK_EQ(Integer(type(12)).isqrt(), Integer(type(3)));
        CHECK_EQ(Integer(type(13)).isqrt(), Integer(type(3)));
        CHECK_EQ(Integer(type(14)).isqrt(), Integer(type(3)));
        CHECK_EQ(Integer(type(15)).isqrt(), Integer(type(3)));
        CHECK_EQ(Integer(type(16)).isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(17)).isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(18)).isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(19)).isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(20)).isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(21)).isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(22)).isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(23)).isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(24)).isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(25)).isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(26)).isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(27)).isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(28)).isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(29)).isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(30)).isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(31)).isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(32)).isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(33)).isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(34)).isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(35)).isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(36)).isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(37)).isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(38)).isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(39)).isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(40)).isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(41)).isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(42)).isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(43)).isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(44)).isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(45)).isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(46)).isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(47)).isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(48)).isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(49)).isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(50)).isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(51)).isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(52)).isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(53)).isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(54)).isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(55)).isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(56)).isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(57)).isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(58)).isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(59)).isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(60)).isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(61)).isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(62)).isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(63)).isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(64)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(65)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(66)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(67)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(68)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(69)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(70)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(71)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(72)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(73)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(74)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(75)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(76)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(77)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(78)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(79)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(80)).isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(81)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(82)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(83)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(84)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(85)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(86)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(87)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(88)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(89)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(90)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(91)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(92)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(93)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(94)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(95)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(96)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(97)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(98)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(99)).isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(100)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(101)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(102)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(103)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(104)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(105)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(106)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(107)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(108)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(109)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(110)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(111)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(112)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(113)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(114)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(115)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(116)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(117)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(118)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(119)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(120)).isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(121)).isqrt(), Integer(type(11)));
        CHECK_EQ(Integer(type(122)).isqrt(), Integer(type(11)));
        CHECK_EQ(Integer(type(123)).isqrt(), Integer(type(11)));
        CHECK_EQ(Integer(type(124)).isqrt(), Integer(type(11)));
        CHECK_EQ(Integer(type(125)).isqrt(), Integer(type(11)));
        CHECK_EQ(Integer(type(126)).isqrt(), Integer(type(11)));
        CHECK_EQ(Integer(type(127)).isqrt(), Integer(type(11)));
    }

    TEST_CASE_TEMPLATE("checked_isqrt ",
                       Integer,
                       ztd::v2::i8,
                       ztd::v2::i16,
                       ztd::v2::i32,
                       ztd::v2::i64,
                       ztd::v2::isize)
    {
        using type = typename Integer::integer_type;

        CHECK_EQ(Integer::MIN().checked_isqrt(), std::nullopt);
        CHECK_EQ(Integer(type(-10)).checked_isqrt(), std::nullopt);
        CHECK_EQ(Integer(type(-9)).checked_isqrt(), std::nullopt);
        CHECK_EQ(Integer(type(-8)).checked_isqrt(), std::nullopt);
        CHECK_EQ(Integer(type(-7)).checked_isqrt(), std::nullopt);
        CHECK_EQ(Integer(type(-6)).checked_isqrt(), std::nullopt);
        CHECK_EQ(Integer(type(-5)).checked_isqrt(), std::nullopt);
        CHECK_EQ(Integer(type(-4)).checked_isqrt(), std::nullopt);
        CHECK_EQ(Integer(type(-3)).checked_isqrt(), std::nullopt);
        CHECK_EQ(Integer(type(-2)).checked_isqrt(), std::nullopt);
        CHECK_EQ(Integer(type(-1)).checked_isqrt(), std::nullopt);

        CHECK_EQ(Integer(type(0)).checked_isqrt(), Integer(type(0)));
        CHECK_EQ(Integer(type(1)).checked_isqrt(), Integer(type(1)));
        CHECK_EQ(Integer(type(2)).checked_isqrt(), Integer(type(1)));
        CHECK_EQ(Integer(type(3)).checked_isqrt(), Integer(type(1)));
        CHECK_EQ(Integer(type(4)).checked_isqrt(), Integer(type(2)));
        CHECK_EQ(Integer(type(5)).checked_isqrt(), Integer(type(2)));
        CHECK_EQ(Integer(type(6)).checked_isqrt(), Integer(type(2)));
        CHECK_EQ(Integer(type(7)).checked_isqrt(), Integer(type(2)));
        CHECK_EQ(Integer(type(8)).checked_isqrt(), Integer(type(2)));
        CHECK_EQ(Integer(type(9)).checked_isqrt(), Integer(type(3)));
        CHECK_EQ(Integer(type(10)).checked_isqrt(), Integer(type(3)));
        CHECK_EQ(Integer(type(11)).checked_isqrt(), Integer(type(3)));
        CHECK_EQ(Integer(type(12)).checked_isqrt(), Integer(type(3)));
        CHECK_EQ(Integer(type(13)).checked_isqrt(), Integer(type(3)));
        CHECK_EQ(Integer(type(14)).checked_isqrt(), Integer(type(3)));
        CHECK_EQ(Integer(type(15)).checked_isqrt(), Integer(type(3)));
        CHECK_EQ(Integer(type(16)).checked_isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(17)).checked_isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(18)).checked_isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(19)).checked_isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(20)).checked_isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(21)).checked_isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(22)).checked_isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(23)).checked_isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(24)).checked_isqrt(), Integer(type(4)));
        CHECK_EQ(Integer(type(25)).checked_isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(26)).checked_isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(27)).checked_isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(28)).checked_isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(29)).checked_isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(30)).checked_isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(31)).checked_isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(32)).checked_isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(33)).checked_isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(34)).checked_isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(35)).checked_isqrt(), Integer(type(5)));
        CHECK_EQ(Integer(type(36)).checked_isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(37)).checked_isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(38)).checked_isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(39)).checked_isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(40)).checked_isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(41)).checked_isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(42)).checked_isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(43)).checked_isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(44)).checked_isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(45)).checked_isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(46)).checked_isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(47)).checked_isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(48)).checked_isqrt(), Integer(type(6)));
        CHECK_EQ(Integer(type(49)).checked_isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(50)).checked_isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(51)).checked_isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(52)).checked_isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(53)).checked_isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(54)).checked_isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(55)).checked_isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(56)).checked_isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(57)).checked_isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(58)).checked_isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(59)).checked_isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(60)).checked_isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(61)).checked_isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(62)).checked_isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(63)).checked_isqrt(), Integer(type(7)));
        CHECK_EQ(Integer(type(64)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(65)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(66)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(67)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(68)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(69)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(70)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(71)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(72)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(73)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(74)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(75)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(76)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(77)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(78)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(79)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(80)).checked_isqrt(), Integer(type(8)));
        CHECK_EQ(Integer(type(81)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(82)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(83)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(84)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(85)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(86)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(87)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(88)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(89)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(90)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(91)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(92)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(93)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(94)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(95)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(96)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(97)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(98)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(99)).checked_isqrt(), Integer(type(9)));
        CHECK_EQ(Integer(type(100)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(101)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(102)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(103)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(104)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(105)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(106)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(107)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(108)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(109)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(110)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(111)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(112)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(113)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(114)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(115)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(116)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(117)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(118)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(119)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(120)).checked_isqrt(), Integer(type(10)));
        CHECK_EQ(Integer(type(121)).checked_isqrt(), Integer(type(11)));
        CHECK_EQ(Integer(type(122)).checked_isqrt(), Integer(type(11)));
        CHECK_EQ(Integer(type(123)).checked_isqrt(), Integer(type(11)));
        CHECK_EQ(Integer(type(124)).checked_isqrt(), Integer(type(11)));
        CHECK_EQ(Integer(type(125)).checked_isqrt(), Integer(type(11)));
        CHECK_EQ(Integer(type(126)).checked_isqrt(), Integer(type(11)));
        CHECK_EQ(Integer(type(127)).checked_isqrt(), Integer(type(11)));
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
