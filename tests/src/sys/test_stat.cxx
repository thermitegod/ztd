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

#include <gtest/gtest.h>

#include <filesystem>

#include <chrono>
#include <system_error>

#include "ztd/ztd.hxx"

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

/**
 * ztd::stat
 */

TEST(stat, error_throwing)
{
    EXPECT_ANY_THROW(ztd::stat(test_data_path / "does_not_exist"));
}

TEST(stat, error_ec)
{
    std::error_code ec1;
    ztd::stat(test_data_path / "does_not_exist", ec1);
    EXPECT_TRUE(ec1);

    std::error_code ec2;
    ztd::stat(test_data_regular_file, ec2);
    EXPECT_FALSE(ec2);
}

TEST(stat, regular_file)
{
    const auto stat = ztd::stat(test_data_regular_file);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_TRUE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    EXPECT_EQ(stat.size(), 102400);
    // EXPECT_EQ(stat.size_on_disk(), 1024); // disk compression

    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
}

TEST(stat, symlink)
{
    const auto stat = ztd::stat(test_data_symlink);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_TRUE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
}

TEST(stat, directory)
{
    const auto stat = ztd::stat(test_data_directory);

    EXPECT_TRUE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
}

TEST(stat, directory_symlink)
{
    const auto stat = ztd::stat(test_data_directory_symlink);

    EXPECT_TRUE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
}

TEST(stat, block)
{
    const auto stat = ztd::stat(test_data_block);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_TRUE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_TRUE(stat.is_other());

    EXPECT_EQ(stat.size(), 0);
}

TEST(stat, character)
{
    const auto stat = ztd::stat(test_data_char);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_TRUE(stat.is_character_file());
    EXPECT_TRUE(stat.is_other());

    EXPECT_EQ(stat.size(), 0);
}

/**
 * ztd::lstat
 */

TEST(lstat, error_throwing)
{
    EXPECT_ANY_THROW(ztd::lstat(test_data_path / "does_not_exist"));
}

TEST(lstat, error_ec)
{
    std::error_code ec1;
    ztd::lstat(test_data_path / "does_not_exist", ec1);
    EXPECT_TRUE(ec1);

    std::error_code ec2;
    ztd::lstat(test_data_regular_file, ec2);
    EXPECT_FALSE(ec2);
}

TEST(lstat, regular_file)
{
    const auto stat = ztd::lstat(test_data_regular_file);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_TRUE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    EXPECT_EQ(stat.size(), 102400);
    // EXPECT_EQ(stat.size_on_disk(), 1024); // disk compression

    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
}

TEST(lstat, symlink)
{
    const auto stat = ztd::lstat(test_data_symlink);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_TRUE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861807);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861807);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861807);
}

TEST(lstat, directory)
{
    const auto stat = ztd::lstat(test_data_directory);

    EXPECT_TRUE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
}

TEST(lstat, directory_symlink)
{
    const auto stat = ztd::lstat(test_data_directory_symlink);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_TRUE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861799);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861799);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861799);
}

TEST(lstat, block)
{
    const auto stat = ztd::lstat(test_data_block);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_TRUE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_TRUE(stat.is_other());

    EXPECT_EQ(stat.size(), 0);
}

TEST(lstat, character)
{
    const auto stat = ztd::lstat(test_data_char);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_TRUE(stat.is_character_file());
    EXPECT_TRUE(stat.is_other());

    EXPECT_EQ(stat.size(), 0);
}

/**
 * ztd::statx follow symlinks
 */

TEST(statx, follow__error_throwing)
{
    EXPECT_ANY_THROW(ztd::statx(test_data_path / "does_not_exist"));
}

TEST(statx, follow__error_ec)
{
    std::error_code ec1;
    ztd::statx(test_data_path / "does_not_exist", ec1);
    EXPECT_TRUE(ec1);

    std::error_code ec2;
    ztd::statx(test_data_regular_file, ec2);
    EXPECT_FALSE(ec2);
}

