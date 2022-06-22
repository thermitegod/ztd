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

#include <algorithm>

#include <string>
#include <string_view>

#include <cstring>

#include <array>
#include <vector>

#include <utility>

#include <cmath>

#include "../string-utils.hxx"

namespace ztd
{
    /**
     * @brief Left Trim
     *
     * - Trims whitespace from the left end of the provided std::string
     *
     * @param[in] str The std::string to trim
     *
     * @return The modified std::string, or an empty std::string if the
     * original is all whitespace
     */
    [[deprecated("Replace with ztd::lstrip()")]] static inline const std::string
    ltrim(std::string_view str) noexcept
    {
        std::size_t start_pos = str.find_first_not_of(" \n\t");
        if (start_pos == std::string_view::npos)
            return std::string("");
        return std::string(str.substr(start_pos));
    }

    /**
     * @brief Right Trim
     *
     * - Trims whitespace from the right end of the provided std::string
     *
     * @param[in] str The std::string to trim
     *
     * @return The modified std::string, or an empty std::string if the
     * original is all whitespace
     */
    [[deprecated("Replace with ztd::rstrip()")]] static inline const std::string
    rtrim(std::string_view str) noexcept
    {
        std::size_t end_pos = str.find_last_not_of(" \n\t");
        if (end_pos == std::string_view::npos)
            return std::string("");
        return std::string(str.substr(0, end_pos + 1));
    }

    /**
     * @brief Trim
     *
     * - Trims whitespace from both ends of the provided std::string
     *
     * @param[in] str The std::string to trim
     *
     * @return The modified std::string, or an empty std::string if the
     * original is all whitespace
     */
    [[deprecated("Replace with ztd::strip()")]] static inline const std::string
    trim(std::string_view str) noexcept
    {
        return ltrim(rtrim(str));
    }

    /**
     * @brief Prefix
     *
     * - Check if the std::string starts with this prefix
     *
     * @param[in] str The std::string to be parsed for a given prefix
     * @param[in] prefix The std::string prefix
     *
     * @return true if the std::string has the given prefix
     */
    [[deprecated("Replace with ztd::startswith()")]] static inline bool
    prefix(std::string_view str, std::string_view prefix) noexcept
    {
        if (str.size() >= prefix.size())
            return (str.compare(0, prefix.size(), prefix) == 0);
        return false;
    }

    /**
     * @brief Suffix
     *
     * - Check if the std::string ends with this suffix
     *
     * @param[in] str The std::string to be parsed for a given suffix
     * @param[in] suffix The std::string suffix
     *
     * @return true if the std::string has the given suffix
     */
    [[deprecated("Replace with ztd::endswith()")]] static inline bool
    suffix(std::string_view str, std::string_view suffix) noexcept
    {
        if (str.size() >= suffix.size())
            return (str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0);
        return false;
    }

    /**
     * @brief ISame
     *
     * - Check if the string is the exact same as another string,
     * case insensitive
     *
     * @param[in] str1 The string to be compared
     * @param[in] str2 The other string to be compared
     *
     * @return true if both strings are the same
     */
    [[deprecated("Replace with ztd::same() and ztd::lower()")]] static inline bool
    isame(const std::string& str1, const std::string& str2) noexcept
    {
        return same(upper(str1), upper(str2));
    }

    /**
     * @brief ISame
     *
     * - Check if the string is the exact same as another string,
     * case insensitive
     *
     * @param[in] str1 The string to be compared
     * @param[in] str2 The other string to be compared
     *
     * @return true if both strings are the same
     */
    [[deprecated("Replace with ztd::same() and ztd::lower()")]] static inline bool
    isame(const std::string& str1, const char* str2) noexcept
    {
        if (str2 == nullptr)
            return false;
        return same(upper(str1), upper(str2));
    }

    /**
     * @brief ISame
     *
     * - Check if the string is the exact same as another string,
     * case insensitive
     *
     * @param[in] str1 The string to be compared
     * @param[in] str2 The other string to be compared
     *
     * @return true if both strings are the same
     */
    [[deprecated("Replace with ztd::same() and ztd::lower()")]] static inline bool
    isame(const char* str1, const std::string& str2) noexcept
    {
        if (str1 == nullptr)
            return false;
        return same(upper(str1), upper(str2));
    }

    /**
     * @brief ISame
     *
     * - Check if the string is the exact same as another string,
     * case insensitive
     *
     * @param[in] str1 The string to be compared
     * @param[in] str2 The other string to be compared
     *
     * @return true if both strings are the same
     */
    [[deprecated("Replace with ztd::same() and ztd::lower()")]] static inline bool
    isame(const char* str1, const char* str2) noexcept
    {
        if (str1 == nullptr || str2 == nullptr)
            return false;
        return same(upper(str1), upper(str2));
    }

    /**
     * @brief Remove Before
     *
     * - Remove everything before the last instance of a substring, inclusive.
     *
     * @param[in] str The std::string to be operated on
     * @param[in] remove the substring and everything before it to remove
     *
     * @return New string without the unwanted substring, or the original
     * string if substring is not in the string
     */
    [[deprecated("Replace with ztd::rpartition()[2]")]] static inline const std::string
    remove_before(const std::string& str, const std::string& remove) noexcept
    {
        if (!contains(str, remove))
            return str;
        std::size_t pos = str.rfind(remove);
        return str.substr(pos + remove.size());
    }

    /**
     * @brief Remove After
     *
     * - Remove everything after the first instance of a substring, inclusive.
     *
     * @param[in] str The string to be operated on
     * @param[in] remove the substring and everything after it to remove
     *
     * @return New string without the unwanted substring, or the original
     * string if substring is not in the string
     */
    [[deprecated("Replace with ztd::partition()[0]")]] static inline const std::string
    remove_after(const std::string& str, const std::string& remove) noexcept
    {
        if (!contains(str, remove))
            return str;
        std::size_t pos = str.find(remove);
        return str.substr(0, pos);
    }
} // namespace ztd
