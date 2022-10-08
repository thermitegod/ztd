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

#include "string-python.hxx"

#include "types.hxx"

namespace ztd
{
    namespace
    {
        // std::literals::string_view_literals::operator""sv
        using namespace std::literals::string_view_literals;
    } // namespace

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
     * @brief Contains Any
     *
     * - Check if the string containes any of the substring string in vector
     *
     * @param[in] str The string to be searched
     * @param[in] subs The array of string to look for
     *
     * @return true if the string str containes any of the
     * substrings in subs
     */
    template<usize arr_size>
    static inline bool
    contains_any(std::string_view str, const std::array<std::string_view, arr_size>& subs) noexcept
    {
        if (subs.empty())
            return false;

        for (std::string_view sub: subs)
        {
            if (str.find(sub) != std::string_view::npos)
                return true;
        }
        return false;
    }

    /**
     * @brief Contains Any
     *
     * - Check if the string containes any of the substring string in vector
     *
     * @param[in] str The string to be searched
     * @param[in] subs The array of string to look for
     *
     * @return true if the string str containes any of the
     * substrings in subs
     */
    template<usize arr_size>
    static inline bool
    contains_any(std::string_view str, const std::array<std::string, arr_size>& subs) noexcept
    {
        if (subs.empty())
            return false;

        for (std::string_view sub: subs)
        {
            if (str.find(sub) != std::string_view::npos)
                return true;
        }
        return false;
    }

    /**
     * @brief Contains Any
     *
     * - Check if the string containes any of the substring string in vector
     *
     * @param[in] str The string to be searched
     * @param[in] subs The vector of string to look for
     *
     * @return true if the string str containes any of the
     * substrings in subs
     */
    static inline bool
    contains_any(std::string_view str, const std::vector<std::string_view>& subs) noexcept
    {
        if (subs.empty())
            return false;

        for (std::string_view sub: subs)
        {
            if (str.find(sub) != std::string_view::npos)
                return true;
        }
        return false;
    }

    /**
     * @brief Contains Any
     *
     * - Check if the string containes any of the substring string in vector
     *
     * @param[in] str The string to be searched
     * @param[in] subs The vector of string to look for
     *
     * @return true if the string str containes any of the
     * substrings in subs
     */
    static inline bool
    contains_any(std::string_view str, const std::vector<std::string>& subs) noexcept
    {
        if (subs.empty())
            return false;

        for (std::string_view sub: subs)
        {
            if (str.find(sub) != std::string_view::npos)
                return true;
        }
        return false;
    }

#ifdef ZTD_STRING_VIEW_SAME
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
#else
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
    same(const std::string& str1, const std::string& str2) noexcept
    {
        return (str1.compare(str2) == 0);
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
    same(const char* str1, const std::string& str2) noexcept
    {
        if (str1 == nullptr)
            return false;
        return (str2.compare(str1) == 0);
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
    same(const std::string& str1, const char* str2) noexcept
    {
        if (str2 == nullptr)
            return false;
        return (str1.compare(str2) == 0);
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
    same(const char* str1, const char* str2) noexcept
    {
        if (str1 == nullptr || str2 == nullptr)
            return false;
        return (std::strcmp(str1, str2) == 0);
    }
#endif

    /**
     * @brief Replace Multiple
     *
     * - Replaces all instances of multiple substrings with a new substring
     *
     * @param[in] str The string to be parsed for replacments
     * @param[in] arr_find The array of string to be found and replaced
     * @param[in] str_replace The string to replace with
     * @param[in] count If count is given, at most count replacements are
     * done for each element to be replaced. If count is not specified or -1, then there
     * is no limit on the number of replacements (all possible replacements are made).
     *
     * @return replaced string
     */
    template<usize arr_size>
    static inline const std::string
    replace_multiple(std::string_view str, const std::array<std::string, arr_size>& arr_find,
                     std::string_view str_replace, i32 count = -1) noexcept
    {
        if (arr_find.empty() || count == 0)
            return str.data();

        std::string rstr = str.data();
        for (std::string_view str_find: arr_find)
        {
            rstr = replace(rstr, str_find, str_replace, count);
        }
        return rstr;
    }

    /**
     * @brief Replace Multiple
     *
     * - Replaces all instances of multiple substrings with a new substring
     *
     * @param[in] str The string to be parsed for replacments
     * @param[in] arr_find The array of string to be found and replaced
     * @param[in] str_replace The string to replace with
     * @param[in] count If count is given, at most count replacements are
     * done for each element to be replaced. If count is not specified or -1, then there
     * is no limit on the number of replacements (all possible replacements are made).
     *
     * @return replaced string
     */
    template<usize arr_size>
    static inline const std::string
    replace_multiple(std::string_view str, const std::array<std::string_view, arr_size>& arr_find,
                     std::string_view str_replace, i32 count = -1) noexcept
    {
        if (arr_find.empty() || count == 0)
            return str.data();

        std::string rstr = str.data();
        for (std::string_view str_find: arr_find)
        {
            rstr = replace(rstr, str_find, str_replace, count);
        }
        return rstr;
    }

    /**
     * @brief Replace Multiple
     *
     * - Replaces all instances of multiple substrings with a new substring
     *
     * @param[in] str The string to be parsed for replacments
     * @param[in] vec_find The vector of string to be found and replaced
     * @param[in] str_replace The string to replace with
     * @param[in] count If count is given, at most count replacements are
     * done for each element to be replaced. If count is not specified or -1, then there
     * is no limit on the number of replacements (all possible replacements are made).
     *
     * @return replaced string
     */
    static inline const std::string
    replace_multiple(std::string_view str, const std::vector<std::string>& vec_find,
                     std::string_view str_replace, i32 count = -1) noexcept
    {
        if (vec_find.empty() || count == 0)
            return str.data();

        std::string rstr = str.data();
        for (std::string_view str_find: vec_find)
        {
            rstr = replace(rstr, str_find, str_replace, count);
        }
        return rstr;
    }

    /**
     * @brief Replace Multiple
     *
     * - Replaces all instances of multiple substrings with a new substring
     *
     * @param[in] str The string to be parsed for replacments
     * @param[in] vec_find The vector of string to be found and replaced
     * @param[in] str_replace The string to replace with
     * @param[in] count If count is given, at most count replacements are
     * done for each element to be replaced. If count is not specified or -1, then there
     * is no limit on the number of replacements (all possible replacements are made).
     *
     * @return replaced string
     */
    static inline const std::string
    replace_multiple(std::string_view str, const std::vector<std::string_view>& vec_find,
                     std::string_view str_replace, i32 count = -1) noexcept
    {
        if (vec_find.empty() || count == 0)
            return str.data();

        std::string rstr = str.data();
        for (std::string_view str_find: vec_find)
        {
            rstr = replace(rstr, str_find, str_replace, count);
        }
        return rstr;
    }
} // namespace ztd
