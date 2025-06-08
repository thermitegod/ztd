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

struct custom_int
{
};
struct custom_uint
{
};

template<> struct ztd::integer_type<custom_int>
{
    using type = std::int32_t;
    using sign_conversion = custom_uint;
};

template<> struct ztd::integer_type<custom_uint>
{
    using type = std::uint32_t;
    using sign_conversion = custom_int;
};

using cint = ztd::integer<custom_int>;
using cuint = ztd::integer<custom_uint>;

TEST_SUITE("integer<T>" * doctest::description(""))
{
    TEST_CASE("custom types")
    {
        cint x;
        cuint y;

        CHECK(std::same_as<decltype(x), decltype(y.cast_signed())>);
        CHECK(std::same_as<decltype(y), decltype(x.cast_unsigned())>);

        CHECK_FALSE(std::same_as<cint, ztd::u32>);
        CHECK_FALSE(std::same_as<cuint, ztd::i32>);
    }
}
