/**
 * Copyright (C) 2024 Brandon Zorn <brandonzorn@cock.li>
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

#include <filesystem>

#include <array>

#include <cstdlib>

#include "../../types.hxx"

namespace ztd::sort
{
namespace detail
{
inline constexpr std::array<i64, 3> ints{-1, 0, 1};
} // namespace detail

/**
 * Compare l and r randomly.
 *
 * @param[in] l left string
 * @param[in] r right string
 *
 * @return random -1, 0, 1.
 */
[[nodiscard]] inline i64
random(const std::string_view l, const std::string_view r) noexcept
{
    (void)l;
    (void)r;

    return detail::ints.at(std::rand() % detail::ints.size());
}

namespace filesystem
{
[[nodiscard]] inline i64
random(const std::filesystem::path& l, const std::filesystem::path& r) noexcept
{
    (void)l;
    (void)r;

    return detail::ints.at(std::rand() % detail::ints.size());
}
} // namespace filesystem
} // namespace ztd::sort
