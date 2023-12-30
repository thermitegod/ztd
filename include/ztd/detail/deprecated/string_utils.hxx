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

#include <span>

#include <algorithm>

#include "../types.hxx"

namespace ztd
{
/**
 *  @brief  Compare to a string.
 *
 *  Returns an integer < 0 if str2 is ordered before
 *  str1, 0 if their values are equivalent, or > 0 if this
 *  string is ordered after str1.
 *
 * @param[in] str1 The string to be compared
 * @param[in] str2 The other string to be compared
 *
 * @return Integer < 0, 0, or > 0.
 */
[[deprecated("use std::string::compare")]] [[nodiscard]] inline i32
compare(const std::string_view str1, const std::string_view str2) noexcept
{
    return str1.compare(str2);
}

/**
 * @brief Contains
 *
 * - Check if the string contains the supplied substring
 *
 * @param[in] str The string to be searched
 * @param[in] sub Substring to look for
 *
 * @return true if the string contains the supplied substring, otherwise false.
 */
[[deprecated("use std::string::contains")]] [[nodiscard]] inline bool
contains(const std::string_view str, const std::string_view sub) noexcept
{
#if defined(__cpp_lib_string_contains)
    return str.contains(sub);
#else
    return (str.find(sub) != std::string_view::npos);
#endif
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
[[deprecated("use std::string::contains")]] [[nodiscard]] inline bool
contains(const std::string_view str, const std::string_view sub, usize start,
         usize end = std::string_view::npos) noexcept
{
    if (start >= end)
    {
        return false;
    }

#if defined(__cpp_lib_string_contains)
    return str.substr(start, end).contains(sub);
#else
    return contains(str.substr(start, end), sub);
#endif
}

/**
 * @brief Contains
 *
 * - Check if the string contains any of the substring string in the span
 *
 * @param[in] str The string to be searched
 * @param[in] subs The span of string to look for
 *
 * @return true if the string str contains any of the
 * substrings in subs
 */
[[deprecated("use std::ranges::contains")]] [[nodiscard]] inline bool
contains(const std::string_view str, const std::span<const std::string_view> subs) noexcept
{
#if defined(__cpp_lib_string_contains)
    const auto check = [str](const std::string_view sub) { return str.contains(sub); };
#else
    const auto check = [str](const std::string_view sub) { return contains(str, sub); };
#endif

    return std::ranges::any_of(subs, check);
}

/**
 * @brief Contains
 *
 * - Check if the string contains any of the substring string in the span
 *
 * @param[in] str The string to be searched
 * @param[in] subs The span of string to look for
 *
 * @return true if the string str contains any of the
 * substrings in subs
 */
[[deprecated("use std::ranges::contains")]] [[nodiscard]] inline bool
contains(const std::string_view str, const std::span<const std::string> subs) noexcept
{
#if defined(__cpp_lib_string_contains)
    const auto check = [str](const std::string_view sub) { return str.contains(sub); };
#else
    const auto check = [str](const std::string_view sub) { return contains(str, sub); };
#endif

    return std::ranges::any_of(subs, check);
}

/**
 * @brief Contains
 *
 * - Check if any of the strings in the span match the string
 *
 * @param[in] subs The span to be searched
 * @param[in] str The string to look for
 *
 * @return true if the span contains the string
 */
[[deprecated("use std::ranges::contains")]] [[nodiscard]] inline bool
contains(const std::span<const std::string> subs, const std::string_view str) noexcept
{
#if defined(__cpp_lib_ranges_contains)
    return std::ranges::contains(subs, str);
#else
    return std::ranges::find(subs.begin(), subs.end(), str) != subs.end();
#endif
}

/**
 * @brief Contains
 *
 * - Check if any of the strings in the span match the string
 *
 * @param[in] subs The span to be searched
 * @param[in] str The string to look for
 *
 * @return true if the span contains the string
 */
[[deprecated("use std::ranges::contains")]] [[nodiscard]] inline bool
contains(const std::span<const std::string_view> subs, const std::string_view str) noexcept
{
#if defined(__cpp_lib_ranges_contains)
    return std::ranges::contains(subs, str);
#else
    return std::ranges::find(subs.begin(), subs.end(), str) != subs.end();
#endif
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
[[deprecated("use operator==")]] [[nodiscard]] inline bool
same(const std::string_view str1, const std::string_view str2) noexcept
{
    return (str1.compare(str2) == 0);
}
} // namespace ztd
