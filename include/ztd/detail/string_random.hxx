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

#pragma once

#include <array>
#include <string>

#include "random.hxx"
#include "types.hxx"

namespace ztd
{
namespace detail
{
static constexpr std::array<char, 62> table{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',

    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',

    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
};

[[nodiscard]] inline std::string
random_string(const std::size_t len, const std::uint32_t charset_size) noexcept
{
    std::string str;
    str.reserve(len);
    while (str.size() < len)
    {
        str += table.at(ztd::random<std::uint32_t>(0, charset_size - 1));
    }
    return str;
}
} // namespace detail

/**
 * @brief randhex
 *
 * @param[in] len Length of the random string to return
 *
 * @return Get a random hex string
 */
[[nodiscard]] inline std::string
randhex(const ztd::usize len = 10_usize) noexcept
{
    return detail::random_string(len.data(), 16);
}

/**
 * @brief randhex
 *
 * @param[in] len Length of the random string to return
 *
 * @return Get a random hex string
 */
[[nodiscard]] inline std::string
randstr(const ztd::usize len = 10_usize) noexcept
{
    return detail::random_string(len.data(), detail::table.size());
}
} // namespace ztd
