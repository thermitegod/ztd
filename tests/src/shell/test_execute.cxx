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

#if (ZTD_VERSION == 1)

#include <gtest/gtest.h>

#include <string>

#include "ztd/ztd.hxx"

TEST(Execute, ls_stdout)
{
    const std::string command = "ls -d /tmp";

    // ztd::Execute cmd(command);
    const auto cmd = ztd::shell::Execute(command);

    EXPECT_EQ(ztd::strip(cmd.standard_output()), "/tmp");
    EXPECT_EQ(ztd::strip(cmd.standard_error()), "");
}

TEST(Execute, ls_stderr)
{
    const std::string command = "ls does_not_exist";

    // ztd::Execute cmd(command);
    const auto cmd = ztd::shell::Execute(command);

    EXPECT_EQ(ztd::strip(cmd.standard_output()), "");
    EXPECT_EQ(ztd::strip(cmd.standard_error()), "ls: cannot access 'does_not_exist': No such file or directory");
}

#endif
