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

#pragma once

#include <string>
#include <string_view>

#include <array>
#include <vector>

#include "types.hxx"

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
    const std::vector<std::string> split(std::string_view str, std::string_view sep = "", i32 maxsplit = -1) noexcept;

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
    const std::vector<std::string> rsplit(std::string_view str, std::string_view sep = "", i32 maxsplit = -1) noexcept;

    /**
     * @brief join
     *
     * @param[in] iterable vector of string to be joined together
     * @param[in] sep separator to be used between elements in the string
     *
     * @return A string which is the concatenation of the strings in iterable, with sep
     * inserted between each element.
     */
    const std::string join(const std::vector<std::string>& iterable, std::string_view sep) noexcept;

    /**
     * @brief join
     *
     * @param[in] iterable vector of string to be joined together
     * @param[in] sep separator to be used between elements in the string
     *
     * @return A string which is the concatenation of the strings in iterable, with sep
     * inserted between each element.
     */
    const std::string join(const std::vector<std::string_view>& iterable, std::string_view sep) noexcept;

    /**
     * @brief lower
     *
     * @param[in] str The string to be lowercased
     *
     * @return A copy of the string with all the cased characters converted to lowercase.
     */
    const std::string lower(std::string_view str) noexcept;

    /**
     * @brief upper
     *
     * @param[in] str The string to be uppercased
     *
     * @return A copy of the string with all the cased characters converted to uppercase.
     */
    const std::string upper(std::string_view str) noexcept;

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
    const std::string replace(std::string_view str, std::string_view str_find, std::string_view str_replace,
                              i32 count = -1) noexcept;

    /**
     * @brief capitalize
     *
     * @param[in] str The string to be capitalized
     *
     * @return A copy of the string with its first character
     * capitalized and the rest lowercased.
     */
    const std::string capitalize(std::string_view str) noexcept;

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
    const std::string center(std::string_view str, u32 width, char fillchar = ' ') noexcept;

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
    u64 count(std::string_view str, std::string_view find, usize start = 0,
              usize end = std::string_view::npos) noexcept;

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
    bool endswith(std::string_view str, std::string_view suffix, usize start = 0,
                  usize end = std::string_view::npos) noexcept;

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
    bool endswith(std::string_view str, const std::vector<std::string>& suffixes, usize start = 0,
                  usize end = std::string_view::npos) noexcept;

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
    bool endswith(std::string_view str, const std::vector<std::string_view>& suffixes, usize start = 0,
                  usize end = std::string_view::npos) noexcept;

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
    bool startswith(std::string_view str, std::string_view prefix, usize start = 0,
                    usize end = std::string_view::npos) noexcept;

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
    bool startswith(std::string_view str, const std::vector<std::string>& prefixes, usize start = 0,
                    usize end = std::string_view::npos) noexcept;

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
    bool startswith(std::string_view str, const std::vector<std::string_view>& prefixes, usize start = 0,
                    usize end = std::string_view::npos) noexcept;

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
    const std::string expandtabs(std::string_view str, u32 tabsize = 8) noexcept;

    /**
     * @brief isalnum
     *
     * @param[in] str The string to be checked
     *
     * @return True if all characters in the string are alphanumeric
     * and there is at least one character, otherwise flase.
     */
    bool isalnum(std::string_view str) noexcept;

    /**
     * @brief isalpha
     *
     * @param[in] str The string to use
     *
     * @return True if all characters in the string are alphabetic and
     * there is at least one character, False otherwise.
     */
    bool isalpha(std::string_view str) noexcept;

    /**
     * @brief isdigit
     *
     * @param[in] str The string to use
     *
     * @return True if all characters in the string are digits
     * and there is at least one character, False otherwise.
     */
    bool isdigit(std::string_view str) noexcept;

    /**
     * @brief islower
     *
     * @param[in] str The string to use
     *
     * @return True if all cased characters in the string are
     * lowercase and there is at least one cased character,
     * False otherwise.
     */
    bool islower(std::string_view str) noexcept;

    /**
     * @brief isupper
     *
     * @param[in] str The string to use
     *
     * @return True if all cased characters in the string are
     * uppercase and there is at least one cased character,
     * False otherwise.
     */
    bool isupper(std::string_view str) noexcept;

    /**
     * @brief isspace
     *
     * @param[in] str The string to use
     *
     * @return True if there are only whitespace characters
     * in the string and there is at least one character,
     * False otherwise.
     */
    bool isspace(std::string_view str) noexcept;

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
    bool istitle(std::string_view str) noexcept;

    /**
     * @brief title
     *
     * @param[in] str The string to use
     *
     * @return A titlecased version of the string where words
     * start with an uppercase character and the remaining
     * characters are lowercase.
     */
    const std::string title(std::string_view str) noexcept;

    /**
     * @brief swapcase
     *
     * @param[in] str The string to use
     *
     * @return the string with uppercase characters converted
     * to lowercase and vice versa. Note that it is not necessarily
     * true that swapcase(swapcase(s)) == s.
     */
    const std::string swapcase(std::string_view str) noexcept;

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
    const std::string ljust(std::string_view str, usize width, char fillchar = ' ') noexcept;

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
    const std::string rjust(std::string_view str, usize width, char fillchar = ' ') noexcept;

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
    const std::string lstrip(std::string_view str, std::string_view chars = " \r\n\t") noexcept;

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
    const std::string rstrip(std::string_view str, std::string_view chars = " \r\n\t") noexcept;

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
    const std::string strip(std::string_view str, std::string_view chars = " \r\n\t") noexcept;

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
    const std::string removeprefix(std::string_view str, std::string_view prefix) noexcept;

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
    const std::string removesuffix(std::string_view str, std::string_view suffix) noexcept;

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
    const std::array<std::string, 3> partition(std::string_view str, std::string_view sep) noexcept;

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
    const std::array<std::string, 3> rpartition(std::string_view str, std::string_view sep) noexcept;

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
    const std::string zfill(std::string_view str, usize width) noexcept;
} // namespace ztd
