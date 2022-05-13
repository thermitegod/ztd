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
#include <cstring>

#include <array>
#include <vector>

#include <utility>

namespace ztd
{
    /**
     * @brief Lower
     *
     * - Convert a std::string into a lowercase std::string
     *
     * @param[in] __str The std::string to be lowercased
     *
     * @return lowercase std::string
     */
    static inline const std::string
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
     * @param[in] __str The std::string to be uppercased
     *
     * @return uppercase std::string
     */
    static inline const std::string
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
     * @param[in] __str The std::string to trim
     * @param[in] _trim_chars std::string of chars to be trimmed
     *
     * @return The modified std::string, or an empty std::string if the
     * original is all whitespace
     */
    static inline const std::string
    ltrim(const std::string& __str, const std::string& _trim_chars = " \n\t") noexcept
    {
        std::size_t start_pos = __str.find_first_not_of(_trim_chars);
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
     * @param[in] _trim_chars std::string of chars to be trimmed
     *
     * @return The modified std::string, or an empty std::string if the
     * original is all whitespace
     */
    static inline const std::string
    rtrim(const std::string& __str, const std::string& _trim_chars = " \n\t") noexcept
    {
        std::size_t end_pos = __str.find_last_not_of(_trim_chars);
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
     * @param[in] _trim_chars std::string of chars to be trimmed
     *
     * @return The modified std::string, or an empty std::string if the
     * original is all whitespace
     */
    static inline const std::string
    trim(const std::string& __str, const std::string& _trim_chars = " \n\t") noexcept
    {
        return ltrim(rtrim(__str, _trim_chars), _trim_chars);
    }

    /**
     * @brief Contains
     *
     * - Check if the std::string containes the substring std::string
     *
     * @param[in] __haystack The string to be searched
     * @param[in] __needle What to look for in __haystack
     *
     * @return true if the std::string haystack containes the
     * std::string substring needle
     */
    static inline bool
    contains(const std::string& __haystack, const std::string& __needle) noexcept
    {
        return (__haystack.find(__needle) != std::string::npos);
    }

    /**
     * @brief Contains
     *
     * - Check if the std::string containes the substring std::string
     *
     * @param[in] __haystack The string to be searched
     * @param[in] __needle What to look for in __haystack
     *
     * @return true if the std::string haystack containes the
     * std::string substring needle
     */
    static inline bool
    contains(const std::string& __haystack, const char* __needle) noexcept
    {
        if (__needle == nullptr)
            return false;
        return (__haystack.find(__needle) != std::string::npos);
    }

    /**
     * @brief Contains
     *
     * - Check if the std::string containes the substring std::string
     *
     * @param[in] __haystack The string to be searched
     * @param[in] __needle What to look for in __haystack
     *
     * @return true if the std::string haystack containes the
     * std::string substring needle
     */
    static inline bool
    contains(const char* __haystack, const std::string& __needle) noexcept
    {
        if (__haystack == nullptr)
            return false;
        std::string haystack = __haystack;
        return (haystack.find(__needle) != std::string::npos);
    }

    /**
     * @brief Contains
     *
     * - Check if the std::string containes the substring std::string
     *
     * @param[in] __haystack The string to be searched
     * @param[in] __needle What to look for in __haystack
     *
     * @return true if the std::string haystack containes the
     * std::string substring needle
     */
    static inline bool
    contains(const char* __haystack, const char* __needle) noexcept
    {
        if (__haystack == nullptr || __needle == nullptr)
            return false;
        std::string haystack = __haystack;
        return (haystack.find(__needle) != std::string::npos);
    }

    /**
     * @brief Contains
     *
     * - Check if the std::string containes the substring std::string
     *
     * @param[in] __haystack The string to be searched
     * @param[in] __needle What to look for in __haystack
     *
     * @return true if the std::string haystack containes the
     * char substring needle
     */
    static inline bool
    contains(const std::string& __haystack, const char __needle) noexcept
    {
        return (__haystack.find(__needle) != std::string::npos);
    }

    /**
     * @brief Contains
     *
     * - Check if the std::string containes the substring std::string
     *
     * @param[in] __haystack The string to be searched
     * @param[in] __needle What to look for in __haystack
     *
     * @return true if the std::string haystack containes the
     * char substring needle
     */
    static inline bool
    contains(const char* __haystack, const char __needle) noexcept
    {
        if (__haystack == nullptr)
            return false;
        std::string haystack = __haystack;
        return (haystack.find(__needle) != std::string::npos);
    }

    /**
     * @brief Contains Any
     *
     * - Check if the std::string containes any of the substring std::string in std::vector
     *
     * @param[in] __haystack The std::string to be searched
     * @param[in] __needles The std::array of std::string to look for
     *
     * @return true if the std::string haystack containes any of thethe
     * std::string substring in needles
     */
    template<std::size_t arr_size>
    static inline bool
    contains_any(const std::string& __haystack,
                 const std::array<std::string, arr_size>& __needles) noexcept
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
     * @brief Contains Any
     *
     * - Check if the std::string containes any of the substring std::string in std::vector
     *
     * @param[in] __haystack The std::string to be searched
     * @param[in] __needles The std::vector of std::string to look for
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
     * - Check if one string is the exact same as another string
     *
     * @param[in] __str1 The string to be compared
     * @param[in] __str2 The other string to be compared
     *
     * @return true if both strings are the same
     */
    static inline bool
    same(const std::string& __str1, const std::string& __str2) noexcept
    {
        return (__str1.compare(__str2) == 0);
    }

    /**
     * @brief Same
     *
     * - Check if one string is the exact same as another string
     *
     * @param[in] __str1 The string to be compared
     * @param[in] __str2 The other string to be compared
     *
     * @return true if both strings are the same
     */
    static inline bool
    same(const char* __str1, const std::string& __str2) noexcept
    {
        if (__str1 == nullptr)
            return false;
        return (__str2.compare(__str1) == 0);
    }

    /**
     * @brief Same
     *
     * - Check if one string is the exact same as another string
     *
     * @param[in] __str1 The string to be compared
     * @param[in] __str2 The other string to be compared
     *
     * @return true if both strings are the same
     */
    static inline bool
    same(const std::string& __str1, const char* __str2) noexcept
    {
        if (__str2 == nullptr)
            return false;
        return (__str1.compare(__str2) == 0);
    }

    /**
     * @brief Same
     *
     * - Check if one string is the exact same as another string
     *
     * @param[in] __str1 The string to be compared
     * @param[in] __str2 The other string to be compared
     *
     * @return true if both strings are the same
     */
    static inline bool
    same(const char* __str1, const char* __str2) noexcept
    {
        if (__str1 == nullptr || __str2 == nullptr)
            return false;
        return (std::strcmp(__str1, __str2) == 0);
    }

    /**
     * @brief ISame
     *
     * - Check if the string is the exact same as another string,
     * case insensitive
     *
     * @param[in] __str1 The string to be compared
     * @param[in] __str2 The other string to be compared
     *
     * @return true if both strings are the same
     */
    static inline bool
    isame(const std::string& __str1, const std::string& __str2) noexcept
    {
        return same(upper(__str1), upper(__str2));
    }

    /**
     * @brief ISame
     *
     * - Check if the string is the exact same as another string,
     * case insensitive
     *
     * @param[in] __str1 The string to be compared
     * @param[in] __str2 The other string to be compared
     *
     * @return true if both strings are the same
     */
    static inline bool
    isame(const std::string& __str1, const char* __str2) noexcept
    {
        if (__str2 == nullptr)
            return false;
        return same(upper(__str1), upper(__str2));
    }

    /**
     * @brief ISame
     *
     * - Check if the string is the exact same as another string,
     * case insensitive
     *
     * @param[in] __str1 The string to be compared
     * @param[in] __str2 The other string to be compared
     *
     * @return true if both strings are the same
     */
    static inline bool
    isame(const char* __str1, const std::string& __str2) noexcept
    {
        if (__str1 == nullptr)
            return false;
        return same(upper(__str1), upper(__str2));
    }

    /**
     * @brief ISame
     *
     * - Check if the string is the exact same as another string,
     * case insensitive
     *
     * @param[in] __str1 The string to be compared
     * @param[in] __str2 The other string to be compared
     *
     * @return true if both strings are the same
     */
    static inline bool
    isame(const char* __str1, const char* __str2) noexcept
    {
        if (__str1 == nullptr || __str2 == nullptr)
            return false;
        return same(upper(__str1), upper(__str2));
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
     * @param[in] __str The std::string to be parsed for a given suffix
     * @param[in] __suffix The std::string suffix
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
     * @param[in] __str The std::string to be parsed for a given prefix
     * @param[in] __prefix The std::string prefix
     *
     * @return New std::string without the prefix
     */
    static inline const std::string
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
     * @param[in] __str The std::string to be parsed for a given suffix
     * @param[in] __suffix The std::string suffix
     *
     * @return New std::string without the suffix
     */
    static inline const std::string
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
     * @param[in] __str The std::string to be operated on
     * @param[in] __remove the substring and everything before it to remove
     *
     * @return New std::string without the unwanted substring, or the original
     * string if substring is not in the std::string
     */
    static inline const std::string
    remove_before(const std::string& __str, const std::string& __remove) noexcept
    {
        if (!contains(__str, __remove))
            return __str;
        std::string str = __str;
        std::size_t pos = str.rfind(__remove);
        return trim(str.substr(pos + __remove.size()));
    }

    /**
     * @brief Remove After
     *
     * - Remove everything after the first instance of a substring, inclusive.
     *
     * @param[in] __str The std::string to be operated on
     * @param[in] __remove the substring and everything after it to remove
     *
     * @return New std::string without the unwanted substring, or the original
     * string if substring is not in the std::string
     */
    static inline const std::string
    remove_after(const std::string& __str, const std::string& __remove) noexcept
    {
        if (!contains(__str, __remove))
            return __str;
        std::string str = __str;
        std::size_t pos = str.find(__remove);
        return trim(str.substr(0, pos));
    }

    /**
     * @brief Replace
     *
     * - Replaces all instances of a given substring with a new substring
     *
     * @param[in] __str The std::string to be parsed for replacments
     * @param[in] __str_find The std::string to be found and replaced
     * @param[in] __str_replace The std::string to replace with
     *
     * @return The modified std::string
     */
    static inline const std::string
    replace(const std::string& __str, const std::string& __str_find,
            const std::string& __str_replace) noexcept
    {
        if (__str.empty())
            return __str;

        std::string str = __str;

        std::size_t start_pos = str.find(__str_find);
        if (start_pos == std::string::npos)
            return str;

        while ((start_pos = str.find(__str_find, start_pos)) != std::string::npos)
        {
            str.replace(start_pos, __str_find.size(), __str_replace);
            // In case 'str_replace' is in 'str_find', i.e. replace 'bar' with 'foobar'
            start_pos += __str_replace.size();
        }
        return str;
    }

    /**
     * @brief Replace First
     *
     * - Replaces first instances of a given substring with a new substring
     *
     * @param[in] __str The std::string to be parsed for replacments
     * @param[in] __str_find The std::string to be found and replaced
     * @param[in] __str_replace The std::string to replace with
     *
     * @return The modified std::string
     */
    static inline const std::string
    replace_first(const std::string& __str, const std::string& __str_find,
                  const std::string& __str_replace) noexcept
    {
        std::size_t start_pos = __str.find(__str_find);
        if (start_pos == std::string::npos)
            return __str;

        std::string str = __str;

        str.replace(start_pos, __str_find.size(), __str_replace);

        return str;
    }

    /**
     * @brief Replace Last
     *
     * - Replaces last instances of a given substring with a new substring
     *
     * @param[in] __str The std::string to be parsed for replacments
     * @param[in] __str_find The std::string to be found and replaced
     * @param[in] __str_replace The std::string to replace with
     *
     * @return The modified std::string
     */
    static inline const std::string
    replace_last(const std::string& __str, const std::string& __str_find,
                 const std::string& __str_replace) noexcept
    {
        std::size_t start_pos = __str.rfind(__str_find);
        if (start_pos == std::string::npos)
            return __str;

        std::string str = __str;

        str.replace(start_pos, __str_find.size(), __str_replace);

        return str;
    }

    /**
     * @brief Replace Multiple
     *
     * - Replaces all instances of multiple substrings with a new substring
     *
     * @param[in] __str The std::string to be parsed for replacments
     * @param[in] __arr_find The std::array of std::string to be found and replaced
     * @param[in] __str_replace The std::string to replace with
     *
     * @return The modified std::string
     */
    template<std::size_t arr_size>
    static inline const std::string
    replace_multiple(const std::string& __str, const std::array<std::string, arr_size>& __arr_find,
                     const std::string& __str_replace) noexcept
    {
        if (__arr_find.empty())
            return __str;

        std::string str = __str;
        for (const std::string& str_find: __arr_find)
        {
            str = replace(str, str_find, __str_replace);
        }
        return str;
    }

    /**
     * @brief Replace Multiple
     *
     * - Replaces all instances of multiple substrings with a new substring
     *
     * @param[in] __str The std::string to be parsed for replacments
     * @param[in] __vec_find The std::vector of std::string to be found and replaced
     * @param[in] __str_replace The std::string to replace with
     *
     * @return The modified std::string
     */
    static inline const std::string
    replace_multiple(const std::string& __str, const std::vector<std::string>& __vec_find,
                     const std::string& __str_replace) noexcept
    {
        if (__vec_find.empty())
            return __str;

        std::string str = __str;
        for (const std::string& str_find: __vec_find)
        {
            str = replace(str, str_find, __str_replace);
        }
        return str;
    }

    /**
     * @brief Replace Multiple
     *
     * - Replaces all instances of multiple substrings with a new substring
     *
     * @param[in] __str The std::string to be parsed for replacments
     * @param[in] __vec_find_repace The std::vector of std::pairs to be found and replaced,
     * first item in pair is find, second item in pair is replace.
     *
     * @return The modified std::string
     */
    static inline const std::string
    replace_multiple(
        const std::string& __str,
        const std::vector<std::pair<std::string, std::string>>& __vec_find_repace) noexcept
    {
        if (__vec_find_repace.empty())
            return __str;

        std::string str = __str;
        for (const auto& find_replace: __vec_find_repace)
        {
            str = replace(str, find_replace.first, find_replace.second);
        }
        return str;
    }
} // namespace ztd
