/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <string>
#include <vector>

#include <algorithm>

#include <stdlib.h>

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

    /**
     *
     * std::string to/from std::vector
     *
     */

    /**
     * @brief Split
     *
     * - Splits a std::string at a delimiter, and put substring into a vector.
     *
     * @param[out] __str The std::string to be split
     * @param[out] __delimiter The std::string to be used as a delimiter
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
                result.push_back(split_string.substr(0, index));
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
     * @param[out] __tokens The std::vector to be joined
     * @param[out] __delimiter The std::string to be used as a delimiter
     *
     * @return std::string with all the elements and a delimiter
     */
    static inline std::string
    join(const std::vector<std::string>& __tokens, const std::string& __delimiter) noexcept
    {
        std::ostringstream ss;
        for (auto it = __tokens.begin(); it != __tokens.end(); ++it)
        {
            if (it != __tokens.begin())
                ss << __delimiter;
            ss << *it;
        }
        std::string new_string = ss.str();
        return new_string;
    }

    /**
     *
     * Filesystem Paths
     *
     * Cannot use variadic functions when the args are std::string.
     * This is not the ideal solution, but it works.
     *
     */

    /**
     * @brief Remove double '//' from path
     *
     * @param[out] __path to clean
     *
     * @return modify in place the provided path
     */
    static inline void
    build_path_clean(std::string& __path) noexcept
    {
        while (contains(__path, "//"))
        {
            __path = replace(__path, "//", "/");
        }
    }

    /**
     * @brief Build Path
     *
     * - Build a filesystem path from std::string, overloads for up to 6 path segments
     *
     * @param[out] __p1...__p6 The std::string to build the path with
     *
     * @return a filesystem path
     */
    static inline std::string
    build_path(const std::string& __p1) noexcept
    {
        std::string path;

        path.append(__p1);

        build_path_clean(path);

        return path;
    }

    /**
     * @brief Build Path
     *
     * - Build a filesystem path from std::string, overloads for up to 6 path segments
     *
     * @param[out] __p1...__p6 The std::string to build the path with
     *
     * @return a filesystem path
     */
    static inline std::string
    build_path(const std::string& __p1, const std::string& __p2) noexcept
    {
        std::string path;

        path.append(__p1 + "/");
        path.append(__p2);

        build_path_clean(path);

        return path;
    }

    /**
     * @brief Build Path
     *
     * - Build a filesystem path from std::string, overloads for up to 6 path segments
     *
     * @param[out] __p1...__p6 The std::string to build the path with
     *
     * @return a filesystem path
     */
    static inline std::string
    build_path(const std::string& __p1, const std::string& __p2, const std::string& __p3) noexcept
    {
        std::string path;

        path.append(__p1 + "/");
        path.append(__p2 + "/");
        path.append(__p3);

        build_path_clean(path);

        return path;
    }

    /**
     * @brief Build Path
     *
     * - Build a filesystem path from std::string, overloads for up to 6 path segments
     *
     * @param[out] __p1...__p6 The std::string to build the path with
     *
     * @return a filesystem path
     */
    static inline std::string
    build_path(const std::string& __p1, const std::string& __p2, const std::string& __p3,
               const std::string& __p4) noexcept
    {
        std::string path;

        path.append(__p1 + "/");
        path.append(__p2 + "/");
        path.append(__p3 + "/");
        path.append(__p4);

        build_path_clean(path);

        return path;
    }

    /**
     * @brief Build Path
     *
     * - Build a filesystem path from std::string, overloads for up to 6 path segments
     *
     * @param[out] __p1...__p6 The std::string to build the path with
     *
     * @return a filesystem path
     */
    static inline std::string
    build_path(const std::string& __p1, const std::string& __p2, const std::string& __p3,
               const std::string& __p4, const std::string& __p5) noexcept
    {
        std::string path;

        path.append(__p1 + "/");
        path.append(__p2 + "/");
        path.append(__p3 + "/");
        path.append(__p4 + "/");
        path.append(__p5);

        build_path_clean(path);

        return path;
    }

    /**
     * @brief Build Path
     *
     * - Build a filesystem path from std::string, overloads for up to 6 path segments
     *
     * @param[out] __p1...__p6 The std::string to build the path with
     *
     * @return a filesystem path
     */
    static inline std::string
    build_path(const std::string& __p1, const std::string& __p2, const std::string& __p3,
               const std::string& __p4, const std::string& __p5, const std::string& __p6) noexcept
    {
        std::string path;

        path.append(__p1 + "/");
        path.append(__p2 + "/");
        path.append(__p3 + "/");
        path.append(__p4 + "/");
        path.append(__p5 + "/");
        path.append(__p6);

        build_path_clean(path);

        return path;
    }

    /**
     *
     * Lazy Functions
     *
     */

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

    /**
     *
     * C Interface
     *
     */

    /**
     * @brief Null Check
     *
     * - Checks if the char* is NULL and if it is return an empty std::string.
     * Setting a std::string to NULL is UB and, nobody likes segfaults
     *
     * @param[out] __str The char* to be checked for NULL
     *
     * @return an empty std::string if char* is NULL
     */
    static inline std::string
    null_check(const char* __str) noexcept
    {
        if (!__str)
            return "";

        return __str;
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[out] __str pointer to the null-terminated byte string to duplicate
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    static inline char*
    strdup(const char* __str) noexcept
    {
        if (!__str)
            return nullptr;
        return strndup(__str, std::strlen(__str));
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[out] __str std::string to convert into a char* string pointer
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    static inline char*
    strdup(const std::string& __str) noexcept
    {
        return strndup(__str.c_str(), __str.size());
    }

    /**
     * @brief strdup
     *
     * - Returns a pointer to a null-terminated byte string.
     *
     * @param[out] __str std::string pointer to convert into a char* string pointer
     *
     * @return A pointer to the newly allocated string.
     * New string must be freed by caller.
     */
    static inline char*
    strdup(const std::string* __str) noexcept
    {
        return strndup(__str->c_str(), __str->size());
    }

    /**
     *
     * std::vector<T>
     *
     */

    /**
     * @brief Move
     *
     * - Move vector element to new position
     *
     * @param[out] __v The std::vector to check
     * @param[out] __old_index The index being moved
     * @param[out] __new_index The index to move to
     */
    template<typename T>
    static inline void
    move(std::vector<T>& __v, std::size_t __old_index, std::size_t __new_index) noexcept
    {
        if (__old_index > __new_index)
            std::rotate(__v.rend() - __old_index - 1,
                        __v.rend() - __old_index,
                        __v.rend() - __new_index);
        else
            std::rotate(__v.begin() + __old_index,
                        __v.begin() + __old_index + 1,
                        __v.begin() + __new_index + 1);
    }

    /**
     * @brief Index
     *
     * - Get the index of an element in an std::vector,
     * throws std::out_of_range if not found
     *
     * @param[out] __v The std::vector to check
     * @param[out] __element The element to get the index of

     *
     * @return The index of the element
     */
    template<typename T>
    static inline std::size_t
    index(std::vector<T>& __v, T& __element)
    {
        std::size_t index;
        auto it = find(__v.begin(), __v.end(), __element);
        if (it != __v.end())
            index = it - __v.begin();
        else
            throw std::out_of_range("Item not in vector");
        return index;
    }

    /**
     * @brief Contains
     *
     * - Check if the std::vector containes the element
     *
     * @param[out] __v The std::vector to check
     * @param[out] __element The element to look for
     *
     * @return true if the std::vector containes the element
     */
    template<typename T>
    static inline bool
    contains(std::vector<T>& __v, T& __element) noexcept
    {
        if (std::find(__v.begin(), __v.end(), __element) != __v.end())
            return true;
        return false;
    }

    /**
     * @brief Remove
     *
     * - Remove element from an std::vector
     *
     * @param[out] __v The std::vector to check
     * @param[out] __element The element to remove
     *
     * @return true if the std::vector containes the element
     */
    template<typename T>
    static inline void
    remove(std::vector<T>& __v, T& __element) noexcept
    {
        if (contains(__v, __element))
            __v.erase(std::remove(__v.begin(), __v.end(), __element), __v.end());
    }

    /**
     * @brief Merge
     *
     * - Merge two std::vectors into a new std::vector,
     * duplicate elements are included only once.
     *
     * @param[out] __v1 std::vector
     * @param[out] __v2 std::vector
     *
     * @return new std::vector
     */
    template<typename T>
    static inline std::vector<T>
    merge(std::vector<T>& __v1, std::vector<T>& __v2) noexcept
    {
        std::vector<T> new_vec;
        for (T element: __v1)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        for (T element: __v2)
        {
            if (contains(new_vec, element))
                continue;
            new_vec.push_back(element);
        }
        return new_vec;
    }
} // namespace ztd
