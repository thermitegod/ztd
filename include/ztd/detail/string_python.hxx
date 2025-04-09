/**
 * Copyright (C) 2024 Brandon Zorn <brandonzorn@cock.li>
 *
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

#pragma once

#include <algorithm>
#include <array>
#include <format>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <cmath>

#include "types.hxx"

/**
 * https://docs.python.org/3/library/stdtypes.html#string-methods
 *
 * Implemented
 * ===========
 * capitalize    - Full
 * center        - Full
 * count         - Full
 * expandtabs    - Full
 * isalnum       - Full
 * isalpha       - Full
 * isascii       - Disabled
 *                 - llvm libc++ has a macro with the same name
 * isdecimal     - Full
 * isdigit       - Partial
 *                 - Only supports base10
 * islower       - Full
 * isnumeric     - Partial
 *                 - Only supports base10
 * isspace       - Full
 * istitle       - Full
 * isupper       - Full
 * join          - Full
 * ljust         - Full
 * lower         - Full
 * lstrip        - Full
 * partition     - Full
 *                 - Note, for empty 'sep', Python throws ValueError, We return {"str", "", ""}
 * removeprefix  - Full
 * removesuffix  - Full
 * replace       - Full
 *                 - WONTFIX, a empty 'str_find' does not cause 'str_replace' to be
 *                   inserted between every character in 'str', Just returns the
 *                   original string. Python Example below.
 *                      >>> a = ' z '
 *                      >>> a.replace('', 'a')
 *                      'a aza a'
 * rjust         - Full
 * rpartition    - Full
 *                 - Note, for empty 'sep', Python throws ValueError, We return {"", "", "str"}
 * rsplit        - Full
 * rstrip        - Full
 * split         - Full
 * splitlines    - Full
 * strip         - Full
 * swapcase      - Full
 * title         - Full
 * upper         - Full
 * zfill         - Full
 *
 * Not implemented
 * ===============
 * casefold      - Maybe
 * encode        - No
 * endswith      - No use std::string::ends_with
 * find          - No use std::string::find
 * format        - No use std::format
 * format_map    - No use std::format
 * index         - No use std::string::find
 * isidentifier  - No
 * isprintable   - No
 * maketrans     - No
 * rfind         - No use std::string::rfind
 * rindex        - No use std::string::rfind
 * startswith    - No use std::string::starts_with
 * translate     - No
 */

