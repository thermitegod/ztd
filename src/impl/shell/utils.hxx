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

#ifndef ZTD_SHELL_HEADER
#error "Only <ztd-shell.hxx> can be included directly"
#endif

#pragma once

#include <string>

#include <fmt/format.h>

#include "../../ztd.hxx"

// #define ZTD_MAIN_HEADER
// #include "../string.hxx"
// #undef ZTD_MAIN_HEADER

namespace ztd
{
    /**
     * @brief Shell Quote
     *
     * - quote string so that is will work with ztd::Execute
     *
     * @param[in] __str The string to be quoted
     *
     * @return a quoted string, if string is empty returns empty quotes
     */
    static inline const std::string
    shell_quote(const std::string& __str) noexcept
    {
        if (__str.empty())
            return "\"\"";
        return fmt::format("\"{}\"", ztd::replace(__str, "\"", "\\\""));
    }
} // namespace ztd
