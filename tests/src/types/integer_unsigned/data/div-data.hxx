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
template<typename T> struct div final
{
    T x;
    T y;
    T result;
};
} // namespace detail

template<typename T>
std::vector<detail::div<T>> div_data{
    // positive / positive
    {
        // low decimal
        .x = T(typename T::integer_type(7)),
        .y = T(typename T::integer_type(3)),
        .result = T(typename T::integer_type(2)),
    },

    {
        // mid decimal
        .x = T(typename T::integer_type(5)),
        .y = T(typename T::integer_type(2)),
        .result = T(typename T::integer_type(2)),
    },

    {
        // high decimal
        .x = T(typename T::integer_type(8)),
        .y = T(typename T::integer_type(3)),
        .result = T(typename T::integer_type(2)),
    },

    {
        // exact
        .x = T(typename T::integer_type(10)),
        .y = T(typename T::integer_type(5)),
        .result = T(typename T::integer_type(2)),
    },
};

template<typename T>
std::vector<detail::div<T>> div_up_data{
    // positive / positive
    {
        // low decimal
        .x = T(typename T::integer_type(7)),
        .y = T(typename T::integer_type(3)),
        .result = T(typename T::integer_type(3)),
    },

    {
        // mid decimal
        .x = T(typename T::integer_type(5)),
        .y = T(typename T::integer_type(2)),
        .result = T(typename T::integer_type(3)),
    },

    {
        // high decimal
        .x = T(typename T::integer_type(8)),
        .y = T(typename T::integer_type(3)),
        .result = T(typename T::integer_type(3)),
    },

    {
        // exact
        .x = T(typename T::integer_type(10)),
        .y = T(typename T::integer_type(5)),
        .result = T(typename T::integer_type(2)),
    },
};

template<typename T>
std::vector<detail::div<T>> div_floor_data{
    // positive / positive
    {
        // low decimal
        .x = T(typename T::integer_type(7)),
        .y = T(typename T::integer_type(3)),
        .result = T(typename T::integer_type(2)),
    },

    {
        // mid decimal
        .x = T(typename T::integer_type(5)),
        .y = T(typename T::integer_type(2)),
        .result = T(typename T::integer_type(2)),
    },

    {
        // high decimal
        .x = T(typename T::integer_type(8)),
        .y = T(typename T::integer_type(3)),
        .result = T(typename T::integer_type(2)),
    },

    {
        // exact
        .x = T(typename T::integer_type(10)),
        .y = T(typename T::integer_type(5)),
        .result = T(typename T::integer_type(2)),
    },
};

template<typename T>
std::vector<detail::div<T>> div_ceil_data{
    // positive / positive
    {
        // low decimal
        .x = T(typename T::integer_type(7)),
        .y = T(typename T::integer_type(3)),
        .result = T(typename T::integer_type(3)),
    },

    {
        // mid decimal
        .x = T(typename T::integer_type(5)),
        .y = T(typename T::integer_type(2)),
        .result = T(typename T::integer_type(3)),
    },

    {
        // high decimal
        .x = T(typename T::integer_type(8)),
        .y = T(typename T::integer_type(3)),
        .result = T(typename T::integer_type(3)),
    },

    {
        // exact
        .x = T(typename T::integer_type(10)),
        .y = T(typename T::integer_type(5)),
        .result = T(typename T::integer_type(2)),
    },
};

template<typename T>
std::vector<detail::div<T>> div_euclid_data{
    // positive / positive
    {
        // low decimal
        .x = T(typename T::integer_type(7)),
        .y = T(typename T::integer_type(3)),
        .result = T(typename T::integer_type(2)),
    },

    {
        // mid decimal
        .x = T(typename T::integer_type(5)),
        .y = T(typename T::integer_type(2)),
        .result = T(typename T::integer_type(2)),
    },

    {
        // high decimal
        .x = T(typename T::integer_type(8)),
        .y = T(typename T::integer_type(3)),
        .result = T(typename T::integer_type(2)),
    },

    {
        // exact
        .x = T(typename T::integer_type(10)),
        .y = T(typename T::integer_type(5)),
        .result = T(typename T::integer_type(2)),
    },
};
} // namespace test::unsigned_int
