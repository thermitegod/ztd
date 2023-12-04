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

namespace ztd::shell
{
/**
 * @brief Shell Quote
 *
 * - quote string so that is will work with ztd::Execute
 *
 * @param[in] str The string to be quoted
 *
 * @return a quoted string, if string is empty returns empty quotes
 */
[[nodiscard]] const std::string quote(const std::string_view str) noexcept;
} // namespace ztd::shell
