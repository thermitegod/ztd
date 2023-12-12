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
#include <string_view>

#include <algorithm>
#include <ranges>

#include <array>

#include <stdexcept>

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

/**
 * enumerate
 */

TEST(python_builtin, enumerate__array)
{
    using namespace std::literals::string_literals;

    const auto data = std::array{
        "aaa"s, "bbb"s, "ccc"s, "ddd"s, "eee"s, "fff"s, "ggg"s, "hhh"s, "iii"s, "jjj"s, "kkk"s, "lll"s, "mmm"s,
        "nnn"s, "ooo"s, "ppp"s, "qqq"s, "rrr"s, "sss"s, "ttt"s, "uuu"s, "vvv"s, "www"s, "xxx"s, "yyy"s, "zzz"s,
    };

    usize end_index = 0;
    for (const auto [index, value] : ztd::enumerate(data))
    {
        if (index == 0)
        {
            EXPECT_EQ(value, "aaa");
        }
        else if (index == 1)
        {
            EXPECT_EQ(value, "bbb");
        }
        else if (index == 2)
        {
            EXPECT_EQ(value, "ccc");
        }
        else if (index == 3)
        {
            EXPECT_EQ(value, "ddd");
        }
        else if (index == 4)
        {
            EXPECT_EQ(value, "eee");
        }
        else if (index == 5)
        {
            EXPECT_EQ(value, "fff");
        }
        else if (index == 6)
        {
            EXPECT_EQ(value, "ggg");
        }
        else if (index == 7)
        {
            EXPECT_EQ(value, "hhh");
        }
        else if (index == 8)
        {
            EXPECT_EQ(value, "iii");
        }
        else if (index == 9)
        {
            EXPECT_EQ(value, "jjj");
        }
        else if (index == 10)
        {
            EXPECT_EQ(value, "kkk");
        }
        else if (index == 11)
        {
            EXPECT_EQ(value, "lll");
        }
        else if (index == 12)
        {
            EXPECT_EQ(value, "mmm");
        }
        else if (index == 13)
        {
            EXPECT_EQ(value, "nnn");
        }
        else if (index == 14)
        {
            EXPECT_EQ(value, "ooo");
        }
        else if (index == 15)
        {
            EXPECT_EQ(value, "ppp");
        }
        else if (index == 16)
        {
            EXPECT_EQ(value, "qqq");
        }
        else if (index == 17)
        {
            EXPECT_EQ(value, "rrr");
        }
        else if (index == 18)
        {
            EXPECT_EQ(value, "sss");
        }
        else if (index == 19)
        {
            EXPECT_EQ(value, "ttt");
        }
        else if (index == 20)
        {
            EXPECT_EQ(value, "uuu");
        }
        else if (index == 21)
        {
            EXPECT_EQ(value, "vvv");
        }
        else if (index == 22)
        {
            EXPECT_EQ(value, "www");
        }
        else if (index == 23)
        {
            EXPECT_EQ(value, "xxx");
        }
        else if (index == 24)
        {
            EXPECT_EQ(value, "yyy");
        }
        else if (index == 25)
        {
            EXPECT_EQ(value, "zzz");
        }

        end_index = index;
    }

    EXPECT_EQ(end_index, data.size() - 1);
}

TEST(python_builtin, enumerate__vector)
{
    using namespace std::literals::string_literals;

    const auto data = std::vector{
        "aaa"s, "bbb"s, "ccc"s, "ddd"s, "eee"s, "fff"s, "ggg"s, "hhh"s, "iii"s, "jjj"s, "kkk"s, "lll"s, "mmm"s,
        "nnn"s, "ooo"s, "ppp"s, "qqq"s, "rrr"s, "sss"s, "ttt"s, "uuu"s, "vvv"s, "www"s, "xxx"s, "yyy"s, "zzz"s,
    };

    usize end_index = 0;
    for (const auto [index, value] : ztd::enumerate(data))
    {
        if (index == 0)
        {
            EXPECT_EQ(value, "aaa");
        }
        else if (index == 1)
        {
            EXPECT_EQ(value, "bbb");
        }
        else if (index == 2)
        {
            EXPECT_EQ(value, "ccc");
        }
        else if (index == 3)
        {
            EXPECT_EQ(value, "ddd");
        }
        else if (index == 4)
        {
            EXPECT_EQ(value, "eee");
        }
        else if (index == 5)
        {
            EXPECT_EQ(value, "fff");
        }
        else if (index == 6)
        {
            EXPECT_EQ(value, "ggg");
        }
        else if (index == 7)
        {
            EXPECT_EQ(value, "hhh");
        }
        else if (index == 8)
        {
            EXPECT_EQ(value, "iii");
        }
        else if (index == 9)
        {
            EXPECT_EQ(value, "jjj");
        }
        else if (index == 10)
        {
            EXPECT_EQ(value, "kkk");
        }
        else if (index == 11)
        {
            EXPECT_EQ(value, "lll");
        }
        else if (index == 12)
        {
            EXPECT_EQ(value, "mmm");
        }
        else if (index == 13)
        {
            EXPECT_EQ(value, "nnn");
        }
        else if (index == 14)
        {
            EXPECT_EQ(value, "ooo");
        }
        else if (index == 15)
        {
            EXPECT_EQ(value, "ppp");
        }
        else if (index == 16)
        {
            EXPECT_EQ(value, "qqq");
        }
        else if (index == 17)
        {
            EXPECT_EQ(value, "rrr");
        }
        else if (index == 18)
        {
            EXPECT_EQ(value, "sss");
        }
        else if (index == 19)
        {
            EXPECT_EQ(value, "ttt");
        }
        else if (index == 20)
        {
            EXPECT_EQ(value, "uuu");
        }
        else if (index == 21)
        {
            EXPECT_EQ(value, "vvv");
        }
        else if (index == 22)
        {
            EXPECT_EQ(value, "www");
        }
        else if (index == 23)
        {
            EXPECT_EQ(value, "xxx");
        }
        else if (index == 24)
        {
            EXPECT_EQ(value, "yyy");
        }
        else if (index == 25)
        {
            EXPECT_EQ(value, "zzz");
        }

        end_index = index;
    }

    EXPECT_EQ(end_index, data.size() - 1);
}

