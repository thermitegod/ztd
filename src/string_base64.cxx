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

#include <algorithm>

#include "ztd/internal/types.hxx"

#include "ztd/internal/string_base64.hxx"

// clang-format off
static constexpr std::array<unsigned char, 64> Base64CharacterTable{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/',
};
// clang-format on

const std::string
ztd::base64_encode(const std::string_view input) noexcept
{
    std::string output;
    std::array<unsigned char, 3> char_array_3;
    std::array<unsigned char, 4> char_array_4;
    usize i = 0;

    while (i < input.size())
    {
        char_array_3[i % 3] = static_cast<unsigned char>(input[i]);
        i++;

        if (i % 3 == 0)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            std::ranges::transform(char_array_4.cbegin(),
                                   char_array_4.cend(),
                                   std::back_inserter(output),
                                   [](unsigned char c) { return Base64CharacterTable[c]; });
        }
    }

    if (i % 3 != 0)
    {
        for (usize j = i % 3; j < 3; j++)
        {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        std::ranges::transform(char_array_4.cbegin(),
                               char_array_4.cbegin() + (i % 3) + 1,
                               std::back_inserter(output),
                               [](unsigned char c) { return Base64CharacterTable[c]; });

        while ((i % 3) != 0)
        { // base64 padding char
            output += '=';
            i++;
        }
    }

    return output;
}

const std::string
ztd::base64_decode(const std::string_view input) noexcept
{
    std::string output;
    std::array<unsigned char, 3> char_array_3;
    std::array<unsigned char, 4> char_array_4;
    usize i = 0;

    while (i < input.size() && input[i] != '=')
    {
        char_array_4[i % 4] = static_cast<unsigned char>(std::ranges::distance(
            Base64CharacterTable.cbegin(),
            std::ranges::find(Base64CharacterTable.cbegin(), Base64CharacterTable.cend(), input[i])));
        i++;

        if (i % 4 == 0)
        {
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0x0f) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x03) << 6) + char_array_4[3];

            std::copy(char_array_3.cbegin(), char_array_3.cend(), std::back_inserter(output));
        }
    }

    if (i % 4 != 0)
    {
        for (usize j = i % 4; j < 4; j++)
        {
            char_array_4[j] = 0;
        }

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0x0f) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x03) << 6) + char_array_4[3];

        std::copy(char_array_3.cbegin(), char_array_3.cbegin() + (i % 4) - 1, std::back_inserter(output));
    }

    return output;
}
