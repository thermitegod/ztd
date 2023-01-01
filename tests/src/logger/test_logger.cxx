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

#if 0

#include <gtest/gtest.h>

#include <string>

#include "ztd/ztd.hxx"

TEST(Logger, init)
{
    bool double_init_fail = false;

    ztd::Logger->initialize();
    try
    {
        ztd::Logger->initialize();
    }
    catch (const ztd::LoggerException& e)
    {
        double_init_fail = true;
    }

    EXPECT_TRUE(double_init_fail);
}

#endif
