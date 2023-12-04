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

#include "types.hxx"

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
[[nodiscard]] ztd::i32 compare(const std::string_view str1, const std::string_view str2) noexcept;

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
[[nodiscard]] bool contains(const std::string_view str, const std::string_view sub) noexcept;

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
[[nodiscard]] bool contains(const std::string_view str, const std::string_view sub, usize start,
                            usize end = std::string_view::npos) noexcept;

/**
 * @brief Contains
 *
 * - Check if the string containes any of the substring string in the span
 *
 * @param[in] str The string to be searched
 * @param[in] subs The span of string to look for
 *
 * @return true if the string str containes any of the
 * substrings in subs
 */
[[nodiscard]] bool contains(const std::string_view str, const std::span<const std::string_view> subs) noexcept;

/**
 * @brief Contains
 *
 * - Check if the string containes any of the substring string in the span
 *
 * @param[in] str The string to be searched
 * @param[in] subs The span of string to look for
 *
 * @return true if the string str containes any of the
 * substrings in subs
 */
[[nodiscard]] bool contains(const std::string_view str, const std::span<const std::string> subs) noexcept;

/**
 * @brief Contains
 *
 * - Check if any of the strings in the span match the string
 *
 * @param[in] subs The span to be searched
 * @param[in] str The string to look for
 *
 * @return true if the span containes the string
 */
[[nodiscard]] bool contains(const std::span<const std::string> subs, const std::string_view str) noexcept;

/**
 * @brief Contains
 *
 * - Check if any of the strings in the span match the string
 *
 * @param[in] subs The span to be searched
 * @param[in] str The string to look for
 *
 * @return true if the span containes the string
 */
[[nodiscard]] bool contains(const std::span<const std::string_view> subs, const std::string_view str) noexcept;

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
[[nodiscard]] bool same(const std::string_view str1, const std::string_view str2) noexcept;
} // namespace ztd
