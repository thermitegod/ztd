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

#include "../../../src/ztd.hxx"
#include "../../../src/ztd-shell.hxx"

TEST(shell, utils)
{
    const std::string q = ztd::shell_quote("file with spaces.txt");

    ASSERT_TRUE(ztd::same(q, "\"file with spaces.txt\""));
}

TEST(shell, utils__empty)
{
    const std::string q = ztd::shell_quote("");

    ASSERT_TRUE(ztd::same(q, "\"\""));
}

TEST(shell, utils__double_quote_in_name)
{
    const std::string q = ztd::shell_quote("a\".txt");

    ASSERT_TRUE(ztd::same(q, "\"a\\\".txt\""));
}