/**
 * range()
 */

TEST(python_builtin, range__zero)
{
    const auto range = ztd::range(0);

    EXPECT_EQ(range.size(), 0);
}

TEST(python_builtin, range_pos)
{
    const auto range = ztd::range(10);
    EXPECT_EQ(range.size(), 10);

    EXPECT_EQ(range.at(0), 0);
    EXPECT_EQ(range.at(1), 1);
    EXPECT_EQ(range.at(2), 2);
    EXPECT_EQ(range.at(3), 3);
    EXPECT_EQ(range.at(4), 4);
    EXPECT_EQ(range.at(5), 5);
    EXPECT_EQ(range.at(6), 6);
    EXPECT_EQ(range.at(7), 7);
    EXPECT_EQ(range.at(8), 8);
    EXPECT_EQ(range.at(9), 9);
}

TEST(python_builtin, range_neg)
{
    // Python will not iter with this, example
    // for i in range(-10): print(i)
    // to use a neg need to do ztd::range(0, -10, -1)
    const auto range = ztd::range(-10);

    EXPECT_EQ(range.size(), 0);
}

TEST(python_builtin, range__step__pos_pos_pos)
{
    const auto range = ztd::range(0, 10, 2);
    EXPECT_EQ(range.size(), 5);

    EXPECT_EQ(range.at(0), 0);
    EXPECT_EQ(range.at(1), 2);
    EXPECT_EQ(range.at(2), 4);
    EXPECT_EQ(range.at(3), 6);
    EXPECT_EQ(range.at(4), 8);
}

TEST(python_builtin, range__step__pos_pos_neg)
{
    // Invalid return empty
    const auto range = ztd::range(0, 10, -2);
    EXPECT_EQ(range.size(), 0);
}

TEST(python_builtin, range__step__pos_neg_neg)
{
    const auto range = ztd::range(2, -10, -2);
    EXPECT_EQ(range.size(), 6);

    EXPECT_EQ(range.at(0), 2);
    EXPECT_EQ(range.at(1), 0);
    EXPECT_EQ(range.at(2), -2);
    EXPECT_EQ(range.at(3), -4);
    EXPECT_EQ(range.at(4), -6);
    EXPECT_EQ(range.at(5), -8);
}

TEST(python_builtin, range__step__pos_neg_pos)
{
    // Invalid return empty
    const auto range = ztd::range(0, -10, 1);
    EXPECT_EQ(range.size(), 0);
}

TEST(python_builtin, range__step__neg_pos_pos)
{
    const auto range = ztd::range(-5, 5, 1);
    EXPECT_EQ(range.size(), 10);

    EXPECT_EQ(range.at(0), -5);
    EXPECT_EQ(range.at(1), -4);
    EXPECT_EQ(range.at(2), -3);
    EXPECT_EQ(range.at(3), -2);
    EXPECT_EQ(range.at(4), -1);
    EXPECT_EQ(range.at(5), 0);
    EXPECT_EQ(range.at(6), 1);
    EXPECT_EQ(range.at(7), 2);
    EXPECT_EQ(range.at(8), 3);
    EXPECT_EQ(range.at(9), 4);
}

TEST(python_builtin, range__step__neg_pos_neg)
{
    // Invalid return empty
    const auto range = ztd::range(-10, 10, -1);
    EXPECT_EQ(range.size(), 0);
}

TEST(python_builtin, range__step__neg_neg_pos)
{
    // Invalid return empty
    const auto range = ztd::range(-1, -10, 1);
    EXPECT_EQ(range.size(), 0);
}

TEST(python_builtin, range__step__neg_neg_neg)
{
    const auto range = ztd::range(-1, -10, -1);
    EXPECT_EQ(range.size(), 9);

    EXPECT_EQ(range.at(0), -1);
    EXPECT_EQ(range.at(1), -2);
    EXPECT_EQ(range.at(2), -3);
    EXPECT_EQ(range.at(3), -4);
    EXPECT_EQ(range.at(4), -5);
    EXPECT_EQ(range.at(5), -6);
    EXPECT_EQ(range.at(6), -7);
    EXPECT_EQ(range.at(7), -8);
    EXPECT_EQ(range.at(8), -9);
}

#endif