namespace ztd
{
/**
 * @brief split
 *
 * - Splits the string at occurrences of the delimiter, Except for splitting
 * from the left, split() behaves like rsplit().
 *
 * @param[in] str The string to be split
 * @param[in] sep If sep is given, consecutive delimiters
 * are not grouped together and are deemed to delimit empty strings
 * (for example, split("1,,2", ",") returns {"1", "", "2"}).
 * The sep argument may consist of multiple characters
 * (for example, split("1<>2<>3", "<>") returns {"1", "2", "3"}).
 * @param[in] maxsplit If maxsplit is given, at most maxsplit splits are
 * done (thus, the list will have at most maxsplit+1 elements). If maxsplit
 * is not specified or -1, then there is no limit on the number of
 * splits (all possible splits are made).
 *
 * @return A list of the words in the string, using sep as the delimiting string.
 */
[[nodiscard]] inline std::vector<std::string>
split(const std::string_view str, const std::string_view sep = "", const i32 maxsplit = -1) noexcept
{
    if (str.empty() || sep.empty() || maxsplit == 0)
    {
        return {std::string(str)};
    }

    std::vector<std::string> result;
    for (const auto&& token : str | std::views::split(sep))
    {
        result.emplace_back(token.cbegin(), token.cend());
        if (maxsplit > 0 && static_cast<i32>(result.size()) == maxsplit)
        {
            result.emplace_back(std::ranges::next(token.cend(), static_cast<i64>(sep.size())),
                                str.cend());
            break;
        }
    }
    return result;
}

/**
 * @brief rsplit
 *
 * - Splits the string at occurrences of the delimiter, Except for splitting
 * from the right, rsplit() behaves like split().
 *
 * @param[in] str The string to be split
 * @param[in] sep If sep is given, consecutive delimiters
 * are not grouped together and are deemed to delimit empty strings
 * (for example, split("1,,2", ",") returns {"1", "", "2"}).
 * The sep argument may consist of multiple characters
 * (for example, split("1<>2<>3", "<>") returns {"1", "2", "3"}).
 * @param[in] maxsplit If maxsplit is given, at most maxsplit splits are
 * done (thus, the list will have at most maxsplit+1 elements). If maxsplit
 * is not specified or -1, then there is no limit on the number of
 * splits (all possible splits are made).
 *
 * @return A list of the words in the string, using sep as the delimiting string.
 */
[[nodiscard]] inline std::vector<std::string>
rsplit(const std::string_view str, const std::string_view sep = "",
       const i32 maxsplit = -1) noexcept
{
    using namespace std::string_literals;

    if (str.empty() || sep.empty() || maxsplit == 0)
    {
        return {std::string(str)};
    }

    auto split = str | std::views::split(sep);

    i32 total_merges_needed = 0;
    if (maxsplit > 0)
    {
        total_merges_needed = static_cast<i32>(std::ranges::distance(split)) - maxsplit;
    }

    std::vector<std::string> result;
    for (const auto& [idx, token] : std::views::enumerate(split))
    {
        if (total_merges_needed >= idx + 1)
        {
            if (result.size() == 0)
            {
                result.push_back(""s);
            }
            result.front().append(token.cbegin(), token.cend());
            if (total_merges_needed > idx + 1)
            {
                result.front().append(sep);
            }
        }
        else
        {
            result.emplace_back(token.cbegin(), token.cend());
        }
    }
    return result;
}

/**
 * @brief join
 *
 * @param[in] span a span of strings to be joined together
 * @param[in] sep separator to be used between elements in the string
 *
 * @return A string which is the concatenation of the strings in vec, with sep
 * inserted between each element.
 */
[[nodiscard]] inline std::string
join(const std::span<const std::string> span, const std::string_view sep) noexcept
{
    using namespace std::string_literals;

    if (span.empty())
    {
        return ""s;
    }

    std::string result;
    for (std::string::size_type i = 0; i < span.size(); ++i)
    {
        result.append(span[i]);
        if (i < span.size() - 1)
        {
            result.append(sep);
        }
    }
    return result;
}

/**
 * @brief join
 *
 * @param[in] span a span of strings to be joined together
 * @param[in] sep separator to be used between elements in the string
 *
 * @return A string which is the concatenation of the strings in vec, with sep
 * inserted between each element.
 */
[[nodiscard]] inline std::string
join(const std::span<const std::string_view> span, const std::string_view sep) noexcept
{
    using namespace std::string_literals;

    if (span.empty())
    {
        return ""s;
    }

    std::string result;
    for (std::string_view::size_type i = 0; i < span.size(); ++i)
    {
        result.append(span[i]);
        if (i < span.size() - 1)
        {
            result.append(sep);
        }
    }
    return result;
}

/**
 * @brief lower
 *
 * @param[in] str The string to be lowercased
 *
 * @return A copy of the string with all the cased characters converted to lowercase.
 */
[[nodiscard]] inline std::string
lower(const std::string_view str) noexcept
{
    std::string result(str.size(), 0);
    std::ranges::transform(str,
                           result.begin(),
                           [](const auto& c)
                           { return static_cast<std::string::value_type>(std::tolower(c)); });
    return result;
}

/**
 * @brief upper
 *
 * @param[in] str The string to be uppercased
 *
 * @return A copy of the string with all the cased characters converted to uppercase.
 */
[[nodiscard]] inline std::string
upper(const std::string_view str) noexcept
{
    std::string result(str.size(), 0);
    std::ranges::transform(str,
                           result.begin(),
                           [](const auto& c)
                           { return static_cast<std::string::value_type>(std::toupper(c)); });
    return result;
}

[[nodiscard]] inline std::string
replace(const std::string_view str, const std::string_view str_find,
        const std::string_view str_replace, const i32 count = -1) noexcept
{
    if (str.empty() || str_find.empty() || count == 0)
    {
        return {str.cbegin(), str.cend()};
    }

    std::string result{str.cbegin(), str.cend()};
    usize pos = 0;
    i32 counter = 0;

    while ((pos = result.find(str_find, pos)) != std::string_view::npos)
    {
        result.replace(pos, str_find.size(), str_replace);
        // In case 'str_replace' is in 'str_find', i.e. replace 'bar' with 'foobar'
        pos += str_replace.size();

        if (++counter == count)
        {
            break;
        }
    }
    return result;
}

/**
 * @brief capitalize
 *
 * @param[in] str The string to be capitalized
 *
 * @return A copy of the string with its first character
 * capitalized and the rest lowercased.
 */
[[nodiscard]] inline std::string
capitalize(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return {str.cbegin(), str.cend()};
    }

