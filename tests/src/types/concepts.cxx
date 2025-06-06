/**
 * Copyright (C) 2025 Brandon Zorn <brandonzorn@cock.li>
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

#include <cstddef>

#include <doctest/doctest.h>

#include "ztd/detail/types.hxx"

TEST_SUITE("integer<T>" * doctest::description(""))
{
    TEST_CASE("type traits")
    {
        SUBCASE("is_integer")
        {
            CHECK(ztd::detail::is_integer<std::uint8_t>);
            CHECK(ztd::detail::is_integer<std::uint16_t>);
            CHECK(ztd::detail::is_integer<std::uint32_t>);
            CHECK(ztd::detail::is_integer<std::uint64_t>);
            CHECK(ztd::detail::is_integer<std::size_t>);

            CHECK(ztd::detail::is_integer<std::int8_t>);
            CHECK(ztd::detail::is_integer<std::int16_t>);
            CHECK(ztd::detail::is_integer<std::int32_t>);
            CHECK(ztd::detail::is_integer<std::int64_t>);
            CHECK(ztd::detail::is_integer<std::ptrdiff_t>);

            CHECK_FALSE(ztd::detail::is_integer<char>);
            CHECK_FALSE(ztd::detail::is_integer<bool>);
        }

        SUBCASE("is_signed_integer")
        {
            CHECK_FALSE(ztd::detail::is_signed_integer<std::uint8_t>);
            CHECK_FALSE(ztd::detail::is_signed_integer<std::uint16_t>);
            CHECK_FALSE(ztd::detail::is_signed_integer<std::uint32_t>);
            CHECK_FALSE(ztd::detail::is_signed_integer<std::uint64_t>);
            CHECK_FALSE(ztd::detail::is_signed_integer<std::size_t>);

            CHECK(ztd::detail::is_signed_integer<std::int8_t>);
            CHECK(ztd::detail::is_signed_integer<std::int16_t>);
            CHECK(ztd::detail::is_signed_integer<std::int32_t>);
            CHECK(ztd::detail::is_signed_integer<std::int64_t>);
            CHECK(ztd::detail::is_signed_integer<std::ptrdiff_t>);
        }

        SUBCASE("is_unsigned_integer")
        {
            CHECK(ztd::detail::is_unsigned_integer<std::uint8_t>);
            CHECK(ztd::detail::is_unsigned_integer<std::uint16_t>);
            CHECK(ztd::detail::is_unsigned_integer<std::uint32_t>);
            CHECK(ztd::detail::is_unsigned_integer<std::uint64_t>);
            CHECK(ztd::detail::is_unsigned_integer<std::size_t>);

            CHECK_FALSE(ztd::detail::is_unsigned_integer<std::int8_t>);
            CHECK_FALSE(ztd::detail::is_unsigned_integer<std::int16_t>);
            CHECK_FALSE(ztd::detail::is_unsigned_integer<std::int32_t>);
            CHECK_FALSE(ztd::detail::is_unsigned_integer<std::int64_t>);
            CHECK_FALSE(ztd::detail::is_unsigned_integer<std::ptrdiff_t>);
        }

        SUBCASE("is_integer_conversion_safe")
        {
            SUBCASE("from std::uint8_t")
            {
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint8_t, std::uint8_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint8_t, std::uint16_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint8_t, std::uint32_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint8_t, std::uint64_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint8_t, std::size_t>);

                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint8_t, std::int8_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint8_t, std::int16_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint8_t, std::int32_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint8_t, std::int64_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint8_t, std::ptrdiff_t>);
            }

            SUBCASE("from std::uint16_t")
            {
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint16_t, std::uint8_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint16_t, std::uint16_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint16_t, std::uint32_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint16_t, std::uint64_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint16_t, std::size_t>);

                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint16_t, std::int8_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint16_t, std::int16_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint16_t, std::int32_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint16_t, std::int64_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint16_t, std::ptrdiff_t>);
            }

            SUBCASE("from std::uint32_t")
            {
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint32_t, std::uint8_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint32_t, std::uint16_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint32_t, std::uint32_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint32_t, std::uint64_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint32_t, std::size_t>);

                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint32_t, std::int8_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint32_t, std::int16_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint32_t, std::int32_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint32_t, std::int64_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint32_t, std::ptrdiff_t>);
            }

            SUBCASE("from std::uint64_t")
            {
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint64_t, std::uint8_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint64_t, std::uint16_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint64_t, std::uint32_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint64_t, std::uint64_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::uint64_t, std::size_t>);

                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint64_t, std::int8_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint64_t, std::int16_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint64_t, std::int32_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint64_t, std::int64_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::uint64_t, std::ptrdiff_t>);
            }

            SUBCASE("from std::size_t")
            {
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::size_t, std::uint8_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::size_t, std::uint16_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::size_t, std::uint32_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::size_t, std::uint64_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::size_t, std::size_t>);

                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::size_t, std::int8_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::size_t, std::int16_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::size_t, std::int32_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::size_t, std::int64_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::size_t, std::ptrdiff_t>);
            }

            SUBCASE("from std::int8_t")
            {
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int8_t, std::uint8_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int8_t, std::uint16_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int8_t, std::uint32_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int8_t, std::uint64_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int8_t, std::size_t>);

                CHECK(ztd::detail::is_integer_conversion_safe<std::int8_t, std::int8_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::int8_t, std::int16_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::int8_t, std::int32_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::int8_t, std::int64_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::int8_t, std::ptrdiff_t>);
            }

            SUBCASE("from std::int16_t")
            {
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int16_t, std::uint8_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int16_t, std::uint16_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int16_t, std::uint32_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int16_t, std::uint64_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int16_t, std::size_t>);

                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int16_t, std::int8_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::int16_t, std::int16_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::int16_t, std::int32_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::int16_t, std::int64_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::int16_t, std::ptrdiff_t>);
            }

            SUBCASE("from std::int32_t")
            {
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int32_t, std::uint8_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int32_t, std::uint16_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int32_t, std::uint32_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int32_t, std::uint64_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int32_t, std::size_t>);

                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int32_t, std::int8_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int32_t, std::int16_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::int32_t, std::int32_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::int32_t, std::int64_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::int32_t, std::ptrdiff_t>);
            }

            SUBCASE("from std::int64_t")
            {
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int64_t, std::uint8_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int64_t, std::uint16_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int64_t, std::uint32_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int64_t, std::uint64_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int64_t, std::size_t>);

                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int64_t, std::int8_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int64_t, std::int16_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::int64_t, std::int32_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::int64_t, std::int64_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::int64_t, std::ptrdiff_t>);
            }

            SUBCASE("from std::ptrdiff_t")
            {
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::ptrdiff_t, std::uint8_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::ptrdiff_t, std::uint16_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::ptrdiff_t, std::uint32_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::ptrdiff_t, std::uint64_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::ptrdiff_t, std::size_t>);

                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::ptrdiff_t, std::int8_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::ptrdiff_t, std::int16_t>);
                CHECK_FALSE(ztd::detail::is_integer_conversion_safe<std::ptrdiff_t, std::int32_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::ptrdiff_t, std::int64_t>);
                CHECK(ztd::detail::is_integer_conversion_safe<std::ptrdiff_t, std::ptrdiff_t>);
            }
        }
    }
}
