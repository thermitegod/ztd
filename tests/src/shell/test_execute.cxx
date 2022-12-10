/**
 * Copyright (C) 2022 Brandon Zorn <brandonzorn@cock.li>
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

#include "ztd/ztd.hxx"
#include "ztd/ztd_extra.hxx"

TEST(Execute, ls_stdout)
{
    const std::string command = "ls -d /tmp";

    // ztd::Execute cmd(command);
    const auto cmd = ztd::Execute(command);

    ASSERT_TRUE(ztd::same(ztd::strip(cmd.standard_output()), "/tmp"));
    ASSERT_TRUE(ztd::same(ztd::strip(cmd.standard_error()), ""));
}

TEST(Execute, ls_stderr)
{
    const std::string command = "ls does_not_exist";

    // ztd::Execute cmd(command);
    const auto cmd = ztd::Execute(command);

    // clang-format off
    ASSERT_TRUE(ztd::same(ztd::strip(cmd.standard_output()), ""));
    ASSERT_TRUE(ztd::same(ztd::strip(cmd.standard_error()), "ls: cannot access 'does_not_exist': No such file or directory"));
    // clang-format on
}
