/**
 * Copyright (C) 2026 Brandon Zorn <brandonzorn@cock.li>
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
template<typename T> struct shl final
{
    T x;
    u32 shift;
    T result;
};
} // namespace detail

template<typename T>
std::vector<detail::shl<T>> shl_data{
    // zero
    {
        .x = T(typename T::integer_type(0)),
        .shift = 0_u32,
        .result = T(typename T::integer_type(0)),
    },
    {
        .x = T(typename T::integer_type(5)),
        .shift = 0_u32,
        .result = T(typename T::integer_type(5)),
    },

    // normal shift
    {
        .x = T(typename T::integer_type(1)),
        .shift = 1_u32,
        .result = T(typename T::integer_type(2)),
    },
    {
        .x = T(typename T::integer_type(1)),
        .shift = 4_u32,
        .result = T(typename T::integer_type(16)),
    },
    {
        .x = T(typename T::integer_type(5)),
        .shift = 2_u32,
        .result = T(typename T::integer_type(20)),
    },
};
} // namespace test::signed_int
