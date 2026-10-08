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

#include <chrono>
#include <filesystem>
#include <system_error>

#include <cassert>

#include <doctest/doctest.h>

#include "ztd/detail/sys/stat.hxx"

// TODO
// git does not store file timestamps. need a better way to check atime, etc
// without having meson run a script with every build to change file timestamps.

const std::filesystem::path test_data_path = TEST_DATA_PATH;

const std::filesystem::path test_data_bad_path = test_data_path / "does_not_exist";

const std::filesystem::path test_data_regular_file = test_data_path / "test_data";
const std::filesystem::path test_data_symlink = test_data_path / "test_data_symlink";
const std::filesystem::path test_data_directory = test_data_path / "test_data_directory";
const std::filesystem::path test_data_directory_symlink =
    test_data_path / "test_data_directory_symlink";
// const std::filesystem::path test_data_socket = test_data_path; // TODO
// const std::filesystem::path test_data_fifo = test_data_path;   // TODO
const std::filesystem::path test_data_block = "/dev/nvme0n1";
const std::filesystem::path test_data_char = "/dev/zero";
// const std::filesystem::path test_data_other = test_data_path;

TEST_SUITE("ztd::stat family")
{
    TEST_CASE("ztd::stat")
    {
        assert(std::filesystem::exists(test_data_path) == true);
        assert(std::filesystem::exists(test_data_bad_path) == false);
        assert(std::filesystem::exists(test_data_regular_file) == true);
        assert(std::filesystem::exists(test_data_symlink) == true);
        assert(std::filesystem::exists(test_data_directory) == true);
        assert(std::filesystem::exists(test_data_directory_symlink) == true);
        // assert(std::filesystem::exists(test_data_socket) == true);
        // assert(std::filesystem::exists(test_data_fifo) == true);
        assert(std::filesystem::exists(test_data_block) == true);
        assert(std::filesystem::exists(test_data_char) == true);
        // assert(std::filesystem::exists(test_data_other) == true);

        SUBCASE("create()")
        {
            const auto stat1 = ztd::stat::create(test_data_path / "does_not_exist");
            CHECK_FALSE(stat1.has_value());
            CHECK(stat1.error() == std::errc(2));

            const auto stat2 = ztd::stat::create(test_data_regular_file);
            CHECK(stat2.has_value());
        }

        SUBCASE("regular file")
        {
            const auto stat = ztd::stat::create(test_data_regular_file);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());

            CHECK(s.size() == 102400);
        }

        SUBCASE("symlink")
        {
            const auto stat = ztd::stat::create(test_data_symlink);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());
        }

        SUBCASE("directory")
        {
            const auto stat = ztd::stat::create(test_data_directory);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());
        }

        SUBCASE("directory symlink")
        {
            const auto stat = ztd::stat::create(test_data_directory_symlink);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());
        }

        SUBCASE("block")
        {
            const auto stat = ztd::stat::create(test_data_block);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK(s.is_other());

            CHECK(s.size() == 0);
        }

        SUBCASE("character")
        {
            const auto stat = ztd::stat::create(test_data_char);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK(s.is_character_file());
            CHECK(s.is_other());

            CHECK(s.size() == 0);
        }
    }

    TEST_CASE("ztd::lstat")
    {
        SUBCASE("create()")
        {
            const auto stat1 = ztd::lstat::create(test_data_path / "does_not_exist");
            CHECK_FALSE(stat1.has_value());
            CHECK(stat1.error() == std::errc(2));

            const auto stat2 = ztd::lstat::create(test_data_regular_file);
            CHECK(stat2.has_value());
        }

        SUBCASE("regular file")
        {
            const auto stat = ztd::lstat::create(test_data_regular_file);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());

            CHECK(s.size() == 102400);
        }

        SUBCASE("symlink")
        {
            const auto stat = ztd::lstat::create(test_data_symlink);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());
        }

        SUBCASE("directory")
        {
            const auto stat = ztd::lstat::create(test_data_directory);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());
        }

        SUBCASE("directory symlink")
        {
            const auto stat = ztd::lstat::create(test_data_directory_symlink);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());
        }

        SUBCASE("block")
        {
            const auto stat = ztd::lstat::create(test_data_block);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK(s.is_other());

            CHECK(s.size() == 0);
        }

        SUBCASE("character")
        {
            const auto stat = ztd::lstat::create(test_data_char);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK(s.is_character_file());
            CHECK(s.is_other());

            CHECK(s.size() == 0);
        }
    }

    TEST_CASE("ztd::statx follow symlinks")
    {
        SUBCASE("create()")
        {
            const auto stat1 = ztd::statx::create(test_data_path / "does_not_exist");
            CHECK_FALSE(stat1.has_value());
            CHECK(stat1.error() == std::errc(2));

            const auto stat2 = ztd::statx::create(test_data_regular_file);
            CHECK(stat2.has_value());
        }

        SUBCASE("regular file")
        {
            const auto stat = ztd::statx::create(test_data_regular_file);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());

            CHECK(s.size() == 102400);
        }

        SUBCASE("symlink")
        {
            const auto stat = ztd::statx::create(test_data_symlink);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());
        }

        SUBCASE("directory")
        {
            const auto stat = ztd::statx::create(test_data_directory);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());
        }

        SUBCASE("directory symlink")
        {
            const auto stat = ztd::statx::create(test_data_directory_symlink);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());
        }

        SUBCASE("block")
        {
            const auto stat = ztd::statx::create(test_data_block);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK(s.is_other());

            CHECK(s.size() == 0);
        }

        SUBCASE("character")
        {
            const auto stat = ztd::statx::create(test_data_char);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK(s.is_character_file());
            CHECK(s.is_other());

            CHECK(s.size() == 0);
        }
    }

    TEST_CASE("ztd::statx no follow symlinks")
    {
        SUBCASE("create()")
        {
            const auto stat1 = ztd::statx::create(test_data_path / "does_not_exist",
                                                  ztd::statx::symlink::no_follow);
            CHECK_FALSE(stat1.has_value());
            CHECK(stat1.error() == std::errc(2));

            const auto stat2 =
                ztd::statx::create(test_data_regular_file, ztd::statx::symlink::no_follow);
            CHECK(stat2.has_value());
        }

        SUBCASE("regular file")
        {
            const auto stat =
                ztd::statx::create(test_data_regular_file, ztd::statx::symlink::no_follow);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());

            CHECK(s.size() == 102400);
        }

        SUBCASE("symlink")
        {
            const auto stat = ztd::statx::create(test_data_symlink, ztd::statx::symlink::no_follow);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());
        }

        SUBCASE("directory")
        {
            const auto stat =
                ztd::statx::create(test_data_directory, ztd::statx::symlink::no_follow);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());
        }

        SUBCASE("directory symlink")
        {
            const auto stat =
                ztd::statx::create(test_data_directory_symlink, ztd::statx::symlink::no_follow);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK_FALSE(s.is_other());
        }

        SUBCASE("block")
        {
            const auto stat = ztd::statx::create(test_data_block, ztd::statx::symlink::no_follow);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK(s.is_block_file());
            CHECK_FALSE(s.is_character_file());
            CHECK(s.is_other());

            CHECK(s.size() == 0);
        }

        SUBCASE("character")
        {
            const auto stat = ztd::statx::create(test_data_char, ztd::statx::symlink::no_follow);
            REQUIRE(stat.has_value());

            const auto& s = stat.value();

            CHECK_FALSE(s.is_directory());
            CHECK_FALSE(s.is_regular_file());
            CHECK_FALSE(s.is_symlink());
            CHECK_FALSE(s.is_socket());
            CHECK_FALSE(s.is_fifo());
            CHECK_FALSE(s.is_block_file());
            CHECK(s.is_character_file());
            CHECK(s.is_other());

            CHECK(s.size() == 0);
        }
    }
}
