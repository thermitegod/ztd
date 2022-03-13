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

#include <string>

namespace ztd
{
    /**
     * @brief Clear
     *
     * - Checks if std::string is not empty and clear it
     *
     * @param[out] __str The std::string to clear
     */
    static inline void
    clear(std::string& __str) noexcept
    {
        if (__str.empty())
            return;
        __str.clear();
    }

    /**
     * @brief Empty
     *
     * - Checks if std::string is not empty, same as 'str.empty()'
     *
     * @param[out] __str The std::string to check
     *
     * @return true if the std::string is empty
     */
    static inline bool
    empty(std::string& __str) noexcept
    {
        if (__str.empty())
            return true;
        return false;
    }

    /**
     * @brief Not Empty
     *
     * - Checks if std::string is not empty, same as '!str.empty()'
     *
     * @param[out] __str The std::string to check
     *
     * @return true if the std::string is not empty
     */
    static inline bool
    nempty(std::string& __str) noexcept
    {
        return !empty(__str);
    }

    /**
     * @brief Bool Check
     *
     * - replacment for using '!T.empty()'
     *
     * @param[out] __b Object to check
     *
     * @return True if object is not empty, false otherwise.
     */
    template<typename T>
    static inline bool
    b(T __b) noexcept
    {
        if (__b.empty())
            return false;
        return true;
    }
} // namespace ztd
