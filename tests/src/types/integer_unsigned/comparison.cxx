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

#include "ztd/detail/types.hxx"

TEST_SUITE("unsigned integer<T>" * doctest::description(""))
{
    TEST_CASE_TEMPLATE("operator== ",
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
            const auto max = Integer::MAX();
            const auto min = Integer::MIN();

            CHECK_EQ((max == max), true);
            CHECK_EQ((min == min), true);
            CHECK_EQ(!(max == min), true);
        }

        SUBCASE("cpp integers")
        {
            SUBCASE("positive")
            {
                auto x = Integer(type(10));

                CHECK(x == 10);
                CHECK(x == 10u);
                CHECK(x == 10l);
                CHECK(x == 10ull);
                CHECK(x == 10ll);
                CHECK(x == 10uz);
                CHECK(x == 10z);

                CHECK(10 == x);
                CHECK(10u == x);
                CHECK(10l == x);
                CHECK(10ull == x);
                CHECK(10ll == x);
                CHECK(10uz == x);
                CHECK(10z == x);
            }
        }

        SUBCASE("ztd::integer")
        {
            SUBCASE("positive")
            {
                auto x = Integer(type(10));

                CHECK(x == 10_i8);
                CHECK(x == 10_i16);
                CHECK(x == 10_i32);
                CHECK(x == 10_i64);
                CHECK(x == 10_isize);

                CHECK(x == 10_u8);
                CHECK(x == 10_u16);
                CHECK(x == 10_u32);
                CHECK(x == 10_u64);
                CHECK(x == 10_usize);

                CHECK(10_i8 == x);
                CHECK(10_i16 == x);
                CHECK(10_i32 == x);
                CHECK(10_i64 == x);
                CHECK(10_isize == x);

                CHECK(10_u8 == x);
                CHECK(10_u16 == x);
                CHECK(10_u32 == x);
                CHECK(10_u64 == x);
                CHECK(10_usize == x);
            }
        }
    }

    TEST_CASE_TEMPLATE("operator!= ",
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
            const auto max = Integer::MAX();
            const auto min = Integer::MIN();

            CHECK_EQ(!(max != max), true);
            CHECK_EQ(!(min != min), true);
            CHECK_EQ((max != min), true);
        }

        SUBCASE("cpp integers")
        {
            SUBCASE("positive")
            {
                auto x = Integer(type(5));

                CHECK(x != 10);
                CHECK(x != 10u);
                CHECK(x != 10l);
                CHECK(x != 10ull);
                CHECK(x != 10ll);
                CHECK(x != 10uz);
                CHECK(x != 10z);

                CHECK(10 != x);
                CHECK(10u != x);
                CHECK(10l != x);
                CHECK(10ull != x);
                CHECK(10ll != x);
                CHECK(10uz != x);
                CHECK(10z != x);
            }

            SUBCASE("negative")
            {
                auto x = Integer(type(5));

                CHECK(x != -10);
                CHECK(x != -10l);
                CHECK(x != -10ll);
                CHECK(x != -10z);

                CHECK(-10 != x);
                CHECK(-10l != x);
                CHECK(-10ll != x);
                CHECK(-10z != x);
            }
        }

        SUBCASE("ztd::integer")
        {
            SUBCASE("positive")
            {
                auto x = Integer(type(5));

                CHECK(x != 10_i8);
                CHECK(x != 10_i16);
                CHECK(x != 10_i32);
                CHECK(x != 10_i64);
                CHECK(x != 10_isize);

                CHECK(x != 10_u8);
                CHECK(x != 10_u16);
                CHECK(x != 10_u32);
                CHECK(x != 10_u64);
                CHECK(x != 10_usize);

                CHECK(10_i8 != x);
                CHECK(10_i16 != x);
                CHECK(10_i32 != x);
                CHECK(10_i64 != x);
                CHECK(10_isize != x);

                CHECK(10_u8 != x);
                CHECK(10_u16 != x);
                CHECK(10_u32 != x);
                CHECK(10_u64 != x);
                CHECK(10_usize != x);
            }

            SUBCASE("negative")
            {
                auto x = Integer(type(5));

                CHECK(x != -10_i8);
                CHECK(x != -10_i16);
                CHECK(x != -10_i32);
                CHECK(x != -10_i64);
                CHECK(x != -10_isize);

                CHECK(-10_i8 != x);
                CHECK(-10_i16 != x);
                CHECK(-10_i32 != x);
                CHECK(-10_i64 != x);
                CHECK(-10_isize != x);
            }
        }
    }

    TEST_CASE_TEMPLATE("operator> ",
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
            const auto max = Integer::MAX();
            const auto min = Integer::MIN();

            CHECK_EQ(min > min, false);
            CHECK_EQ(min > max, false);

            CHECK_EQ(max > min, true);
            CHECK_EQ(max > max, false);
        }

        SUBCASE("cpp integers")
        {
            SUBCASE("positive")
            {
                auto x = Integer(type(10));

                CHECK(x > 5);
                CHECK(x > 5u);
                CHECK(x > 5l);
                CHECK(x > 5ull);
                CHECK(x > 5ll);
                CHECK(x > 5uz);
                CHECK(x > 5z);

                CHECK(15 > x);
                CHECK(15u > x);
                CHECK(15l > x);
                CHECK(15ull > x);
                CHECK(15ll > x);
                CHECK(15uz > x);
                CHECK(15z > x);
            }

            SUBCASE("negative")
            {
                auto x = Integer(type(10));

                CHECK(x > -15);
                CHECK(x > -15l);
                CHECK(x > -15ll);
                CHECK(x > -15z);
            }
        }

        SUBCASE("ztd::integer")
        {
            SUBCASE("positive")
            {
                auto x = Integer(type(10));

                CHECK(x > 5_i8);
                CHECK(x > 5_i16);
                CHECK(x > 5_i32);
                CHECK(x > 5_i64);
                CHECK(x > 5_isize);

                CHECK(x > 5_u8);
                CHECK(x > 5_u16);
                CHECK(x > 5_u32);
                CHECK(x > 5_u64);
                CHECK(x > 5_usize);

                CHECK(15_i8 > x);
                CHECK(15_i16 > x);
                CHECK(15_i32 > x);
                CHECK(15_i64 > x);
                CHECK(15_isize > x);

                CHECK(15_u8 > x);
                CHECK(15_u16 > x);
                CHECK(15_u32 > x);
                CHECK(15_u64 > x);
                CHECK(15_usize > x);
            }

            SUBCASE("negative")
            {
                auto x = Integer(type(10));

                CHECK(x > -15_i8);
                CHECK(x > -15_i16);
                CHECK(x > -15_i32);
                CHECK(x > -15_i64);
                CHECK(x > -15_isize);
            }
        }
    }

    TEST_CASE_TEMPLATE("operator>= ",
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
            const auto max = Integer::MAX();
            const auto min = Integer::MIN();

            CHECK_EQ(min >= min, true);
            CHECK_EQ(min >= max, false);

            CHECK_EQ(max >= min, true);
            CHECK_EQ(max >= max, true);
        }

        SUBCASE("cpp integers")
        {
            SUBCASE("positive")
            {
                auto x = Integer(type(10));

                CHECK(x >= 10);
                CHECK(x >= 10u);
                CHECK(x >= 10l);
                CHECK(x >= 10ull);
                CHECK(x >= 10ll);
                CHECK(x >= 10uz);
                CHECK(x >= 10z);

                CHECK(x >= 5);
                CHECK(x >= 5u);
                CHECK(x >= 5l);
                CHECK(x >= 5ull);
                CHECK(x >= 5ll);
                CHECK(x >= 5uz);
                CHECK(x >= 5z);

                CHECK(10 >= x);
                CHECK(10u >= x);
                CHECK(10l >= x);
                CHECK(10ull >= x);
                CHECK(10ll >= x);
                CHECK(10uz >= x);
                CHECK(10z >= x);

                CHECK(15 >= x);
                CHECK(15u >= x);
                CHECK(15l >= x);
                CHECK(15ull >= x);
                CHECK(15ll >= x);
                CHECK(15uz >= x);
                CHECK(15z >= x);
            }

            SUBCASE("negative")
            {
                auto x = Integer(type(10));

                CHECK(x >= -10);
                CHECK(x >= -10l);
                CHECK(x >= -10ll);
                CHECK(x >= -10z);

                CHECK(x >= -15);
                CHECK(x >= -15l);
                CHECK(x >= -15ll);
                CHECK(x >= -15z);
            }
        }

        SUBCASE("ztd::integer")
        {
            SUBCASE("positive")
            {
                auto x = Integer(type(10));

                CHECK(x >= 10_i8);
                CHECK(x >= 10_i16);
                CHECK(x >= 10_i32);
                CHECK(x >= 10_i64);
                CHECK(x >= 10_isize);

                CHECK(x >= 5_i8);
                CHECK(x >= 5_i16);
                CHECK(x >= 5_i32);
                CHECK(x >= 5_i64);
                CHECK(x >= 5_isize);

                CHECK(x >= 10_u8);
                CHECK(x >= 10_u16);
                CHECK(x >= 10_u32);
                CHECK(x >= 10_u64);
                CHECK(x >= 10_usize);

                CHECK(x >= 5_u8);
                CHECK(x >= 5_u16);
                CHECK(x >= 5_u32);
                CHECK(x >= 5_u64);
                CHECK(x >= 5_usize);

                CHECK(10_i8 >= x);
                CHECK(10_i16 >= x);
                CHECK(10_i32 >= x);
                CHECK(10_i64 >= x);
                CHECK(10_isize >= x);

                CHECK(15_i8 >= x);
                CHECK(15_i16 >= x);
                CHECK(15_i32 >= x);
                CHECK(15_i64 >= x);
                CHECK(15_isize >= x);

                CHECK(10_u8 >= x);
                CHECK(10_u16 >= x);
                CHECK(10_u32 >= x);
                CHECK(10_u64 >= x);
                CHECK(10_usize >= x);

                CHECK(15_u8 >= x);
                CHECK(15_u16 >= x);
                CHECK(15_u32 >= x);
                CHECK(15_u64 >= x);
                CHECK(15_usize >= x);
            }

            SUBCASE("negative")
            {
                auto x = Integer(type(10));

                CHECK(x >= -10_i8);
                CHECK(x >= -10_i16);
                CHECK(x >= -10_i32);
                CHECK(x >= -10_i64);
                CHECK(x >= -10_isize);

                CHECK(x >= -15_i8);
                CHECK(x >= -15_i16);
                CHECK(x >= -15_i32);
                CHECK(x >= -15_i64);
                CHECK(x >= -15_isize);
            }
        }
    }

    TEST_CASE_TEMPLATE("operator< ",
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
            const auto max = Integer::MAX();
            const auto min = Integer::MIN();

            CHECK_EQ(min < min, false);
            CHECK_EQ(min < max, true);

            CHECK_EQ(max < min, false);
            CHECK_EQ(max < max, false);
        }

        SUBCASE("cpp integers")
        {
            SUBCASE("positive")
            {
                auto x = Integer(type(10));

                CHECK(x < 15);
                CHECK(x < 15u);
                CHECK(x < 15l);
                CHECK(x < 15ull);
                CHECK(x < 15ll);
                CHECK(x < 15uz);
                CHECK(x < 15z);

                CHECK(5 < x);
                CHECK(5u < x);
                CHECK(5l < x);
                CHECK(5ull < x);
                CHECK(5ll < x);
                CHECK(5uz < x);
                CHECK(5z < x);
            }
        }

        SUBCASE("ztd::integer")
        {
            SUBCASE("positive")
            {
                auto x = Integer(type(10));

                CHECK(x < 15_i8);
                CHECK(x < 15_i16);
                CHECK(x < 15_i32);
                CHECK(x < 15_i64);
                CHECK(x < 15_isize);

                CHECK(x < 15_u8);
                CHECK(x < 15_u16);
                CHECK(x < 15_u32);
                CHECK(x < 15_u64);
                CHECK(x < 15_usize);

                CHECK(5_i8 < x);
                CHECK(5_i16 < x);
                CHECK(5_i32 < x);
                CHECK(5_i64 < x);
                CHECK(5_isize < x);

                CHECK(5_u8 < x);
                CHECK(5_u16 < x);
                CHECK(5_u32 < x);
                CHECK(5_u64 < x);
                CHECK(5_usize < x);
            }
        }
    }

    TEST_CASE_TEMPLATE("operator<= ",
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
            const auto max = Integer::MAX();
            const auto min = Integer::MIN();

            CHECK_EQ(min <= min, true);
            CHECK_EQ(min <= max, true);

            CHECK_EQ(max <= min, false);
            CHECK_EQ(max <= max, true);
        }

        SUBCASE("cpp integers")
        {
            SUBCASE("positive")
            {
                auto x = Integer(type(10));

                CHECK(x <= 10);
                CHECK(x <= 10u);
                CHECK(x <= 10l);
                CHECK(x <= 10ull);
                CHECK(x <= 10ll);
                CHECK(x <= 10uz);
                CHECK(x <= 10z);

                CHECK(x <= 15);
                CHECK(x <= 15u);
                CHECK(x <= 15l);
                CHECK(x <= 15ull);
                CHECK(x <= 15ll);
                CHECK(x <= 15uz);
                CHECK(x <= 15z);

                CHECK(10 <= x);
                CHECK(10u <= x);
                CHECK(10l <= x);
                CHECK(10ull <= x);
                CHECK(10ll <= x);
                CHECK(10uz <= x);
                CHECK(10z <= x);

                CHECK(5 <= x);
                CHECK(5u <= x);
                CHECK(5l <= x);
                CHECK(5ull <= x);
                CHECK(5ll <= x);
                CHECK(5uz <= x);
                CHECK(5z <= x);
            }

            SUBCASE("negative")
            {
                auto x = Integer(type(10));

                CHECK(x <= 10);
                CHECK(x <= 10l);
                CHECK(x <= 10ll);
                CHECK(x <= 10z);
            }
        }

        SUBCASE("ztd::integer")
        {
            SUBCASE("positive")
            {
                auto x = Integer(type(10));

                CHECK(x <= 10_i8);
                CHECK(x <= 10_i16);
                CHECK(x <= 10_i32);
                CHECK(x <= 10_i64);
                CHECK(x <= 10_isize);

                CHECK(x <= 15_i8);
                CHECK(x <= 15_i16);
                CHECK(x <= 15_i32);
                CHECK(x <= 15_i64);
                CHECK(x <= 15_isize);

                CHECK(x <= 10_u8);
                CHECK(x <= 10_u16);
                CHECK(x <= 10_u32);
                CHECK(x <= 10_u64);
                CHECK(x <= 10_usize);

                CHECK(x <= 15_u8);
                CHECK(x <= 15_u16);
                CHECK(x <= 15_u32);
                CHECK(x <= 15_u64);
                CHECK(x <= 15_usize);

                CHECK(10_i8 <= x);
                CHECK(10_i16 <= x);
                CHECK(10_i32 <= x);
                CHECK(10_i64 <= x);
                CHECK(10_isize <= x);

                CHECK(5_i8 <= x);
                CHECK(5_i16 <= x);
                CHECK(5_i32 <= x);
                CHECK(5_i64 <= x);
                CHECK(5_isize <= x);

                CHECK(10_u8 <= x);
                CHECK(10_u16 <= x);
                CHECK(10_u32 <= x);
                CHECK(10_u64 <= x);
                CHECK(10_usize <= x);

                CHECK(5_u8 <= x);
                CHECK(5_u16 <= x);
                CHECK(5_u32 <= x);
                CHECK(5_u64 <= x);
                CHECK(5_usize <= x);
            }

            SUBCASE("negative")
            {
                auto x = Integer(type(10));

                CHECK(x <= 10_i8);
                CHECK(x <= 10_i16);
                CHECK(x <= 10_i32);
                CHECK(x <= 10_i64);
                CHECK(x <= 10_isize);
            }
        }
    }
}