TEST(statx, follow__regular_file)
{
    const auto stat = ztd::statx(test_data_regular_file);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_TRUE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    EXPECT_EQ(stat.size(), 102400);
    // EXPECT_EQ(stat.size_on_disk(), 1024); // disk compression

    // CT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
    // CT_EQ(std::chrono::system_clock::to_time_t(stat.btime()), 1702861781);
    // CT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
    // CT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
}

TEST(statx, follow__symlink)
{
    const auto stat = ztd::statx(test_data_symlink);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_TRUE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.btime()), 1702861781);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
}

TEST(statx, follow__directory)
{
    const auto stat = ztd::statx(test_data_directory);

    EXPECT_TRUE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.btime()), 1702861788);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
}

TEST(statx, follow__directory_symlink)
{
    const auto stat = ztd::statx(test_data_directory_symlink);

    EXPECT_TRUE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.btime()), 1702861781);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
}

TEST(statx, follow__block)
{
    const auto stat = ztd::stat(test_data_block);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_TRUE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_TRUE(stat.is_other());

    EXPECT_EQ(stat.size(), 0);
}

TEST(statx, follow__character)
{
    const auto stat = ztd::stat(test_data_char);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_TRUE(stat.is_character_file());
    EXPECT_TRUE(stat.is_other());

    EXPECT_EQ(stat.size(), 0);
}

/**
 * ztd::statx no follow symlinks
 */

TEST(statx, error_throwing)
{
    EXPECT_ANY_THROW(ztd::statx(test_data_path / "does_not_exist", ztd::statx::symlink::no_follow));
}

TEST(statx, error_ec)
{
    std::error_code ec1;
    ztd::statx(test_data_path / "does_not_exist", ztd::statx::symlink::no_follow, ec1);
    EXPECT_TRUE(ec1);

    std::error_code ec2;
    ztd::statx(test_data_regular_file, ztd::statx::symlink::no_follow, ec2);
    EXPECT_FALSE(ec2);
}

TEST(statx, no_follow__regular_file)
{
    const auto stat = ztd::statx(test_data_regular_file, ztd::statx::symlink::no_follow);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_TRUE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    EXPECT_EQ(stat.size(), 102400);
    // EXPECT_EQ(stat.size_on_disk(), 1024); // disk compression

    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861781);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861781);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861781);
}

TEST(statx, no_follow__symlink)
{
    const auto stat = ztd::statx(test_data_symlink, ztd::statx::symlink::no_follow);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_TRUE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861807);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861807);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861807);
}

TEST(statx, no_follow__directory)
{
    const auto stat = ztd::statx(test_data_directory, ztd::statx::symlink::no_follow);

    EXPECT_TRUE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861788);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861788);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861788);
}

TEST(statx, no_follow__directory_symlink)
{
    const auto stat = ztd::statx(test_data_directory_symlink, ztd::statx::symlink::no_follow);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_TRUE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_FALSE(stat.is_other());

    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.atime()), 1702861799);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.ctime()), 1702861799);
    // EXPECT_EQ(std::chrono::system_clock::to_time_t(stat.mtime()), 1702861799);
}

TEST(statx, no_follow__block)
{
    const auto stat = ztd::statx(test_data_block, ztd::statx::symlink::no_follow);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_TRUE(stat.is_block_file());
    EXPECT_FALSE(stat.is_character_file());
    EXPECT_TRUE(stat.is_other());

    EXPECT_EQ(stat.size(), 0);
}

TEST(statx, no_follow__character)
{
    const auto stat = ztd::statx(test_data_char, ztd::statx::symlink::no_follow);

    EXPECT_FALSE(stat.is_directory());
    EXPECT_FALSE(stat.is_regular_file());
    EXPECT_FALSE(stat.is_symlink());
    EXPECT_FALSE(stat.is_socket());
    EXPECT_FALSE(stat.is_fifo());
    EXPECT_FALSE(stat.is_block_file());
    EXPECT_TRUE(stat.is_character_file());
    EXPECT_TRUE(stat.is_other());

    EXPECT_EQ(stat.size(), 0);
}
