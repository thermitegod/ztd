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

namespace test::signed_int
{
namespace detail
{
template<typename T> struct sub final
{
    T x;
    T y;
    T result;
};

template<typename T, typename U> struct sub_unsigned final
{
    T x;
    U y;
    T result;
};
} // namespace detail

// signed - signed
template<typename T>
std::vector<detail::sub<T>> sub_data{
    // zero
    {
        .x = T(typename T::integer_type(0)),
        .y = T(typename T::integer_type(0)),
        .result = T(typename T::integer_type(0)),
    },

    // positive - positive
    {
        .x = T(typename T::integer_type(5)),
        .y = T(typename T::integer_type(10)),
        .result = T(typename T::integer_type(-5)),
    },

    // positive - negative
    {
        .x = T(typename T::integer_type(5)),
        .y = T(typename T::integer_type(-10)),
        .result = T(typename T::integer_type(15)),
    },

    {
        .x = T(typename T::integer_type(10)),
        .y = T(typename T::integer_type(-5)),
        .result = T(typename T::integer_type(15)),
    },

    // negative - positive
    {
        .x = T(typename T::integer_type(-5)),
        .y = T(typename T::integer_type(10)),
        .result = T(typename T::integer_type(-15)),
    },

    {
        .x = T(typename T::integer_type(-10)),
        .y = T(typename T::integer_type(5)),
        .result = T(typename T::integer_type(-15)),
    },

    // negative - negative
    {
        .x = T(typename T::integer_type(-5)),
        .y = T(typename T::integer_type(-10)),
        .result = T(typename T::integer_type(5)),
    },
};

// signed - unsigned
template<typename T, typename U>
std::vector<detail::sub_unsigned<T, U>> sub_unsigned_data{
    // zerosub
    {
        .x = T(typename T::integer_type(0)),
        .y = U(typename U::integer_type(0)),
        .result = T(typename T::integer_type(0)),
    },

    // positive - positive
    {
        .x = T(typename T::integer_type(5)),
        .y = U(typename U::integer_type(10)),
        .result = T(typename T::integer_type(-5)),
    },

    // negative - positive
    {
        .x = T(typename T::integer_type(-5)),
        .y = U(typename U::integer_type(10)),
        .result = T(typename T::integer_type(-15)),
    },

    {
        .x = T(typename T::integer_type(-10)),
        .y = U(typename U::integer_type(5)),
        .result = T(typename T::integer_type(-15)),
    },
};
} // namespace test::signed_int
