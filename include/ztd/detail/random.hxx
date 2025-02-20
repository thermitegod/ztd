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

#include <limits>
#include <random>
#include <type_traits>

#include <cassert>

#include "types.hxx"

namespace ztd
{
namespace detail
{
inline std::mt19937&
rng()
{
    static thread_local std::mt19937 rng(std::random_device{}());
    return rng;
}
} // namespace detail

/**
 *  @brief rand
 *
 *  - get a random integral of type T between (min, max)
 *
 * @param[in] min min random value
 * @param[in] max max random value
 *
 * @return a random integral
 */
template<typename T>
[[nodiscard]] inline T
rand(const T min = std::numeric_limits<T>::min(),
     const T max = std::numeric_limits<T>::max()) noexcept
    requires(std::is_integral_v<T>)
{
    assert(min <= max);

    std::uniform_int_distribution<T> dist(min, max);
    return dist(detail::rng());
}

/**
 *  @brief urand
 *
 *  - get a random u64 between (ULONG_MIN, ULONG_MAX)
 *
 * @param[in] min min random value
 * @param[in] max max random value
 *
 * @return a random u64
 */
[[nodiscard]] inline u64
urand(const u64 min = std::numeric_limits<u64>::min(),
      const u64 max = std::numeric_limits<u64>::max()) noexcept
{
    return rand<u64>(min, max);
}

/**
 *  @brief irand
 *
 *  - get a random i64 between (LONG_MIN, LONG_MAX)
 *
 * @param[in] min min random value
 * @param[in] max max random value
 *
 * @return a random i64
 */
[[nodiscard]] inline i64
irand(const i64 min = std::numeric_limits<i64>::min(),
      const i64 max = std::numeric_limits<i64>::max()) noexcept
{
    return rand<i64>(min, max);
}
} // namespace ztd
