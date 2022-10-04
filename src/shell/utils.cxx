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

#include <string>

#include <fmt/format.h>

#include "ztd/ztd.hxx"

#include "ztd/internal/shell/utils.hxx"

namespace ztd
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
    const std::string
    shell_quote(const std::string& str) noexcept
    {
        if (str.empty())
            return "\"\"";
        return fmt::format("\"{}\"", ztd::replace(str, "\"", "\\\""));
    }
} // namespace ztd
