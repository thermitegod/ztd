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

#include <string>

#include <doctest/doctest.h>

#include "ztd/detail/string_base64.hxx"

// clang-format off
static const std::string PLAIN_TEXT =
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed et risus ac felis posuere mattis. Pellentesque "
    "semper mi nunc, at efficitur tellus facilisis quis. Suspendisse euismod massa in lacus commodo varius. Nulla "
    "facilisi. Nulla bibendum eget lectus id consectetur. Sed eu velit tristique, elementum dolor in, vehicula "
    "leo. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Cras vel "
    "sagittis nisl. Nulla facilisi. Proin congue mauris enim, eget maximus sapien tristique eu.";

static const std::string BASE64_TEXT =
    "TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQsIGNvbnNlY3RldHVyIGFkaXBpc2NpbmcgZWxpdC4gU2VkIGV0IHJpc3VzIGFjIGZlbGlzIHBvc3"
    "VlcmUgbWF0dGlzLiBQZWxsZW50ZXNxdWUgc2VtcGVyIG1pIG51bmMsIGF0IGVmZmljaXR1ciB0ZWxsdXMgZmFjaWxpc2lzIHF1aXMuIFN1c3Bl"
    "bmRpc3NlIGV1aXNtb2QgbWFzc2EgaW4gbGFjdXMgY29tbW9kbyB2YXJpdXMuIE51bGxhIGZhY2lsaXNpLiBOdWxsYSBiaWJlbmR1bSBlZ2V0IG"
    "xlY3R1cyBpZCBjb25zZWN0ZXR1ci4gU2VkIGV1IHZlbGl0IHRyaXN0aXF1ZSwgZWxlbWVudHVtIGRvbG9yIGluLCB2ZWhpY3VsYSBsZW8uIFZl"
    "c3RpYnVsdW0gYW50ZSBpcHN1bSBwcmltaXMgaW4gZmF1Y2lidXMgb3JjaSBsdWN0dXMgZXQgdWx0cmljZXMgcG9zdWVyZSBjdWJpbGlhIGN1cm"
    "FlOyBDcmFzIHZlbCBzYWdpdHRpcyBuaXNsLiBOdWxsYSBmYWNpbGlzaS4gUHJvaW4gY29uZ3VlIG1hdXJpcyBlbmltLCBlZ2V0IG1heGltdXMg"
    "c2FwaWVuIHRyaXN0aXF1ZSBldS4=";
// clang-format on

TEST_SUITE("ztd::base64" * doctest::description(""))
{
    TEST_CASE("encode/decode empty")
    {
        std::string input;
        const auto encoded = ztd::base64_encode(input);
        const auto decoded = ztd::base64_decode(encoded);

        CHECK_EQ(input, decoded);
    }

    TEST_CASE("encode/decode")
    {
        const auto encoded = ztd::base64_encode(PLAIN_TEXT);
        const auto decoded = ztd::base64_decode(encoded);

        CHECK_EQ(PLAIN_TEXT, decoded);
    }

    TEST_CASE("decode")
    {
        const auto decoded = ztd::base64_decode(BASE64_TEXT);

        CHECK_EQ(PLAIN_TEXT, decoded);
    }

    TEST_CASE("encode")
    {
        const auto encoded = ztd::base64_encode(PLAIN_TEXT);

        CHECK_EQ(BASE64_TEXT, encoded);
    }
}
