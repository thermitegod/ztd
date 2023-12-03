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

#include <filesystem>

#include "../types.hxx"

namespace ztd::sort
{
/**
 * Compare l and r with the same semantics as strcmp(), but with
 * the "Alphanum Algorithm" which produces more human-friendly
 * results.
 *
 * @param[in] l left string
 * @param[in] r right string
 *
 * @return negative if left<right, 0 if left==right, positive if left>right.
 */
[[nodiscard]] ztd::i64 alphanumeric(const std::string_view l, const std::string_view r) noexcept;

namespace filesystem
{
[[nodiscard]] ztd::i64 alphanumeric(const std::filesystem::path& l, const std::filesystem::path& r) noexcept;
}
} // namespace ztd::sort
