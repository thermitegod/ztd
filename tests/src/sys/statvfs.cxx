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

#include <expected>
#include <filesystem>
#include <system_error>

#include <doctest/doctest.h>

#include "ztd/detail/sys/statvfs.hxx"

TEST_SUITE("ztd::statvfs")
{
    TEST_CASE("create")
    {
        SUBCASE("current path")
        {
            const auto result = ztd::statvfs::create(std::filesystem::current_path());
            REQUIRE(result.has_value());

            struct ::statvfs expected{};
            REQUIRE(::statvfs(std::filesystem::current_path().c_str(), &expected) == 0);

            CHECK(result->bsize() == expected.f_bsize);
            CHECK(result->frsize() == expected.f_frsize);
            CHECK(result->blocks() == expected.f_blocks);
            CHECK(result->bfree() == expected.f_bfree);
            CHECK(result->bavail() == expected.f_bavail);
            CHECK(result->files() == expected.f_files);
            CHECK(result->ffree() == expected.f_ffree);
            CHECK(result->favail() == expected.f_favail);
            CHECK(result->fsid() == expected.f_fsid);
            CHECK(result->flag() == expected.f_flag);
            CHECK(result->namemax() == expected.f_namemax);
            CHECK(result->type() == expected.f_type);
        }

        SUBCASE("nonexistent path")
        {
            const auto result = ztd::statvfs::create("/nonexistent/path/");

            REQUIRE_FALSE(result.has_value());
            CHECK(result.error() == std::errc::no_such_file_or_directory);
        }

        SUBCASE("empty path")
        {
            const auto result = ztd::statvfs::create(std::filesystem::path{});

            REQUIRE_FALSE(result.has_value());
            CHECK(result.error() == std::errc::no_such_file_or_directory);
        }
    }
}
