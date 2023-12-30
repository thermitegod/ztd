/**
 * Copyright (C) 2023 Brandon Zorn <brandonzorn@cock.li>
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

#include <random>
#include <limits>

#include "types.hxx"

namespace ztd
{
/**
 *  @brief urand
 *
 *  - Use std::mt19937 to get a random u64 between (ULONG_MIN, ULONG_MAX)
 *
 * @param[in] min min random value
 * @param[in] max max random value
 *
 * @return a random u64
 */
[[nodiscard]] inline u64
urand(u64 min = std::numeric_limits<u64>::min(), u64 max = std::numeric_limits<u64>::max()) noexcept
{
    std::mt19937 rng;
    rng.seed(std::random_device{}());
    std::uniform_int_distribution<u64> dist(min, max);

    return dist(rng);
}

/**
 *  @brief irand
 *
 *  - Use std::mt19937 to get a random i64 between (LONG_MIN, LONG_MAX)
 *
 * @param[in] min min random value
 * @param[in] max max random value
 *
 * @return a random i64
 */
[[nodiscard]] inline i64
irand(i64 min = std::numeric_limits<i64>::min(), i64 max = std::numeric_limits<i64>::max()) noexcept
{
    std::mt19937 rng;
    rng.seed(std::random_device{}());
    std::uniform_int_distribution<i64> dist(min, max);

    return dist(rng);
}
} // namespace ztd
