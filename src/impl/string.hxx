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

#include <cmath>

namespace ztd
{
    /**
     * @brief Split
     *
     * - Splits a std::string at a delimiter, and put substring into a vector.
     *
     * @param[in] __str The std::string to be split
     * @param[in] __delimiter The std::string to be used as a delimiter
     * for splitting
     *
     * @return A std::vector of std::string with the spit tokens and
     * without the delimiter, If delimiter is not found return an
     * empty vector
     */
    static inline std::vector<std::string>
    split(const std::string& __str, const std::string& __delimiter) noexcept
    {
        std::string split_string = __str;
        std::vector<std::string> result;
        while (split_string.size())
        {
            std::size_t index = split_string.find(__delimiter);
            if (index != std::string::npos)
            {
                std::string token = split_string.substr(0, index);
                if (!token.empty())
                    result.push_back(token);
                split_string = split_string.substr(index + __delimiter.size());
                if (split_string.size() == 0)
                    result.push_back(split_string);
            }
            else
            {
                result.push_back(split_string);
                split_string = "";
            }
        }
        return result;
    }

    /**
     * @brief Join
     *
     * - Join elements of a vector into a std::string with a delimiter
     * inserted between the elements
     *
     * @param[in] __tokens The std::vector to be joined
     * @param[in] __delimiter The std::string to be used as a delimiter
     *
     * @return std::string with all the elements and a delimiter
     */
    static inline const std::string
    join(const std::vector<std::string>& __tokens, const std::string& __delimiter) noexcept
    {
        std::string str;
        for (auto it = __tokens.begin(); it != __tokens.end(); ++it)
        {
            if (it != __tokens.begin())
                str.append(__delimiter);
            str.append(*it);
        }
        return str;
    }

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
        return str.substr(pos + __remove.size());
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
        return str.substr(0, pos);
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

    /**
     * Python esque string functions
     */

    /**
     * @brief capitalize
     *
     * - Capitalize the first character in an string
     *
     * @param[in] __str The string to be capitalized
     *
     * @return a std::string with the first letter capitalized
     */
    static inline const std::string
    capitalize(const std::string& __str) noexcept
    {
        if (__str.empty())
            return __str;

        std::string cap = __str;
        cap[0] = std::toupper(cap[0]);
        return cap;
    }

    /**
     * @brief center
     *
     * - Padding is done using the specified fillchar (default is an ASCII space).
     * The original string is returned if width is less than or equal to
     *
     * @param[in] __str The string to be centered
     * @param[in] __width width to center the string in
     * @param[in] __fillchar The char to center the string with
     *
     * @return string centered in a string of length width
     */
    static inline const std::string
    center(const std::string& __str, unsigned int __width, char __fillchar = ' ') noexcept
    {
        if (__str.size() >= __width)
            return __str;

        unsigned int width = __width - __str.size();

        unsigned int offset_r = 0;
        if (width % 2 != 0)
            offset_r = 1;

        unsigned int pad_l = std::floor(width / 2);
        unsigned int pad_r = std::floor(width / 2) + offset_r;

        std::string str;
        str.append(pad_l, __fillchar);
        str.append(__str);
        str.append(pad_r, __fillchar);

        return str;
    }

    /**
     * @brief count
     *
     * - Count occurrences of substring in string
     *
     * @param[in] __str The string to be searched
     * @param[in] __find substring to count
     * @param[in] __start position to start looking
     * @param[in] __end position to stop looking
     *
     * @return the number of non-overlapping occurrences of substring in the range
     */
    static inline std::uint64_t
    count(const std::string& __str, const std::string& __find, std::size_t __start = 0,
          std::size_t __end = std::string::npos) noexcept
    {
        std::uint64_t count = 0;

        if (__str.empty())
            return count;

        std::size_t start_pos = __str.find(__find);
        if (start_pos == std::string::npos)
            return count;

        const std::string search_string = __str.substr(__start, __end - __start);

        while ((start_pos = search_string.find(__find, start_pos)) != std::string::npos)
        {
            start_pos += __find.size();
            count += 1;
        }
        return count;
    }

    /**
     * @brief endswith
     *
     * - Check if the string ends with this suffix
     *
     * @param[in] __str The string to be searched
     * @param[in] __suffix suffix to look for
     * @param[in] __start position to start looking
     * @param[in] __end position to stop looking
     *
     * @return true if the string ends with the specified suffix, otherwise return false
     */
    static inline bool
    endswith(const std::string& __str, const std::string& __suffix, std::size_t __start = 0,
             std::size_t __end = std::string::npos) noexcept
    {
        std::size_t start_pos = __str.find(__suffix);
        if (start_pos == std::string::npos)
            return false;

        const std::string search_string = __str.substr(__start, __end - __start);
        return (search_string.compare(search_string.size() - __suffix.size(),
                                      __suffix.size(),
                                      __suffix) == 0);
    }

