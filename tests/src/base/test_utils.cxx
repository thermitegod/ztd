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

#include <string>
#include <system_error>

#include <cstdint>

#include <doctest/doctest.h>

#include "ztd/detail/utils.hxx"

TEST_SUITE("ztd:: utils" * doctest::description(""))
{
    TEST_CASE("from_string()")
    {
        SUBCASE("OK")
        {
            SUBCASE("positive")
            {
                const std::string str = "100";

                const auto result = ztd::from_string<std::int32_t>(str);

                CHECK(result);
                CHECK_EQ(result.value(), 100);
            }

            SUBCASE("negative")
            {
                const std::string str = "-100";

                const auto result = ztd::from_string<std::int32_t>(str);

                CHECK(result);
                CHECK_EQ(result.value(), -100);
            }
        }

        SUBCASE("Not a number")
        {
            SUBCASE("empty")
            {
                const std::string str;

                const auto result = ztd::from_string<std::int32_t>(str);

                CHECK(bool(!result));
                CHECK_EQ(result.error() == std::errc::invalid_argument, true);
            }

            SUBCASE("mixed trailing")
            {
                const std::string str = "100a";

                const auto result = ztd::from_string<std::int32_t>(str);

                CHECK(bool(!result));
                CHECK_EQ(result.error() == std::errc::invalid_argument, true);
            }

            SUBCASE("mixed leading")
            {
                const std::string str = "a100";

                const auto result = ztd::from_string<std::int32_t>(str);

                CHECK(bool(!result));
                CHECK_EQ(result.error() == std::errc::invalid_argument, true);
            }

            SUBCASE("alpha")
            {
                const std::string str = "ABC";

                const auto result = ztd::from_string<std::int32_t>(str);

                CHECK(bool(!result));
                CHECK_EQ(result.error() == std::errc::invalid_argument, true);
            }
        }

        SUBCASE("overflow")
        {
            SUBCASE("positive")
            {
                const std::string str = "100000000000000000000000000";

                const auto result = ztd::from_string<std::int32_t>(str);

                CHECK(bool(!result));
                CHECK_EQ(result.error() == std::errc::result_out_of_range, true);
            }

            SUBCASE("negative")
            {
                const std::string str = "-100000000000000000000000000";

                const auto result = ztd::from_string<std::int32_t>(str);

                CHECK(bool(!result));
                CHECK_EQ(result.error() == std::errc::result_out_of_range, true);
            }
        }

        SUBCASE("floating point")
        {
            SUBCASE("float")
            {
                const std::string str = "100.0";

                const auto result = ztd::from_string<float>(str);

                CHECK(result);
                CHECK_EQ(result.value(), 100.0f);
            }

            SUBCASE("double")
            {
                const std::string str = "100.0";

                const auto result = ztd::from_string<double>(str);

                CHECK(result);
                CHECK_EQ(result.value(), 100.0f);
            }
        }

        SUBCASE("special cases")
        {
            SUBCASE("newline trailing")
            {
                const std::string str = "100\n";

                const auto result = ztd::from_string<std::int32_t>(str);

                CHECK(result);
                CHECK_EQ(result.value(), 100);
            }

            SUBCASE("newline leading")
            {
                const std::string str = "\n100";

                const auto result = ztd::from_string<std::int32_t>(str);

                CHECK(bool(!result));
                CHECK_EQ(result.error() == std::errc::invalid_argument, true);
            }

            SUBCASE("double newline trailing")
            {
                const std::string str = "100\n\n";

                const auto result = ztd::from_string<std::int32_t>(str);

                CHECK(bool(!result));
                CHECK_EQ(result.error() == std::errc::invalid_argument, true);
            }

            SUBCASE("newline in number")
            {
                const std::string str = "100\n00";

                const auto result = ztd::from_string<std::int32_t>(str);

                CHECK(bool(!result));
                CHECK_EQ(result.error() == std::errc::invalid_argument, true);
            }
        }
    }
}
