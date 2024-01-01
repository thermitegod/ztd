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

#if (ZTD_VERSION == 1)

#include <gtest/gtest.h>

#include <string>
#include <string_view>

#include <vector>

#include <algorithm>
#include <ranges>

#include "ztd/ztd.hxx"

#if 0
// just run the test suite multiple times
TEST(sort, random_manual)
{
    EXPECT_TRUE(ztd::sort::random("a", "a") == 0);
}
#endif

TEST(sort, random__loop_check)
{
    const i64 rand_res = ztd::sort::random("a", "a");

    // statistically this should never fail
    for (usize i = 0; i < 100; ++i)
    {
        const i64 rand_res2 = ztd::sort::random("a", "a");

        if (rand_res != rand_res2)
        {
            return;
        }
    }
    EXPECT_TRUE(false);
}

#endif
