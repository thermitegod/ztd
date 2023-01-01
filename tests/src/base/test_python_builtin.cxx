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

#include <string>
#include <string_view>

#include <array>

#include "ztd/ztd.hxx"

/**
 * sorted array
 */
TEST(python_builtin, sorted__array_string)
{
    using namespace std::literals::string_literals;

    const auto result = ztd::sorted(std::array{
        "iii"s, "ppp"s, "ddd"s, "www"s, "sss"s, "vvv"s, "kkk"s, "qqq"s, "ooo"s, "nnn"s, "aaa"s, "yyy"s, "eee"s,
        "xxx"s, "ttt"s, "uuu"s, "ccc"s, "jjj"s, "hhh"s, "fff"s, "zzz"s, "mmm"s, "ggg"s, "bbb"s, "lll"s, "rrr"s,
    });

    const auto result_wanted = std::array{
        "aaa"s, "bbb"s, "ccc"s, "ddd"s, "eee"s, "fff"s, "ggg"s, "hhh"s, "iii"s, "jjj"s, "kkk"s, "lll"s, "mmm"s,
        "nnn"s, "ooo"s, "ppp"s, "qqq"s, "rrr"s, "sss"s, "ttt"s, "uuu"s, "vvv"s, "www"s, "xxx"s, "yyy"s, "zzz"s,
    };

    EXPECT_EQ(result, result_wanted);
}

TEST(python_builtin, sorted__array_string__reverse)
{
    using namespace std::literals::string_literals;

    const auto result = ztd::sorted(
        std::array{
            "iii"s, "ppp"s, "ddd"s, "www"s, "sss"s, "vvv"s, "kkk"s, "qqq"s, "ooo"s, "nnn"s, "aaa"s, "yyy"s, "eee"s,
            "xxx"s, "ttt"s, "uuu"s, "ccc"s, "jjj"s, "hhh"s, "fff"s, "zzz"s, "mmm"s, "ggg"s, "bbb"s, "lll"s, "rrr"s,
        },
        true);

    const auto result_wanted = std::array{
        "zzz"s, "yyy"s, "xxx"s, "www"s, "vvv"s, "uuu"s, "ttt"s, "sss"s, "rrr"s, "qqq"s, "ppp"s, "ooo"s, "nnn"s,
        "mmm"s, "lll"s, "kkk"s, "jjj"s, "iii"s, "hhh"s, "ggg"s, "fff"s, "eee"s, "ddd"s, "ccc"s, "bbb"s, "aaa"s,
    };

    EXPECT_EQ(result, result_wanted);
}

TEST(python_builtin, sorted__vector_string)
{
    using namespace std::literals::string_literals;

    const auto result = ztd::sorted(std::vector{
        "iii"s, "ppp"s, "ddd"s, "www"s, "sss"s, "vvv"s, "kkk"s, "qqq"s, "ooo"s, "nnn"s, "aaa"s, "yyy"s, "eee"s,
        "xxx"s, "ttt"s, "uuu"s, "ccc"s, "jjj"s, "hhh"s, "fff"s, "zzz"s, "mmm"s, "ggg"s, "bbb"s, "lll"s, "rrr"s,
    });

    const auto result_wanted = std::vector{
        "aaa"s, "bbb"s, "ccc"s, "ddd"s, "eee"s, "fff"s, "ggg"s, "hhh"s, "iii"s, "jjj"s, "kkk"s, "lll"s, "mmm"s,
        "nnn"s, "ooo"s, "ppp"s, "qqq"s, "rrr"s, "sss"s, "ttt"s, "uuu"s, "vvv"s, "www"s, "xxx"s, "yyy"s, "zzz"s,
    };

    EXPECT_EQ(result, result_wanted);
}

