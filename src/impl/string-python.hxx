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

#include <string>
#include <string_view>

#include <algorithm>
#include <ranges>

#include <cstring>

#include <array>
#include <vector>

#include <cmath>

#include "types.hxx"

/**
 * https://docs.python.org/3/library/stdtypes.html#string-methods
 *
 * implemented
 * ===========
 * capitalize
 * center
 * count
 * endswith
 * expandtabs
 * isalpha
 * isdigit
 * islower
 * isspace
 * istitle
 * isupper
 * join
 * ljust
 * lower
 * lstrip
 * partition
 * removeprefix
 * removesuffix
 * replace
 * rjust
 * rpartition
 * rsplit
 * rstrip
 * split
 * startswith
 * strip
 * swapcase
 * title
 * upper
 * zfill
 *
 * Not implemented
 * ===============
 * casefold - ?
 * encode - NO
 * find - NO - std::string::find
 * format - NO
 * format_map - NO
 * index - NO
 * isalnum - ?
 * isascii - ?
 * isdecimal - ?
 * isidentifier - NO
 * isnumeric - ?
 * isprintable - NO
 * maketrans - NO
 * rfind - NO - std::string::rfind
 * rindex - NO
 * splitlines - ?
 * translate - NO
 */

namespace ztd
{
    namespace
    {
        // std::literals::string_view_literals::operator""sv
        using namespace std::literals::string_view_literals;
    } // namespace

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
    static inline const std::vector<std::string>
    split(std::string_view str, std::string_view sep = ""sv, i32 maxsplit = -1) noexcept
    {
        if (str.empty())
            return {std::string(""sv)};

        if (sep.empty() || maxsplit == 0)
            return {str.data()};

        i32 split_counter = 0;
        std::string split_string = str.data();
        std::vector<std::string> result;

        while (!split_string.empty())
        {
            const usize index = split_string.find(sep);
            if (index == std::string_view::npos)
            {
                result.emplace_back(split_string);
                break;
            }

            result.emplace_back(split_string.substr(0, index));
            split_string = split_string.substr(index + sep.size());
            if (split_string.size() == 0)
                result.emplace_back(split_string);

            // Limit total number of splits
            split_counter += 1;
            if (split_counter == maxsplit)
            {
                result.emplace_back(split_string);
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
    static inline const std::vector<std::string>
    rsplit(std::string_view str, std::string_view sep = ""sv, i32 maxsplit = -1) noexcept
    {
        if (str.empty())
            return {std::string(""sv)};

        if (sep.empty() || maxsplit == 0)
            return {str.data()};

        i32 split_counter = 0;
        std::string split_string = str.data();
        std::vector<std::string> result;

        while (!split_string.empty())
        {
            const usize index = split_string.rfind(sep);
            if (index == std::string_view::npos)
            {
                result.emplace_back(split_string);
                break;
            }

            result.emplace_back(split_string.substr(index + sep.size()));
            split_string = split_string.substr(0, index);
            if (split_string.size() == 0)
                result.emplace_back(split_string);

            // Limit total number of splits
            split_counter += 1;
            if (split_counter == maxsplit)
            {
                result.emplace_back(split_string);
                break;
            }
        }

        std::ranges::reverse(result);

        return result;
    }

    /**
     * @brief join
     *
     * @param[in] iterable vector of string to be joined together
     * @param[in] sep separator to be used between elements in the string
     *
     * @return A string which is the concatenation of the strings in iterable, with sep
     * inserted between each element.
     */
    static inline const std::string
    join(const std::vector<std::string>& iterable, std::string_view sep) noexcept
    {
        std::string str;
        for (auto it = iterable.cbegin(); it != iterable.cend(); ++it)
        {
            if (it != iterable.cbegin())
                str.append(sep.data());
            str.append(*it);
        }
        return str;
    }

    /**
     * @brief join
     *
     * @param[in] iterable vector of string to be joined together
     * @param[in] sep separator to be used between elements in the string
     *
     * @return A string which is the concatenation of the strings in iterable, with sep
     * inserted between each element.
     */
    static inline const std::string
    join(const std::vector<std::string_view>& iterable, std::string_view sep) noexcept
    {
        std::string str;
        for (auto it = iterable.cbegin(); it != iterable.cend(); ++it)
        {
            if (it != iterable.cbegin())
                str.append(sep.data());
            str.append(*it);
        }
        return str;
    }

    /**
     * @brief lower
     *
     * @param[in] str The string to be lowercased
     *
     * @return A copy of the string with all the cased characters converted to lowercase.
     */
    static inline const std::string
    lower(std::string_view str) noexcept
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
    static inline const std::string
    upper(std::string_view str) noexcept
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
    static inline const std::string
    replace(std::string_view str, std::string_view str_find, std::string_view str_replace, i32 count = -1) noexcept
    {
        if (str.empty() || count == 0)
            return str.data();

        usize start_pos = str.find(str_find);
        if (start_pos == std::string_view::npos)
            return str.data();

        i32 counter = 0;
        std::string rep = str.data();

        while ((start_pos = rep.find(str_find, start_pos)) != std::string_view::npos)
        {
            rep.replace(start_pos, str_find.size(), str_replace);
            // In case 'str_replace' is in 'str_find', i.e. replace 'bar' with 'foobar'
            start_pos += str_replace.size();

            counter += 1;
            if (counter == count)
                break;
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
    static inline const std::string
    capitalize(std::string_view str) noexcept
    {
        if (str.empty())
            return str.data();

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
    static inline const std::string
    center(std::string_view str, u32 width, char fillchar = ' ') noexcept
    {
        if (str.size() >= width)
            return str.data();

        u32 w = width - str.size();

        u32 offset_r = 0;
        if (w % 2 != 0)
            offset_r = 1;

        u32 pad_l = std::floor(w / 2);
        u32 pad_r = std::floor(w / 2) + offset_r;

        std::string center_str;
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
     * @param[in] start position to start looking
     * @param[in] end position to stop looking
     *
     * @return The number of non-overlapping occurrences of substring sub
     * in the range of 'start, end'.
     */
    static inline u64
    count(std::string_view str, std::string_view find, usize start = 0, usize end = std::string_view::npos) noexcept
    {
        u64 count = 0;

        if (str.empty())
            return count;

        if (start >= end)
            return count;

        usize start_pos = str.find(find);
        if (start_pos == std::string_view::npos)
            return count;

        const std::string_view ss{str.substr(start, end - start)};

        while ((start_pos = ss.find(find, start_pos)) != std::string_view::npos)
        {
            start_pos += find.size();
            count += 1;
        }
        return count;
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
    static inline bool
    endswith(std::string_view str, std::string_view suffix, usize start = 0,
             usize end = std::string_view::npos) noexcept
    {
        if (start >= end)
            return false;

        const usize start_pos = str.find(suffix);
        if (start_pos == std::string_view::npos)
            return false;

        const std::string_view ss{str.substr(start, end - start)};

        return (ss.compare(ss.size() - suffix.size(), suffix.size(), suffix) == 0);
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
    static inline bool
    endswith(std::string_view str, const std::vector<std::string>& suffixes, usize start = 0,
             usize end = std::string_view::npos) noexcept
    {
        if (start >= end)
            return false;

        for (std::string_view suffix : suffixes)
        {
            if (endswith(str, suffix, start, end))
                return true;
        }
        return false;
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
    static inline bool
    endswith(std::string_view str, const std::vector<std::string_view>& suffixes, usize start = 0,
             usize end = std::string_view::npos) noexcept
    {
        if (start >= end)
            return false;

        for (std::string_view suffix : suffixes)
        {
            if (endswith(str, suffix, start, end))
                return true;
        }
        return false;
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
    static inline bool
    startswith(std::string_view str, std::string_view prefix, usize start = 0,
               usize end = std::string_view::npos) noexcept
    {
        if (start >= end)
            return false;

        const usize start_pos = str.find(prefix);
        if (start_pos == std::string_view::npos)
            return false;

        const std::string_view ss{str.substr(start, end - start)};

        return (ss.compare(0, prefix.size(), prefix) == 0);
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
    static inline bool
    startswith(std::string_view str, const std::vector<std::string>& prefixes, usize start = 0,
               usize end = std::string_view::npos) noexcept
    {
        if (start >= end)
            return false;

        for (std::string_view prefix : prefixes)
        {
            if (startswith(str, prefix, start, end))
                return true;
        }
        return false;
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
    static inline bool
    startswith(std::string_view str, const std::vector<std::string_view>& prefixes, usize start = 0,
               usize end = std::string_view::npos) noexcept
    {
        if (start >= end)
            return false;

        for (std::string_view prefix : prefixes)
        {
            if (startswith(str, prefix, start, end))
                return true;
        }
        return false;
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
    static inline const std::string
    expandtabs(std::string_view str, u32 tabsize = 8) noexcept
    {
        std::string expanded;

        auto columns = split(str, "\t"sv);

        // need to track columns to avoid adding
        // extra whitespace at the end of a line
        usize columns_count = 1;

        for (std::string_view column : columns)
        {
            usize tab_diff = 0;
            if (column.size() < tabsize)
            {
                expanded.append(column);
                tab_diff = tabsize - column.size();
                if (columns.size() != columns_count)
                    expanded.append(tab_diff, ' ');
            }
            else if (column.size() > tabsize)
            {
                expanded.append(column);
                tab_diff = column.size() % tabsize;
                if (columns.size() != columns_count)
                    expanded.append(tab_diff, ' ');
            }
            else if (column.size() == tabsize)
            {
                expanded.append(column);
                if (columns.size() != columns_count)
                    expanded.append(tabsize, ' ');
            }
            ++columns_count;
        }
        return expanded;
    }

    /**
     * @brief isalpha
     *
     * @param[in] str The string to use
     *
     * @return True if all characters in the string are alphabetic and
     * there is at least one character, False otherwise.
     */
    static inline bool
    isalpha(std::string_view str) noexcept
    {
        if (str.empty())
            return false;

        for (usize i = 0; i < str.size(); ++i)
        {
            if (!std::isalpha(str[i]))
                return false;
        }
        return true;
    }

    /**
     * @brief isdigit
     *
     * @param[in] str The string to use
     *
     * @return True if all characters in the string are digits
     * and there is at least one character, False otherwise.
     */
    static inline bool
    isdigit(std::string_view str) noexcept
    {
        if (str.empty())
            return false;

        for (usize i = 0; i < str.size(); ++i)
        {
            if (!std::isdigit(str[i]))
                return false;
        }
        return true;
    }

    /**
     * @brief islower
     *
     * @param[in] str The string to use
     *
     * @return True if all cased characters in the string are
     * lowercase and there is at least one cased character,
     * False otherwise.
     */
    static inline bool
    islower(std::string_view str) noexcept
    {
        if (str.empty())
            return false;

        for (usize i = 0; i < str.size(); ++i)
        {
            if (std::isalpha(str[i]) && !std::islower(str[i]))
                return false;
        }
        return true;
    }

    /**
     * @brief isupper
     *
     * @param[in] str The string to use
     *
     * @return True if all cased characters in the string are
     * uppercase and there is at least one cased character,
     * False otherwise.
     */
    static inline bool
    isupper(std::string_view str) noexcept
    {
        if (str.empty())
            return false;

        for (usize i = 0; i < str.size(); ++i)
        {
            if (std::isalpha(str[i]) && !std::isupper(str[i]))
                return false;
        }
        return true;
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
    static inline bool
    isspace(std::string_view str) noexcept
    {
        if (str.empty())
            return false;

        for (usize i = 0; i < str.size(); ++i)
        {
            if (!std::isspace(str[i]))
                return false;
        }
        return true;
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
    static inline bool
    istitle(std::string_view str) noexcept
    {
        if (str.empty())
            return false;

        bool in_word = false;
        u32 in_word_count = 0;

        for (usize i = 0; i < str.size(); ++i)
        {
            if (std::isalpha(str[i]))
            {
                in_word = true;

                if (in_word_count == 0)
                {
                    if (!std::isupper(str[i]))
                        return false;
                }
                else
                {
                    if (!std::islower(str[i]))
                        return false;
                }
            }
            else
            {
                in_word = false;
            }

            if (in_word)
            {
                in_word_count += 1;
            }
            else
            {
                in_word_count = 0;
            }
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
    static inline const std::string
    title(std::string_view str) noexcept
    {
        if (str.empty())
            return std::string(""sv);

        bool in_word = false;
        u32 in_word_count = 0;

        std::string title_str;
        for (usize i = 0; i < str.size(); ++i)
        {
            if (std::isalpha(str[i]))
            {
                in_word = true;

                if (in_word_count == 0)
                {
                    title_str.append(upper(std::string(str.substr(i, 1))));
                }
                else
                {
                    title_str.append(lower(std::string(str.substr(i, 1))));
                }
            }
            else
            {
                in_word = false;
                title_str.append(std::string(str.substr(i, 1)));
            }

            if (in_word)
            {
                in_word_count += 1;
            }
            else
            {
                in_word_count = 0;
            }
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
    static inline const std::string
    swapcase(std::string_view str) noexcept
    {
        if (str.empty())
            return std::string(""sv);

        std::string swapcase_str;
        for (usize i = 0; i < str.size(); ++i)
        {
            if (std::isalpha(str[i]))
            {
                if (std::isupper(str[i]))
                {
                    swapcase_str.append(lower(std::string(str.substr(i, 1))));
                }
                else if (std::islower(str[i]))
                {
                    swapcase_str.append(upper(std::string(str.substr(i, 1))));
                }
                else
                {
                    swapcase_str.append(std::string(str.substr(i, 1)));
                }
            }
            else
            {
                swapcase_str.append(std::string(str.substr(i, 1)));
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
    static inline const std::string
    ljust(std::string_view str, usize width, char fillchar = ' ') noexcept
    {
        if (str.size() >= width)
            return str.data();

        u32 w = width - str.size();

        std::string ljust_str;
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
    static inline const std::string
    rjust(std::string_view str, usize width, char fillchar = ' ') noexcept
    {
        if (str.size() >= width)
            return str.data();

        u32 w = width - str.size();

        std::string rjust_str;
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
    static inline const std::string
    lstrip(std::string_view str, std::string_view chars = " \r\n\t"sv) noexcept
    {
        const usize start_pos = str.find_first_not_of(chars);
        if (start_pos == std::string_view::npos)
            return std::string(""sv);
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
    static inline const std::string
    rstrip(std::string_view str, std::string_view chars = " \r\n\t"sv) noexcept
    {
        const usize end_pos = str.find_last_not_of(chars);
        if (end_pos == std::string_view::npos)
            return std::string(""sv);
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
    static inline const std::string
    strip(std::string_view str, std::string_view chars = " \r\n\t"sv) noexcept
    {
        return lstrip(rstrip(str, chars), chars);
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
    static inline const std::string
    removeprefix(std::string_view str, std::string_view prefix) noexcept
    {
        if (!startswith(str, prefix))
            return str.data();
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
    static inline const std::string
    removesuffix(std::string_view str, std::string_view suffix) noexcept
    {
        if (!endswith(str, suffix))
            return str.data();
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
    static inline const std::array<std::string, 3>
    partition(std::string_view str, std::string_view sep) noexcept
    {
        const usize index = str.find(sep);
        if (index == std::string_view::npos)
            return {std::string(str), std::string(""sv), std::string(""sv)};

        const std::string_view begin{str.substr(0, index)};
        const std::string_view end{str.substr(index + sep.size())};

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
    static inline const std::array<std::string, 3>
    rpartition(std::string_view str, std::string_view sep) noexcept
    {
        const usize index = str.rfind(sep);
        if (index == std::string_view::npos)
            return {std::string(""sv), std::string(""sv), std::string(str)};

        const std::string_view begin{str.substr(0, index)};
        const std::string_view end{str.substr(index + sep.size())};

        return {std::string(begin), std::string(sep), std::string(end)};
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
    static inline const std::string
    zfill(std::string_view str, usize width) noexcept
    {
        if (str.size() >= width)
            return str.data();

        u32 w = width - str.size();

        std::string zstr;
        if (str[0] == '+')
        {
            zstr.append("+"sv);
            zstr.append(w, '0');
            zstr.append(str, 1);
        }
        else if (str[0] == '-')
        {
            zstr.append("-"sv);
            zstr.append(w, '0');
            zstr.append(str, 1);
        }
        else
        {
            zstr.append(w, '0');
            zstr.append(str);
        }

        return zstr;
    }
} // namespace ztd
