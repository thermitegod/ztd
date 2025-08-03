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

#include <vector>

#include "ztd/detail/types.hxx"

namespace test::signed_int
{
namespace detail
{
template<typename T> struct pow final
{
    T x;
    u32 y;
    T result;
};
} // namespace detail

// unsigned + unsigned
template<typename T>
std::vector<detail::pow<T>> pow_data{
    // zero
    {
        .x = T(typename T::integer_type(0)),
        .y = 0_u32,
        .result = T(typename T::integer_type(0)),
    },
    {
        .x = T(typename T::integer_type(0)),
        .y = 1_u32,
        .result = T(typename T::integer_type(0)),
    },
    {
        .x = T(typename T::integer_type(0)),
        .y = 2_u32,
        .result = T(typename T::integer_type(0)),
    },
    {
        .x = T(typename T::integer_type(0)),
        .y = 3_u32,
        .result = T(typename T::integer_type(0)),
    },
    {
        .x = T(typename T::integer_type(0)),
        .y = 3_u32,
        .result = T(typename T::integer_type(0)),
    },
    {
        .x = T(typename T::integer_type(0)),
        .y = 4_u32,
        .result = T(typename T::integer_type(0)),
    },
    {
        .x = T(typename T::integer_type(0)),
        .y = 5_u32,
        .result = T(typename T::integer_type(0)),
    },
    {
        .x = T(typename T::integer_type(0)),
        .y = 6_u32,
        .result = T(typename T::integer_type(0)),
    },
    {
        .x = T(typename T::integer_type(0)),
        .y = 7_u32,
        .result = T(typename T::integer_type(0)),
    },
    {
        .x = T(typename T::integer_type(0)),
        .y = 8_u32,
        .result = T(typename T::integer_type(0)),
    },
    {
        .x = T(typename T::integer_type(0)),
        .y = 8_u32,
        .result = T(typename T::integer_type(0)),
    },

    // one
    {
        .x = T(typename T::integer_type(1)),
        .y = 0_u32,
        .result = T(typename T::integer_type(1)),
    },
    {
        .x = T(typename T::integer_type(1)),
        .y = 1_u32,
        .result = T(typename T::integer_type(1)),
    },
    {
        .x = T(typename T::integer_type(1)),
        .y = 2_u32,
        .result = T(typename T::integer_type(1)),
    },
    {
        .x = T(typename T::integer_type(1)),
        .y = 3_u32,
        .result = T(typename T::integer_type(1)),
    },
    {
        .x = T(typename T::integer_type(1)),
        .y = 3_u32,
        .result = T(typename T::integer_type(1)),
    },
    {
        .x = T(typename T::integer_type(1)),
        .y = 4_u32,
        .result = T(typename T::integer_type(1)),
    },
    {
        .x = T(typename T::integer_type(1)),
        .y = 5_u32,
        .result = T(typename T::integer_type(1)),
    },
    {
        .x = T(typename T::integer_type(1)),
        .y = 6_u32,
        .result = T(typename T::integer_type(1)),
    },
    {
        .x = T(typename T::integer_type(1)),
        .y = 7_u32,
        .result = T(typename T::integer_type(1)),
    },
    {
        .x = T(typename T::integer_type(1)),
        .y = 8_u32,
        .result = T(typename T::integer_type(1)),
    },
    {
        .x = T(typename T::integer_type(1)),
        .y = 8_u32,
        .result = T(typename T::integer_type(1)),
    },

    // two
    {
        .x = T(typename T::integer_type(2)),
        .y = 0_u32,
        .result = T(typename T::integer_type(1)),
    },
    {
        .x = T(typename T::integer_type(2)),
        .y = 1_u32,
        .result = T(typename T::integer_type(2)),
    },
    {
        .x = T(typename T::integer_type(2)),
        .y = 2_u32,
        .result = T(typename T::integer_type(4)),
    },
    {
        .x = T(typename T::integer_type(2)),
        .y = 3_u32,
        .result = T(typename T::integer_type(8)),
    },
    {
        .x = T(typename T::integer_type(2)),
        .y = 4_u32,
        .result = T(typename T::integer_type(16)),
    },
    {
        .x = T(typename T::integer_type(2)),
        .y = 5_u32,
        .result = T(typename T::integer_type(32)),
    },
    {
        .x = T(typename T::integer_type(2)),
        .y = 6_u32,
        .result = T(typename T::integer_type(64)),
    },

    // negative two
    {
        .x = T(typename T::integer_type(-2)),
        .y = 0_u32,
        .result = T(typename T::integer_type(1)),
    },
    {
        .x = T(typename T::integer_type(-2)),
        .y = 1_u32,
        .result = T(typename T::integer_type(-2)),
    },
    {
        .x = T(typename T::integer_type(-2)),
        .y = 2_u32,
        .result = T(typename T::integer_type(4)),
    },
    {
        .x = T(typename T::integer_type(-2)),
        .y = 3_u32,
        .result = T(typename T::integer_type(-8)),
    },
    {
        .x = T(typename T::integer_type(-2)),
        .y = 4_u32,
        .result = T(typename T::integer_type(16)),
    },
    {
        .x = T(typename T::integer_type(-2)),
        .y = 5_u32,
        .result = T(typename T::integer_type(-32)),
    },
    {
        .x = T(typename T::integer_type(-2)),
        .y = 6_u32,
        .result = T(typename T::integer_type(64)),
    },
};
} // namespace test::signed_int
