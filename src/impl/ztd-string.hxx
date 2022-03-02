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
#include <vector>

#include <algorithm>

namespace ztd
{
    /**
     *
     * std::string
     *
     */

    /**
     * @brief Lower
     *
     * - Convert a std::string into a lowercase std::string
     *
     * @param[out] __str The std::string to be lowercased
     *
     * @return lowercase std::string
     */
    static inline std::string
    lower(const std::string& __str) noexcept
    {
        std::string lower = __str;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return lower;
    }

    /**
     * @brief Upper
     *
     * - Convert a std::string into a uppercase std::string
     *
     * @param[out] __str The std::string to be uppercased
     *
     * @return uppercase std::string
     */
    static inline std::string
    upper(const std::string& __str) noexcept
    {
        std::string upper = __str;
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        return upper;
    }

    /**
     * @brief Left Trim
     *
     * - Trims whitespace from the left end of the provided std::string
     *
     * @param[out] __str The std::string to trim
     *
     * @return The modified std::string, or an empty std::string if the
     * original is all whitespace
     */
    static inline std::string
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
     * @param[out] __str The std::string to trim
     *
     * @return The modified std::string, or an empty std::string if the
     * original is all whitespace
     */
    static inline std::string
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
     * @param[out] __str The std::string to trim
     *
     * @return The modified std::string, or an empty std::string if the
     * original is all whitespace
     */
    static inline std::string
    trim(const std::string& __str) noexcept
    {
        return ltrim(rtrim(__str));
    }

    /**
     * @brief Contains
     *
     * - Check if the std::string containes the substring std::string
     *
     * @param[out] __haystack The std::string to be searched
     * @param[out] __needle The std::string to look for
     *
     * @return true if the std::string haystack containes the
     * std::string substring needle
     */
    static inline bool
    contains(const std::string& __haystack, const std::string& __needle) noexcept
    {
        if (__haystack.find(__needle) != std::string::npos)
            return true;
        return false;
    }

    /**
     * @brief Contains
     *
     * - Check if the std::string containes the substring std::string
     *
     * @param[out] __haystack The std::string to be searched
     * @param[out] __needle The single char to look for
     *
     * @return true if the std::string haystack containes the
     * char substring needle
     */
    static inline bool
    contains(const std::string& __haystack, const char __needle) noexcept
    {
        return contains(__haystack, std::string(1, __needle));
    }

    /**
     * @brief Contains Any
     *
     * - Check if the std::string containes any of the substring std::string in std::vector
     *
     * @param[out] __haystack The std::string to be searched
     * @param[out] __needles The std::vector of std::string to look for
     *
     * @return true if the std::string haystack containes any of thethe
     * std::string substring in needles
     */
    static inline bool
    contains_any(const std::string& __haystack, const std::vector<std::string>& __needles) noexcept
    {
        if (__needles.empty())
            return false;

        for (const std::string& needle: __needles)
        {
            if (contains(__haystack, needle))
                return true;
        }
        return false;
    }

    /**
     * @brief Same
     *
     * - Check if the std::string is the exact same as another std::string
     *
     * @param[out] __str1 The std::string to be compared
     * @param[out] __str2 The other std::string to be compared
     *
     * @return true if both std::string are the same
     */
    static inline bool
    same(const std::string& __str1, const std::string& __str2) noexcept
    {
        if (__str1.compare(__str2) == 0)
            return true;
        return false;
    }

    /**
     * @brief Not Same
     *
     * - Check if the std::string is the not the same as another std::string,
     * equivalent to using "!ztd::same()"
     *
     * @param[out] __str1 The std::string to be compared
     * @param[out] __str2 The other std::string to be compared
     *
     * @return true if both std::string are not the same
     */
    static inline bool
    not_same(const std::string& __str1, const std::string& __str2) noexcept
    {
        return !same(__str1, __str2);
    }

    /**
     * @brief ISame
     *
     * - Check if the std::string is the exact same as another std::string,
     * case insensitive
     *
     * @param[out] __str1 The std::string to be compared
     * @param[out] __str2 The other std::string to be compared
     *
     * @return true if both std::string are the same
     */
    static inline bool
    isame(const std::string& __str1, const std::string& __str2) noexcept
    {
        return same(lower(__str1), lower(__str2));
    }

    /**
     * @brief Not ISame
     *
     * - Check if the std::string is the exact same as another std::string,
     * case insensitive
     *
     * @param[out] __str1 The std::string to be compared
     * @param[out] __str2 The other std::string to be compared
     *
     * @return true if both std::string are the same
     */
    static inline bool
    not_isame(const std::string& __str1, const std::string& __str2) noexcept
    {
        return !isame(__str1, __str2);
    }

    /**
     * @brief Prefix
     *
     * - Check if the std::string starts with this prefix
     *
     * @param[out] __str The std::string to be parsed for a given prefix
     * @param[out] __prefix The std::string prefix
     *
     * @return true if the std::string has the given prefix
     */
    static inline bool
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
     * @param[out] __str The std::string to be parsed for a given suffix
     * @param[out] __suffix The std::string suffix
     *
     * @return true if the std::string has the given suffix
     */
    static inline bool
    suffix(const std::string& __str, const std::string& __suffix) noexcept
    {
        if (__str.size() >= __suffix.size())
            return (__str.compare(__str.size() - __suffix.size(), __suffix.size(), __suffix) == 0);
        return false;
    }

