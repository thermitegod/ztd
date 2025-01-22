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

#include <charconv>
#include <expected>
#include <system_error>
#include <type_traits>

namespace ztd
{
/**
 * @brief from_string
 *
 *  - Extract a numeric value from a string, the string must only
 *    be a numeric and can not be a mix of letters, numbers or control
 *    characters.
 *
 *  - Special case: A single trailing newline is allowed.
 *
 * @param[in] str The string to extract a numeric value from
 *
 * @return The numeric value from str, or an std::error_code
 */
template<typename T>
[[nodiscard]] constexpr std::expected<T, std::error_code>
from_string(const std::string_view str) noexcept
    requires(std::is_integral_v<T> || std::is_floating_point_v<T>)
{
    T result{};
    const auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), result);
    if (ec != std::errc())
    {
        return std::unexpected(std::make_error_code(ec));
    }
    if (ptr != str.data() + str.size())
    {
        if (ptr == str.data() + str.size() - 1 && *ptr == '\n')
        { // allow a single trailing newline
            return result;
        }
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }
    return result;
}
} // namespace ztd
