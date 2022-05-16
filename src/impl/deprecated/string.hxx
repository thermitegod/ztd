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

#ifndef ZTD_DEPRECATED_STRING_HEADER
#error "Only <ztd.hxx> can be included directly"
#endif

#pragma once

#include <algorithm>

#include <string>
#include <cstring>

#include <array>
#include <vector>

#include <utility>

#include <cmath>

namespace ztd
{
    /**
     * @brief Left Trim
     *
     * - Trims whitespace from the left end of the provided std::string
     *
     * @param[in] __str The std::string to trim
     *
     * @return The modified std::string, or an empty std::string if the
     * original is all whitespace
     */
    [[deprecated("Replace with ztd::lstrip()")]] static inline const std::string
    ltrim(const std::string& __str) noexcept
    {
        std::size_t start_pos = __str.find_first_not_of(" \n\t");
        if (start_pos == std::string::npos)
            return "";
        return __str.substr(start_pos);
    }

    /**
     * @brief Right Trim
     *
     * - Trims whitespace from the right end of the provided std::string
     *
     * @param[in] __str The std::string to trim
     *
     * @return The modified std::string, or an empty std::string if the
     * original is all whitespace
     */
    [[deprecated("Replace with ztd::rstrip()")]] static inline const std::string
    rtrim(const std::string& __str) noexcept
    {
        std::size_t end_pos = __str.find_last_not_of(" \n\t");
        if (end_pos == std::string::npos)
            return "";
        return __str.substr(0, end_pos + 1);
    }

    /**
     * @brief Trim
     *
     * - Trims whitespace from both ends of the provided std::string
     *
     * @param[in] __str The std::string to trim
     *
     * @return The modified std::string, or an empty std::string if the
     * original is all whitespace
     */
    [[deprecated("Replace with ztd::strip()")]] static inline const std::string
    trim(const std::string& __str) noexcept
    {
        return ltrim(rtrim(__str));
    }

    /**
     * @brief Prefix
     *
     * - Check if the std::string starts with this prefix
     *
     * @param[in] __str The std::string to be parsed for a given prefix
     * @param[in] __prefix The std::string prefix
     *
     * @return true if the std::string has the given prefix
     */
    [[deprecated("Replace with ztd::startswith()")]] static inline bool
    prefix(const std::string& __str, const std::string& __prefix) noexcept
    {
        if (__str.size() >= __prefix.size())
            return (__str.compare(0, __prefix.size(), __prefix) == 0);
        return false;
    }

    /**
     * @brief Suffix
     *
     * - Check if the std::string ends with this suffix
     *
     * @param[in] __str The std::string to be parsed for a given suffix
     * @param[in] __suffix The std::string suffix
     *
     * @return true if the std::string has the given suffix
     */
    [[deprecated("Replace with ztd::endswith()")]] static inline bool
    suffix(const std::string& __str, const std::string& __suffix) noexcept
    {
        if (__str.size() >= __suffix.size())
            return (__str.compare(__str.size() - __suffix.size(), __suffix.size(), __suffix) == 0);
        return false;
    }
} // namespace ztd
