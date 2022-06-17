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

#include <array>

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
    template<typename T, std::size_t arr_size>
    static inline bool
    contains(const std::array<T, arr_size>& a, const T& element) noexcept
    {
        return (std::find(a.begin(), a.end(), element) != a.end());
    }
} // namespace ztd
