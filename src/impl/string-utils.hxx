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

//#define ZTD_MAIN_HEADER
#include "string-python.hxx"
//#undef ZTD_MAIN_HEADER

namespace ztd
{
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
    contains(const std::string& str, const std::string& sub, std::size_t start = 0,
             std::size_t end = std::string::npos) noexcept
    {
        if (start >= end)
            return false;

        std::string_view s{str};
        std::string_view ss{s.substr(start, end)};

        return (ss.find(sub) != std::string_view::npos);
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
    contains(const std::string& str, const char* sub, std::size_t start = 0,
             std::size_t end = std::string::npos) noexcept
    {
        if (sub == nullptr)
            return false;

        if (start >= end)
            return false;

        std::string_view s{str};
        std::string_view ss{s.substr(start, end)};

        return (ss.find(sub) != std::string_view::npos);
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
    contains(const char* str, const std::string& sub, std::size_t start = 0,
             std::size_t end = std::string::npos) noexcept
    {
        if (str == nullptr)
            return false;

        if (start >= end)
            return false;

        std::string_view cs{str};
        std::string_view ss{cs.substr(start, end)};

        return (ss.find(sub) != std::string_view::npos);
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
    contains(const char* str, const char* sub, std::size_t start = 0,
             std::size_t end = std::string::npos) noexcept
    {
        if (str == nullptr || sub == nullptr)
            return false;

        if (start >= end)
            return false;

        std::string_view cs{str};
        std::string_view ss{cs.substr(start, end)};

        return (ss.find(sub) != std::string_view::npos);
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
    contains(const std::string& str, const char sub, std::size_t start = 0,
             std::size_t end = std::string::npos) noexcept
    {
        if (start >= end)
            return false;

        std::string_view s{str};
        std::string_view ss{s.substr(start, end)};

        return (ss.find(sub) != std::string_view::npos);
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
    contains(const char* str, const char sub, std::size_t start = 0,
             std::size_t end = std::string::npos) noexcept
    {
        if (str == nullptr)
            return false;

        if (start >= end)
            return false;

        std::string_view cs{str};
        std::string_view ss{cs.substr(start, end)};

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
    template<std::size_t arr_size>
    static inline bool
    contains_any(const std::string& str, const std::array<std::string, arr_size>& subs) noexcept
    {
        if (subs.empty())
            return false;

        for (const std::string& sub: subs)
        {
            std::string_view s{str};
            if (s.find(sub) != std::string_view::npos)
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
    contains_any(const std::string& str, const std::vector<std::string>& subs) noexcept
    {
        if (subs.empty())
            return false;

        for (const std::string& sub: subs)
        {
            std::string_view s{str};
            if (s.find(sub) != std::string_view::npos)
                return true;
        }
        return false;
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
    template<std::size_t arr_size>
    static inline const std::string
    replace_multiple(const std::string& str, const std::array<std::string, arr_size>& arr_find,
                     const std::string& str_replace, int count = -1) noexcept
    {
        if (arr_find.empty() || count == 0)
            return str;

        std::string rstr = str;
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
    replace_multiple(const std::string& str, const std::vector<std::string>& vec_find,
                     const std::string& str_replace, int count = -1) noexcept
    {
        if (vec_find.empty() || count == 0)
            return str;

        std::string rstr = str;
        for (std::string_view str_find: vec_find)
        {
            rstr = replace(rstr, str_find, str_replace, count);
        }
        return rstr;
    }
} // namespace ztd
