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

#ifndef ZTD_MAIN_HEADER
#error "Only <ztd.hxx> can be included directly"
#endif

#pragma once

#include <vector>

namespace ztd
{
    /**
     *
     * std::vector<T>
     *
     */

    /**
     * @brief Move
     *
     * - Move vector element to new position
     *
     * @param[out] __v The std::vector<T> to check
     * @param[out] __old_index The index being moved
     * @param[out] __new_index The index to move to
     */
    template<typename T>
    static inline void
    move(std::vector<T>& __v, std::size_t __old_index, std::size_t __new_index) noexcept
    {
        if (__old_index > __new_index)
            std::rotate(__v.rend() - __old_index - 1,
                        __v.rend() - __old_index,
                        __v.rend() - __new_index);
        else
            std::rotate(__v.begin() + __old_index,
                        __v.begin() + __old_index + 1,
                        __v.begin() + __new_index + 1);
    }

    /**
     * @brief Index
     *
     * - Get the index of an element in an std::vector,
     * throws std::out_of_range if not found
     *
     * @param[out] __v The std::vector<T> to check
     * @param[out] __element The element to get the index of

     *
     * @return The index of the element
     */
    template<typename T>
    static inline std::size_t
    index(std::vector<T>& __v, T& __element)
    {
        std::size_t index;
        auto it = find(__v.begin(), __v.end(), __element);
        if (it != __v.end())
            index = it - __v.begin();
        else
            throw std::out_of_range("Item not in vector");
        return index;
    }

    /**
     * @brief Contains
     *
     * - Check if the std::vector containes the element
     *
     * @param[out] __v The std::vector to check
     * @param[out] __element The element to look for
     *
     * @return true if the std::vector<T> containes the element
     */
    template<typename T>
    static inline bool
    contains(std::vector<T>& __v, T& __element) noexcept
    {
        if (std::find(__v.begin(), __v.end(), __element) != __v.end())
            return true;
        return false;
    }

    /**
     * @brief Remove
     *
     * - Remove element from an std::vector
     *
     * @param[out] __v The std::vector to check
     * @param[out] __element The element to remove
     *
     * @return true if the std::vector<T> containes the element
     */
    template<typename T>
    static inline void
    remove(std::vector<T>& __v, T& __element) noexcept
    {
        if (contains(__v, __element))
            __v.erase(std::remove(__v.begin(), __v.end(), __element), __v.end());
    }

    /**
     * @brief Merge
     *
     * - Merge two std::vectors into a new std::vector,
     * duplicate elements are included only once.
     *
     * @param[out] __v1 std::vector<T>
     * @param[out] __v2 std::vector<T>
     *
     * @return new std::vector<T>
     */
    template<typename T>
    static inline std::vector<T>
    merge(std::vector<T>& __v1, std::vector<T>& __v2) noexcept
    {
        std::vector<T> new_vec;
        for (T element: __v1)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        for (T element: __v2)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        return new_vec;
    }

    /**
     * @brief Merge
     *
     * - Merge three std::vectors into a new std::vector,
     * duplicate elements are included only once.
     *
     * @param[out] __v1 std::vector<T>
     * @param[out] __v2 std::vector<T>
     * @param[out] __v3 std::vector<T>
     *
     * @return new std::vector<T>
     */
    template<typename T>
    static inline std::vector<T>
    merge(std::vector<T>& __v1, std::vector<T>& __v2, std::vector<T>& __v3) noexcept
    {
        std::vector<T> new_vec;
        for (T element: __v1)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        for (T element: __v2)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        for (T element: __v3)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        return new_vec;
    }

    /**
     * @brief Merge
     *
     * - Merge four std::vectors into a new std::vector,
     * duplicate elements are included only once.
     *
     * @param[out] __v1 std::vector<T>
     * @param[out] __v2 std::vector<T>
     * @param[out] __v3 std::vector<T>
     * @param[out] __v4 std::vector<T>
     *
     * @return new std::vector<T>
     */
    template<typename T>
    static inline std::vector<T>
    merge(std::vector<T>& __v1, std::vector<T>& __v2, std::vector<T>& __v3,
          std::vector<T>& __v4) noexcept
    {
        std::vector<T> new_vec;
        for (T element: __v1)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        for (T element: __v2)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        for (T element: __v3)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        for (T element: __v4)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        return new_vec;
    }
} // namespace ztd
