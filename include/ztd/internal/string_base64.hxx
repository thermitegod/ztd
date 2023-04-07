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

namespace ztd
{
    /**
     *  @brief base64_decode
     *
     *  - decode base64 string
     *
     * @return decoded base64 string
     */
    [[nodiscard]] const std::string base64_decode(const std::string_view input) noexcept;

    /**
     *  @brief base64_encode
     *
     *  - encode string to base64
     *
     * @return encoded base64 string
     */
    [[nodiscard]] const std::string base64_encode(const std::string_view input) noexcept;
} // namespace ztd
