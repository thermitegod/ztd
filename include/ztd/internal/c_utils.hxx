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

namespace ztd
{
/**
 * @brief Null Check
 *
 * - Checks if the char* is NULL and if it is return an empty std::string.
 * Setting a std::string to NULL is UB and, nobody likes segfaults
 *
 * @param[in] str The char* to be checked for NULL
 *
 * @return an empty std::string if char* is NULL
 */
[[nodiscard]] const std::string null_check(const char* str) noexcept;
} // namespace ztd