    /**
     * @brief startswith
     *
     * - Check if the string starts with this prefix
     *
     * @param[in] __str The string to be searched
     * @param[in] __prefix prefix to look for
     * @param[in] __start position to start looking
     * @param[in] __end position to stop looking
     *
     * @return true if the string starts with the specified prefix, otherwise return false
     */
    static inline bool
    startswith(const std::string& __str, const std::string& __prefix, std::size_t __start = 0,
               std::size_t __end = std::string::npos) noexcept
    {
        std::size_t start_pos = __str.find(__prefix);
        if (start_pos == std::string::npos)
            return false;

        const std::string search_string = __str.substr(__start, __end - __start);

        return (search_string.compare(0, __prefix.size(), __prefix) == 0);
    }

    /**
     * @brief expandtabs
     *
     * - Replace tab characters with spaces
     *
     * @param[in] __str The string to be searched
     * @param[in] __tabsize spaces to use for each tab
     *
     * @return the string where all tab characters are replaced by one or more spaces.
     * currently does not have special handling for '\n' or '\r'
     */
    static inline const std::string
    expandtabs(const std::string& __str, unsigned int __tabsize = 8) noexcept
    {
        std::string expanded;

        auto columns = split(__str, "\t");

        // need to track columns to avoid adding
        // extra whitespace at the end of a line
        std::size_t columns_count = 1;

        for (const std::string& column: columns)
        {
            std::size_t tab_diff = 0;
            if (column.size() < __tabsize)
            {
                expanded.append(column);
                tab_diff = __tabsize - column.size();
                if (columns.size() != columns_count)
                    expanded.append(tab_diff, ' ');
            }
            else if (column.size() > __tabsize)
            {
                expanded.append(column);
                tab_diff = column.size() % __tabsize;
                if (columns.size() != columns_count)
                    expanded.append(tab_diff, ' ');
            }
            else if (column.size() == __tabsize)
            {
                expanded.append(column);
                if (columns.size() != columns_count)
                    expanded.append(__tabsize, ' ');
            }
            ++columns_count;
        }
        return expanded;
    }

    /**
     * @brief isalpha
     *
     * @param[in] __str The string to use
     *
     * @return True if all characters in the string are alphabetic
     * and there is at least one character, False otherwise
     */
    static inline bool
    isalpha(const std::string& __str) noexcept
    {
        if (__str.empty())
            return false;

        for (std::size_t i = 0; i < __str.size(); ++i)
        {
            if (!std::isalpha(__str[i]))
                return false;
        }
        return true;
    }

    /**
     * @brief isdigit
     *
     * @param[in] __str The string to use
     *
     * @return True if all characters in the string are digits
     * and there is at least one character, False otherwise
     */
    static inline bool
    isdigit(const std::string& __str) noexcept
    {
        if (__str.empty())
            return false;

        for (std::size_t i = 0; i < __str.size(); ++i)
        {
            if (!std::isdigit(__str[i]))
                return false;
        }
        return true;
    }

    /**
     * @brief islower
     *
     * @param[in] __str The string to use
     *
     * @return True if all cased characters in the string are
     * lowercase and there is at least one cased character,
     * False otherwise
     */
    static inline bool
    islower(const std::string& __str) noexcept
    {
        if (__str.empty())
            return false;

        for (std::size_t i = 0; i < __str.size(); ++i)
        {
            if (std::isalpha(__str[i]) && !std::islower(__str[i]))
                return false;
        }
        return true;
    }

    /**
     * @brief isupper
     *
     * @param[in] __str The string to use
     *
     * @return True if all cased characters in the string are
     * uppercase and there is at least one cased character,
     * False otherwise
     */
    static inline bool
    isupper(const std::string& __str) noexcept
    {
        if (__str.empty())
            return false;

        for (std::size_t i = 0; i < __str.size(); ++i)
        {
            if (std::isalpha(__str[i]) && !std::isupper(__str[i]))
                return false;
        }
        return true;
    }

    /**
     * @brief ljust
     *
     * - Left justify string
     *
     * @param[in] __str The string to use
     * @param[in] __width width to center the string in
     * @param[in] __fillchar The char to center the string with
     *
     * @return the string left justified in a string of length width.
     * The original string is returned if width is less than or equal
     * to string length
     */
    static inline const std::string
    ljust(const std::string& __str, std::size_t __width, char __fillchar = ' ') noexcept
    {
        if (__str.size() >= __width)
            return __str;

        unsigned int width = __width - __str.size();

        std::string str;
        str.append(__str);
        str.append(width, __fillchar);
        return str;
    }

    /**
     * @brief rjust
     *
     * - Right justify string
     *
     * @param[in] __str The string to use
     * @param[in] __width width to center the string in
     * @param[in] __fillchar The char to center the string with
     *
     * @return the string right justified in a string of length width.
     * The original string is returned if width is less than or equal
     * to string length
     */
    static inline const std::string
    rjust(const std::string& __str, std::size_t __width, char __fillchar = ' ') noexcept
    {
        if (__str.size() >= __width)
            return __str;

        unsigned int width = __width - __str.size();

        std::string str;
        str.append(width, __fillchar);
        str.append(__str);
        return str;
    }

