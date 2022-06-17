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

#include <cmath>

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
    /**
     * @brief split
     *
     * - Splits the string at occurrences of the delimiter, Except for splitting
     * from the left, split() behaves like rsplit().
     *
     * @param[in] __str The string to be split
     * @param[in] __delimiter If delimiter is given, consecutive delimiters
     * are not grouped together and are deemed to delimit empty strings
     * (for example, split("1,,2", ",") returns {"1", "", "2"}).
     * The sep argument may consist of multiple characters
     * (for example, split("1<>2<>3", "<>") returns {"1", "2", "3"}).
     * @param[in] __maxsplit If maxsplit is given, at most maxsplit splits are
     * done (thus, the list will have at most maxsplit+1 elements). If maxsplit
     * is not specified or -1, then there is no limit on the number of
     * splits (all possible splits are made).
     *
     * @return A list of the words in the string, using delimiter as the delimiting string.
     */
    static inline std::vector<std::string>
    split(const std::string& __str, const std::string& __delimiter = "",
          int __maxsplit = -1) noexcept
    {
        if (__str.empty())
            return {""};

        if (__delimiter.empty() || __maxsplit == 0)
            return {__str};

        int split_counter = 0;
        std::string split_string = __str;
        std::vector<std::string> result;

        while (!split_string.empty())
        {
            std::size_t index = split_string.find(__delimiter);
            if (index == std::string::npos)
            {
                result.push_back(split_string);
                break;
            }

            result.push_back(split_string.substr(0, index));
            split_string = split_string.substr(index + __delimiter.size());
            if (split_string.size() == 0)
                result.push_back(split_string);

            // Limit total number of splits
            split_counter += 1;
            if (split_counter == __maxsplit)
            {
                result.push_back(split_string);
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
     * @param[in] __str The string to be split
     * @param[in] __delimiter If delimiter is given, consecutive delimiters
     * are not grouped together and are deemed to delimit empty strings
     * (for example, split("1,,2", ",") returns {"1", "", "2"}).
     * The sep argument may consist of multiple characters
     * (for example, split("1<>2<>3", "<>") returns {"1", "2", "3"}).
     * @param[in] __maxsplit If maxsplit is given, at most maxsplit splits are
     * done (thus, the list will have at most maxsplit+1 elements). If maxsplit
     * is not specified or -1, then there is no limit on the number of
     * splits (all possible splits are made).
     *
     * @return A list of the words in the string, using delimiter as the delimiting string.
     */
    static inline std::vector<std::string>
    rsplit(const std::string& __str, const std::string& __delimiter = "",
           int __maxsplit = -1) noexcept
    {
        if (__str.empty())
            return {""};

        if (__delimiter.empty() || __maxsplit == 0)
            return {__str};

        int split_counter = 0;
        std::string split_string = __str;
        std::vector<std::string> result;

        while (!split_string.empty())
        {
            std::size_t index = split_string.rfind(__delimiter);
            if (index == std::string::npos)
            {
                result.push_back(split_string);
                break;
            }

            result.push_back(split_string.substr(index + __delimiter.size()));
            split_string = split_string.substr(0, index);
            if (split_string.size() == 0)
                result.push_back(split_string);

            // Limit total number of splits
            split_counter += 1;
            if (split_counter == __maxsplit)
            {
                result.push_back(split_string);
                break;
            }
        }

        std::reverse(result.begin(), result.end());

        return result;
    }

    /**
     * @brief join
     *
     * @param[in] __tokens The std::vector to be joined
     * @param[in] __delimiter The std::string to be used as a delimiter
     *
     * @return A string which is the concatenation of the strings in tokens, with delimiter
     * inserted between each element.
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
     * @brief lower
     *
     * @param[in] __str The std::string to be lowercased
     *
     * @return A copy of the string with all the cased characters converted to lowercase.
     */
    static inline const std::string
    lower(const std::string& __str) noexcept
    {
        std::string lower = __str;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return lower;
    }

    /**
     * @brief upper
     *
     * @param[in] __str The std::string to be uppercased
     *
     * @return A copy of the string with all the cased characters converted to uppercase.
     */
    static inline const std::string
    upper(const std::string& __str) noexcept
    {
        std::string upper = __str;
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        return upper;
    }

    /**
     * @brief replace
     *
     * @param[in] __str The std::string to be parsed for replacements
     * @param[in] __str_find The std::string to be found and replaced
     * @param[in] __str_replace The std::string to replace with
     * @param[in] __count If count is given, at most count replacements are
     * done. If count is not specified or -1, then there is no limit on the
     * number of replacements (all possible replacements are made).
     *
     * @return A copy of the string with all occurrences of substring old replaced by new.
     */
    static inline const std::string
    replace(const std::string& __str, const std::string& __str_find,
            const std::string& __str_replace, int __count = -1) noexcept
    {
        if (__str.empty() || __count == 0)
            return __str;

        int counter = 0;
        std::string str = __str;

        std::size_t start_pos = str.find(__str_find);
        if (start_pos == std::string::npos)
            return str;

        while ((start_pos = str.find(__str_find, start_pos)) != std::string::npos)
        {
            str.replace(start_pos, __str_find.size(), __str_replace);
            // In case 'str_replace' is in 'str_find', i.e. replace 'bar' with 'foobar'
            start_pos += __str_replace.size();

            counter += 1;
            if (counter == __count)
                break;
        }
        return str;
    }

    /**
     * @brief capitalize
     *
     * @param[in] __str The string to be capitalized
     *
     * @return A copy of the string with its first character
     * capitalized and the rest lowercased.
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
     * @param[in] __str The string to be centered
     * @param[in] __width width to center the string in
     * @param[in] __fillchar The char to center the string with
     *
     * @return Centered in a string of length width. Padding is done using
     * the specified fillchar (default is an ASCII space). The original
     * string is returned if width is less than or equal to the strings
     * length.
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
     * @param[in] __str The string to be searched
     * @param[in] __find substring to count
     * @param[in] __start position to start looking
     * @param[in] __end position to stop looking
     *
     * @return The number of non-overlapping occurrences of substring sub
     * in the range of 'start, end'.
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
     * @param[in] __str The string to be searched
     * @param[in] __suffix suffix to look for
     * @param[in] __start position to start looking
     * @param[in] __end position to stop looking
     *
     * @return True if the string ends with the specified suffix,
     * otherwise return False. With optional start, test beginning at that
     * position. With optional end, stop comparing at that position.
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
     * @param[in] __str The string to be searched
     * @param[in] __prefix prefix to look for
     * @param[in] __start position to start looking
     * @param[in] __end position to stop looking
     *
     * @return True if the string starts with the specified prefix,
     * otherwise return False. With optional start, test beginning at that
     * position. With optional end, stop comparing at that position.
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
     * @return True if all characters in the string are alphabetic and
     * there is at least one character, False otherwise.
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
     * and there is at least one character, False otherwise.
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
     * False otherwise.
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
     * False otherwise.
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
     * @brief isspace
     *
     * @param[in] __str The string to use
     *
     * @return True if there are only whitespace characters
     * in the string and there is at least one character,
     * False otherwise.
     */
    static inline bool
    isspace(const std::string& __str) noexcept
    {
        if (__str.empty())
            return false;

        for (std::size_t i = 0; i < __str.size(); ++i)
        {
            if (!std::isspace(__str[i]))
                return false;
        }
        return true;
    }

    /**
     * @brief istitle
     *
     * @param[in] __str The string to use
     *
     * @return True if the string is a titlecased string and
     * there is at least one character, for example uppercase
     * characters may only follow uncased characters and lowercase
     * characters only cased ones. Return False otherwise.
     */
    static inline bool
    istitle(const std::string& __str) noexcept
    {
        if (__str.empty())
            return false;

        bool in_word = false;
        uint in_word_count = 0;

        std::string str;
        for (std::size_t i = 0; i < __str.size(); ++i)
        {
            if (std::isalpha(__str[i]))
            {
                in_word = true;

                if (in_word_count == 0)
                {
                    if (!std::isupper(__str[i]))
                        return false;
                }
                else
                {
                    if (!std::islower(__str[i]))
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
     * @param[in] __str The string to use
     *
     * @return A titlecased version of the string where words
     * start with an uppercase character and the remaining
     * characters are lowercase.
     */
    static inline const std::string
    title(const std::string& __str) noexcept
    {
        if (__str.empty())
            return "";

        bool in_word = false;
        uint in_word_count = 0;

        std::string str;
        for (std::size_t i = 0; i < __str.size(); ++i)
        {
            if (std::isalpha(__str[i]))
            {
                in_word = true;

                if (in_word_count == 0)
                {
                    str.append(upper(__str.substr(i, 1)));
                }
                else
                {
                    str.append(lower(__str.substr(i, 1)));
                }
            }
            else
            {
                in_word = false;
                str.append(__str.substr(i, 1));
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
        return str;
    }

    /**
     * @brief swapcase
     *
     * @param[in] __str The string to use
     *
     * @return the string with uppercase characters converted
     * to lowercase and vice versa. Note that it is not necessarily
     * true that swapcase(swapcase(s)) == s.
     */
    static inline const std::string
    swapcase(const std::string& __str) noexcept
    {
        if (__str.empty())
            return "";

        std::string str;
        for (std::size_t i = 0; i < __str.size(); ++i)
        {
            if (std::isalpha(__str[i]))
            {
                if (std::isupper(__str[i]))
                {
                    str.append(lower(__str.substr(i, 1)));
                }
                else if (std::islower(__str[i]))
                {
                    str.append(upper(__str.substr(i, 1)));
                }
                else
                {
                    str.append(__str.substr(i, 1));
                }
            }
            else
            {
                str.append(__str.substr(i, 1));
            }
        }
        return str;
    }

    /**
     * @brief ljust
     *
     * @param[in] __str The string to use
     * @param[in] __width width to center the string in
     * @param[in] __fillchar The char to center the string with
     *
     * @return the string left justified in a string of length width.
     * The original string is returned if width is less than or equal
     * to the strings length.
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
     * @param[in] __str The string to use
     * @param[in] __width width to center the string in
     * @param[in] __fillchar The char to center the string with
     *
     * @return the string right justified in a string of length width.
     * The original string is returned if width is less than or equal
     * to the string length.
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
     * @param[in] __str The string to trim
     * @param[in] __chars string of chars to be trimmed
     *
     * @return A copy of the string with leading characters removed. The
     * chars argument is a string specifying the set of characters to be
     * removed. If omitted, the chars argument defaults to removing whitespace.
     * The chars argument is not a prefix; rather, all combinations of its
     * values are stripped.
     */
    static inline const std::string
    lstrip(const std::string& __str, const std::string& __chars = " \r\n\t") noexcept
    {
        std::size_t start_pos = __str.find_first_not_of(__chars);
        if (start_pos == std::string::npos)
            return "";
        return __str.substr(start_pos);
    }

    /**
     * @brief rstrip
     *
     * @param[in] __str The string to trim
     * @param[in] __chars string of chars to be trimmed
     *
     * @return A copy of the string with trailing characters removed. The
     * chars argument is a string specifying the set of characters to be
     * removed. If omitted, the chars argument defaults to removing whitespace.
     * The chars argument is not a suffix; rather, all combinations of its
     * values are stripped.
     */
    static inline const std::string
    rstrip(const std::string& __str, const std::string& __chars = " \r\n\t") noexcept
    {
        std::size_t end_pos = __str.find_last_not_of(__chars);
        if (end_pos == std::string::npos)
            return "";
        return __str.substr(0, end_pos + 1);
    }

    /**
     * @brief strip
     *
     * @param[in] __str The string to trim
     * @param[in] __chars string of chars to be trimmed
     *
     * @return A copy of the string with the leading and trailing characters
     * removed. The chars argument is a string specifying the set of characters
     * to be removed. If omitted, the chars argument defaults to removing
     * whitespace. The chars argument is not a prefix or suffix; rather, all
     * combinations of its values are stripped.
     */
    static inline const std::string
    strip(const std::string& __str, const std::string& __chars = " \r\n\t") noexcept
    {
        return lstrip(rstrip(__str, __chars), __chars);
    }

    /**
     * @brief removeprefix
     *
     * @param[in] __str The string to be parsed for a given prefix
     * @param[in] __prefix The string prefix
     *
     * @return If the string starts with the prefix string, return
     * the string without the prefix. Otherwise, return a copy of the
     * original string.
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
     * @param[in] __str The string to be parsed for a given suffix
     * @param[in] __suffix The string suffix
     *
     * @return If the string ends with the suffix string, return
     * the string without the suffix. Otherwise, return a copy of the
     * original string.
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
     * @return A 3 element array containing the part before the separator,
     * the separator itself, and the part after the separator. If the
     * separator is not found, return a 3 element array containing the string
     * itself, followed by two empty strings.
     */
    static inline const std::array<std::string, 3>
    partition(const std::string& __str, const std::string& __delimiter) noexcept
    {
        std::size_t index = __str.find(__delimiter);
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
     * @return A 3 element array containing the part before the separator,
     * the separator itself, and the part after the separator. If the
     * separator is not found, return a 3 element array containing
     * two empty strings, followed by the string itself.
     */
    static inline const std::array<std::string, 3>
    rpartition(const std::string& __str, const std::string& __delimiter) noexcept
    {
        std::size_t index = __str.rfind(__delimiter);
        if (index == std::string::npos)
            return {"", "", __str};

        const std::string begin = __str.substr(0, index);
        const std::string end = __str.substr(index + __delimiter.size());

        return {begin, __delimiter, end};
    }

    /**
     * @brief zfill
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

    static inline auto& remove_prefix = removeprefix;
    static inline auto& remove_suffix = removesuffix;
} // namespace ztd
