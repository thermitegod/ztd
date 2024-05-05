/**
 * Copyright (C) 2024 Brandon Zorn <brandonzorn@cock.li>
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

#include <gtest/gtest.h>

#include <string>
#include <string_view>

#include <vector>

#include "ztd/detail/string_base64.hxx"

/**
 * base64 encode and decode internal
 */

TEST(base64, encode_decode__empty)
{
    std::string input = "";
    std::string encoded = ztd::base64_encode(input);
    std::string decoded = ztd::base64_decode(encoded);

    ASSERT_EQ(input, decoded);
}

TEST(base64, encode_decode)
{
    const std::string input =
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed et risus ac felis posuere mattis. Pellentesque "
        "semper mi nunc, at efficitur tellus facilisis quis. Suspendisse euismod massa in lacus commodo varius. Nulla "
        "facilisi. Nulla bibendum eget lectus id consectetur. Sed eu velit tristique, elementum dolor in, vehicula "
        "leo. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Cras vel "
        "sagittis nisl. Nulla facilisi. Proin congue mauris enim, eget maximus sapien tristique eu.";

    std::string encoded = ztd::base64_encode(input);
    std::string decoded = ztd::base64_decode(encoded);

    ASSERT_EQ(input, decoded);
}

/**
 * base64 decode external
 */
TEST(base64, decode_string)
{
    const std::string input =
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed et risus ac felis posuere mattis. Pellentesque "
        "semper mi nunc, at efficitur tellus facilisis quis. Suspendisse euismod massa in lacus commodo varius. Nulla "
        "facilisi. Nulla bibendum eget lectus id consectetur. Sed eu velit tristique, elementum dolor in, vehicula "
        "leo. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Cras vel "
        "sagittis nisl. Nulla facilisi. Proin congue mauris enim, eget maximus sapien tristique eu.";

    const std::string external_encoded =
        "TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQsIGNvbnNlY3RldHVyIGFkaXBpc2NpbmcgZWxpdC4gU2VkIGV0IHJpc3VzIGFjIGZlbGlzIHBvc3"
        "VlcmUgbWF0dGlzLiBQZWxsZW50ZXNxdWUgc2VtcGVyIG1pIG51bmMsIGF0IGVmZmljaXR1ciB0ZWxsdXMgZmFjaWxpc2lzIHF1aXMuIFN1c3Bl"
        "bmRpc3NlIGV1aXNtb2QgbWFzc2EgaW4gbGFjdXMgY29tbW9kbyB2YXJpdXMuIE51bGxhIGZhY2lsaXNpLiBOdWxsYSBiaWJlbmR1bSBlZ2V0IG"
        "xlY3R1cyBpZCBjb25zZWN0ZXR1ci4gU2VkIGV1IHZlbGl0IHRyaXN0aXF1ZSwgZWxlbWVudHVtIGRvbG9yIGluLCB2ZWhpY3VsYSBsZW8uIFZl"
        "c3RpYnVsdW0gYW50ZSBpcHN1bSBwcmltaXMgaW4gZmF1Y2lidXMgb3JjaSBsdWN0dXMgZXQgdWx0cmljZXMgcG9zdWVyZSBjdWJpbGlhIGN1cm"
        "FlOyBDcmFzIHZlbCBzYWdpdHRpcyBuaXNsLiBOdWxsYSBmYWNpbGlzaS4gUHJvaW4gY29uZ3VlIG1hdXJpcyBlbmltLCBlZ2V0IG1heGltdXMg"
        "c2FwaWVuIHRyaXN0aXF1ZSBldS4=";

    // std::string encoded = base64_encode(input);
    std::string decoded = ztd::base64_decode(external_encoded);

    ASSERT_EQ(input, decoded);
}

/**
 * base64 encode external
 */
TEST(base64, encode_string)
{
    const std::string input =
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed et risus ac felis posuere mattis. Pellentesque "
        "semper mi nunc, at efficitur tellus facilisis quis. Suspendisse euismod massa in lacus commodo varius. Nulla "
        "facilisi. Nulla bibendum eget lectus id consectetur. Sed eu velit tristique, elementum dolor in, vehicula "
        "leo. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Cras vel "
        "sagittis nisl. Nulla facilisi. Proin congue mauris enim, eget maximus sapien tristique eu.";

    const std::string external_encoded =
        "TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQsIGNvbnNlY3RldHVyIGFkaXBpc2NpbmcgZWxpdC4gU2VkIGV0IHJpc3VzIGFjIGZlbGlzIHBvc3"
        "VlcmUgbWF0dGlzLiBQZWxsZW50ZXNxdWUgc2VtcGVyIG1pIG51bmMsIGF0IGVmZmljaXR1ciB0ZWxsdXMgZmFjaWxpc2lzIHF1aXMuIFN1c3Bl"
        "bmRpc3NlIGV1aXNtb2QgbWFzc2EgaW4gbGFjdXMgY29tbW9kbyB2YXJpdXMuIE51bGxhIGZhY2lsaXNpLiBOdWxsYSBiaWJlbmR1bSBlZ2V0IG"
        "xlY3R1cyBpZCBjb25zZWN0ZXR1ci4gU2VkIGV1IHZlbGl0IHRyaXN0aXF1ZSwgZWxlbWVudHVtIGRvbG9yIGluLCB2ZWhpY3VsYSBsZW8uIFZl"
        "c3RpYnVsdW0gYW50ZSBpcHN1bSBwcmltaXMgaW4gZmF1Y2lidXMgb3JjaSBsdWN0dXMgZXQgdWx0cmljZXMgcG9zdWVyZSBjdWJpbGlhIGN1cm"
        "FlOyBDcmFzIHZlbCBzYWdpdHRpcyBuaXNsLiBOdWxsYSBmYWNpbGlzaS4gUHJvaW4gY29uZ3VlIG1hdXJpcyBlbmltLCBlZ2V0IG1heGltdXMg"
        "c2FwaWVuIHRyaXN0aXF1ZSBldS4=";

    std::string encoded = ztd::base64_encode(input);
    // std::string decoded = base64_decode(encoded);

    ASSERT_EQ(encoded, external_encoded);
}
