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

#ifndef ZTD_MAIN_HEADER
#error "Only <ztd.hxx> can be included directly"
#endif

#pragma once

#include <string>
#include <string_view>

#include <cstdlib>

namespace ztd
{
    namespace
    {
        static inline const std::string
        _private_rand_str(std::size_t len, std::string_view chars) noexcept
        {
            std::string str;
            str.reserve(len);

            for (std::size_t i = 0; i < len; ++i) { str += chars.at(std::rand() % chars.size()); }

            return str;
        }
    } // namespace

    /**
     * @brief randhex
     *
     * - std::srand must be seeded before calling
     *
     * @param[in] len Length of the random string to return
     *
     * @return Get a random hex string
     */
    static inline const std::string
    randhex(std::size_t len) noexcept
    {
        static const std::string chars_hex = "0123456789abcdef";

        return _private_rand_str(len, chars_hex);
    }

    /**
     * @brief randhex
     *
     * - std::srand must be seeded before calling
     *
     * @param[in] len Length of the random string to return
     *
     * @return Get a random hex string
     */
    static inline const std::string
    randstr(std::size_t len) noexcept
    {
        static const std::string chars_alphanum = "0123456789"
                                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                  "abcdefghijklmnopqrstuvwxyz";

        return _private_rand_str(len, chars_alphanum);
    }
} // namespace ztd
