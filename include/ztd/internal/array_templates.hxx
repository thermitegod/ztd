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

#include <string>
#include <string_view>

#include <algorithm>
#include <ranges>

#include <array>

#include "types.hxx"

namespace ztd
{
    /**
     * @brief Contains
     *
     * - Check if the std::array containes the element
     *
     * @param[in] a The std::array to check
     * @param[in] element The element to look for
     *
     * @return true if the std::array<T> containes the element
     */
    template<typename T, usize arr_size>
    [[nodiscard]] bool
    contains(const std::array<std::string, arr_size>& a, std::string_view element) noexcept
    {
        return (std::ranges::find(a.cbegin(), a.cend(), element) != a.cend());
    }

    /**
     * @brief Contains
     *
     * - Check if the std::array containes the element
     *
     * @param[in] a The std::array to check
     * @param[in] element The element to look for
     *
     * @return true if the std::array<T> containes the element
     */
    template<typename T, usize arr_size>
    [[nodiscard]] bool
    contains(const std::array<std::string_view, arr_size>& a, std::string_view element) noexcept
    {
        return (std::ranges::find(a.cbegin(), a.cend(), element) != a.cend());
    }

    /**
     * @brief Contains
     *
     * - Check if the std::array containes the element
     *
     * @param[in] a The std::array to check
     * @param[in] element The element to look for
     *
     * @return true if the std::array<T> containes the element
     */
    template<typename T, usize arr_size>
    [[nodiscard]] bool
    contains(const std::array<T, arr_size>& a, const T& element) noexcept
    {
        return (std::ranges::find(a.cbegin(), a.cend(), element) != a.cend());
    }
} // namespace ztd
