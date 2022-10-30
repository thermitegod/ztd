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
#include <string_view>

#include <cstdlib>

#include "types.hxx"

namespace ztd
{
    /**
     * @brief randhex
     *
     * - std::srand must be seeded before calling
     *
     * @param[in] len Length of the random string to return
     *
     * @return Get a random hex string
     */
    const std::string randhex(usize len) noexcept;

    /**
     * @brief randhex
     *
     * - std::srand must be seeded before calling
     *
     * @param[in] len Length of the random string to return
     *
     * @return Get a random hex string
     */
    const std::string randstr(usize len) noexcept;
} // namespace ztd
