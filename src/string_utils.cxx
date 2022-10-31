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

#include <string_view>

#include <array>
#include <vector>

#include <ranges>

#include "ztd/internal/types.hxx"

#include "ztd/internal/string_utils.hxx"

i32
ztd::compare(std::string_view str1, std::string_view str2) noexcept
{
    return str1.compare(str2);
}

bool
ztd::contains(std::string_view str, std::string_view sub) noexcept
{
    return (str.find(sub) != std::string_view::npos);
}

bool
ztd::contains(std::string_view str, std::string_view sub, usize start, usize end) noexcept
{
    if (start >= end)
        return false;

    const std::string_view ss{str.substr(start, end)};

    return contains(ss, sub);
}

bool
ztd::contains(std::string_view str, const std::vector<std::string_view>& subs) noexcept
{
    if (subs.empty())
        return false;

    // std::ranges::any_of(subs, [str](std::string_view sub) { return contains(str, sub); });

    for (std::string_view sub : subs)
    {
        if (contains(str, sub))
            return true;
    }
    return false;
}

bool
ztd::contains(std::string_view str, const std::vector<std::string>& subs) noexcept
{
    if (subs.empty())
        return false;

    // std::ranges::any_of(subs, [str](std::string_view sub) { return contains(str, sub); });

    for (std::string_view sub : subs)
    {
        if (contains(str, sub))
            return true;
    }
    return false;
}

bool
ztd::same(std::string_view str1, std::string_view str2) noexcept
{
    return (str1.compare(str2) == 0);
}
