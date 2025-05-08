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

#include <algorithm>
#include <span>
#include <stdexcept>
#include <vector>

namespace ztd
{
/**
 * @brief Move
 *
 * - Move vector element to new position
 *
 * @param[in,out] v The std::vector<T> to be rearranged
 * @param[in] old_index The index being moved
 * @param[in] new_index The index to move to
 */
template<typename T>
void
move(std::vector<T>& v, const std::size_t old_index, const std::size_t new_index) noexcept
{
    if (old_index == new_index || old_index >= v.size() || new_index >= v.size())
    {
        return;
    }

    using diff_t = std::vector<T>::difference_type;

    if (old_index < new_index)
    {
        std::rotate(v.begin() + static_cast<diff_t>(old_index),
                    v.begin() + static_cast<diff_t>(old_index) + 1,
                    v.begin() + static_cast<diff_t>(new_index) + 1);
    }
    else
    {
        std::rotate(v.begin() + static_cast<diff_t>(new_index),
                    v.begin() + static_cast<diff_t>(old_index),
                    v.begin() + static_cast<diff_t>(old_index) + 1);
    }
}

/**
 * @brief Index
 *
 * - Get the index of an element in an std::vector,
 * throws std::out_of_range if not found
 *
 * @param[in] v The std::vector<T> to check
 * @param[in] element The element to get the index of
 *
 * @return The index of the element
 */
template<typename T>
[[nodiscard]] std::size_t
index(const std::vector<T>& v, const T& element)
{
    const auto it = std::ranges::find(v.cbegin(), v.cend(), element);
    if (it == v.cend())
    {
        throw std::out_of_range("Item not in vector");
    }
    return static_cast<std::size_t>(it - v.cbegin());
}

/**
 * @brief Merge
 *
 * - Merge multiple std::vectors into a new std::vector,
 * duplicate elements are included only once.
 *
 * @tparam T Type of the elements.
 * @param V Multiple std::vector<T> to merge.
 *
 * @return new std::vector<T>
 */
template<typename T, typename... V>
[[nodiscard]] std::vector<T>
merge(const std::vector<T>& first, const V&... others) noexcept
{
    std::vector<T> result;
    const auto merger = [&](const std::span<const T>& vec)
    {
        for (const T& element : vec)
        {
            if (!std::ranges::contains(result, element))
            {
                result.emplace_back(element);
            }
        }
    };

    merger(first);
    (merger(others), ...);

    return result;
}

/**
 * @brief Dedup
 *
 * - Returns a new std::vector with duplicate
 * elements removed
 *
 * @param[in] v1 std::vector<T>
 *
 * @return new std::vector<T>
 */
template<typename T>
[[nodiscard]] std::vector<T>
dedup(const std::vector<T>& v1) noexcept
{
    std::vector<T> new_vec;
    for (const T& element : v1)
    {
        if (std::ranges::contains(new_vec, element))
        {
            continue;
        }
        new_vec.emplace_back(element);
    }
    return new_vec;
}

/**
 * @brief Prune
 *
 * - Returns a new vector with all v1 elements that are not in v2
 *
 * @param[in] v1 std::vector<T>
 * @param[in] v2 std::vector<T>
 */
template<typename T>
[[nodiscard]] std::vector<T>
prune(const std::vector<T>& v1, const std::vector<T>& v2) noexcept
{
    std::vector<T> new_vec;
    for (const T& element : v1)
    {
        if (std::ranges::contains(v2, element))
        {
            continue;
        }
        new_vec.emplace_back(element);
    }
    return new_vec;
}
} // namespace ztd
