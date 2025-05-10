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
random(const T min = std::numeric_limits<T>::min(),
       const T max = std::numeric_limits<T>::max()) noexcept
    requires(std::is_integral_v<T> && !std::is_same_v<T, bool>)
{
    assert(min <= max);

    std::uniform_int_distribution<T> dist(min, max);
    return dist(detail::rng());
}

/**
 *  @brief rand
 *
 *  - get a random floating point of type T between (min, max)
 *
 * @param[in] min min random value
 * @param[in] max max random value
 *
 * @return a random floating point
 */
template<typename T>
[[nodiscard]] inline T
random(const T min = std::numeric_limits<T>::lowest(),
       const T max = std::numeric_limits<T>::max()) noexcept
    requires(std::is_floating_point_v<T>)
{
    assert(min <= max);

    std::uniform_real_distribution<T> dist(min, max);
    return dist(detail::rng());
}

/**
 *  @brief rand
 *
 *  - get a random bool
 *
 * @return a random bool
 */
template<typename T>
[[nodiscard]] inline T
random() noexcept
    requires(std::is_same_v<T, bool>)
{
    static thread_local std::bernoulli_distribution dist(0.5);
    return dist(detail::rng());
}
} // namespace ztd
