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

#include <string_view>

#include <span>

#include <algorithm>
#include <ranges>

#include "ztd/internal/types.hxx"

#include "ztd/internal/string_utils.hxx"

i32
ztd::compare(const std::string_view str1, const std::string_view str2) noexcept
{
    return str1.compare(str2);
}

bool
ztd::contains(const std::string_view str, const std::string_view sub) noexcept
{
    return (str.find(sub) != std::string_view::npos);
}

bool
ztd::contains(const std::string_view str, const std::string_view sub, usize start, usize end) noexcept
{
    if (start >= end)
    {
        return false;
    }
    return contains(str.substr(start, end), sub);
}

bool
ztd::contains(const std::string_view str, const std::span<const std::string_view> subs) noexcept
{
    const auto check = [str](const std::string_view sub) { return contains(str, sub); };
    return std::ranges::any_of(subs, check);
}

bool
ztd::contains(const std::string_view str, const std::span<const std::string> subs) noexcept
{
    const auto check = [str](const std::string_view sub) { return contains(str, sub); };
    return std::ranges::any_of(subs, check);
}

bool
ztd::contains(const std::span<const std::string> subs, const std::string_view str) noexcept
{
    return (std::ranges::find(subs.begin(), subs.end(), str) != subs.end());
}

bool
ztd::contains(const std::span<const std::string_view> subs, const std::string_view str) noexcept
{
    return (std::ranges::find(subs.begin(), subs.end(), str) != subs.end());
}

bool
ztd::same(const std::string_view str1, const std::string_view str2) noexcept
{
    return (str1.compare(str2) == 0);
}