    auto result = ztd::lower(str);
    if (std::isalpha(result[0]))
    {
        result[0] = static_cast<std::string::value_type>(std::toupper(result[0]));
    }
    return result;
}

/**
 * @brief center
 *
 * @param[in] str The string to be centered
 * @param[in] width width to center the string in
 * @param[in] fillchar The char to center the string with
 *
 * @return Centered in a string of length width. Padding is done using
 * the specified fillchar (default is an ASCII space). The original
 * string is returned if width is less than or equal to the strings
 * length.
 */
[[nodiscard]] inline std::string
center(const std::string_view str, const u32 width, const char fillchar = ' ') noexcept
{
    if (str.size() >= width)
    {
        return {str.cbegin(), str.cend()};
    }

    const auto size = width - str.size();
    const auto pad_l = size / 2;
    const auto pad_r = size - pad_l;

    std::string result;
    result.reserve(size);
    result.append(pad_l, fillchar);
    result.append(str);
    result.append(pad_r, fillchar);
    return result;
}

/**
 * @brief count
 *
 * @param[in] str The string to be searched
 * @param[in] find substring to count
 *
 * @return The number of non-overlapping occurrences of substring sub
 * in the string
 */
[[nodiscard]] inline u64
count(const std::string_view str, const std::string_view find) noexcept
{
    if (str.empty() || find.empty())
    {
        return 0;
    }

    std::uint64_t count = 0;
    std::size_t pos = 0;

    while ((pos = str.find(find, pos)) != std::string_view::npos)
    {
        ++count;
        pos += find.size();
    }
    return count;
}

/**
 * @brief count
 *
 * @param[in] str The string to be searched
 * @param[in] find substring to count
 *
 * @return The number of non-overlapping occurrences of substring sub
 * in the string
 */
[[nodiscard]] inline u64
count(const std::string_view str, const char find) noexcept
{
    if (str.empty())
    {
        return 0;
    }

    std::uint64_t count = 0;
    std::size_t pos = 0;

    while ((pos = str.find(find, pos)) != std::string_view::npos)
    {
        ++count;
        pos += 1;
    }
    return count;
}

/**
 * @brief count
 *
 * @param[in] str The string to be searched
 * @param[in] find substring to count
 * @param[in] start position to start looking
 * @param[in] end position to stop looking
 *
 * @return The number of non-overlapping occurrences of substring sub
 * in the range of 'start, end'.
 */
[[nodiscard]] inline u64
count(const std::string_view str, const std::string_view find, const usize start,
      const usize end = std::string_view::npos) noexcept
{
    if (start >= end)
    {
        return 0;
    }
    return count(str.substr(start, end - start), find);
}

/**
 * @brief count
 *
 * @param[in] str The string to be searched
 * @param[in] find substring to count
 * @param[in] start position to start looking
 * @param[in] end position to stop looking
 *
 * @return The number of non-overlapping occurrences of substring sub
 * in the range of 'start, end'.
 */
[[nodiscard]] inline u64
count(const std::string_view str, const char find, const usize start,
      const usize end = std::string_view::npos) noexcept
{
    if (start >= end)
    {
        return 0;
    }
    return count(str.substr(start, end - start), find);
}

/**
 * @brief expandtabs
 *
 * - Replace tab characters with spaces
 *
 * @param[in] str The string to be searched
 * @param[in] tabsize spaces to use for each tab
 *
 * @return Return a copy of the string where all tab characters are replaced
 * by one or more spaces, depending on the current column and the given tab size.
 * Tab positions occur every tabsize characters (default is 8, giving tab
 * positions at columns 0, 8, 16 and so on). To expand the string, the current
 * column is set to zero and the string is examined character by character. If
 * the character is a tab (\t), one or more space characters are inserted in the
 * result until the current column is equal to the next tab position. (The tab
 * character itself is not copied.) If the character is a newline (\n) or return (\r),
 * it is copied and the current column is reset to zero, this is currently
 * unimplemented. Any other character is copied unchanged and the current column
 * is incremented by one regardless of how the character is represented when printed.
 */
