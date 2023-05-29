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

#include <type_traits>

#include "ztd/ztd.hxx"

/**
 * irand
 */

TEST(random, irand)
{
    // auto x = 420_u8;
    // EXPECT_TRUE((std::is_same<decltype(x), ztd::u8>::value));

    const auto result = ztd::irand();
    EXPECT_TRUE((std::is_same<decltype(result), ztd::i64>::value));
}

TEST(random, irand__min__max)
{
    // auto x = 420_u8;
    // EXPECT_TRUE((std::is_same<decltype(x), ztd::u8>::value));

    const auto result = ztd::irand(0, 10);
    EXPECT_TRUE(result >= 0 && result <= 10);
}

/**
 * urand
 */

TEST(random, urand)
{
    // auto x = 420_u8;
    // EXPECT_TRUE((std::is_same<decltype(x), ztd::u8>::value));

    const auto result = ztd::urand();
    EXPECT_TRUE((std::is_same<decltype(result), ztd::u64>::value));
}

TEST(random, urand__min__max)
{
    // auto x = 420_u8;
    // EXPECT_TRUE((std::is_same<decltype(x), ztd::u8>::value));

    const auto result = ztd::urand(0, 10);
    EXPECT_TRUE(result >= 0 && result <= 10);
}