    /**
     * @brief lstrip
     *
     * - Strip whitespace from the left end of the provided string
     *
     * @param[in] __str The string to trim
     * @param[in] __chars string of chars to be trimmed
     *
     * @return The modified string, or an empty string if the
     * original is all whitespace
     */
    static inline const std::string
    lstrip(const std::string& __str, const std::string& __chars = " \n\t") noexcept
    {
        std::size_t start_pos = __str.find_first_not_of(__chars);
        if (start_pos == std::string::npos)
            return "";
        return __str.substr(start_pos);
    }

    /**
     * @brief rstrip
     *
     * - Strip whitespace from the right end of the provided string
     *
     * @param[in] __str The string to trim
     * @param[in] __chars string of chars to be trimmed
     *
     * @return The modified string, or an empty string if the
     * original is all whitespace
     */
    static inline const std::string
    rstrip(const std::string& __str, const std::string& __chars = " \n\t") noexcept
    {
        std::size_t end_pos = __str.find_last_not_of(__chars);
        if (end_pos == std::string::npos)
            return "";
        return __str.substr(0, end_pos + 1);
    }

    /**
     * @brief strip
     *
     * - Strip whitespace from both ends of the provided string
     *
     * @param[in] __str The string to trim
     * @param[in] __chars string of chars to be trimmed
     *
     * @return The modified string, or an empty string if the
     * original is all whitespace
     */
    static inline const std::string
    strip(const std::string& __str, const std::string& __chars = " \n\t") noexcept
    {
        return lstrip(rstrip(__str, __chars), __chars);
    }

    /**
     * @brief removeprefix
     *
     * - Remove the prefix from the string
     *
     * @param[in] __str The string to be parsed for a given prefix
     * @param[in] __prefix The string prefix
     *
     * @return the string without the prefix
     */
    static inline const std::string
    removeprefix(const std::string& __str, const std::string& __prefix) noexcept
    {
        if (!startswith(__str, __prefix))
            return __str;
        return __str.substr(__prefix.size(), __str.size());
    }

    /**
     * @brief removesuffix
     *
     * - Remove the suffix from the string
     *
     * @param[in] __str The string to be parsed for a given suffix
     * @param[in] __suffix The string suffix
     *
     * @return the string without the suffix
     */
    static inline const std::string
    removesuffix(const std::string& __str, const std::string& __suffix) noexcept
    {
        if (!endswith(__str, __suffix))
            return __str;
        return __str.substr(0, __str.size() - __suffix.size());
    }

    /**
     * @brief partition
     *
     * - Split string at first instance of the delimiter
     *
     * @param[in] __str The string to be split
     * @param[in] __delimiter string to be split at
     *
     * @return std::array(begin, delimiter, end). If delimiter is not
     * found the original string will be put into 'begin'
     */
    static inline const std::array<std::string, 3>
    partition(const std::string& __str, const std::string& __delimiter) noexcept
    {
        std::size_t index = __str.find_first_of(__delimiter);
        if (index == std::string::npos)
            return {__str, "", ""};

        const std::string begin = __str.substr(0, index);
        const std::string end = __str.substr(index + __delimiter.size());

        return {begin, __delimiter, end};
    }

    /**
     * @brief rpartition
     *
     * - Split string at last instance of the delimiter
     *
     * @param[in] __str The string to be split
     * @param[in] __delimiter The string to be split at
     *
     * @return std::array(begin, delimiter, end). If delimiter is not
     * found the original string will be put into 'end'
     */
    static inline const std::array<std::string, 3>
    rpartition(const std::string& __str, const std::string& __delimiter) noexcept
    {
        std::size_t index = __str.find_last_of(__delimiter);
        if (index == std::string::npos)
            return {"", "", __str};

        const std::string begin = __str.substr(0, index);
        const std::string end = __str.substr(index + __delimiter.size());

        return {begin, __delimiter, end};
    }

    /**
     * @brief zfill
     *
     * - Zero filled signed string
     *
     * @param[in] __str The string to use
     * @param[in] __width new string length
     *
     * @return A copy of the string left filled with
     * ASCII '0' digits to make a string of length width.
     * - A leading sign prefix ('+'/'-') is handled by inserting
     * the padding after the sign character rather than before.
     * The original string is returned if width is less than or equal to
     * string length.
     */
    static inline const std::string
    zfill(const std::string& __str, std::size_t __width) noexcept
    {
        if (__str.size() >= __width)
            return __str;

        unsigned int width = __width - __str.size();

        std::string str;
        if (__str[0] == '+')
        {
            str.append("+");
            str.append(width, '0');
            str.append(__str, 1);
        }
        else if (__str[0] == '-')
        {
            str.append("-");
            str.append(width, '0');
            str.append(__str, 1);
        }
        else
        {
            str.append(width, '0');
            str.append(__str);
        }

        return str;
    }

    /**
     * deprecated function names
     */

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
    static inline auto& remove_prefix = removeprefix;

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
    static inline auto& remove_suffix = removesuffix;
} // namespace ztd
