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
     * @brief Move
     *
     * - Move vector element to new position
     *
     * @param[in,out] v The std::vector<T> to be rearranged
     * @param[in] old_index The index being moved
     * @param[in] new_index The index to move to
     */
    template<typename T>
    static inline void
    move(std::vector<T>& v, std::size_t old_index, std::size_t new_index) noexcept
    {
        if (old_index == new_index)
            return;
        if (old_index > new_index)
            std::rotate(v.rend() - old_index - 1, v.rend() - old_index, v.rend() - new_index);
        else
            std::rotate(v.begin() + old_index,
                        v.begin() + old_index + 1,
                        v.begin() + new_index + 1);
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
    static inline std::size_t
    index(const std::vector<T>& v, const T& element)
    {
        auto it = find(v.begin(), v.end(), element);
        if (it != v.end())
            return (it - v.begin());
        throw std::out_of_range("Item not in vector");
    }

    /**
     * @brief Contains
     *
     * - Check if the std::vector containes the element
     *
     * @param[in] v The std::vector to check
     * @param[in] element The element to look for
     *
     * @return true if the std::vector<T> containes the element
     */
    template<typename T>
    static inline bool
    contains(const std::vector<T>& v, const T& element) noexcept
    {
        return (std::find(v.begin(), v.end(), element) != v.end());
    }

    /**
     * @brief Remove
     *
     * - Remove element from an std::vector
     *
     * @param[in] v The std::vector to check
     * @param[in] element The element to remove
     *
     * @return true if the std::vector<T> containes the element
     */
    template<typename T>
    static inline void
    remove(std::vector<T>& v, const T& element) noexcept
    {
        if (!contains(v, element))
            return;
        v.erase(std::remove(v.begin(), v.end(), element), v.end());
    }

    /**
     * @brief Merge
     *
     * - Merge two std::vectors into a new std::vector,
     * duplicate elements are included only once.
     *
     * @param[in] v1 std::vector<T>
     * @param[in] v2 std::vector<T>
     *
     * @return new std::vector<T>
     */
    template<typename T>
    static inline std::vector<T>
    merge(const std::vector<T>& v1, const std::vector<T>& v2) noexcept
    {
        std::vector<T> new_vec;
        for (const T& element: v1)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        for (const T& element: v2)
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
     * @param[in] v1 std::vector<T>
     * @param[in] v2 std::vector<T>
     * @param[in] v3 std::vector<T>
     *
     * @return new std::vector<T>
     */
    template<typename T>
    static inline std::vector<T>
    merge(const std::vector<T>& v1, const std::vector<T>& v2, const std::vector<T>& v3) noexcept
    {
        std::vector<T> new_vec;
        for (const T& element: v1)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        for (const T& element: v2)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        for (const T& element: v3)
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
     * @param[in] v1 std::vector<T>
     * @param[in] v2 std::vector<T>
     * @param[in] v3 std::vector<T>
     * @param[in] v4 std::vector<T>
     *
     * @return new std::vector<T>
     */
    template<typename T>
    static inline std::vector<T>
    merge(const std::vector<T>& v1, const std::vector<T>& v2, const std::vector<T>& v3,
          const std::vector<T>& v4) noexcept
    {
        std::vector<T> new_vec;
        for (const T& element: v1)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        for (const T& element: v2)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        for (const T& element: v3)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        for (const T& element: v4)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        return new_vec;
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
    static inline std::vector<T>
    dedup(const std::vector<T>& v1) noexcept
    {
        std::vector<T> new_vec;
        for (const T& element: v1)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        return new_vec;
    }

    /**
     * @brief Prune
     *
     * - Remove all elements in the first vector that
     * are also in the second vector
     *
     * @param[in,out] v1 std::vector<T>
     * @param[in] v2 std::vector<T>
     */
    template<typename T>
    static inline void
    prune(std::vector<T>& v1, const std::vector<T>& v2) noexcept
    {
        for (const T& element: v2)
        {
            if (contains(v1, element))
                remove(v1, element);
        }
    }
} // namespace ztd
