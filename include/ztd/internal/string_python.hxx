/**
 * Copyright (C) 2023 Brandon Zorn <brandonzorn@cock.li>
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

#include <array>
#include <span>
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
[[nodiscard]] const std::vector<std::string> split(const std::string_view str, const std::string_view sep = "",
                                                   ztd::i32 maxsplit = -1) noexcept;

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
[[nodiscard]] const std::vector<std::string> rsplit(const std::string_view str, const std::string_view sep = "",
                                                    ztd::i32 maxsplit = -1) noexcept;

/**
 * @brief join
 *
 * @param[in] span a span of strings to be joined together
 * @param[in] sep separator to be used between elements in the string
 *
 * @return A string which is the concatenation of the strings in vec, with sep
 * inserted between each element.
 */
[[nodiscard]] const std::string join(const std::span<const std::string> span, const std::string_view sep) noexcept;

/**
 * @brief join
 *
 * @param[in] span a span of strings to be joined together
 * @param[in] sep separator to be used between elements in the string
 *
 * @return A string which is the concatenation of the strings in vec, with sep
 * inserted between each element.
 */
[[nodiscard]] const std::string join(const std::span<const std::string_view> span, const std::string_view sep) noexcept;

/**
 * @brief lower
 *
 * @param[in] str The string to be lowercased
 *
 * @return A copy of the string with all the cased characters converted to lowercase.
 */
[[nodiscard]] const std::string lower(const std::string_view str) noexcept;

/**
 * @brief upper
 *
 * @param[in] str The string to be uppercased
 *
 * @return A copy of the string with all the cased characters converted to uppercase.
 */
[[nodiscard]] const std::string upper(const std::string_view str) noexcept;

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
[[nodiscard]] const std::string replace(const std::string_view str, const std::string_view str_find,
                                        const std::string_view str_replace, ztd::i32 count = -1) noexcept;

/**
 * @brief capitalize
 *
 * @param[in] str The string to be capitalized
 *
 * @return A copy of the string with its first character
 * capitalized and the rest lowercased.
 */
[[nodiscard]] const std::string capitalize(const std::string_view str) noexcept;

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
[[nodiscard]] const std::string center(const std::string_view str, u32 width, char fillchar = ' ') noexcept;

/**
 * @brief count
 *
 * @param[in] str The string to be searched
 * @param[in] find substring to count
 *
 * @return The number of non-overlapping occurrences of substring sub
 * in the string
 */
[[nodiscard]] u64 count(const std::string_view str, const std::string_view find) noexcept;

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
[[nodiscard]] u64 count(const std::string_view str, const std::string_view find, usize start,
                        usize end = std::string_view::npos) noexcept;

/**
 * @brief endswith
 *
 * @param[in] str The string to be searched
 * @param[in] suffix suffix to look for
 *
 * @return True if the string ends with the specified suffix,
 * otherwise return False.
 */
[[nodiscard]] bool endswith(const std::string_view str, const std::string_view suffix) noexcept;

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
[[nodiscard]] bool endswith(const std::string_view str, const std::string_view suffix, usize start,
                            usize end = std::string_view::npos) noexcept;

/**
 * @brief endswith
 *
 * @param[in] str The string to be searched
 * @param[in] suffixes suffixes to look for
 *
 * @return True if the string ends with the specified suffix,
 * otherwise return False.
 */
[[nodiscard]] bool endswith(const std::string_view str, const std::span<const std::string> suffixes) noexcept;

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
[[nodiscard]] bool endswith(const std::string_view str, const std::span<const std::string> suffixes, usize start,
                            usize end = std::string_view::npos) noexcept;

/**
 * @brief endswith
 *
 * @param[in] str The string to be searched
 * @param[in] suffixes suffixes to look for
 *
 * @return True if the string ends with the specified suffix,
 * otherwise return False.
 */
[[nodiscard]] bool endswith(const std::string_view str, const std::span<const std::string_view> suffixes) noexcept;

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
[[nodiscard]] bool endswith(const std::string_view str, const std::span<const std::string_view> suffixes, usize start,
                            usize end = std::string_view::npos) noexcept;

/**
 * @brief startswith
 *
 * @param[in] str The string to be searched
 * @param[in] prefix prefix to look for
 *
 * @return True if the string starts with the specified prefix,
 * otherwise return False.
 */