[[nodiscard]] inline std::string
expandtabs(const std::string_view str, const u32 tabsize = 8) noexcept
{
    std::string result;

    u32 current_column = 0;
    for (const auto& c : str)
    {
        if (c == '\t')
        {
            const auto spaces = tabsize - (current_column % tabsize);

            result.append(spaces, ' ');
            current_column += spaces;
        }
        else if (c == '\n' || c == '\r')
        {
            result.push_back(c);
            current_column = 0;
        }
        else
        {
            result.push_back(c);
            current_column++;
        }
    }

    return result;
}

/**
 * @brief isalnum
 *
 * @param[in] str The string to be checked
 *
 * @return True if all characters in the string are alphanumeric
 * and there is at least one character, otherwise flase.
 */
[[nodiscard]] inline bool
isalnum(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return false;
    }
    return std::ranges::all_of(str.cbegin(),
                               str.cend(),
                               [](const auto& c)
                               { return !(std::isalpha(c) == 0 && std::isdigit(c) == 0); });
}

/**
 * @brief isalpha
 *
 * @param[in] str The string to use
 *
 * @return True if all characters in the string are alphabetic and
 * there is at least one character, False otherwise.
 */
[[nodiscard]] inline bool
isalpha(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return false;
    }
    return std::ranges::all_of(str.cbegin(),
                               str.cend(),
                               [](const auto& c) { return !(std::isalpha(c) == 0); });
}

#if 0
/**
 * @brief isascii
 *
 * @param[in] str The string to use
 *
 * @return Return True if the string is empty or all characters in
 * the string are ASCII, False otherwise. ASCII characters have
 * code points in the range U+0000-U+007F.
 */
[[nodiscard]] inline bool
isascii(const std::string_view str) noexcept
{
    if (str.empty())
        return true;

    for (const auto& c : str)
    {
        // unsigned char ch = static_cast<int>(str.at(i));
        const u64 ch = static_cast<u64>(c);
        if (ch > 127)
            return false;
    }
    return true;
}
#endif

/**
 * @brief isdecimal
 *
 * @param[in] str The string to use
 *
 * @return True if all characters in the string are decimal characters
 * and there is at least one character, False otherwise. Decimal characters
 * are those that can be used to form numbers in base 10.
 */
[[nodiscard]] inline bool
isdecimal(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return false;
    }
    return std::ranges::all_of(str.cbegin(),
                               str.cend(),
                               [](const auto& c) { return !(std::isdigit(c) == 0); });
}

/**
 * @brief isdigit
 *
 * @param[in] str The string to use
 *
 * @return True if all characters in the string are digits
 * and there is at least one character, False otherwise.
 */
static inline const auto& isdigit = isdecimal;

/**
 * @brief islower
 *
 * @param[in] str The string to use
 *
 * @return True if all cased characters in the string are
 * lowercase and there is at least one cased character,
 * False otherwise.
 */
[[nodiscard]] inline bool
islower(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return false;
    }
    return std::ranges::all_of(str.cbegin(),
                               str.cend(),
                               [](const auto& c)
                               { return !(std::isalpha(c) != 0 && std::islower(c) == 0); });
}

/**
 * @brief isnumeric
 *
 * @param[in] str The string to use
 *
 * @return True if all characters in the string are digits
 * and there is at least one character, False otherwise.
 * Numeric characters include digit characters, and all
 * characters that have the Unicode numeric value property.
 */
static inline const auto& isnumeric = isdecimal;

/**
 * @brief isupper
 *
 * @param[in] str The string to use
 *
 * @return True if all cased characters in the string are
 * uppercase and there is at least one cased character,
 * False otherwise.
 */
[[nodiscard]] inline bool
isupper(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return false;
    }
    return std::ranges::all_of(str.cbegin(),
                               str.cend(),
                               [](const auto& c)
                               { return !(std::isalpha(c) != 0 && std::isupper(c) == 0); });
}

