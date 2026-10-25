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

#include <tuple>
#include <vector>

namespace test::signed_int
{
namespace detail
{
template<typename T> struct divmod final
{
    T x;
    T y;
    std::tuple<T, T> results;
};
} // namespace detail

template<typename T>
std::vector<detail::divmod<T>> divmod_data{
    // positive / positive
    {
        .x = T(typename T::integer_type(7)),
        .y = T(typename T::integer_type(3)),
        .results = {typename T::integer_type(2), typename T::integer_type(1)},
    },
    {
        .x = T(typename T::integer_type(5)),
        .y = T(typename T::integer_type(2)),
        .results = {typename T::integer_type(2), typename T::integer_type(1)},
    },
    {
        .x = T(typename T::integer_type(8)),
        .y = T(typename T::integer_type(3)),
        .results = {typename T::integer_type(2), typename T::integer_type(2)},
    },
    {
        .x = T(typename T::integer_type(10)),
        .y = T(typename T::integer_type(5)),
        .results = {typename T::integer_type(2), typename T::integer_type(0)},
    },

    // positive / negative
    {
        .x = T(typename T::integer_type(7)),
        .y = T(typename T::integer_type(-3)),
        .results = {typename T::integer_type(-2), typename T::integer_type(1)},
    },
    {
        .x = T(typename T::integer_type(5)),
        .y = T(typename T::integer_type(-2)),
        .results = {typename T::integer_type(-2), typename T::integer_type(1)},
    },
    {
        .x = T(typename T::integer_type(8)),
        .y = T(typename T::integer_type(-3)),
        .results = {typename T::integer_type(-2), typename T::integer_type(2)},
    },
    {
        .x = T(typename T::integer_type(10)),
        .y = T(typename T::integer_type(-5)),
        .results = {typename T::integer_type(-2), typename T::integer_type(0)},
    },

    // negative / positive
    {
        .x = T(typename T::integer_type(-7)),
        .y = T(typename T::integer_type(3)),
        .results = {typename T::integer_type(-2), typename T::integer_type(-1)},
    },
    {
        .x = T(typename T::integer_type(-5)),
        .y = T(typename T::integer_type(2)),
        .results = {typename T::integer_type(-2), typename T::integer_type(-1)},
    },
    {
        .x = T(typename T::integer_type(-8)),
        .y = T(typename T::integer_type(3)),
        .results = {typename T::integer_type(-2), typename T::integer_type(-2)},
    },
    {
        .x = T(typename T::integer_type(-10)),
        .y = T(typename T::integer_type(5)),
        .results = {typename T::integer_type(-2), typename T::integer_type(0)},
    },

    // negative / negative
    {
        .x = T(typename T::integer_type(-7)),
        .y = T(typename T::integer_type(-3)),
        .results = {typename T::integer_type(2), typename T::integer_type(-1)},
    },
    {
        .x = T(typename T::integer_type(-5)),
        .y = T(typename T::integer_type(-2)),
        .results = {typename T::integer_type(2), typename T::integer_type(-1)},
    },
    {
        .x = T(typename T::integer_type(-8)),
        .y = T(typename T::integer_type(-3)),
        .results = {typename T::integer_type(2), typename T::integer_type(-2)},
    },
    {
        .x = T(typename T::integer_type(-10)),
        .y = T(typename T::integer_type(-5)),
        .results = {typename T::integer_type(2), typename T::integer_type(0)},
    },

    // zero dividend
    {
        .x = T(typename T::integer_type(0)),
        .y = T(typename T::integer_type(5)),
        .results = {typename T::integer_type(0), typename T::integer_type(0)},
    },
    {
        .x = T(typename T::integer_type(0)),
        .y = T(typename T::integer_type(-5)),
        .results = {typename T::integer_type(0), typename T::integer_type(0)},
    },

    // dividend smaller than divisor
    {
        .x = T(typename T::integer_type(1)),
        .y = T(typename T::integer_type(3)),
        .results = {typename T::integer_type(0), typename T::integer_type(1)},
    },
    {
        .x = T(typename T::integer_type(-1)),
        .y = T(typename T::integer_type(3)),
        .results = {typename T::integer_type(0), typename T::integer_type(-1)},
    },
    {
        .x = T(typename T::integer_type(1)),
        .y = T(typename T::integer_type(-3)),
        .results = {typename T::integer_type(0), typename T::integer_type(1)},
    },
    {
        .x = T(typename T::integer_type(-1)),
        .y = T(typename T::integer_type(-3)),
        .results = {typename T::integer_type(0), typename T::integer_type(-1)},
    },

    // divisor +1, -1
    {
        .x = T(typename T::integer_type(5)),
        .y = T(typename T::integer_type(1)),
        .results = {typename T::integer_type(5), typename T::integer_type(0)},
    },
    {
        .x = T(typename T::integer_type(5)),
        .y = T(typename T::integer_type(-1)),
        .results = {typename T::integer_type(-5), typename T::integer_type(0)},
    },
    {
        .x = T(typename T::integer_type(-5)),
        .y = T(typename T::integer_type(1)),
        .results = {typename T::integer_type(-5), typename T::integer_type(0)},
    },
    {
        .x = T(typename T::integer_type(-5)),
        .y = T(typename T::integer_type(-1)),
        .results = {typename T::integer_type(5), typename T::integer_type(0)},
    },
};
} // namespace test::signed_int
