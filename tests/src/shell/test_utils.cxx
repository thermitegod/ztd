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

TEST(shell, utils)
{
    const std::string q = ztd::shell::quote("file with spaces.txt");

    EXPECT_EQ(q, "\"file with spaces.txt\"");
}

TEST(shell, utils__empty)
{
    const std::string q = ztd::shell::quote("");

    EXPECT_EQ(q, "\"\"");
}

TEST(shell, utils__double_quote_in_name)
{
    const std::string q = ztd::shell::quote("a\".txt");

    EXPECT_EQ(q, "\"a\\\".txt\"");
}

#endif
