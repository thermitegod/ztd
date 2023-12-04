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

#include <filesystem>

namespace ztd::program
{
/**
 * @brief Program Executable
 *
 * @return Current executing program path
 */
[[nodiscard]] const std::filesystem::path exe() noexcept;

/**
 * @brief Program Name
 *
 * @return Current executing program name
 */
[[nodiscard]] const std::string name() noexcept;
} // namespace ztd::program
