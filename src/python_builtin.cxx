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

#include <vector>

#include <stdexcept>

#include "ztd/internal/types.hxx"

#include "ztd/internal/python_builtin.hxx"

const std::vector<i64>
ztd::range(i64 stop)
{
    return range(0, stop, 1);
}

const std::vector<i64>
ztd::range(i64 start, i64 stop, i64 step)
{
    if (step == 0)
    {
        throw std::invalid_argument("step must not be zero");
    }

    std::vector<i64> result;

    if ((step > 0 && start >= stop) || (step < 0 && start <= stop))
    {
        return result;
    }

    for (i64 i = start; (step > 0) ? (i < stop) : (i > stop); i += step)
    {
        result.emplace_back(i);
    }
    return result;
}
