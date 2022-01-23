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

#include <algorithm>

#include <string>
#include <sstream>

#include <vector>

#include <fmt/core.h>

#include "ztd.hxx"

static inline const std::string WHITESPACE = " \n\t";

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
 * @param[out] str The std::string to be lowercased
 *
 * @return lowercase std::string
 */
std::string
ztd::lower(const std::string& str)
{
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

/**
 * @brief Upper
 *
 * - Convert a std::string into a uppercase std::string
 *
 * @param[out] str The std::string to be uppercased
 *
 * @return uppercase std::string
 */
std::string
ztd::upper(const std::string& str)
{
    std::string upper = str;
    std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    return upper;
}

/**
 * @brief Contains
 *
 * - Check if the std::string containes the substring std::string
 *
 * @param[out] haystack The std::string to be searched
 * @param[out] needle The std::string to look for
 *
 * @return true if the std::string haystack containes the
 * std::string substring needle
 */
bool
ztd::contains(const std::string& haystack, const std::string& needle)
{
    if (haystack.find(needle) != std::string::npos)
        return true;
    return false;
}

/**
 * @brief Contains
 *
 * - Check if the std::string containes the substring std::string
 *
 * @param[out] haystack The std::string to be searched
 * @param[out] needle The single char to look for
 *
 * @return true if the std::string haystack containes the
 * char substring needle
 */
bool
ztd::contains(const std::string& haystack, const char needle)
{
    return contains(haystack, std::string(1, needle));
}

/**
 * @brief Contains Any
 *
 * - Check if the std::string containes any of the substring std::string in std::vector
 *
 * @param[out] haystack The std::string to be searched
 * @param[out] needles The std::vector of std::string to look for
 *
 * @return true if the std::string haystack containes any of thethe
 * std::string substring in needles
 */
bool
ztd::contains_any(const std::string& haystack, const std::vector<std::string>& needles)
{
    if (needles.empty())
        return false;

    for (std::string needle: needles)
    {
        if (contains(haystack, needle))
            return true;
    }
    return false;
}

/**
 * @brief Same
 *
 * - Check if the std::string is the exact same as another std::string
 *
 * @param[out] str1 The std::string to be compared
 * @param[out] str2 The other std::string to be compared
 *
 * @return true if both std::string are the same
 */
bool
ztd::same(const std::string& str1, const std::string& str2)
{
    if (str1.compare(str2) == 0)
        return true;
    return false;
}

/**
 * @brief Not Same
 *
 * - Check if the std::string is the not the same as another std::string,
 * equivalent to using "!ztd::same()"
 *
 * @param[out] str1 The std::string to be compared
 * @param[out] str2 The other std::string to be compared
 *
 * @return true if both std::string are not the same
 */
bool
ztd::not_same(const std::string& str1, const std::string& str2)
{
    return !same(str1, str2);
}

/**
 * @brief ISame
 *
 * - Check if the std::string is the exact same as another std::string,
 * case insensitive
 *
 * @param[out] str1 The std::string to be compared
 * @param[out] str2 The other std::string to be compared
 *
 * @return true if both std::string are the same
 */
bool
ztd::isame(const std::string& str1, const std::string& str2)
{
    return same(lower(str1), lower(str2));
}

/**
 * @brief Not ISame
 *
 * - Check if the std::string is the exact same as another std::string,
 * case insensitive
 *
 * @param[out] str1 The std::string to be compared
 * @param[out] str2 The other std::string to be compared
 *
 * @return true if both std::string are the same
 */
bool
ztd::not_isame(const std::string& str1, const std::string& str2)
{
    return !isame(str1, str2);
}

/**
 * @brief Prefix
 *
 * - Check if the std::string starts with this prefix
 *
 * @param[out] str The std::string to be parsed for a given prefix
 * @param[out] prefix The std::string prefix
 *
 * @return true if the std::string has the given prefix
 */
bool
ztd::prefix(const std::string& str, const std::string& prefix)
{
    if (str.length() >= prefix.length())
        return (str.compare(0, prefix.size(), prefix) == 0);
    return false;
}

/**
 * @brief Suffix
 *
 * - Check if the std::string ends with this suffix
 *
 * @param[out] str The std::string to be parsed for a given suffix
 * @param[out] suffix The std::string suffix
 *
 * @return true if the std::string has the given suffix
 */
bool
ztd::suffix(const std::string& str, const std::string& suffix)
{
    if (str.length() >= suffix.length())
        return (str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0);
    return false;
}

/**
 * @brief Replace
 *
 * - Replaces all instances of a given substring with a new substring
 *
 * @param[out] str The std::string to be parsed for replacments
 * @param[out] str_find The std::string to be found and replaced
 * @param[out] str_replace The std::string to replace with
 *
 * @return The modified std::string
 */
std::string
ztd::replace(const std::string& str, const std::string& str_find, const std::string& str_replace)
{
    if (str.empty())
        return str;

    std::string new_string = str;

    std::size_t start_pos = new_string.find(str_find);
    if (start_pos == std::string::npos)
        return new_string;

    while ((start_pos = new_string.find(str_find, start_pos)) != std::string::npos)
    {
        new_string.replace(start_pos, str_find.length(), str_replace);
        // In case 'str_replace' is in 'str_find', i.e. replace 'bar' with 'foobar'
        start_pos += str_replace.length();
    }
    return new_string;
}

/**
 * @brief Replace First
 *
 * - Replaces first instances of a given substring with a new substring
 *
 * @param[out] str The std::string to be parsed for replacments
 * @param[out] str_find The std::string to be found and replaced
 * @param[out] str_replace The std::string to replace with
 *
 * @return The modified std::string
 */
std::string
ztd::replace_first(const std::string& str, const std::string& str_find,
                   const std::string& str_replace)
{
    std::size_t start_pos = str.find(str_find);
    if (start_pos == std::string::npos)
        return str;

    std::string new_string = str;

    new_string.replace(start_pos, str_find.length(), str_replace);

    return new_string;
}

/**
 * @brief Replace Last
 *
 * - Replaces last instances of a given substring with a new substring
 *
 * @param[out] str The std::string to be parsed for replacments
 * @param[out] str_find The std::string to be found and replaced
 * @param[out] str_replace The std::string to replace with
 *
 * @return The modified std::string
 */
std::string
ztd::replace_last(const std::string& str, const std::string& str_find,
                  const std::string& str_replace)
{
    std::size_t start_pos = str.rfind(str_find);
    if (start_pos == std::string::npos)
        return str;

    std::string new_string = str;

    new_string.replace(start_pos, str_find.length(), str_replace);

    return new_string;
}

/**
 * @brief Replace Multiple
 *
 * - Replaces all instances of multiple substrings with a new substring
 *
 * @param[out] str The std::string to be parsed for replacments
 * @param[out] vec_find The std::vector of std::string to be found and replaced
 * @param[out] str_replace The std::string to replace with
 *
 * @return The modified std::string
 */
std::string
ztd::replace_multiple(const std::string& str, const std::vector<std::string>& vec_find,
                      const std::string& str_replace)
{
    if (vec_find.empty())
        return str;

    std::string new_string = str;
    for (std::string str_find: vec_find)
    {
        new_string = replace(new_string, str_find, str_replace);
    }
    return new_string;
}

/**
 * @brief Left Trim
 *
 * - Trims whitespace from the left end of the provided std::string
 *
 * @param[out] str The std::string to trim
 *
 * @return The modified std::string, or an empty std::string if the
 * original is all whitespace
 */
std::string
ztd::ltrim(const std::string& str)
{
    std::size_t start_pos = str.find_first_not_of(WHITESPACE);
    if (start_pos == std::string::npos)
        return "";
    return str.substr(start_pos);
}

/**
 * @brief Right Trim
 *
 * - Trims whitespace from the right end of the provided std::string
 *
 * @param[out] str The std::string to trim
 *
 * @return The modified std::string, or an empty std::string if the
 * original is all whitespace
 */
std::string
ztd::rtrim(const std::string& str)
{
    std::size_t end_pos = str.find_last_not_of(WHITESPACE);
    if (end_pos == std::string::npos)
        return "";
    return str.substr(0, end_pos + 1);
}

/**
 * @brief Trim
 *
 * - Trims whitespace from both ends of the provided std::string
 *
 * @param[out] str The std::string to trim
 *
 * @return The modified std::string, or an empty std::string if the
 * original is all whitespace
 */
std::string
ztd::trim(const std::string& str)
{
    return ltrim(rtrim(str));
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
 * @param[out] str The std::string to be split
 * @param[out] delimiter The std::string to be used as a delimiter
 * for splitting
 *
 * @return A std::vector of std::string with the spit tokens and
 * without the delimiter, If delimiter is not found return an
 * empty vector
 */
std::vector<std::string>
ztd::split(const std::string& str, const std::string& delimiter)
{
    std::size_t start_pos;
    std::size_t end_pos;
    std::size_t delimiter_len = delimiter.length();
    std::string token;
    std::vector<std::string> tokens;

    start_pos = str.find(delimiter);
    if (start_pos == std::string::npos)
    {
        tokens.push_back(str);
        return tokens;
    }

    while ((end_pos = str.find(delimiter, start_pos)) != std::string::npos)
    {
        token = str.substr(start_pos, end_pos - start_pos);
        start_pos = end_pos + delimiter_len;
        tokens.push_back(token);
    }

    tokens.push_back(str.substr(start_pos));
    return tokens;
}

/**
 * @brief Join
 *
 * - Join elements of a vector into a std::string with a delimiter
 * inserted between the elements
 *
 * @param[out] tokens The std::vector to be joined
 * @param[out] delimiter The std::string to be used as a delimiter
 *
 * @return std::string with all the elements and a delimiter
 */
std::string
ztd::join(const std::vector<std::string>& tokens, const std::string& delimiter)
{
    std::ostringstream new_string;
    for (auto it = tokens.begin(); it != tokens.end(); ++it)
    {
        if (it != tokens.begin())
            new_string << delimiter;
        new_string << *it;
    }
    return new_string.str();
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
 * @param[out] path to clean
 *
 * @return modify in place the provided path
 */
static inline void
_build_path_clean(std::string& path)
{
    while (ztd::contains(path, "//"))
    {
        path = ztd::replace(path, "//", "/");
    }
}

/**
 * @brief Build Path
 *
 * - Build a filesystem path from std::string, overloads for up to 6 path segments
 *
 * @param[out] p1...p6 The std::string to build the path with
 *
 * @return a filesystem path
 */
std::string
ztd::build_path(const std::string& p1)
{
    std::string path;

    path.append(p1);

    _build_path_clean(path);

    return path;
}

/**
 * @brief Build Path
 *
 * - Build a filesystem path from std::string, overloads for up to 6 path segments
 *
 * @param[out] p1...p6 The std::string to build the path with
 *
 * @return a filesystem path
 */
std::string
ztd::build_path(const std::string& p1, const std::string& p2)
{
    std::string path;

    path.append(p1 + "/");
    path.append(p2);

    _build_path_clean(path);

    return path;
}

/**
 * @brief Build Path
 *
 * - Build a filesystem path from std::string, overloads for up to 6 path segments
 *
 * @param[out] p1...p6 The std::string to build the path with
 *
 * @return a filesystem path
 */
std::string
ztd::build_path(const std::string& p1, const std::string& p2, const std::string& p3)
{
    std::string path;

    path.append(p1 + "/");
    path.append(p2 + "/");
    path.append(p3);

    _build_path_clean(path);

    return path;
}

/**
 * @brief Build Path
 *
 * - Build a filesystem path from std::string, overloads for up to 6 path segments
 *
 * @param[out] p1...p6 The std::string to build the path with
 *
 * @return a filesystem path
 */
std::string
ztd::build_path(const std::string& p1, const std::string& p2, const std::string& p3,
                const std::string& p4)
{
    std::string path;

    path.append(p1 + "/");
    path.append(p2 + "/");
    path.append(p3 + "/");
    path.append(p4);

    _build_path_clean(path);

    return path;
}

/**
 * @brief Build Path
 *
 * - Build a filesystem path from std::string, overloads for up to 6 path segments
 *
 * @param[out] p1...p6 The std::string to build the path with
 *
 * @return a filesystem path
 */
std::string
ztd::build_path(const std::string& p1, const std::string& p2, const std::string& p3,
                const std::string& p4, const std::string& p5)
{
    std::string path;

    path.append(p1 + "/");
    path.append(p2 + "/");
    path.append(p3 + "/");
    path.append(p4 + "/");
    path.append(p5);

    _build_path_clean(path);

    return path;
}

/**
 * @brief Build Path
 *
 * - Build a filesystem path from std::string, overloads for up to 6 path segments
 *
 * @param[out] p1...p6 The std::string to build the path with
 *
 * @return a filesystem path
 */
std::string
ztd::build_path(const std::string& p1, const std::string& p2, const std::string& p3,
                const std::string& p4, const std::string& p5, const std::string& p6)
{
    std::string path;

    path.append(p1 + "/");
    path.append(p2 + "/");
    path.append(p3 + "/");
    path.append(p4 + "/");
    path.append(p5 + "/");
    path.append(p6);

    _build_path_clean(path);

    return path;
}

/**
 *
 * Lazy
 *
 */

/**
 * @brief Not Empty
 *
 * - Checks if std::string is empty, same as '!str.empty()'
 *
 * @param[out] str The std::string to check
 */
bool
ztd::not_empty(const std::string& str)
{
    if (str.empty())
        return false;
    return true;
}

/**
 * @brief Clear
 *
 * - Checks if std::string is not empty and clear it
 *
 * @param[out] str The std::string to clear
 */
void
ztd::clear(std::string& str)
{
    if (str.empty())
        return;
    str.clear();
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
 * @param[out] str The char* to be checked for NULL
 *
 * @return an empty std::string if char* is NULL
 */
std::string
ztd::null_check(const char* str)
{
    if (!str)
        return "";

    return str;
}

/**
 * @brief Empty Null
 *
 * - Checks if the std::string is empty and return nullptr
 *
 * @param[out] str The char* to be checked for NULL
 *
 * @return an empty std::string if char* is NULL
 */
const char*
ztd::empty_null(const std::string& str)
{
    if (not_empty(str))
        return strdup(str.c_str());

    return nullptr;
}
