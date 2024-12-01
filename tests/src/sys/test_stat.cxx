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

#include <doctest/doctest.h>

#include <filesystem>

#include <chrono>
#include <system_error>

#include "ztd/detail/sys/stat.hxx"

// TODO
// git does not store file timestamps. need a better way to check atime, etc
// without having meson run a script with every build to change file timestamps.

const std::filesystem::path test_data_path = TEST_DATA_PATH;

const std::filesystem::path test_data_bad_path = test_data_path / "does_not_exist";

const std::filesystem::path test_data_regular_file = test_data_path / "test_data";
const std::filesystem::path test_data_symlink = test_data_path / "test_data_symlink";
const std::filesystem::path test_data_directory = test_data_path / "test_data_directory";
const std::filesystem::path test_data_directory_symlink = test_data_path / "test_data_directory_symlink";
// const std::filesystem::path test_data_socket = test_data_path; // TODO
// const std::filesystem::path test_data_fifo = test_data_path;   // TODO
const std::filesystem::path test_data_block = "/dev/nvme0n1";
const std::filesystem::path test_data_char = "/dev/zero";
// const std::filesystem::path test_data_other = test_data_path;

TEST_SUITE("ztd::stat family" * doctest::description(""))
{
    TEST_CASE("ztd::stat")
    {
        SUBCASE("error throwing")
        {
            CHECK_THROWS(ztd::stat(test_data_path / "does_not_exist"));
        }

        SUBCASE("error ec")
        {
            std::error_code ec1;
            ztd::stat(test_data_path / "does_not_exist", ec1);
            CHECK_EQ(!!ec1, true);

            std::error_code ec2;
            ztd::stat(test_data_regular_file, ec2);
            CHECK_EQ(!!ec2, false);
        }

        SUBCASE("regular file")
        {
            const auto stat = ztd::stat(test_data_regular_file);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), true);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            CHECK_EQ(stat.size(), 102400);
            // CHECK_EQ(stat.size_on_disk(), 1024); // disk compression

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("symlink")
        {
            const auto stat = ztd::stat(test_data_symlink);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), true);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("directory")
        {
            const auto stat = ztd::stat(test_data_directory);

            CHECK_EQ(stat.is_directory(), true);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("directory symlink")
        {
            const auto stat = ztd::stat(test_data_directory_symlink);

            CHECK_EQ(stat.is_directory(), true);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("block")
        {
            const auto stat = ztd::stat(test_data_block);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), true);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            CHECK_EQ(stat.size(), 0);
        }

        SUBCASE("character")
        {
            const auto stat = ztd::stat(test_data_char);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), true);
            CHECK_EQ(stat.is_other(), false);

            CHECK_EQ(stat.size(), 0);
        }
    }

    TEST_CASE("ztd::lstat")
    {
        SUBCASE("error throwing")
        {
            CHECK_THROWS(ztd::lstat(test_data_path / "does_not_exist"));
        }

        SUBCASE("error ec")
        {
            std::error_code ec1;
            ztd::lstat(test_data_path / "does_not_exist", ec1);
            CHECK_EQ(!!ec1, true);

            std::error_code ec2;
            ztd::lstat(test_data_regular_file, ec2);
            CHECK_EQ(!!ec2, false);
        }

        SUBCASE("regular file")
        {
            const auto stat = ztd::lstat(test_data_regular_file);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), true);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            CHECK_EQ(stat.size(), 102400);
            // CHECK_EQ(stat.size_on_disk(), 1024); // disk compression

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("symlink")
        {
            const auto stat = ztd::lstat(test_data_symlink);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), true);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("directory")
        {
            const auto stat = ztd::lstat(test_data_directory);

            CHECK_EQ(stat.is_directory(), true);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("directory symlink")
        {
            const auto stat = ztd::lstat(test_data_directory_symlink);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), true);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("block")
        {
            const auto stat = ztd::lstat(test_data_block);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), true);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            CHECK_EQ(stat.size(), 0);
        }

        SUBCASE("character")
        {
            const auto stat = ztd::lstat(test_data_char);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), true);
            CHECK_EQ(stat.is_other(), false);

            CHECK_EQ(stat.size(), 0);
        }
    }

    TEST_CASE("ztd::statx follow symlinks")
    {
        SUBCASE("error throwing")
        {
            CHECK_THROWS(ztd::statx(test_data_path / "does_not_exist"));
        }

        SUBCASE("error ec")
        {
            std::error_code ec1;
            ztd::statx(test_data_path / "does_not_exist", ec1);
            CHECK_EQ(!!ec1, true);

            std::error_code ec2;
            ztd::statx(test_data_regular_file, ec2);
            CHECK_EQ(!!ec2, false);
        }

        SUBCASE("regular file")
        {
            const auto stat = ztd::statx(test_data_regular_file);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), true);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            CHECK_EQ(stat.size(), 102400);
            // CHECK_EQ(stat.size_on_disk(), 1024); // disk compression

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("symlink")
        {
            const auto stat = ztd::statx(test_data_symlink);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), true);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("directory")
        {
            const auto stat = ztd::statx(test_data_directory);

            CHECK_EQ(stat.is_directory(), true);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("directory symlink")
        {
            const auto stat = ztd::statx(test_data_directory_symlink);

            CHECK_EQ(stat.is_directory(), true);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("block")
        {
            const auto stat = ztd::statx(test_data_block);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), true);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            CHECK_EQ(stat.size(), 0);
        }

        SUBCASE("character")
        {
            const auto stat = ztd::statx(test_data_char);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), true);
            CHECK_EQ(stat.is_other(), false);

            CHECK_EQ(stat.size(), 0);
        }
    }

    TEST_CASE("ztd::statx no follow symlinks")
    {
        SUBCASE("error throwing")
        {
            CHECK_THROWS(ztd::statx(test_data_path / "does_not_exist", ztd::statx::symlink::no_follow));
        }

        SUBCASE("error ec")
        {
            std::error_code ec1;
            ztd::statx(test_data_path / "does_not_exist", ztd::statx::symlink::no_follow, ec1);
            CHECK_EQ(!!ec1, true);

            std::error_code ec2;
            ztd::statx(test_data_regular_file, ztd::statx::symlink::no_follow, ec2);
            CHECK_EQ(!!ec2, false);
        }

        SUBCASE("regular file")
        {
            const auto stat = ztd::statx(test_data_regular_file, ztd::statx::symlink::no_follow);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), true);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            CHECK_EQ(stat.size(), 102400);
            // CHECK_EQ(stat.size_on_disk(), 1024); // disk compression

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("symlink")
        {
            const auto stat = ztd::statx(test_data_symlink, ztd::statx::symlink::no_follow);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), true);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
        }

        SUBCASE("directory")
        {
            const auto stat = ztd::statx(test_data_directory, ztd::statx::symlink::no_follow);

            CHECK_EQ(stat.is_directory(), true);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("directory symlink")
        {
            const auto stat = ztd::statx(test_data_directory_symlink, ztd::statx::symlink::no_follow);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), true);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
            // CHECK_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
        }

        SUBCASE("block")
        {
            const auto stat = ztd::statx(test_data_block, ztd::statx::symlink::no_follow);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), true);
            CHECK_EQ(stat.is_character_file(), false);
            CHECK_EQ(stat.is_other(), false);

            CHECK_EQ(stat.size(), 0);
        }

        SUBCASE("character")
        {
            const auto stat = ztd::statx(test_data_char, ztd::statx::symlink::no_follow);

            CHECK_EQ(stat.is_directory(), false);
            CHECK_EQ(stat.is_regular_file(), false);
            CHECK_EQ(stat.is_symlink(), false);
            CHECK_EQ(stat.is_socket(), false);
            CHECK_EQ(stat.is_fifo(), false);
            CHECK_EQ(stat.is_block_file(), false);
            CHECK_EQ(stat.is_character_file(), true);
            CHECK_EQ(stat.is_other(), false);

            CHECK_EQ(stat.size(), 0);
        }
    }
}
