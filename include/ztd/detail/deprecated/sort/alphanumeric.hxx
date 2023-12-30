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

#include <string_view>

#include <filesystem>

#include <cctype>
#include <cstdlib>

#include "../types.hxx"

namespace ztd::sort
{
namespace detail
{
enum class sort_mode
{
    string,
    number
};

/**
 * Compare l and r with the same semantics as strcmp(), but using
 * the "Alphanum Algorithm". This function is designed to read
 * through the l and r strings only one time, for
 * maximum performance. It does not allocate memory for
 * substrings.
 *
 * @param[in] l left string
 * @param[in] r right string
 *
 * @return negative if left<right, 0 if left==right, positive if left>right.
 */
static i64
alphanumeric_impl(const char* l, const char* r)
{
    sort_mode mode = sort_mode::string;

    while (*l != 0 && *r != 0)
    {
        if (mode == sort_mode::string)
        {
            char l_char = 0;
            char r_char = 0;
            while ((l_char = *l) != 0 && (r_char = *r) != 0)
            {
                // check if this are digit characters
                const bool l_digit = std::isdigit(l_char) != 0;
                const bool r_digit = std::isdigit(r_char) != 0;
                // if both characters are digits, we continue in NUMBER mode
                if (l_digit && r_digit)
                {
                    mode = sort_mode::number;
                    break;
                }
                // if only the left character is a digit, we have a result
                if (l_digit)
                {
                    return -1;
                }
                // if only the right character is a digit, we have a result
                if (r_digit)
                {
                    return +1;
                }
                // compute the difference of both characters
                const i64 diff = l_char - r_char;
                // if they differ we have a result
                if (diff != 0)
                {
                    return diff;
                }
                // otherwise process the next characters
                ++l;
                ++r;
            }
        }
        else // mode==NUMBER
        {
            // get the left number
            char* l_end = nullptr;
            const u64 l_int = std::strtoul(l, &l_end, 0);
            l = l_end;

            // get the right number
            char* r_end = nullptr;
            const u64 r_int = std::strtoul(r, &r_end, 0);
            r = r_end;

            // if the difference is not equal to zero, we have a comparison result
            const i64 diff = l_int - r_int;
            if (diff != 0)
            {
                return diff;
            }

            // otherwise we process the next substring in STRING mode
            mode = sort_mode::string;
        }
    }

    i32 result = 0;
    if (*r != 0)
    {
        result = -1;
    }
    else if (*l != 0)
    {
        result = +1;
    }
    else
    {
        result = 0;
    }
    return result;
}
} // namespace detail

/**
 * Compare l and r with the same semantics as strcmp(), but with
 * the "Alphanum Algorithm" which produces more human-friendly
 * results.
 *
 * @param[in] l left string
 * @param[in] r right string
 *
 * @return negative if left<right, 0 if left==right, positive if left>right.
 */
[[nodiscard]] inline i64
alphanumeric(const std::string_view l, const std::string_view r) noexcept
{
    return detail::alphanumeric_impl(l.data(), r.data());
}

namespace filesystem
{
[[nodiscard]] inline i64
alphanumeric(const std::filesystem::path& l, const std::filesystem::path& r) noexcept
{
    return detail::alphanumeric_impl(l.c_str(), r.c_str());
}
} // namespace filesystem
} // namespace ztd::sort
