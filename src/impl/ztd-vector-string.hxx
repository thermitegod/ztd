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
#include <vector>

namespace ztd
{
    /**
     * @brief Split
     *
     * - Splits a std::string at a delimiter, and put substring into a vector.
     *
     * @param[in] __str The std::string to be split
     * @param[in] __delimiter The std::string to be used as a delimiter
     * for splitting
     *
     * @return A std::vector of std::string with the spit tokens and
     * without the delimiter, If delimiter is not found return an
     * empty vector
     */
    static inline std::vector<std::string>
    split(const std::string& __str, const std::string& __delimiter) noexcept
    {
        std::string split_string = __str;
        std::vector<std::string> result;
        while (split_string.size())
        {
            std::size_t index = split_string.find(__delimiter);
            if (index != std::string::npos)
            {
                std::string token = split_string.substr(0, index);
                if (!token.empty())
                    result.push_back(token);
                split_string = split_string.substr(index + __delimiter.size());
                if (split_string.size() == 0)
                    result.push_back(split_string);
            }
            else
            {
                result.push_back(split_string);
                split_string = "";
            }
        }
        return result;
    }

    /**
     * @brief Join
     *
     * - Join elements of a vector into a std::string with a delimiter
     * inserted between the elements
     *
     * @param[in] __tokens The std::vector to be joined
     * @param[in] __delimiter The std::string to be used as a delimiter
     *
     * @return std::string with all the elements and a delimiter
     */
    static inline std::string
    join(const std::vector<std::string>& __tokens, const std::string& __delimiter) noexcept
    {
        std::ostringstream ss;
        for (auto it = __tokens.begin(); it != __tokens.end(); ++it)
        {
            if (it != __tokens.begin())
                ss << __delimiter;
            ss << *it;
        }
        std::string new_string = ss.str();
        return new_string;
    }
} // namespace ztd
