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

#include <vector>

#include <algorithm>

#include "../types.hxx"

namespace ztd
{
/**
 * @brief Contains
 *
 * - Check if the std::vector contains the element
 *
 * @param[in] v The std::vector to check
 * @param[in] element The element to look for
 *
 * @return true if the std::vector<T> contains the element
 */
template<typename T>
[[deprecated("use std::ranges::contains")]] [[nodiscard]] bool
contains(const std::vector<T>& v, const T& element) noexcept
{
#if defined(__cpp_lib_ranges_contains)
    return std::ranges::contains(v, element);
#else
    return (std::ranges::find(v.cbegin(), v.cend(), element) != v.cend());
#endif
}

/**
 * @brief Remove
 *
 * - Remove element from an std::vector
 *
 * @param[in] v The std::vector to check
 * @param[in] element The element to remove
 *
 * @return true if the std::vector<T> contains the element
 */
template<typename T>
[[deprecated("use std::ranges::remove")]] void
remove(std::vector<T>& v, const T& element) noexcept
{
    if (!contains(v, element))
    {
        return;
    }
    v.erase(std::remove(v.begin(), v.end(), element), v.end());
}
} // namespace ztd
