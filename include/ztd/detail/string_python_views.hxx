/**
 * Copyright (C) 2026 Brandon Zorn <brandonzorn@cock.li>
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
#include <string_view>
#include <vector>

#include "types.hxx"

namespace ztd::views
{
/**
 * @brief split, non owning view.
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
[[nodiscard]] constexpr std::vector<std::string_view>
split(std::string_view str, std::string_view sep = "", ztd::i32 maxsplit = -1_i32) noexcept
{
    if (str.empty() || sep.empty() || maxsplit == 0_i32)
    {
        return {str};
    }

    std::vector<std::string_view> result;
    auto remaining = str;
    while (maxsplit < 0_i32 || result.size() < maxsplit)
    {
        const auto pos = remaining.find(sep);
        if (pos == std::string_view::npos)
        {
            break;
        }

        result.emplace_back(remaining.substr(0, pos));
        remaining.remove_prefix(pos + sep.size());
    }

    result.emplace_back(remaining);
    return result;
}
} // namespace ztd::views
