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

#include "ztd/detail/byte_size.hxx"

/**
 * Zebibyte, Yobibyte, Robibyte, and Qubibyte test support
 * is disabled because there are no integer types large enough to
 * hold their size in bytes. They can be enabled when the C++ standard
 * has std::uint128_t.
 */
#define NO_VERY_LARGE_INT_TYPE

/**
 * Byte        1
 * Kibibyte    1,024
 * Mebibyte    1,048,576
 * Gibibyte    1,073,741,824
 * Tebibyte    1,099,511,627,776
 * Pebibyte    1,125,899,906,842,624
 * Exbibyte    1,152,921,504,606,846,976
 * Zebibyte    1,180,591,620,717,411,303,424
 * Yobibyte    1,208,925,819,614,629,174,706,176
 * Robibyte    1,237,940,039,285,380,274,899,124,224
 * Qubibyte    1,267,650,600,228,229,401,496,703,205,376
 */

using namespace ztd::byte_iec_literals;

const auto SIZE_BYTE = 1_B;
const auto SIZE_KIBIBYTE = 1_KiB;
const auto SIZE_MEBIBYTE = 1_MiB;
const auto SIZE_GIBIBYTE = 1_GiB;
const auto SIZE_TEBIBYTE = 1_TiB;
const auto SIZE_PEBIBYTE = 1_PiB;
const auto SIZE_EXBIBYTE = 1_EiB;

#ifndef NO_VERY_LARGE_INT_TYPE
const auto SIZE_ZEBIBYTE = 1_ZiB;
const auto SIZE_YOBIBYTE = 1_YiB;
const auto SIZE_ROBIBYTE = 1_RiB;
const auto SIZE_QUBIBYTE = 1_QiB;
#endif