    /**
     * @brief Remove Prefix
     *
     * - Remove the prefix from the std::string
     *
     * @param[out] __str The std::string to be parsed for a given prefix
     * @param[out] __prefix The std::string prefix
     *
     * @return New std::string without the prefix
     */
    static inline std::string
    remove_prefix(const std::string& __str, const std::string& __prefix) noexcept
    {
        if (!prefix(__str, __prefix))
            return __str;

        return trim(__str.substr(__prefix.size(), __str.size()));
    }

    /**
     * @brief Remove Suffix
     *
     * - Remove the suffix from the std::string
     *
     * @param[out] __str The std::string to be parsed for a given suffix
     * @param[out] __suffix The std::string suffix
     *
     * @return New std::string without the suffix
     */
    static inline std::string
    remove_suffix(const std::string& __str, const std::string& __suffix) noexcept
    {
        if (!suffix(__str, __suffix))
            return __str;

        return trim(__str.substr(0, __str.size() - __suffix.size()));
    }

    /**
     * @brief Remove Before
     *
     * - Remove everything before the last instance of a substring, inclusive.
     *
     * @param[out] __str The std::string to be operated on
     * @param[out] __remove the substring and everything before it to remove
     *
     * @return New std::string without the unwanted substring, or the original
     * string if substring is not in the std::string
     */
    static inline std::string
    remove_before(const std::string& __str, const std::string& __remove) noexcept
    {
        if (!contains(__str, __remove))
            return __str;
        std::string new_string = __str;
        std::size_t pos = new_string.rfind(__remove);
        return trim(new_string.substr(pos + __remove.size() + 1));
    }

    /**
     * @brief Remove After
     *
     * - Remove everything after the first instance of a substring, inclusive.
     *
     * @param[out] __str The std::string to be operated on
     * @param[out] __remove the substring and everything after it to remove
     *
     * @return New std::string without the unwanted substring, or the original
     * string if substring is not in the std::string
     */
    static inline std::string
    remove_after(const std::string& __str, const std::string& __remove) noexcept
    {
        if (!contains(__str, __remove))
            return __str;
        std::string new_string = __str;
        std::size_t pos = new_string.find(__remove);
        return trim(new_string.substr(0, pos - 1));
    }

    /**
     * @brief Replace
     *
     * - Replaces all instances of a given substring with a new substring
     *
     * @param[out] __str The std::string to be parsed for replacments
     * @param[out] __str_find The std::string to be found and replaced
     * @param[out] __str_replace The std::string to replace with
     *
     * @return The modified std::string
     */
    static inline std::string
    replace(const std::string& __str, const std::string& __str_find,
            const std::string& __str_replace) noexcept
    {
        if (__str.empty())
            return __str;

        std::string new_string = __str;

        std::size_t start_pos = new_string.find(__str_find);
        if (start_pos == std::string::npos)
            return new_string;

        while ((start_pos = new_string.find(__str_find, start_pos)) != std::string::npos)
        {
            new_string.replace(start_pos, __str_find.size(), __str_replace);
            // In case 'str_replace' is in 'str_find', i.e. replace 'bar' with 'foobar'
            start_pos += __str_replace.size();
        }
        return new_string;
    }

    /**
     * @brief Replace First
     *
     * - Replaces first instances of a given substring with a new substring
     *
     * @param[out] __str The std::string to be parsed for replacments
     * @param[out] __str_find The std::string to be found and replaced
     * @param[out] __str_replace The std::string to replace with
     *
     * @return The modified std::string
     */
    static inline std::string
    replace_first(const std::string& __str, const std::string& __str_find,
                  const std::string& __str_replace) noexcept
    {
        std::size_t start_pos = __str.find(__str_find);
        if (start_pos == std::string::npos)
            return __str;

        std::string new_string = __str;

        new_string.replace(start_pos, __str_find.size(), __str_replace);

        return new_string;
    }

    /**
     * @brief Replace Last
     *
     * - Replaces last instances of a given substring with a new substring
     *
     * @param[out] __str The std::string to be parsed for replacments
     * @param[out] __str_find The std::string to be found and replaced
     * @param[out] __str_replace The std::string to replace with
     *
     * @return The modified std::string
     */
    static inline std::string
    replace_last(const std::string& __str, const std::string& __str_find,
                 const std::string& __str_replace) noexcept
    {
        std::size_t start_pos = __str.rfind(__str_find);
        if (start_pos == std::string::npos)
            return __str;

        std::string new_string = __str;

        new_string.replace(start_pos, __str_find.size(), __str_replace);

        return new_string;
    }

    /**
     * @brief Replace Multiple
     *
     * - Replaces all instances of multiple substrings with a new substring
     *
     * @param[out] __str The std::string to be parsed for replacments
     * @param[out] __vec_find The std::vector of std::string to be found and replaced
     * @param[out] __str_replace The std::string to replace with
     *
     * @return The modified std::string
     */
    static inline std::string
    replace_multiple(const std::string& __str, const std::vector<std::string>& __vec_find,
                     const std::string& __str_replace) noexcept
    {
        if (__vec_find.empty())
            return __str;

        std::string new_string = __str;
        for (const std::string& str_find: __vec_find)
        {
            new_string = replace(new_string, str_find, __str_replace);
        }
        return new_string;
    }
} // namespace ztd
