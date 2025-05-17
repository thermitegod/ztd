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

#pragma once

#include <glaze/glaze.hpp>

#include "ztd/detail/types.hxx"

// Could have just used a friend in ztd::integer<T>
// but that would have pulled glaze into every TU.
//
// friend struct glz::meta<integer<integer_type>>;
//
// template<class T> struct glz::meta<ztd::integer<T>>
// {
//     static constexpr auto value = object(&ztd::integer<T>::value_);
// };

namespace glz
{
template<typename T>
    requires(ztd::is_integral_v<T>)
struct from<JSON, T>
{
    template<auto Opts>
    static void
    op(T& value, auto&&... args)
    {
        typename T::integer_type raw{};
        parse<JSON>::template op<Opts>(raw, std::forward<decltype(args)>(args)...);
        value = T{raw};
    }
};

template<typename T>
    requires(ztd::is_integral_v<T>)
struct to<JSON, T>
{
    template<auto Opts>
    static void
    op(const T& value, auto&&... args) noexcept
    {
        serialize<JSON>::template op<Opts>(value.data(), std::forward<decltype(args)>(args)...);
    }
};
} // namespace glz
