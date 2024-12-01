/**
 * Copyright (C) 2024 Brandon Zorn <brandonzorn@cock.li>
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

#include <format>
#include <type_traits>

#include "ztd/detail/types.hxx"

TEST_SUITE("types" * doctest::description(""))
{
    using namespace ztd::literals::type_literals;

    TEST_CASE("u8")
    {
        SUBCASE("literal")
        {
            auto x = 100_u8;
            CHECK_EQ((std::is_same_v<decltype(x), ztd::u8>), true);
        }

        SUBCASE("const literal")
        {
            const auto x = 100_u8;
            CHECK_EQ((std::is_same_v<decltype(x), const ztd::u8>), true);
        }

        SUBCASE("std::format support")
        {
            CHECK_EQ(std::format("{}", 100_u8), "100");

            auto x = 100_u8;
            CHECK_EQ(std::format("{}", x), "100");
        }
    }

    TEST_CASE("u16")
    {
        SUBCASE("literal")
        {
            auto x = 100_u16;
            CHECK_EQ((std::is_same_v<decltype(x), ztd::u16>), true);
        }

        SUBCASE("const literal")
        {
            const auto x = 100_u16;
            CHECK_EQ((std::is_same_v<decltype(x), const ztd::u16>), true);
        }

        SUBCASE("std::format support")
        {
            CHECK_EQ(std::format("{}", 100_u16), "100");

            auto x = 100_u16;
            CHECK_EQ(std::format("{}", x), "100");
        }
    }

    TEST_CASE("u32")
    {
        SUBCASE("literal")
        {
            auto x = 100_u32;
            CHECK_EQ((std::is_same_v<decltype(x), ztd::u32>), true);
        }

        SUBCASE("const literal")
        {
            const auto x = 100_u32;
            CHECK_EQ((std::is_same_v<decltype(x), const ztd::u32>), true);
        }

        SUBCASE("std::format support")
        {
            CHECK_EQ(std::format("{}", 100_u32), "100");

            auto x = 100_u32;
            CHECK_EQ(std::format("{}", x), "100");
        }
    }

    TEST_CASE("u64")
    {
        SUBCASE("literal")
        {
            auto x = 100_u64;
            CHECK_EQ((std::is_same_v<decltype(x), ztd::u64>), true);
        }

        SUBCASE("const literal")
        {
            const auto x = 100_u64;
            CHECK_EQ((std::is_same_v<decltype(x), const ztd::u64>), true);
        }

        SUBCASE("std::format support")
        {
            CHECK_EQ(std::format("{}", 100_u64), "100");

            auto x = 100_u64;
            CHECK_EQ(std::format("{}", x), "100");
        }
    }

    TEST_CASE("i8")
    {
        SUBCASE("literal")
        {
            auto x = 100_i8;
            CHECK_EQ((std::is_same_v<decltype(x), ztd::i8>), true);
        }

        SUBCASE("const literal")
        {
            const auto x = 100_i8;
            CHECK_EQ((std::is_same_v<decltype(x), const ztd::i8>), true);
        }

        SUBCASE("std::format support")
        {
            CHECK_EQ(std::format("{}", 100_i8), "100");

            auto x = 100_i8;
            CHECK_EQ(std::format("{}", x), "100");
        }
    }

    TEST_CASE("i16")
    {
        SUBCASE("literal")
        {
            auto x = 100_i16;
            CHECK_EQ((std::is_same_v<decltype(x), ztd::i16>), true);
        }

        SUBCASE("const literal")
        {
            const auto x = 100_i16;
            CHECK_EQ((std::is_same_v<decltype(x), const ztd::i16>), true);
        }

        SUBCASE("std::format support")
        {
            CHECK_EQ(std::format("{}", 100_i16), "100");

            auto x = 100_i16;
            CHECK_EQ(std::format("{}", x), "100");
        }
    }

    TEST_CASE("i32")
    {
        SUBCASE("literal")
        {
            auto x = 100_i32;
            CHECK_EQ((std::is_same_v<decltype(x), ztd::i32>), true);
        }

        SUBCASE("const literal")
        {
            const auto x = 100_i32;
            CHECK_EQ((std::is_same_v<decltype(x), const ztd::i32>), true);
        }

        SUBCASE("std::format support")
        {
            CHECK_EQ(std::format("{}", 100_i32), "100");

            auto x = 100_i32;
            CHECK_EQ(std::format("{}", x), "100");
        }
    }

    TEST_CASE("i64")
    {
        SUBCASE("literal")
        {
            auto x = 100_i64;
            CHECK_EQ((std::is_same_v<decltype(x), ztd::i64>), true);
        }

        SUBCASE("const literal")
        {
            const auto x = 100_i64;
            CHECK_EQ((std::is_same_v<decltype(x), const ztd::i64>), true);
        }

        SUBCASE("std::format support")
        {
            CHECK_EQ(std::format("{}", 100_i64), "100");

            auto x = 100_i64;
            CHECK_EQ(std::format("{}", x), "100");
        }
    }

    TEST_CASE("f32")
    {
        SUBCASE("literal")
        {
            auto x = 100.5_f32;
            CHECK_EQ((std::is_same_v<decltype(x), ztd::f32>), true);
        }

        SUBCASE("const literal")
        {
            const auto x = 100.5_f32;
            CHECK_EQ((std::is_same_v<decltype(x), const ztd::f32>), true);
        }

        SUBCASE("std::format support")
        {
            CHECK_EQ(std::format("{}", 100.5_f32), "100.5");

            auto x = 100.5_f32;
            CHECK_EQ(std::format("{}", x), "100.5");
        }
    }

    TEST_CASE("f64")
    {
        SUBCASE("literal")
        {
            auto x = 100.5_f64;
            CHECK_EQ((std::is_same_v<decltype(x), ztd::f64>), true);
        }

        SUBCASE("const literal")
        {
            const auto x = 100.5_f64;
            CHECK_EQ((std::is_same_v<decltype(x), const ztd::f64>), true);
        }

        SUBCASE("std::format support")
        {
            CHECK_EQ(std::format("{}", 100.5_f64), "100.5");

            auto x = 100.5_f64;
            CHECK_EQ(std::format("{}", x), "100.5");
        }
    }

    TEST_CASE("usize")
    {
        SUBCASE("literal")
        {
            auto x = 100_usize;
            CHECK_EQ((std::is_same_v<decltype(x), ztd::usize>), true);
        }

        SUBCASE("const literal")
        {
            const auto x = 100_usize;
            CHECK_EQ((std::is_same_v<decltype(x), const ztd::usize>), true);
        }

        SUBCASE("std::format support")
        {
            CHECK_EQ(std::format("{}", 100_usize), "100");

            auto x = 100_usize;
            CHECK_EQ(std::format("{}", x), "100");
        }
    }

    TEST_CASE("isize")
    {
        SUBCASE("literal")
        {
            auto x = 100_isize;
            CHECK_EQ((std::is_same_v<decltype(x), ztd::isize>), true);
        }

        SUBCASE("const literal")
        {
            const auto x = 100_isize;
            CHECK_EQ((std::is_same_v<decltype(x), const ztd::isize>), true);
        }

        SUBCASE("std::format support")
        {
            CHECK_EQ(std::format("{}", 100_isize), "100");

            auto x = 100_isize;
            CHECK_EQ(std::format("{}", x), "100");
        }
    }
}
