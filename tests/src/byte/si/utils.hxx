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

#include <cstdint>

/**
 * Zettabyte, Yottabyte, Ronnabyte, and Quettabyte test support
 * is disabled because there are no integer types large enough to
 * hold their size in bytes. They can be enabled when the C++ standard
 * has std::uint128_t.
 */
#define NO_VERY_LARGE_INT_TYPE

// clang-format off

/**
 * Byte         1
 * Kilobyte     1,000
 * Megabyte     1,000,000
 * Gigabyte     1,000,000,000
 * Terrabyte    1,000,000,000,000
 * Petabyte     1,000,000,000,000,000
 * Exabyte      1,000,000,000,000,000,000
 * Zettabyte    1,000,000,000,000,000,000,000
 * Yottabyte    1,000,000,000,000,000,000,000,000
 * Ronnabyte    1,000,000,000,000,000,000,000,000,000
 * Quettabyte   1,000,000,000,000,000,000,000,000,000,000
 */

constexpr std::uint64_t SIZE_BYTE       = 1;
constexpr std::uint64_t SIZE_KILOBYTE   = 1000;
constexpr std::uint64_t SIZE_MEGABYTE   = 1000000;
constexpr std::uint64_t SIZE_GIGABYTE   = 1000000000;
constexpr std::uint64_t SIZE_TERABYTE   = 1000000000000;
constexpr std::uint64_t SIZE_PETABYTE   = 1000000000000000;
constexpr std::uint64_t SIZE_EXABYTE    = 1000000000000000000;

#ifndef NO_VERY_LARGE_INT_TYPE
constexpr std::uint64_t SIZE_ZETTABYTE  = 1000000000000000000000;
constexpr std::uint64_t SIZE_YOTTABYTE  = 1000000000000000000000000;
constexpr std::uint64_t SIZE_RONNABYTE  = 1000000000000000000000000000;
constexpr std::uint64_t SIZE_QUETTABYTE = 1000000000000000000000000000000;
#endif
