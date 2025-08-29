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

#include <ranges>
#include <string_view>

#include "random.hxx"
#include "types.hxx"

namespace ztd
{
/**
 * @brief random_hex
 * @param[in] len Length of the random string to return
 * @return Get a random hex string
 */
[[nodiscard]] constexpr std::string
random_hex(const ztd::usize len = 10_usize) noexcept
{
    static constexpr std::string_view table = "0123456789ABCDEF";

    std::string str;
    str.reserve(len.data());
    for (const auto _ : std::views::iota(0ul, len.data()))
    {
        str += table.at(ztd::random<std::uint32_t>(0, table.size() - 1));
    }
    return str;
}

[[deprecated("replace with ztd::random_hex()")]] [[nodiscard]] constexpr std::string
randhex(const ztd::usize len = 10_usize) noexcept
{
    return random_hex(len);
}

/**
 * @brief random_string
 * @param[in] len Length of the random string to return
 * @return Get a random hex string
 */
[[nodiscard]] constexpr std::string
random_string(const ztd::usize len = 10_usize) noexcept
{
    static constexpr std::string_view table = "0123456789"
                                              "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                              "abcdefghijklmnopqrstuvwxyz";

    std::string str;
    str.reserve(len.data());
    for (const auto _ : std::views::iota(0ul, len.data()))
    {
        str += table.at(ztd::random<std::uint32_t>(0, table.size() - 1));
    }
    return str;
}

[[deprecated("replace with ztd::random_string()")]] [[nodiscard]] constexpr std::string
randstr(const ztd::usize len = 10_usize) noexcept
{
    return random_string(len);
}
} // namespace ztd
