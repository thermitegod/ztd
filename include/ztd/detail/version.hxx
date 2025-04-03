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

#include <compare>

#include "types.hxx"

namespace ztd
{
namespace detail
{
struct version_t final
{
    u8 major = 0;
    u8 minor = 5;
    u8 patch = 0;

    constexpr auto operator<=>(const version_t& other) const noexcept = default;
};
} // namespace detail

/**
 * @brief Global constant instance of the current library version
 *
 * Provides access to the current version information of this library
 */
inline constexpr detail::version_t version{};
} // namespace ztd
