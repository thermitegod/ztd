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

#include <limits>
#include <random>

#include "ztd/internal/types.hxx"

#include "ztd/internal/random.hxx"

u64
ztd::urand() noexcept
{
    std::mt19937 rng;
    rng.seed(std::random_device{}());
    std::uniform_int_distribution<u64> dist(std::numeric_limits<u64>::min(), std::numeric_limits<u64>::max());

    return dist(rng);
}

i64
ztd::irand() noexcept
{
    std::mt19937 rng;
    rng.seed(std::random_device{}());
    std::uniform_int_distribution<i64> dist(std::numeric_limits<i64>::min(), std::numeric_limits<i64>::max());

    return dist(rng);
}
