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

TEST_SUITE("ztd::stat family" * doctest::description(""))
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
            CHECK_EQ(stat1.has_value(), false);
            CHECK_EQ(stat1.error(), std::errc(2));

            const auto stat2 = ztd::stat::create(test_data_regular_file);
            CHECK_EQ(stat2.has_value(), true);
        }

        SUBCASE("regular file")
        {
            const auto stat = ztd::stat::create(test_data_regular_file);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), true);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            CHECK_EQ(s.size(), 102400);
            // CHECK_EQ(s.size_on_disk(), 1024); // disk compression

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("symlink")
        {
            const auto stat = ztd::stat::create(test_data_symlink);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), true);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("directory")
        {
            const auto stat = ztd::stat::create(test_data_directory);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), true);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("directory symlink")
        {
            const auto stat = ztd::stat::create(test_data_directory_symlink);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), true);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("block")
        {
            const auto stat = ztd::stat::create(test_data_block);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), true);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), true);

            CHECK_EQ(s.size(), 0);
        }

        SUBCASE("character")
        {
            const auto stat = ztd::stat::create(test_data_char);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), true);
            CHECK_EQ(s.is_other(), true);

            CHECK_EQ(s.size(), 0);
        }
    }

    TEST_CASE("ztd::lstat")
    {
        SUBCASE("create()")
        {
            const auto stat1 = ztd::lstat::create(test_data_path / "does_not_exist");
            CHECK_EQ(stat1.has_value(), false);
            CHECK_EQ(stat1.error(), std::errc(2));

            const auto stat2 = ztd::lstat::create(test_data_regular_file);
            CHECK_EQ(stat2.has_value(), true);
        }

        SUBCASE("regular file")
        {
            const auto stat = ztd::lstat::create(test_data_regular_file);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), true);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            CHECK_EQ(s.size(), 102400);
            // CHECK_EQ(s.size_on_disk(), 1024); // disk compression

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("symlink")
        {
            const auto stat = ztd::lstat::create(test_data_symlink);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), true);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("directory")
        {
            const auto stat = ztd::lstat::create(test_data_directory);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), true);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("directory symlink")
        {
            const auto stat = ztd::lstat::create(test_data_directory_symlink);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), true);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("block")
        {
            const auto stat = ztd::lstat::create(test_data_block);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), true);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), true);

            CHECK_EQ(s.size(), 0);
        }

        SUBCASE("character")
        {
            const auto stat = ztd::lstat::create(test_data_char);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), true);
            CHECK_EQ(s.is_other(), true);

            CHECK_EQ(s.size(), 0);
        }
    }

    TEST_CASE("ztd::statx follow symlinks")
    {
        SUBCASE("create()")
        {
            const auto stat1 = ztd::statx::create(test_data_path / "does_not_exist");
            CHECK_EQ(stat1.has_value(), false);
            CHECK_EQ(stat1.error(), std::errc(2));

            const auto stat2 = ztd::statx::create(test_data_regular_file);
            CHECK_EQ(stat2.has_value(), true);
        }

        SUBCASE("regular file")
        {
            const auto stat = ztd::statx::create(test_data_regular_file);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), true);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            CHECK_EQ(s.size(), 102400);
            // CHECK_EQ(s.size_on_disk(), 1024); // disk compression

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("symlink")
        {
            const auto stat = ztd::statx::create(test_data_symlink);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), true);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("directory")
        {
            const auto stat = ztd::statx::create(test_data_directory);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), true);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("directory symlink")
        {
            const auto stat = ztd::statx::create(test_data_directory_symlink);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), true);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("block")
        {
            const auto stat = ztd::statx::create(test_data_block);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), true);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), true);

            CHECK_EQ(s.size(), 0);
        }

        SUBCASE("character")
        {
            const auto stat = ztd::statx::create(test_data_char);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), true);
            CHECK_EQ(s.is_other(), true);

            CHECK_EQ(s.size(), 0);
        }
    }

    TEST_CASE("ztd::statx no follow symlinks")
    {
        SUBCASE("create()")
        {
            const auto stat1 = ztd::statx::create(test_data_path / "does_not_exist",
                                                  ztd::statx::symlink::no_follow);
            CHECK_EQ(stat1.has_value(), false);
            CHECK_EQ(stat1.error(), std::errc(2));

            const auto stat2 =
                ztd::statx::create(test_data_regular_file, ztd::statx::symlink::no_follow);
            CHECK_EQ(stat2.has_value(), true);
        }

        SUBCASE("regular file")
        {
            const auto stat =
                ztd::statx::create(test_data_regular_file, ztd::statx::symlink::no_follow);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), true);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            CHECK_EQ(s.size(), 102400);
            // CHECK_EQ(s.size_on_disk(), 1024); // disk compression

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("symlink")
        {
            const auto stat = ztd::statx::create(test_data_symlink, ztd::statx::symlink::no_follow);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), true);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("directory")
        {
            const auto stat =
                ztd::statx::create(test_data_directory, ztd::statx::symlink::no_follow);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), true);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("directory symlink")
        {
            const auto stat =
                ztd::statx::create(test_data_directory_symlink, ztd::statx::symlink::no_follow);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), true);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("block")
        {
            const auto stat = ztd::statx::create(test_data_block, ztd::statx::symlink::no_follow);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), true);
            CHECK_EQ(s.is_character_file(), false);
            CHECK_EQ(s.is_other(), true);

            CHECK_EQ(s.size(), 0);
        }

        SUBCASE("character")
        {
            const auto stat = ztd::statx::create(test_data_char, ztd::statx::symlink::no_follow);
            REQUIRE_EQ(stat.has_value(), true);

            const auto& s = stat.value();

            CHECK_EQ(s.is_directory(), false);
            CHECK_EQ(s.is_regular_file(), false);
            CHECK_EQ(s.is_symlink(), false);
            CHECK_EQ(s.is_socket(), false);
            CHECK_EQ(s.is_fifo(), false);
            CHECK_EQ(s.is_block_file(), false);
            CHECK_EQ(s.is_character_file(), true);
            CHECK_EQ(s.is_other(), true);

            CHECK_EQ(s.size(), 0);
        }
    }
}
