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

#pragma once

#include <string>

#include <filesystem>

#include "../types.hxx"

namespace ztd
{
    /**
     * @brief Program Executable
     *
     * @return Current executing program path
     */
    const std::string program_executable() noexcept;

    /**
     * @brief Program Name
     *
     * @return Current executing program name
     */
    const std::string program_name() noexcept;
} // namespace ztd
