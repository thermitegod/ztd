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
#include <string_view>

#include <cctype>
#include <cstdlib>

#include "ztd/internal/types.hxx"

#include "ztd/internal/sort/alphanumeric.hxx"

enum class Mode
{
    STRING,
    NUMBER
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
    Mode mode = Mode::STRING;

    while (*l && *r)
    {
        if (mode == Mode::STRING)
        {
            char l_char;
            char r_char;
            while ((l_char = *l) && (r_char = *r))
            {
                // check if this are digit characters
                const bool l_digit = std::isdigit(l_char);
                const bool r_digit = std::isdigit(r_char);
                // if both characters are digits, we continue in NUMBER mode
                if (l_digit && r_digit)
                {
                    mode = Mode::NUMBER;
                    break;
                }
                // if only the left character is a digit, we have a result
                if (l_digit)
                    return -1;
                // if only the right character is a digit, we have a result
                if (r_digit)
                    return +1;
                // compute the difference of both characters
                const i64 diff = l_char - r_char;
                // if they differ we have a result
                if (diff != 0)
                    return diff;
                // otherwise process the next characters
                ++l;
                ++r;
            }
        }
        else // mode==NUMBER
        {
            // get the left number
            char* l_end;
            const u64 l_int = std::strtoul(l, &l_end, 0);
            l = l_end;

            // get the right number
            char* r_end;
            const u64 r_int = std::strtoul(r, &r_end, 0);
            r = r_end;

            // if the difference is not equal to zero, we have a comparison result
            const i64 diff = l_int - r_int;
            if (diff != 0)
                return diff;

            // otherwise we process the next substring in STRING mode
            mode = Mode::STRING;
        }
    }

    if (*r)
        return -1;
    else if (*l)
        return +1;
    else
        return 0;
}

i64
ztd::sort::alphanumeric(std::string_view l, std::string_view r) noexcept
{
    return alphanumeric_impl(l.data(), r.data());
}
