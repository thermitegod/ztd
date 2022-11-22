/**
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
#include <cstddef>

#include <sys/types.h>

// better type names
namespace ztd
{
    inline namespace v1
    {
        // shared_ptr/unique_ptr like interface
        template<typename T> using raw_ptr = T*;

        // clang-format off
        using i8    = int8_t;
        using i16   = int16_t;
        using i32   = int32_t;
        using i64   = int64_t;
        using i128  = __int128_t;

        using u8    = uint8_t;
        using u16   = uint16_t;
        using u32   = uint32_t;
        using u64   = uint64_t;
        using u128  = __uint128_t;

        using f32   = float;
        using f64   = double;

        using usize = size_t;
        using isize = ssize_t;
        // clang-format on
    } // namespace v1
} // namespace ztd

#ifndef ZTD_DISABLE_GLOBAL_TYPES

// clang-format off
using i8    = ztd::i8;
using i16   = ztd::i16;
using i32   = ztd::i32;
using i64   = ztd::i64;
using i128  = ztd::i128;

using u8    = ztd::u8;
using u16   = ztd::u16;
using u32   = ztd::u32;
using u64   = ztd::u64;
using u128  = ztd::u128;

using f32   = ztd::f32;
using f64   = ztd::f64;

using usize = ztd::usize;
using isize = ztd::isize;
// clang-format on

#endif
