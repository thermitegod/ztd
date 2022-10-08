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

#include <string_view>

#include "types.hxx"

namespace ztd
{
    /**
     *  @brief  Compare to a string.
     *
     *  Returns an integer < 0 if str2 is ordered before
     *  str1, 0 if their values are equivalent, or > 0 if this
     *  string is ordered after str1.
     *
     * @param[in] str1 The string to be compared
     * @param[in] str2 The other string to be compared
     *
     * @return Integer < 0, 0, or > 0.
     */
    static inline i32
    compare(std::string_view str1, std::string_view str2) noexcept
    {
        return str1.compare(str2);
    }

    /**
     * @brief Contains
     *
     * - Check if the string contains the supplied substring
     *
     * @param[in] str The string to be searched
     * @param[in] sub Substring to look for
     * @param[in] start Position to start looking
     * @param[in] end Position to stop looking
     *
     * @return true if the string contains the supplied substring, otherwise false.
     */
    static inline bool
    contains(std::string_view str, std::string_view sub, usize start = 0,
             usize end = std::string::npos) noexcept
    {
        if (start >= end)
            return false;

        const std::string_view ss{str.substr(start, end)};

        return (ss.find(sub) != std::string_view::npos);
    }

    /**
     * @brief Same
     *
     * - Check if one string is the exact same as another string
     *
     * @param[in] str1 The string to be compared
     * @param[in] str2 The other string to be compared
     *
     * @return true if both strings are the same
     */
    static inline bool
    same(std::string_view str1, std::string_view str2) noexcept
    {
        return (str1.compare(str2) == 0);
    }
} // namespace ztd