/**
 * @brief isspace
 *
 * @param[in] str The string to use
 *
 * @return True if there are only whitespace characters
 * in the string and there is at least one character,
 * False otherwise.
 */
[[nodiscard]] inline bool
isspace(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return false;
    }
    return std::ranges::all_of(str.cbegin(),
                               str.cend(),
                               [](const auto& c) { return !(std::isspace(c) == 0); });
}

/**
 * @brief istitle
 *
 * @param[in] str The string to use
 *
 * @return True if the string is a titlecased string and
 * there is at least one character, for example uppercase
 * characters may only follow uncased characters and lowercase
 * characters only cased ones. Return False otherwise.
 */
[[nodiscard]] inline bool
istitle(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return false;
    }

    bool word_start = true;
    bool inside_word = false;

    for (const auto& c : str)
    {
        if (std::isalpha(c) != 0)
        {
            inside_word = true;

            if (word_start)
            {
                if (std::isupper(c) == 0)
                {
                    return false;
                }
            }
            else
            {
                if (std::islower(c) == 0)
                {
                    return false;
                }
            }
        }
        else
        {
            inside_word = false;
        }

        word_start = !inside_word;
    }
    return true;
}

/**
 * @brief title
 *
 * @param[in] str The string to use
 *
 * @return A titlecased version of the string where words
 * start with an uppercase character and the remaining
 * characters are lowercase.
 */
[[nodiscard]] inline std::string
title(const std::string_view str) noexcept
{
    using namespace std::string_literals;

    if (str.empty())
    {
        return ""s;
    }

    bool word_start = true;
    bool inside_word = false;

    std::string result;
    result.reserve(str.size());
    for (const auto& c : str)
    {
        if (std::isalpha(c) != 0)
        {
            inside_word = true;

            if (word_start && std::isupper(c) == 0)
            {
                result += static_cast<std::string::value_type>(std::toupper(c));
            }
            else if (!word_start && std::islower(c) == 0)
            {
                result += static_cast<std::string::value_type>(std::tolower(c));
            }
            else
            {
                result += c;
            }
        }
        else
        {
            inside_word = false;
            result += c;
        }

        word_start = !inside_word;
    }
    return result;
}

/**
 * @brief swapcase
 *
 * @param[in] str The string to use
 *
 * @return the string with uppercase characters converted
 * to lowercase and vice versa. Note that it is not necessarily
 * true that swapcase(swapcase(s)) == s.
 */
[[nodiscard]] inline std::string
swapcase(const std::string_view str) noexcept
{
    using namespace std::string_literals;

    if (str.empty())
    {
        return ""s;
    }

    std::string result;
    result.reserve(str.size());
    for (const auto& c : str)
    {
        if (std::isalpha(c) != 0)
        {
            if (std::isupper(c) != 0)
            {
                result += static_cast<std::string::value_type>(std::tolower(c));
            }
            else if (std::islower(c) != 0)
            {
                result += static_cast<std::string::value_type>(std::toupper(c));
            }
            else
            {
                result += c;
            }
        }
        else
        {
            result += c;
        }
    }
    return result;
}

/**
 * @brief ljust
 *
 * @param[in] str The string to use
 * @param[in] width width to center the string in
 * @param[in] fillchar The char to center the string with
 *
 * @return the string left justified in a string of length width.
 * The original string is returned if width is less than or equal
 * to the strings length.
 */
[[nodiscard]] inline std::string
ljust(const std::string_view str, const usize width, const char fillchar = ' ') noexcept
{
    if (str.size() >= width)
    {
        return {str.cbegin(), str.cend()};
    }

    const auto w = width - str.size();

    std::string result;
    result.reserve(w);
    result.append(str);
    result.append(w, fillchar);
    return result;
}

/**
 * @brief rjust
 *
 * @param[in] str The string to use
 * @param[in] width width to center the string in
 * @param[in] fillchar The char to center the string with
 *
 * @return the string right justified in a string of length width.
 * The original string is returned if width is less than or equal
 * to the string length.
 */
