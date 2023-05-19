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

#include <string>
#include <string_view>

#include <filesystem>

#include <array>

#include <cstdlib>

#include "ztd/internal/types.hxx"

#include "ztd/internal/sort/random.hxx"

inline constexpr std::array<i64, 3> ints{-1, 0, 1};

i64
ztd::sort::random(const std::string_view l, const std::string_view r) noexcept
{
    (void)l;
    (void)r;

    return ints.at(std::rand() % ints.size());
}

i64
ztd::sort::filesystem::random(const std::filesystem::path& l, const std::filesystem::path& r) noexcept
{
    (void)l;
    (void)r;

    return ints.at(std::rand() % ints.size());
}
