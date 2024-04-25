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

#include <string>
#include <string_view>

#include <format>

#include <ranges>
#include <algorithm>

#include <array>
#include <span>
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
 * endswith      - Full
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
 * splitlines    - Disabled
 *                 - Does not work
 * startswith    - Full
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
 * find          - No use std::string::find
 * format        - No use std::format
 * format_map    - No use std::format
 * index         - No use std::string::find
 * isidentifier  - No
 * isprintable   - No
 * maketrans     - No
 * rfind         - No use std::string::rfind
 * rindex        - No use std::string::rfind
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
[[nodiscard]] inline const std::vector<std::string>
split(const std::string_view str, const std::string_view sep = "", const i32 maxsplit = -1) noexcept
{
    if (str.empty() || sep.empty() || maxsplit == 0)
    {
        return {str.data()};
    }

    std::vector<std::string> result;
    for (const auto&& token : str | std::views::split(sep))
    {
#if defined(__cpp_lib_ranges_as_const)
        result.emplace_back(token.cbegin(), token.cend());
#else
        result.emplace_back(token.begin(), token.end());
#endif

        if ((i32)result.size() == maxsplit)
        {
#if defined(__cpp_lib_ranges_as_const)
            result.emplace_back(std::ranges::next(token.cend() + sep.size() - 1), str.cend());
#else
            result.emplace_back(std::ranges::next(token.end() + sep.size() - 1), str.end());
#endif
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
[[nodiscard]] inline const std::vector<std::string>
rsplit(const std::string_view str, const std::string_view sep = "", const i32 maxsplit = -1) noexcept
{
    using namespace std::literals::string_literals;

    if (str.empty() || sep.empty() || maxsplit == 0)
    {
        return {str.data()};
    }

    auto split = str | std::views::split(sep);

    i32 total_merges_needed = 0;
    if (maxsplit > 0)
    {
        total_merges_needed = (i32)std::ranges::distance(split) - maxsplit;
    }

    std::vector<std::string> result;
#if defined(__cpp_lib_ranges_enumerate)
    for (const auto& [idx, token] : std::views::enumerate(split))
#else
    usize idx = 0;
    for (const auto& token : split)
#endif
    {
        if (total_merges_needed >= idx + 1)
        {
            if (result.size() == 0)
            {
                result.push_back(""s);
            }
#if defined(__cpp_lib_ranges_as_const)
            result.front().append(token.cbegin(), token.cend());
#else
            result.front().append(token.begin(), token.end());
#endif
            if (total_merges_needed > idx + 1)
            {
                result.front().append(sep);
            }
        }
        else
        {
#if defined(__cpp_lib_ranges_as_const)
            result.emplace_back(token.cbegin(), token.cend());
#else
            result.emplace_back(token.begin(), token.end());
#endif
        }

#if !defined(__cpp_lib_ranges_enumerate)
        idx++;
#endif
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
[[nodiscard]] inline const std::string
join(const std::span<const std::string> span, const std::string_view sep) noexcept
{
    std::string str;
    for (const std::string_view part : span)
    {
        str = std::format("{}{}{}", str, part, sep);
    }
    return str.substr(0, str.size() - sep.size());
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
[[nodiscard]] inline const std::string
join(const std::span<const std::string_view> span, const std::string_view sep) noexcept
{
    std::string str;
    for (const std::string_view part : span)
    {
        str = std::format("{}{}{}", str, part, sep);
    }
    return str.substr(0, str.size() - sep.size());
}

/**
 * @brief lower
 *
 * @param[in] str The string to be lowercased
 *
 * @return A copy of the string with all the cased characters converted to lowercase.
 */
[[nodiscard]] inline const std::string
lower(const std::string_view str) noexcept
{
    std::string lower = str.data();
    std::ranges::transform(lower.cbegin(), lower.cend(), lower.begin(), ::tolower);
    return lower;
}

/**
 * @brief upper
 *
 * @param[in] str The string to be uppercased
 *
 * @return A copy of the string with all the cased characters converted to uppercase.
 */
[[nodiscard]] inline const std::string
upper(const std::string_view str) noexcept
{
    std::string upper = str.data();
    std::ranges::transform(upper.cbegin(), upper.cend(), upper.begin(), ::toupper);
    return upper;
}

/**
 * @brief replace
 *
 * @param[in] str The string to be parsed for replacements
 * @param[in] str_find The string to be found and replaced
 * @param[in] str_replace The string to replace with
 * @param[in] count If count is given, at most count replacements are
 * done. If count is not specified or -1, then there is no limit on the
 * number of replacements (all possible replacements are made).
 *
 * @return A copy of the string with all occurrences of substring old replaced by new.
 */
[[nodiscard]] inline const std::string
replace(const std::string_view str, const std::string_view str_find, const std::string_view str_replace,
        const i32 count = -1) noexcept
{
    if (str.empty() || str_find.empty() || count == 0)
    {
        return str.data();
    }

    auto start_pos = str.find(str_find);
    if (start_pos == std::string_view::npos)
    {
        return str.data();
    }

    i32 counter = 0;
    std::string rep = str.data();

    while ((start_pos = rep.find(str_find, start_pos)) != std::string_view::npos)
    {
        rep.replace(start_pos, str_find.size(), str_replace);
        // In case 'str_replace' is in 'str_find', i.e. replace 'bar' with 'foobar'
        start_pos += str_replace.size();

        counter += 1;
        if (counter == count)
        {
            break;
        }
    }
    return rep;
}

/**
 * @brief capitalize
 *
 * @param[in] str The string to be capitalized
 *
 * @return A copy of the string with its first character
 * capitalized and the rest lowercased.
 */
[[nodiscard]] inline const std::string
capitalize(const std::string_view str) noexcept
{
    if (str.empty())
    {
        return str.data();
    }

    std::string cap = lower(str);
    cap[0] = std::toupper(cap[0]);
    return cap;
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
[[nodiscard]] inline const std::string
center(const std::string_view str, const u32 width, const char fillchar = ' ') noexcept
{
    if (str.size() >= width)
    {
        return str.data();
    }

    const auto w = width - str.size();

    u64 offset_r = 0;
    if (w % 2 != 0)
    {
        offset_r = 1;
    }

    const u64 pad_l = static_cast<u64>(std::floor(w / 2));
    const u64 pad_r = static_cast<u64>(std::floor(w / 2)) + offset_r;

    std::string center_str;
    center_str.reserve(w);
    center_str.append(pad_l, fillchar);
    center_str.append(str);
    center_str.append(pad_r, fillchar);
    return center_str;
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
    u64 count = 0;

    if (str.empty())
    {
        return count;
    }

    auto start_pos = str.find(find);
    if (start_pos == std::string_view::npos)
    {
        return count;
    }

    while ((start_pos = str.find(find, start_pos)) != std::string_view::npos)
    {
        start_pos += find.size();
        count += 1;
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

    const std::string_view ss{str.substr(start, end - start)};

    return count(ss, find);
}

/**
 * @brief endswith
 *
 * @param[in] str The string to be searched
 * @param[in] suffix suffix to look for
 *
 * @return True if the string ends with the specified suffix,
 * otherwise return False.
 */
[[nodiscard]] inline bool
endswith(const std::string_view str, const std::string_view suffix) noexcept
{
    const auto start_pos = str.find(suffix);
    if (start_pos == std::string_view::npos)
    {
        return false;
    }

    return (str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0);
}

/**
 * @brief endswith
 *
 * @param[in] str The string to be searched
 * @param[in] suffix suffix to look for
 * @param[in] start position to start looking
 * @param[in] end position to stop looking
 *
 * @return True if the string ends with the specified suffix,
 * otherwise return False. With optional start, test beginning at that
 * position. With optional end, stop comparing at that position.
 */
[[nodiscard]] inline bool
endswith(const std::string_view str, const std::string_view suffix, const usize start,
         const usize end = std::string_view::npos) noexcept
{
    if (start >= end)
    {
        return false;
    }

    const std::string_view ss{str.substr(start, end - start)};

    return endswith(ss, suffix);
}

/**
 * @brief endswith
 *
 * @param[in] str The string to be searched
 * @param[in] suffixes suffixes to look for
 *
 * @return True if the string ends with the specified suffix,
 * otherwise return False.
 */
[[nodiscard]] inline bool
endswith(const std::string_view str, const std::span<const std::string> suffixes) noexcept
{
    const auto check = [=](const std::string_view suffix) { return endswith(str, suffix); };
    return std::ranges::any_of(suffixes.begin(), suffixes.end(), check);
}

/**
 * @brief endswith
 *
 * @param[in] str The string to be searched
 * @param[in] suffixes suffixes to look for
 * @param[in] start position to start looking
 * @param[in] end position to stop looking
 *
 * @return True if the string ends with the specified suffix,
 * otherwise return False. With optional start, test beginning at that
 * position. With optional end, stop comparing at that position.
 */
[[nodiscard]] inline bool
endswith(const std::string_view str, const std::span<const std::string> suffixes, const usize start,
         const usize end = std::string_view::npos) noexcept
{
    if (start >= end)
    {
        return false;
    }

    const auto check = [=](const std::string_view suffix) { return endswith(str, suffix, start, end); };
    return std::ranges::any_of(suffixes.begin(), suffixes.end(), check);
}

/**
 * @brief endswith
 *
 * @param[in] str The string to be searched
 * @param[in] suffixes suffixes to look for
 *
 * @return True if the string ends with the specified suffix,
 * otherwise return False.
 */
[[nodiscard]] inline bool
endswith(const std::string_view str, const std::span<const std::string_view> suffixes) noexcept
{
    const auto check = [=](const std::string_view suffix) { return endswith(str, suffix); };
    return std::ranges::any_of(suffixes.begin(), suffixes.end(), check);
}

/**
 * @brief endswith
 *
 * @param[in] str The string to be searched
 * @param[in] suffixes suffixes to look for
 * @param[in] start position to start looking
 * @param[in] end position to stop looking
 *
 * @return True if the string ends with the specified suffix,
 * otherwise return False. With optional start, test beginning at that
 * position. With optional end, stop comparing at that position.
 */
[[nodiscard]] inline bool
endswith(const std::string_view str, const std::span<const std::string_view> suffixes, const usize start,
         const usize end = std::string_view::npos) noexcept
{
    if (start >= end)
    {
        return false;
    }

    const auto check = [=](const std::string_view suffix) { return endswith(str, suffix, start, end); };
    return std::ranges::any_of(suffixes.begin(), suffixes.end(), check);
}

/**
 * @brief startswith
 *
 * @param[in] str The string to be searched
 * @param[in] prefix prefix to look for
 *
 * @return True if the string starts with the specified prefix,
 * otherwise return False.
 */
[[nodiscard]] inline bool
startswith(const std::string_view str, const std::string_view prefix) noexcept
{
    const auto start_pos = str.find(prefix);
    if (start_pos == std::string_view::npos)
    {
        return false;
    }

    return (str.compare(0, prefix.size(), prefix) == 0);
}

/**
 * @brief startswith
 *
 * @param[in] str The string to be searched
 * @param[in] prefix prefix to look for
 * @param[in] start position to start looking
 * @param[in] end position to stop looking
 *
 * @return True if the string starts with the specified prefix,
 * otherwise return False. With optional start, test beginning at that
 * position. With optional end, stop comparing at that position.
 */
[[nodiscard]] inline bool
startswith(const std::string_view str, const std::string_view prefix, const usize start,
           const usize end = std::string_view::npos) noexcept
{
    if (start >= end)
    {
        return false;
    }

    const std::string_view ss{str.substr(start, end - start)};

    return startswith(ss, prefix);
}

/**
 * @brief startswith
 *
 * @param[in] str The string to be searched
 * @param[in] prefixes prefixes to look for
 *
 * @return True if the string starts with the specified prefix,
 * otherwise return False.
 */
[[nodiscard]] inline bool
startswith(const std::string_view str, const std::span<const std::string> prefixes) noexcept
{
    const auto check = [=](const std::string_view prefix) { return startswith(str, prefix); };
    return std::ranges::any_of(prefixes.begin(), prefixes.end(), check);
}

/**
 * @brief startswith
 *
 * @param[in] str The string to be searched
 * @param[in] prefixes prefixes to look for
 * @param[in] start position to start looking
 * @param[in] end position to stop looking
 *
 * @return True if the string starts with the specified prefix,
 * otherwise return False. With optional start, test beginning at that
 * position. With optional end, stop comparing at that position.
 */
[[nodiscard]] inline bool
startswith(const std::string_view str, const std::span<const std::string> prefixes, const usize start,
           const usize end = std::string_view::npos) noexcept
{
    if (start >= end)
    {
        return false;
    }

    const auto check = [=](const std::string_view prefix) { return startswith(str, prefix, start, end); };
    return std::ranges::any_of(prefixes.begin(), prefixes.end(), check);
}

/**
 * @brief startswith
 *
 * @param[in] str The string to be searched
 * @param[in] prefixes prefixes to look for
 *
 * @return True if the string starts with the specified prefix,
 * otherwise return False.
 */
[[nodiscard]] inline bool
startswith(const std::string_view str, const std::span<const std::string_view> prefixes) noexcept
{
    const auto check = [=](const std::string_view prefix) { return startswith(str, prefix); };
    return std::ranges::any_of(prefixes.begin(), prefixes.end(), check);
}

/**
 * @brief startswith
 *
 * @param[in] str The string to be searched
 * @param[in] prefixes prefixes to look for
 * @param[in] start position to start looking
 * @param[in] end position to stop looking
 *
 * @return True if the string starts with the specified prefix,
 * otherwise return False. With optional start, test beginning at that
 * position. With optional end, stop comparing at that position.
 */
[[nodiscard]] inline bool
startswith(const std::string_view str, const std::span<const std::string_view> prefixes, const usize start,
           const usize end = std::string_view::npos) noexcept
{
    if (start >= end)
    {
        return false;
    }

    const auto check = [=](const std::string_view prefix) { return startswith(str, prefix, start, end); };
    return std::ranges::any_of(prefixes.begin(), prefixes.end(), check);
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
[[nodiscard]] inline const std::string
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

    const auto check = [=](const auto& c) { return !(std::isalpha(c) == 0 && std::isdigit(c) == 0); };
    return std::ranges::all_of(str.cbegin(), str.cend(), check);
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

    const auto check = [=](const auto& c) { return !(std::isalpha(c) == 0); };
    return std::ranges::all_of(str.cbegin(), str.cend(), check);
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

    const auto check = [=](const auto& c) { return !(std::isdigit(c) == 0); };
    return std::ranges::all_of(str.cbegin(), str.cend(), check);
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

    const auto check = [=](const auto& c) { return !(std::isalpha(c) != 0 && std::islower(c) == 0); };
    return std::ranges::all_of(str.cbegin(), str.cend(), check);
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

    const auto check = [=](const auto& c) { return !(std::isalpha(c) != 0 && std::isupper(c) == 0); };
    return std::ranges::all_of(str.cbegin(), str.cend(), check);
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

    const auto check = [=](const auto& c) { return !(std::isspace(c) == 0); };
    return std::ranges::all_of(str.cbegin(), str.cend(), check);
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
[[nodiscard]] inline const std::string
title(const std::string_view str) noexcept
{
    using namespace std::literals::string_literals;

    if (str.empty())
    {
        return ""s;
    }

    bool word_start = true;
    bool inside_word = false;

    std::string title_str;
    title_str.reserve(str.size());
    for (const auto& c : str)
    {
        if (std::isalpha(c) != 0)
        {
            inside_word = true;

            if (word_start && std::isupper(c) == 0)
            {
                title_str += std::toupper(c);
            }
            else if (!word_start && std::islower(c) == 0)
            {
                title_str += std::tolower(c);
            }
            else
            {
                title_str += c;
            }
        }
        else
        {
            inside_word = false;
            title_str += c;
        }

        word_start = !inside_word;
    }
    return title_str;
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
[[nodiscard]] inline const std::string
swapcase(const std::string_view str) noexcept
{
    using namespace std::literals::string_literals;

    if (str.empty())
    {
        return ""s;
    }

    std::string swapcase_str;
    swapcase_str.reserve(str.size());
    for (const auto& c : str)
    {
        if (std::isalpha(c) != 0)
        {
            if (std::isupper(c) != 0)
            {
                swapcase_str += std::tolower(c);
            }
            else if (std::islower(c) != 0)
            {
                swapcase_str += std::toupper(c);
            }
            else
            {
                swapcase_str += c;
            }
        }
        else
        {
            swapcase_str += c;
        }
    }
    return swapcase_str;
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
[[nodiscard]] inline const std::string
ljust(const std::string_view str, const usize width, const char fillchar = ' ') noexcept
{
    if (str.size() >= width)
    {
        return str.data();
    }

    const auto w = width - str.size();

    std::string ljust_str;
    ljust_str.reserve(w);
    ljust_str.append(str);
    ljust_str.append(w, fillchar);
    return ljust_str;
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
[[nodiscard]] inline const std::string
rjust(const std::string_view str, const usize width, const char fillchar = ' ') noexcept
{
    if (str.size() >= width)
    {
        return str.data();
    }

    const auto w = width - str.size();

    std::string rjust_str;
    rjust_str.reserve(w);
    rjust_str.append(w, fillchar);
    rjust_str.append(str);
    return rjust_str;
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
[[nodiscard]] inline const std::string
lstrip(const std::string_view str, const std::string_view chars = " \r\n\t") noexcept
{
    using namespace std::literals::string_literals;

    const auto start_pos = str.find_first_not_of(chars);
    if (start_pos == std::string_view::npos)
    {
        return ""s;
    }
    return std::string(str.substr(start_pos));
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
[[nodiscard]] inline const std::string
rstrip(const std::string_view str, const std::string_view chars = " \r\n\t") noexcept
{
    using namespace std::literals::string_literals;

    const auto end_pos = str.find_last_not_of(chars);
    if (end_pos == std::string_view::npos)
    {
        return ""s;
    }
    return std::string(str.substr(0, end_pos + 1));
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
[[nodiscard]] inline const std::string
strip(const std::string_view str, const std::string_view chars = " \r\n\t") noexcept
{
    using namespace std::literals::string_literals;

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
[[nodiscard]] inline const std::string
removeprefix(const std::string_view str, const std::string_view prefix) noexcept
{
    if (!startswith(str, prefix))
    {
        return str.data();
    }
    return std::string(str.substr(prefix.size(), str.size()));
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
[[nodiscard]] inline const std::string
removesuffix(const std::string_view str, const std::string_view suffix) noexcept
{
    if (!endswith(str, suffix))
    {
        return str.data();
    }
    return std::string(str.substr(0, str.size() - suffix.size()));
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
[[nodiscard]] inline const std::array<std::string, 3>
partition(const std::string_view str, const std::string_view sep) noexcept
{
    using namespace std::literals::string_literals;

    if (sep.empty())
    {
        return {str.data(), ""s, ""s};
    }

    const auto index = str.find(sep);
    if (index == std::string_view::npos)
    {
        return {str.data(), ""s, ""s};
    }

    const auto begin = str.substr(0, index);
    const auto end = str.substr(index + sep.size());

    return {std::string(begin), std::string(sep), std::string(end)};
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
[[nodiscard]] inline const std::array<std::string, 3>
rpartition(const std::string_view str, const std::string_view sep) noexcept
{
    using namespace std::literals::string_literals;

    if (sep.empty())
    {
        return {""s, ""s, str.data()};
    }

    const auto index = str.rfind(sep);
    if (index == std::string_view::npos)
    {
        return {""s, ""s, str.data()};
    }

    const auto begin = str.substr(0, index);
    const auto end = str.substr(index + sep.size());

    return {std::string(begin), std::string(sep), std::string(end)};
}

#if 0
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
[[nodiscard]] inline const std::vector<std::string>
splitlines(const std::string_view str, const bool keepends = false) noexcept
{
    if (str.empty())
        return {};

    const std::vector<std::string> delimiters{
        "\r\n",   // Carriage Return + Line Feed
        "\n",     // Line Feed
        "\r",     // Carriage Return
        "\v",     // Line Tabulation
        "\x0b",   // Line Tabulation
        "\f",     // Form Feed
        "\x0c",   // Form Feed
        "\x1c",   // File Separator
        "\x1d",   // Group Separator
        "\x1e",   // Record Separator
        "\x85",   // Next Line (C1 Control Code)
        "\u2028", // Line Separator
        "\u2029", // Paragraph Separator
    };

    std::string split_string = str.data();

    std::vector<std::string> lines;

    while (!split_string.empty())
    {
        bool found = false;

        usize index = 0;
        const std::string_view delimiter;
        for (const std::string_view d : delimiters)
        {
            index = split_string.find(d);
            if (index == std::string_view::npos)
                continue;

            found = true;
            delimiter = d;
            break;
        }
        if (!found)
        {
            lines.emplace_back(split_string);
            break;
        }

        if (keepends)
        {
            lines.emplace_back(split_string.substr(0, index + delimiter.length()));
        }
        else
        {
            lines.emplace_back(split_string.substr(0, index));
        }
        split_string = split_string.substr(index + delimiter.size());
    }
    return lines;
}
#endif

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
[[nodiscard]] inline const std::string
zfill(const std::string_view str, const usize width) noexcept
{
    if (str.size() >= width)
    {
        return str.data();
    }

    const auto w = width - str.size();

    std::string zstr;
    zstr.reserve(w);
    if (str.empty())
    {
        zstr.append(w, '0');
    }
    else
    {
        if (str.at(0) == '+')
        {
            zstr.append("+");
            zstr.append(w, '0');
            zstr.append(str, 1);
        }
        else if (str.at(0) == '-')
        {
            zstr.append("-");
            zstr.append(w, '0');
            zstr.append(str, 1);
        }
        else
        {
            zstr.append(w, '0');
            zstr.append(str);
        }
    }

    return zstr;
}
} // namespace ztd