[[nodiscard]] inline std::string
rjust(const std::string_view str, const usize width, const char fillchar = ' ') noexcept
{
    if (str.size() >= width)
    {
        return {str.cbegin(), str.cend()};
    }

    const auto w = width - str.size();

    std::string result;
    result.reserve(w);
    result.append(w, fillchar);
    result.append(str);
    return result;
}

/**
 * @brief lstrip
 *
 * @param[in] str The string to trim
 * @param[in] chars string of chars to be trimmed
 *
 * @return A copy of the string with leading characters removed. The
 * chars argument is a string specifying the set of characters to be
 * removed. If omitted, the chars argument defaults to removing whitespace.
 * The chars argument is not a prefix; rather, all combinations of its
 * values are stripped.
 */
[[nodiscard]] inline std::string
lstrip(const std::string_view str, const std::string_view chars = " \r\n\t") noexcept
{
    using namespace std::string_literals;

    const auto pos = str.find_first_not_of(chars);
    if (pos == std::string_view::npos)
    {
        return ""s;
    }
    return std::string(str.substr(pos));
}

/**
 * @brief rstrip
 *
 * @param[in] str The string to trim
 * @param[in] chars string of chars to be trimmed
 *
 * @return A copy of the string with trailing characters removed. The
 * chars argument is a string specifying the set of characters to be
 * removed. If omitted, the chars argument defaults to removing whitespace.
 * The chars argument is not a suffix; rather, all combinations of its
 * values are stripped.
 */
[[nodiscard]] inline std::string
rstrip(const std::string_view str, const std::string_view chars = " \r\n\t") noexcept
{
    using namespace std::string_literals;

    const auto pos = str.find_last_not_of(chars);
    if (pos == std::string_view::npos)
    {
        return ""s;
    }
    return std::string(str.substr(0, pos + 1));
}

/**
 * @brief strip
 *
 * @param[in] str The string to trim
 * @param[in] chars string of chars to be trimmed
 *
 * @return A copy of the string with the leading and trailing characters
 * removed. The chars argument is a string specifying the set of characters
 * to be removed. If omitted, the chars argument defaults to removing
 * whitespace. The chars argument is not a prefix or suffix; rather, all
 * combinations of its values are stripped.
 */
[[nodiscard]] inline std::string
strip(const std::string_view str, const std::string_view chars = " \r\n\t") noexcept
{
    using namespace std::string_literals;

    const auto start_pos = str.find_first_not_of(chars);
    if (start_pos == std::string_view::npos)
    {
        return ""s;
    }

    const auto end_pos = str.find_last_not_of(chars);
    return std::string(str.substr(start_pos, end_pos - start_pos + 1));
}

/**
 * @brief removeprefix
 *
 * @param[in] str The string to be parsed for a given prefix
 * @param[in] prefix The string prefix
 *
 * @return If the string starts with the prefix string, return
 * the string without the prefix. Otherwise, return a copy of the
 * original string.
 */
[[nodiscard]] inline std::string
removeprefix(const std::string_view str, const std::string_view prefix) noexcept
{
    if (!str.starts_with(prefix))
    {
        return {str.cbegin(), str.cend()};
    }
    return std::string(str.substr(prefix.size(), str.size() - prefix.size()));
}

/**
 * @brief removeprefix
 *
 * @param[in] str The string to be parsed for a given prefix
 * @param[in] prefix The string prefix
 *
 * @return If the string starts with the prefix string, return
 * the string without the prefix. Otherwise, return a copy of the
 * original string.
 */
[[nodiscard]] inline std::string
removeprefix(const std::string_view str, const char prefix) noexcept
{
    if (!str.starts_with(prefix))
    {
        return {str.cbegin(), str.cend()};
    }
    return std::string(str.substr(1, str.size() - 1));
}

/**
 * @brief removesuffix
 *
 * @param[in] str The string to be parsed for a given suffix
 * @param[in] suffix The string suffix
 *
 * @return If the string ends with the suffix string, return
 * the string without the suffix. Otherwise, return a copy of the
 * original string.
 */
[[nodiscard]] inline std::string
removesuffix(const std::string_view str, const std::string_view suffix) noexcept
{
    if (!str.ends_with(suffix))
    {
        return {str.cbegin(), str.cend()};
    }
    return std::string(str.substr(0, str.size() - suffix.size()));
}

