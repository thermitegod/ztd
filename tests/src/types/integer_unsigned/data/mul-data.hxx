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

namespace test::unsigned_int
{
namespace detail
{
template<typename T> struct mul final
{
    T x;
    T y;
    T result;
};
} // namespace detail

template<typename T>
std::vector<detail::mul<T>> mul_data{
    // zero
    {
        .x = T(typename T::integer_type(0)),
        .y = T(typename T::integer_type(0)),
        .result = T(typename T::integer_type(0)),
    },

    {
        .x = T(typename T::integer_type(10)),
        .y = T(typename T::integer_type(0)),
        .result = T(typename T::integer_type(0)),
    },

    {
        .x = T(typename T::integer_type(0)),
        .y = T(typename T::integer_type(10)),
        .result = T(typename T::integer_type(0)),
    },

    // positive * positive
    {
        .x = T(typename T::integer_type(5)),
        .y = T(typename T::integer_type(2)),
        .result = T(typename T::integer_type(10)),
    },

    {
        .x = T(typename T::integer_type(2)),
        .y = T(typename T::integer_type(5)),
        .result = T(typename T::integer_type(10)),
    },
};
} // namespace test::unsigned_int
