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

#include <concepts>

namespace ztd::detail
{
// clang-format off
template<typename T> concept is_integer          = std::integral<T> && !std::same_as<T, bool> && !std::same_as<T, char>;
template<typename T> concept is_signed_integer   = is_integer<T> && std::signed_integral<T>;
template<typename T> concept is_unsigned_integer = is_integer<T> && std::unsigned_integral<T>;
// clang-format on
} // namespace ztd::detail
