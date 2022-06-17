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
     * @param[in] __str The string to be searched
     * @param[in] __sub Substring to look for
     * @param[in] __start Position to start looking
     * @param[in] __end Position to stop looking
     *
     * @return true if the string contains the supplied substring, otherwise false.
     */
    static inline bool
    contains(const std::string& __str, const std::string& __sub, std::size_t __start = 0,
             std::size_t __end = std::string::npos) noexcept
    {
        if (__start > __end)
            return false;

        const std::string search_string = __str.substr(__start, __end - __start);

        return (search_string.find(__sub) != std::string::npos);
    }

    /**
     * @brief Contains
     *
     * - Check if the string contains the supplied substring
     *
     * @param[in] __str The string to be searched
     * @param[in] __sub Substring to look for
     * @param[in] __start Position to start looking
     * @param[in] __end Position to stop looking
     *
     * @return true if the string contains the supplied substring, otherwise false.
     */
    static inline bool
    contains(const std::string& __str, const char* __sub, std::size_t __start = 0,
             std::size_t __end = std::string::npos) noexcept
    {
        if (__sub == nullptr)
            return false;

        if (__start > __end)
            return false;

        const std::string search_string = __str.substr(__start, __end - __start);

        return (search_string.find(__sub) != std::string::npos);
    }

    /**
     * @brief Contains
     *
     * - Check if the string contains the supplied substring
     *
     * @param[in] __str The string to be searched
     * @param[in] __sub Substring to look for
     * @param[in] __start Position to start looking
     * @param[in] __end Position to stop looking
     *
     * @return true if the string contains the supplied substring, otherwise false.
     */
    static inline bool
    contains(const char* __str, const std::string& __sub, std::size_t __start = 0,
             std::size_t __end = std::string::npos) noexcept
    {
        if (__str == nullptr)
            return false;

        if (__start > __end)
            return false;

        const std::string str = __str;
        const std::string search_string = str.substr(__start, __end - __start);

        return (search_string.find(__sub) != std::string::npos);
    }

    /**
     * @brief Contains
     *
     * - Check if the string contains the supplied substring
     *
     * @param[in] __str The string to be searched
     * @param[in] __sub Substring to look for
     * @param[in] __start Position to start looking
     * @param[in] __end Position to stop looking
     *
     * @return true if the string contains the supplied substring, otherwise false.
     */
    static inline bool
    contains(const char* __str, const char* __sub, std::size_t __start = 0,
             std::size_t __end = std::string::npos) noexcept
    {
        if (__str == nullptr || __sub == nullptr)
            return false;

        if (__start > __end)
            return false;

        const std::string str = __str;
        const std::string search_string = str.substr(__start, __end - __start);

        return (search_string.find(__sub) != std::string::npos);
    }

    /**
     * @brief Contains
     *
     * - Check if the string contains the supplied substring
     *
     * @param[in] __str The string to be searched
     * @param[in] __sub Substring to look for
     * @param[in] __start Position to start looking
     * @param[in] __end Position to stop looking
     *
     * @return true if the string contains the supplied substring, otherwise false.
     */
    static inline bool
    contains(const std::string& __str, const char __sub, std::size_t __start = 0,
             std::size_t __end = std::string::npos) noexcept
    {
        if (__start > __end)
            return false;

        const std::string search_string = __str.substr(__start, __end - __start);

        return (search_string.find(__sub) != std::string::npos);
    }

    /**
     * @brief Contains
     *
     * - Check if the string contains the supplied substring
     *
     * @param[in] __str The string to be searched
     * @param[in] __sub Substring to look for
     * @param[in] __start Position to start looking
     * @param[in] __end Position to stop looking
     *
     * @return true if the string contains the supplied substring, otherwise false.
     */
    static inline bool
    contains(const char* __str, const char __sub, std::size_t __start = 0,
             std::size_t __end = std::string::npos) noexcept
    {
        if (__str == nullptr)
            return false;

        if (__start > __end)
            return false;

        const std::string str = __str;
        const std::string search_string = str.substr(__start, __end);

        return (search_string.find(__sub) != std::string::npos);
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
        std::size_t pos = __str.rfind(__remove);
        return __str.substr(pos + __remove.size());
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
        std::size_t pos = __str.find(__remove);
        return __str.substr(0, pos);
    }

    /**
     * @brief Replace Multiple
     *
     * - Replaces all instances of multiple substrings with a new substring
     *
     * @param[in] __str The std::string to be parsed for replacments
     * @param[in] __arr_find The std::array of std::string to be found and replaced
     * @param[in] __str_replace The std::string to replace with
     * @param[in] __count If count is given, at most count replacements are
     * done for each element to be replaced. If count is not specified or -1, then there
     * is no limit on the number of replacements (all possible replacements are made).
     *
     * @return replaced string
     */
    template<std::size_t arr_size>
    static inline const std::string
    replace_multiple(const std::string& __str, const std::array<std::string, arr_size>& __arr_find,
                     const std::string& __str_replace, int __count = -1) noexcept
    {
        if (__arr_find.empty() || __count == 0)
            return __str;

        std::string str = __str;
        for (const std::string& str_find: __arr_find)
        {
            str = replace(str, str_find, __str_replace, __count);
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
     * @param[in] __count If count is given, at most count replacements are
     * done for each element to be replaced. If count is not specified or -1, then there
     * is no limit on the number of replacements (all possible replacements are made).
     *
     * @return replaced string
     */
    static inline const std::string
    replace_multiple(const std::string& __str, const std::vector<std::string>& __vec_find,
                     const std::string& __str_replace, int __count = -1) noexcept
    {
        if (__vec_find.empty() || __count == 0)
            return __str;

        std::string str = __str;
        for (const std::string& str_find: __vec_find)
        {
            str = replace(str, str_find, __str_replace, __count);
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
     * @param[in] __count If count is given, at most count replacements are
     * done for each element to be replaced. If count is not specified or -1, then there
     * is no limit on the number of replacements (all possible replacements are made).
     *
     * @return replaced string
     */
    static inline const std::string
    replace_multiple(const std::string& __str,
                     const std::vector<std::pair<std::string, std::string>>& __vec_find_repace,
                     int __count = -1) noexcept
    {
        if (__vec_find_repace.empty() || __count == 0)
            return __str;

        std::string str = __str;
        for (const auto& find_replace: __vec_find_repace)
        {
            str = replace(str, find_replace.first, find_replace.second, __count);
        }
        return str;
    }
} // namespace ztd
