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

namespace ztd
{
    namespace
    {
        // std::literals::string_view_literals::operator""sv
        using namespace std::literals::string_view_literals;
    } // namespace

#ifdef ZTD_STRING_VIEW_CONTAINS
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
    contains(std::string_view str, std::string_view sub, std::size_t start = 0,
             std::size_t end = std::string::npos) noexcept
    {
        if (start >= end)
            return false;

        std::string_view ss{str.substr(start, end)};

        return (ss.find(sub) != std::string_view::npos);
    }
#else
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
#endif

#ifndef ZTD_DISABLE_DEPRECATED
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
    [[deprecated("Use ztd::contains() without char")]] static inline bool
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
    [[deprecated("Use ztd::contains() without char")]] static inline bool
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
#endif

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

#ifndef ZTD_DISABLE_DEPRECATED
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
        const std::size_t start_pos = str.find_first_not_of(" \n\t");
        if (start_pos == std::string_view::npos)
            return std::string(""sv);
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
        const std::size_t end_pos = str.find_last_not_of(" \n\t");
        if (end_pos == std::string_view::npos)
            return std::string(""sv);
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
        std::string_view s{str};
        if (s.find(remove) == std::string_view::npos)
            return str;
        const std::size_t pos = str.rfind(remove);
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
        std::string_view s{str};
        if (s.find(remove) == std::string_view::npos)
            return str;
        const std::size_t pos = str.find(remove);
        return str.substr(0, pos);
    }
#endif
} // namespace ztd