/**
 * @brief removesuffix
 *
 * @param[in] str The string to be parsed for a given suffix
 * @param[in] suffix The string suffix
 *
 * @return If the string ends with the suffix string, return
 * the string without the suffix. Otherwise, return a copy of the
 * original string.
 */
[[nodiscard]] inline std::string
removesuffix(const std::string_view str, const char suffix) noexcept
{
    if (!str.ends_with(suffix))
    {
        return {str.cbegin(), str.cend()};
    }
    return std::string(str.substr(0, str.size() - 1));
}

/**
 * @brief partition
 *
 * - Split the string at the first occurrence of sep
 *
 * @param[in] str The string to be split
 * @param[in] sep string to be split at
 *
 * @return A 3 element array containing the part before the separator,
 * the separator itself, and the part after the separator. If the
 * separator is not found, return a 3 element array containing the string
 * itself, followed by two empty strings.
 */
[[nodiscard]] inline std::array<std::string, 3>
partition(const std::string_view str, const std::string_view sep) noexcept
{
    using namespace std::string_literals;

    if (sep.empty())
    {
        return {std::string{str.cbegin(), str.cend()}, ""s, ""s};
    }

    const auto pos = str.find(sep);
    if (pos == std::string_view::npos)
    {
        return {std::string{str.cbegin(), str.cend()}, ""s, ""s};
    }

    return {std::string(str.substr(0, pos)),
            std::string(sep),
            std::string(str.substr(pos + sep.size()))};
}

/**
 * @brief partition
 *
 * - Split the string at the first occurrence of sep
 *
 * @param[in] str The string to be split
 * @param[in] sep string to be split at
 *
 * @return A 3 element array containing the part before the separator,
 * the separator itself, and the part after the separator. If the
 * separator is not found, return a 3 element array containing the string
 * itself, followed by two empty strings.
 */
[[nodiscard]] inline std::array<std::string, 3>
partition(const std::string_view str, const char sep) noexcept
{
    using namespace std::string_literals;

    const auto pos = str.find(sep);
    if (pos == std::string_view::npos)
    {
        return {std::string{str.cbegin(), str.cend()}, ""s, ""s};
    }

    return {std::string(str.substr(0, pos)),
            std::format("{}", sep),
            std::string(str.substr(pos + 1))};
}

/**
 * @brief rpartition
 *
 * - Split the string at the last occurrence of sep
 *
 * @param[in] str The string to be split
 * @param[in] sep The string to be split at
 *
 * @return A 3 element array containing the part before the separator,
 * the separator itself, and the part after the separator. If the
 * separator is not found, return a 3 element array containing
 * two empty strings, followed by the string itself.
 */
[[nodiscard]] inline std::array<std::string, 3>
rpartition(const std::string_view str, const std::string_view sep) noexcept
{
    using namespace std::string_literals;

    if (sep.empty())
    {
        return {""s, ""s, std::string{str.cbegin(), str.cend()}};
    }

    const auto pos = str.rfind(sep);
    if (pos == std::string_view::npos)
    {
        return {""s, ""s, std::string{str.cbegin(), str.cend()}};
    }

    return {std::string(str.substr(0, pos)),
            std::string(sep),
            std::string(str.substr(pos + sep.size()))};
}

/**
 * @brief rpartition
 *
 * - Split the string at the last occurrence of sep
 *
 * @param[in] str The string to be split
 * @param[in] sep The string to be split at
 *
 * @return A 3 element array containing the part before the separator,
 * the separator itself, and the part after the separator. If the
 * separator is not found, return a 3 element array containing
 * two empty strings, followed by the string itself.
 */
[[nodiscard]] inline std::array<std::string, 3>
rpartition(const std::string_view str, const char sep) noexcept
{
    using namespace std::string_literals;

    const auto pos = str.rfind(sep);
    if (pos == std::string_view::npos)
    {
        return {""s, ""s, std::string{str.cbegin(), str.cend()}};
    }

    return {std::string(str.substr(0, pos)),
            std::format("{}", sep),
            std::string(str.substr(pos + 1))};
}

/**
 * @brief splitlines
 *
 * - Split the string at line boundaries
 *
 * @param[in] str The string to be split
 * @param[in] keepends keep line boundaries
 *
 * @return Return a list of the lines in the string, breaking at
 * line boundaries. Line breaks are not included in the resulting
 * list unless keepends is given and true
 */