TEST(python_builtin, sorted__vector_string__reverse)
{
    using namespace std::literals::string_literals;

    const auto result = ztd::sorted(
        std::vector{
            "iii"s, "ppp"s, "ddd"s, "www"s, "sss"s, "vvv"s, "kkk"s, "qqq"s, "ooo"s, "nnn"s, "aaa"s, "yyy"s, "eee"s,
            "xxx"s, "ttt"s, "uuu"s, "ccc"s, "jjj"s, "hhh"s, "fff"s, "zzz"s, "mmm"s, "ggg"s, "bbb"s, "lll"s, "rrr"s,
        },
        true);

    const auto result_wanted = std::vector{
        "zzz"s, "yyy"s, "xxx"s, "www"s, "vvv"s, "uuu"s, "ttt"s, "sss"s, "rrr"s, "qqq"s, "ppp"s, "ooo"s, "nnn"s,
        "mmm"s, "lll"s, "kkk"s, "jjj"s, "iii"s, "hhh"s, "ggg"s, "fff"s, "eee"s, "ddd"s, "ccc"s, "bbb"s, "aaa"s,
    };

    EXPECT_EQ(result, result_wanted);
}

TEST(python_builtin, sorted__array_int)
{
    using namespace std::literals::string_literals;

    const auto result = ztd::sorted(std::array{
        55,  15,  136, 190, 465, 171, 231, 435, 325, 528, 10, 351, 36,  3,   595, 105, 120, 276, 6,
        406, 561, 45,  378, 28,  21,  153, 210, 630, 300, 1,  91,  666, 496, 253, 0,   78,  66,
    });

    const auto result_wanted = std::array{
        0,   1,   3,   6,   10,  15,  21,  28,  36,  45,  55,  66,  78,  91,  105, 120, 136, 153, 171,
        190, 210, 231, 253, 276, 300, 325, 351, 378, 406, 435, 465, 496, 528, 561, 595, 630, 666,
    };

    EXPECT_EQ(result, result_wanted);
}

TEST(python_builtin, sorted__array_int__reverse)
{
    using namespace std::literals::string_literals;

    const auto result = ztd::sorted(
        std::array{
            55,  15,  136, 190, 465, 171, 231, 435, 325, 528, 10, 351, 36,  3,   595, 105, 120, 276, 6,
            406, 561, 45,  378, 28,  21,  153, 210, 630, 300, 1,  91,  666, 496, 253, 0,   78,  66,
        },
        true);

    const auto result_wanted = std::array{
        666, 630, 595, 561, 528, 496, 465, 435, 406, 378, 351, 325, 300, 276, 253, 231, 210, 190, 171,
        153, 136, 120, 105, 91,  78,  66,  55,  45,  36,  28,  21,  15,  10,  6,   3,   1,   0,
    };

    EXPECT_EQ(result, result_wanted);
}

TEST(python_builtin, sorted__vector_int)
{
    using namespace std::literals::string_literals;

    const auto result = ztd::sorted(std::vector{
        55,  15,  136, 190, 465, 171, 231, 435, 325, 528, 10, 351, 36,  3,   595, 105, 120, 276, 6,
        406, 561, 45,  378, 28,  21,  153, 210, 630, 300, 1,  91,  666, 496, 253, 0,   78,  66,
    });

    const auto result_wanted = std::vector{
        0,   1,   3,   6,   10,  15,  21,  28,  36,  45,  55,  66,  78,  91,  105, 120, 136, 153, 171,
        190, 210, 231, 253, 276, 300, 325, 351, 378, 406, 435, 465, 496, 528, 561, 595, 630, 666,
    };

    EXPECT_EQ(result, result_wanted);
}

TEST(python_builtin, sorted__vector_int__reverse)
{
    using namespace std::literals::string_literals;

    const auto result = ztd::sorted(
        std::vector{
            55,  15,  136, 190, 465, 171, 231, 435, 325, 528, 10, 351, 36,  3,   595, 105, 120, 276, 6,
            406, 561, 45,  378, 28,  21,  153, 210, 630, 300, 1,  91,  666, 496, 253, 0,   78,  66,
        },
        true);

    const auto result_wanted = std::vector{
        666, 630, 595, 561, 528, 496, 465, 435, 406, 378, 351, 325, 300, 276, 253, 231, 210, 190, 171,
        153, 136, 120, 105, 91,  78,  66,  55,  45,  36,  28,  21,  15,  10,  6,   3,   1,   0,
    };

    EXPECT_EQ(result, result_wanted);
}