[[nodiscard]] bool startswith(const std::string_view str, const std::string_view prefix) noexcept;

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
[[nodiscard]] bool startswith(const std::string_view str, const std::string_view prefix, usize start,
                              usize end = std::string_view::npos) noexcept;

/**
 * @brief startswith
 *
 * @param[in] str The string to be searched
 * @param[in] prefixes prefixes to look for
 *
 * @return True if the string starts with the specified prefix,
 * otherwise return False.
 */
[[nodiscard]] bool startswith(const std::string_view str, const std::span<const std::string> prefixes) noexcept;

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
[[nodiscard]] bool startswith(const std::string_view str, const std::span<const std::string> prefixes, usize start,
                              usize end = std::string_view::npos) noexcept;

/**
 * @brief startswith
 *
 * @param[in] str The string to be searched
 * @param[in] prefixes prefixes to look for
 *
 * @return True if the string starts with the specified prefix,
 * otherwise return False.
 */
[[nodiscard]] bool startswith(const std::string_view str, const std::span<const std::string_view> prefixes) noexcept;

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
[[nodiscard]] bool startswith(const std::string_view str, const std::span<const std::string_view> prefixes, usize start,
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
[[nodiscard]] const std::string expandtabs(const std::string_view str, u32 tabsize = 8) noexcept;

/**
 * @brief isalnum
 *
 * @param[in] str The string to be checked
 *
 * @return True if all characters in the string are alphanumeric
 * and there is at least one character, otherwise flase.
 */
[[nodiscard]] bool isalnum(const std::string_view str) noexcept;

/**
 * @brief isalpha
 *
 * @param[in] str The string to use
 *
 * @return True if all characters in the string are alphabetic and
 * there is at least one character, False otherwise.
 */
[[nodiscard]] bool isalpha(const std::string_view str) noexcept;

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
[[nodiscard]] bool isascii(const std::string_view str) noexcept;
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
[[nodiscard]] bool isdecimal(const std::string_view str) noexcept;

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
[[nodiscard]] bool islower(const std::string_view str) noexcept;

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
[[nodiscard]] bool isupper(const std::string_view str) noexcept;

/**
 * @brief isspace
 *
 * @param[in] str The string to use
 *
 * @return True if there are only whitespace characters
 * in the string and there is at least one character,
 * False otherwise.
 */
[[nodiscard]] bool isspace(const std::string_view str) noexcept;

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
[[nodiscard]] bool istitle(const std::string_view str) noexcept;

/**
 * @brief title
 *
 * @param[in] str The string to use
 *
 * @return A titlecased version of the string where words
 * start with an uppercase character and the remaining
 * characters are lowercase.
 */
[[nodiscard]] const std::string title(const std::string_view str) noexcept;

/**
 * @brief swapcase
 *
 * @param[in] str The string to use
 *
 * @return the string with uppercase characters converted
 * to lowercase and vice versa. Note that it is not necessarily
 * true that swapcase(swapcase(s)) == s.
 */
[[nodiscard]] const std::string swapcase(const std::string_view str) noexcept;

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
[[nodiscard]] const std::string ljust(const std::string_view str, usize width, char fillchar = ' ') noexcept;

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
[[nodiscard]] const std::string rjust(const std::string_view str, usize width, char fillchar = ' ') noexcept;

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
[[nodiscard]] const std::string lstrip(const std::string_view str, const std::string_view chars = " \r\n\t") noexcept;

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
[[nodiscard]] const std::string rstrip(const std::string_view str, const std::string_view chars = " \r\n\t") noexcept;

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
[[nodiscard]] const std::string strip(const std::string_view str, const std::string_view chars = " \r\n\t") noexcept;

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
[[nodiscard]] const std::string removeprefix(const std::string_view str, const std::string_view prefix) noexcept;

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
[[nodiscard]] const std::string removesuffix(const std::string_view str, const std::string_view suffix) noexcept;

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
[[nodiscard]] const std::array<std::string, 3> partition(const std::string_view str,
                                                         const std::string_view sep) noexcept;

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
[[nodiscard]] const std::array<std::string, 3> rpartition(const std::string_view str,
                                                          const std::string_view sep) noexcept;

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
[[nodiscard]] const std::vector<std::string> splitlines(const std::string_view str, bool keepends = false) noexcept;
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
[[nodiscard]] const std::string zfill(const std::string_view str, usize width) noexcept;
} // namespace ztd
