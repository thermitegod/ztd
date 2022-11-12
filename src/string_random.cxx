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

#include <string>
#include <string_view>

#include <array>

#include "ztd/internal/types.hxx"

#include "ztd/internal/random.hxx"
#include "ztd/internal/string_random.hxx"

// clang-format off
static constexpr std::array<char, 62> AlphanumCharacterTable{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',

    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z',

    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z',
};
// clang-format on

static const std::string
random_string(usize len, u32 charset_num) noexcept
{
    std::string str;
    str.reserve(len);
    while (str.size() < len)
    {
        str += AlphanumCharacterTable.at(ztd::urand() % charset_num);
    }
    return str;
}

const std::string
ztd::randhex(usize len) noexcept
{
    return random_string(len, 16);
}

const std::string
ztd::randstr(usize len) noexcept
{
    return random_string(len, AlphanumCharacterTable.size());
}