[[nodiscard]] inline std::vector<std::string>
splitlines(const std::string_view str, const bool keepends = false) noexcept
{
    if (str.empty())
    {
        return {};
    }

    auto utf8_next = [](const std::string_view str, usize& index) noexcept -> char32_t
    {
        char32_t codepoint = 0;
        const auto c = static_cast<char32_t>(str[index]);
        if (c < 0x80)
        { // 1-byte character
            codepoint = c;
            index += 1;
        }
        else if ((c >> 5) == 0x6)
        { // 2-byte character
            codepoint = static_cast<char32_t>((c & 0x1f) << 6);
            codepoint |= static_cast<char32_t>((str[index + 1] & 0x3f));
            index += 2;
        }
        else if ((c >> 4) == 0xe)
        { // 3-byte character
            codepoint = static_cast<char32_t>((c & 0xf) << 12);
            codepoint |= static_cast<char32_t>((str[index + 1] & 0x3f) << 6);
            codepoint |= static_cast<char32_t>((str[index + 2] & 0x3f));
            index += 3;
        }
        else if ((c >> 3) == 0x1e)
        { // 4-byte character
            codepoint = static_cast<char32_t>((c & 0x7) << 18);
            codepoint |= static_cast<char32_t>((str[index + 1] & 0x3f) << 12);
            codepoint |= static_cast<char32_t>((str[index + 2] & 0x3f) << 6);
            codepoint |= static_cast<char32_t>((str[index + 3] & 0x3f));
            index += 4;
        }
        return codepoint;
    };

    std::vector<std::string> result;

    bool is_crlf = false;
    std::string substr;
    usize index = 0;
    while (index < str.size())
    {
        const auto codepoint = utf8_next(str, index);

        switch (codepoint)
        {
            case 0x000d: // Carriage Return
            {
                // Special Case
                // Carriage Return + Line Feed
                auto i = index;
                if (i < str.size())
                {
                    const auto next_codepoint = utf8_next(str, i);
                    if (next_codepoint == '\n')
                    {
                        index = i;

                        is_crlf = true;
                    }
                }
            }
                [[fallthrough]];
            case 0x000a: // Line Feed
            case 0x000c: // Form Feed
            case 0x000b: // Vertical Tabulation
            case 0x001c: // File Separator
            case 0x001d: // Group Separator
            case 0x001e: // Record Separator
            case 0x0085: // Next Line (C1 Control Code)
            case 0x2028: // Line Separator
            case 0x2029: // Paragraph Separator
            {
                if (keepends)
                {
                    if (is_crlf)
                    {
                        substr += '\r';
                        substr += '\n';
                    }
                    else
                    {
                        substr += static_cast<std::string::value_type>(codepoint);
                    }
                }
                result.push_back(substr);
                substr.clear();
                break;
            }
            default:
                substr += static_cast<std::string::value_type>(codepoint);
                break;
        }
    }
    if (!substr.empty())
    {
        result.push_back(substr);
    }

    return result;
}

/**
 * @brief zfill
 *
 * @param[in] str The string to use
 * @param[in] width new string length
 *
 * @return A copy of the string left filled with
 * ASCII '0' digits to make a string of length width.
 * - A leading sign prefix ('+'/'-') is handled by inserting
 * the padding after the sign character rather than before.
 * The original string is returned if width is less than or equal to
 * string length.
 */
[[nodiscard]] inline std::string
zfill(const std::string_view str, const usize width) noexcept
{
    if (str.size() >= width)
    {
        return {str.cbegin(), str.cend()};
    }

    const auto w = width - str.size();

    std::string result;
    result.reserve(w);
    if (str.empty())
    {
        result.append(w, '0');
    }
    else
    {
        if (str.at(0) == '+')
        {
            result.append("+");
            result.append(w, '0');
            result.append(str, 1);
        }
        else if (str.at(0) == '-')
        {
            result.append("-");
            result.append(w, '0');
            result.append(str, 1);
        }
        else
        {
            result.append(w, '0');
            result.append(str);
        }
    }

    return result;
}
} // namespace ztd
