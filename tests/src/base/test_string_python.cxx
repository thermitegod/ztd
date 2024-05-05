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

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "ztd/detail/string_python.hxx"

/**
 * split
 */
TEST(string_python, split)
{
    const std::string str = "foo foo foo";

    const std::vector<std::string> result_wanted = {"foo", "foo", "foo"};
    const std::vector<std::string> result = ztd::split(str, " ");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__empty_string)
{
    const std::string str = "";

    const std::vector<std::string> result_wanted = {""};
    const std::vector<std::string> result = ztd::split(str, ",");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_first)
{
    const std::string str = ",test,test";

    const std::vector<std::string> result_wanted = {"", "test", "test"};
    const std::vector<std::string> result = ztd::split(str, ",");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_second)
{
    const std::string str = "test,test";

    const std::vector<std::string> result_wanted = {"test", "test"};
    const std::vector<std::string> result = ztd::split(str, ",");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_multiple_empty)
{
    const std::string str = "test,,,test";

    const std::vector<std::string> result_wanted = {"test", "", "", "test"};
    const std::vector<std::string> result = ztd::split(str, ",");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_missing)
{
    const std::string str = "test|test";

    const std::vector<std::string> result_wanted = {"test|test"};
    const std::vector<std::string> result = ztd::split(str, ",");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__no_delimiter)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a,b,c,d,e,f"};
    const std::vector<std::string> result = ztd::split(str);
}

TEST(string_python, split__delimiter_multiple_chars_2__maxsplit_all)
{
    const std::string str = "a<>b<>c<>d<>e<>f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::split(str, "<>");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_multiple_chars_2__maxsplit_0)
{
    const std::string str = "a<>b<>c<>d<>e<>f";

    const std::vector<std::string> result_wanted = {"a<>b<>c<>d<>e<>f"};
    const std::vector<std::string> result = ztd::split(str, "<>", 0);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_multiple_chars_2__maxsplit_1)
{
    const std::string str = "a<>b<>c<>d<>e<>f";

    const std::vector<std::string> result_wanted = {"a", "b<>c<>d<>e<>f"};
    const std::vector<std::string> result = ztd::split(str, "<>", 1);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_multiple_chars_2__maxsplit_2)
{
    const std::string str = "a<>b<>c<>d<>e<>f";

    const std::vector<std::string> result_wanted = {"a", "b", "c<>d<>e<>f"};
    const std::vector<std::string> result = ztd::split(str, "<>", 2);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_multiple_chars_2__maxsplit_3)
{
    const std::string str = "a<>b<>c<>d<>e<>f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d<>e<>f"};
    const std::vector<std::string> result = ztd::split(str, "<>", 3);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_multiple_chars_2__maxsplit_4)
{
    const std::string str = "a<>b<>c<>d<>e<>f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e<>f"};
    const std::vector<std::string> result = ztd::split(str, "<>", 4);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_multiple_chars_2__maxsplit_5)
{
    const std::string str = "a<>b<>c<>d<>e<>f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::split(str, "<>", 5);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_multiple_chars_3__maxsplit_all)
{
    const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::split(str, "<=>");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_multiple_chars_3__maxsplit_0)
{
    const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

    const std::vector<std::string> result_wanted = {"a<=>b<=>c<=>d<=>e<=>f"};
    const std::vector<std::string> result = ztd::split(str, "<=>", 0);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_multiple_chars_3__maxsplit_1)
{
    const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

    const std::vector<std::string> result_wanted = {"a", "b<=>c<=>d<=>e<=>f"};
    const std::vector<std::string> result = ztd::split(str, "<=>", 1);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_multiple_chars_3__maxsplit_2)
{
    const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

    const std::vector<std::string> result_wanted = {"a", "b", "c<=>d<=>e<=>f"};
    const std::vector<std::string> result = ztd::split(str, "<=>", 2);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_multiple_chars_3__maxsplit_3)
{
    const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d<=>e<=>f"};
    const std::vector<std::string> result = ztd::split(str, "<=>", 3);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_multiple_chars_3__maxsplit_4)
{
    const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e<=>f"};
    const std::vector<std::string> result = ztd::split(str, "<=>", 4);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__delimiter_multiple_chars_3__maxsplit_5)
{
    const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::split(str, "<=>", 5);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__maxsplit_all)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::split(str, ",");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__maxsplit_0)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a,b,c,d,e,f"};
    const std::vector<std::string> result = ztd::split(str, ",", 0);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__maxsplit_1)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a", "b,c,d,e,f"};
    const std::vector<std::string> result = ztd::split(str, ",", 1);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__maxsplit_2)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a", "b", "c,d,e,f"};
    const std::vector<std::string> result = ztd::split(str, ",", 2);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__maxsplit_3)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d,e,f"};
    const std::vector<std::string> result = ztd::split(str, ",", 3);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__maxsplit_4)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e,f"};
    const std::vector<std::string> result = ztd::split(str, ",", 4);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__maxsplit_5)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::split(str, ",", 5);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__maxsplit__larger_than_real_maxsplit)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::split(str, ",", 500);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, split__filepath)
{
    const std::string str = "/home/user/download";

    const std::vector<std::string> result_wanted = {"", "home", "user", "download"};
    const std::vector<std::string> result = ztd::split(str, "/");

    EXPECT_EQ(result, result_wanted);
}

/**
 * rsplit
 */
TEST(string_python, rsplit)
{
    const std::string str = "foo foo foo";

    const std::vector<std::string> result_wanted = {"foo", "foo", "foo"};
    const std::vector<std::string> result = ztd::rsplit(str, " ");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__empty_string)
{
    const std::string str = "";

    const std::vector<std::string> result_wanted = {""};
    const std::vector<std::string> result = ztd::rsplit(str, ",");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_first)
{
    const std::string str = ",test,test";

    const std::vector<std::string> result_wanted = {"", "test", "test"};
    const std::vector<std::string> result = ztd::rsplit(str, ",");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_second)
{
    const std::string str = "test,test";

    const std::vector<std::string> result_wanted = {"test", "test"};
    const std::vector<std::string> result = ztd::rsplit(str, ",");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_empty)
{
    const std::string str = "test,,,test";

    const std::vector<std::string> result_wanted = {"test", "", "", "test"};
    const std::vector<std::string> result = ztd::rsplit(str, ",");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_missing)
{
    const std::string str = "test|test";

    const std::vector<std::string> result_wanted = {"test|test"};
    const std::vector<std::string> result = ztd::rsplit(str, ",");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__no_delimiter)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a,b,c,d,e,f"};
    const std::vector<std::string> result = ztd::rsplit(str);
}

TEST(string_python, rsplit__delimiter_multiple_chars_2__maxsplit_all)
{
    const std::string str = "a<>b<>c<>d<>e<>f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, "<>");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_chars_2__maxsplit_0)
{
    const std::string str = "a<>b<>c<>d<>e<>f";

    const std::vector<std::string> result_wanted = {"a<>b<>c<>d<>e<>f"};
    const std::vector<std::string> result = ztd::rsplit(str, "<>", 0);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_chars_2__maxsplit_1)
{
    const std::string str = "a<>b<>c<>d<>e<>f";

    const std::vector<std::string> result_wanted = {"a<>b<>c<>d<>e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, "<>", 1);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_chars_2__maxsplit_2)
{
    const std::string str = "a<>b<>c<>d<>e<>f";

    const std::vector<std::string> result_wanted = {"a<>b<>c<>d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, "<>", 2);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_chars_2__maxsplit_3)
{
    const std::string str = "a<>b<>c<>d<>e<>f";

    const std::vector<std::string> result_wanted = {"a<>b<>c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, "<>", 3);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_chars_2__maxsplit_4)
{
    const std::string str = "a<>b<>c<>d<>e<>f";

    const std::vector<std::string> result_wanted = {"a<>b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, "<>", 4);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_chars_2__maxsplit_5)
{
    const std::string str = "a<>b<>c<>d<>e<>f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, "<>", 5);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_chars_3__maxsplit_all)
{
    const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, "<=>");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_chars_3__maxsplit_0)
{
    const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

    const std::vector<std::string> result_wanted = {"a<=>b<=>c<=>d<=>e<=>f"};
    const std::vector<std::string> result = ztd::rsplit(str, "<=>", 0);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_chars_3__maxsplit_1)
{
    const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

    const std::vector<std::string> result_wanted = {"a<=>b<=>c<=>d<=>e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, "<=>", 1);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_chars_3__maxsplit_2)
{
    const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

    const std::vector<std::string> result_wanted = {"a<=>b<=>c<=>d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, "<=>", 2);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_chars_3__maxsplit_3)
{
    const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

    const std::vector<std::string> result_wanted = {"a<=>b<=>c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, "<=>", 3);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_chars_3__maxsplit_4)
{
    const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

    const std::vector<std::string> result_wanted = {"a<=>b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, "<=>", 4);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__delimiter_multiple_chars_3__maxsplit_5)
{
    const std::string str = "a<=>b<=>c<=>d<=>e<=>f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, "<=>", 5);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__maxsplit_all)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, ",");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__maxsplit_0)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a,b,c,d,e,f"};
    const std::vector<std::string> result = ztd::rsplit(str, ",", 0);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__maxsplit_1)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a,b,c,d,e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, ",", 1);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__maxsplit_2)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a,b,c,d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, ",", 2);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__maxsplit_3)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a,b,c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, ",", 3);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__maxsplit_4)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a,b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, ",", 4);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__maxsplit_5)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, ",", 5);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__maxsplit__larger_than_real_maxsplit)
{
    const std::string str = "a,b,c,d,e,f";

    const std::vector<std::string> result_wanted = {"a", "b", "c", "d", "e", "f"};
    const std::vector<std::string> result = ztd::rsplit(str, ",", 500);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rsplit__filepath)
{
    const std::string str = "/home/user/download";

    const std::vector<std::string> result_wanted = {"", "home", "user", "download"};
    const std::vector<std::string> result = ztd::rsplit(str, "/");

    EXPECT_EQ(result, result_wanted);
}

/**
 * join vector<string>
 */
TEST(string_python, join__empty_string)
{
    const std::vector<std::string> vec = {};

    const std::string result_wanted = "";
    const std::string result = ztd::join(vec, "Z");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, join__vector_string)
{
    const std::vector<std::string> vec = {"foo", "foo", "foo"};

    const std::string result_wanted = "foo foo foo";
    const std::string result = ztd::join(vec, " ");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, join__vector_string__multi_sep)
{
    const std::vector<std::string> vec = {"foo", "foo", "foo"};

    const std::string result_wanted = "foo | foo | foo";
    const std::string result = ztd::join(vec, " | ");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, join__vector_string__empty)
{
    const std::vector<std::string> vec = {};

    const std::string result_wanted = "";
    const std::string result = ztd::join(vec, " ");

    EXPECT_EQ(result, result_wanted);
}

/**
 * join vector<string_view>
 */
TEST(string_python, join__empty_string_view)
{
    const std::vector<std::string_view> vec = {};

    const std::string result_wanted = "";
    const std::string result = ztd::join(vec, "Z");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, join__vector_string_view)
{
    using namespace std::literals::string_view_literals;

    const std::vector<std::string_view> vec = {"foo"sv, "foo"sv, "foo"sv};

    const std::string result_wanted = "foo foo foo";
    const std::string result = ztd::join(vec, " ");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, join__vector_string_view__multi_sep)
{
    using namespace std::literals::string_view_literals;

    const std::vector<std::string_view> vec = {"foo"sv, "foo"sv, "foo"sv};

    const std::string result_wanted = "foo | foo | foo";
    const std::string result = ztd::join(vec, " | ");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, join__vector_string_view__empty)
{
    const std::vector<std::string_view> vec = {};

    const std::string result_wanted = "";
    const std::string result = ztd::join(vec, " ");

    EXPECT_EQ(result, result_wanted);
}

/**
 * lower
 */
TEST(string_python, lower_latin)
{
    const std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    const std::string lower_wanted = "abcdefghijklmnopqrstuvwxyz1234567890";

    const std::string lower = ztd::lower(upper);

    EXPECT_EQ(lower, lower_wanted);
}

TEST(string_python, lower_special)
{
    const std::string upper = "!@$%^&*()_+";
    const std::string lower_wanted = "!@$%^&*()_+";

    const std::string lower = ztd::lower(upper);

    EXPECT_EQ(lower, lower_wanted);
}

TEST(string_python, lower_mixed_special)
{
    const std::string upper = "@A@a@A@";
    const std::string lower_wanted = "@a@a@a@";

    const std::string lower = ztd::lower(upper);

    EXPECT_EQ(lower, lower_wanted);
}

TEST(string_python, lower_japanese)
{
    const std::string upper = "化粧室はどこですか";
    const std::string lower_wanted = "化粧室はどこですか";

    const std::string lower = ztd::lower(upper);

    EXPECT_EQ(lower, lower_wanted);
}

TEST(string_python, lower_korean)
{
    const std::string upper = "화장실이 어디야";
    const std::string lower_wanted = "화장실이 어디야";

    const std::string lower = ztd::lower(upper);

    EXPECT_EQ(lower, lower_wanted);
}

TEST(string_python, lower_empty)
{
    const std::string upper = "";
    const std::string lower_wanted = "";

    const std::string lower = ztd::lower(upper);

    EXPECT_EQ(lower, lower_wanted);
}

/**
 * upper
 */
TEST(string_python, upper_latin)
{
    const std::string lower = "abcdefghijklmnopqrstuvwxyz1234567890!@$%^&*()_+";
    const std::string upper_wanted = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@$%^&*()_+";

    const std::string upper = ztd::upper(lower);

    ASSERT_EQ(upper, upper_wanted);
}

TEST(string_python, upper_special)
{
    const std::string lower = "!@$%^&*()_+";
    const std::string upper_wanted = "!@$%^&*()_+";

    const std::string upper = ztd::upper(lower);

    EXPECT_EQ(upper, upper_wanted);
}

TEST(string_python, upper_mixed_special)
{
    const std::string lower = "@a@A@a@";
    const std::string upper_wanted = "@A@A@A@";

    const std::string upper = ztd::upper(lower);

    EXPECT_EQ(upper, upper_wanted);
}

TEST(string_python, upper_japanese)
{
    const std::string lower = "化粧室はどこですか";
    const std::string upper_wanted = "化粧室はどこですか";

    const std::string upper = ztd::upper(lower);

    ASSERT_EQ(upper, upper_wanted);
}

TEST(string_python, upper_korean)
{
    const std::string lower = "화장실이 어디야";
    const std::string upper_wanted = "화장실이 어디야";

    const std::string upper = ztd::upper(lower);

    ASSERT_EQ(upper, upper_wanted);
}

TEST(string_python, upper_empty)
{
    const std::string lower = "";
    const std::string upper_wanted = "";

    const std::string upper = ztd::upper(lower);

    EXPECT_EQ(upper, upper_wanted);
}

/**
 * replace
 */
TEST(string_python, replace)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "foo";
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbar bazbar bazbar";
    const std::string result = ztd::replace(str, str_find, str_replace);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, replace__str_empty)
{
    const std::string str = "";
    const std::string str_find = "foo";
    const std::string str_replace = "baz";

    const std::string result_wanted = "";
    const std::string result = ztd::replace(str, str_find, str_replace);

    ASSERT_EQ(result, result_wanted);
}

TEST(string_python, replace__find_empty)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "";
    const std::string str_replace = "baz";

    const std::string result_wanted = "foobar foobar foobar";
    const std::string result = ztd::replace(str, str_find, str_replace);

    ASSERT_EQ(result, result_wanted);
}

TEST(string_python, replace__replace_empty)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "foo";
    const std::string str_replace = "";

    const std::string result_wanted = "bar bar bar";
    const std::string result = ztd::replace(str, str_find, str_replace);

    ASSERT_EQ(result, result_wanted);
}

TEST(string_python, replace__missing)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "fooo";
    const std::string str_replace = "baz";

    const std::string result_wanted = "foobar foobar foobar";
    const std::string result = ztd::replace(str, str_find, str_replace);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, replace__count_neg)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "foo";
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbar bazbar bazbar";
    const std::string result = ztd::replace(str, str_find, str_replace, -5);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, replace__count_0)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "foo";
    const std::string str_replace = "baz";

    const std::string result_wanted = "foobar foobar foobar";
    const std::string result = ztd::replace(str, str_find, str_replace, 0);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, replace__count_1)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "foo";
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbar foobar foobar";
    const std::string result = ztd::replace(str, str_find, str_replace, 1);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, replace__count_2)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "foo";
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbar bazbar foobar";
    const std::string result = ztd::replace(str, str_find, str_replace, 2);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, replace__count_3)
{
    const std::string str = "foobar foobar foobar";
    const std::string str_find = "foo";
    const std::string str_replace = "baz";

    const std::string result_wanted = "bazbar bazbar bazbar";
    const std::string result = ztd::replace(str, str_find, str_replace, 3);

    EXPECT_EQ(result, result_wanted);
}

/**
 * capitalize
 */
TEST(string_python, capitalize__space)
{
    const std::string str = " will not capitalize the first letter.";

    const std::string result_wanted = " will not capitalize the first letter.";
    const std::string result = ztd::capitalize(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, capitalize__lower)
{
    const std::string str = "capitalize only the first letter.";

    const std::string result_wanted = "Capitalize only the first letter.";
    const std::string result = ztd::capitalize(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, capitalize__upper)
{
    const std::string str = "AAAA BBBB CCCC";

    const std::string result_wanted = "Aaaa bbbb cccc";
    const std::string result = ztd::capitalize(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, capitalize__mixed)
{
    const std::string str = "aAaA BbBb CcCc";

    const std::string result_wanted = "Aaaa bbbb cccc";
    const std::string result = ztd::capitalize(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, capitalize__empty)
{
    const std::string str = "";

    const std::string result_wanted = "";
    const std::string result = ztd::capitalize(str);

    EXPECT_EQ(result, result_wanted);
}

/**
 * center
 */
TEST(string_python, center__even_string_even_width)
{
    const std::string str = "even";

    const std::string result_wanted = "   even   ";
    const std::string result = ztd::center(str, 10);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, center__even_string_odd_width)
{
    const std::string str = "even";

    const std::string result_wanted = "  even   ";
    const std::string result = ztd::center(str, 9);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, center__odd_string_odd_width)
{
    const std::string str = "odd";

    const std::string result_wanted = " odd ";
    const std::string result = ztd::center(str, 5);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, center__odd_string_even_width)
{
    const std::string str = "odd";

    const std::string result_wanted = "   odd    ";
    const std::string result = ztd::center(str, 10);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, center__empty)
{
    const std::string str = "";

    const std::string result_wanted = "     ";
    const std::string result = ztd::center(str, 5);

    EXPECT_EQ(result, result_wanted);
}

/**
 * count
 */
TEST(string_python, count)
{
    const std::string str = "zaaazaaaz";

    const u64 result_wanted = 6;
    const u64 result = ztd::count(str, "a");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count_multichar)
{
    const std::string str = "zaaazaaaz";

    const u64 result_wanted = 2;
    const u64 result = ztd::count(str, "aaa");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__zero)
{
    const std::string str = "zaaazaaaz";

    const u64 result_wanted = 0;
    const u64 result = ztd::count(str, "w");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__empty)
{
    const std::string str = "";

    const u64 result_wanted = 0;
    const u64 result = ztd::count(str, "w");

    EXPECT_EQ(result, result_wanted);
}

/**
 * count char overload
 */
TEST(string_python, count__char)
{
    const std::string str = "zaaazaaaz";

    const u64 result_wanted = 6;
    const u64 result = ztd::count(str, 'a');

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__char__zero)
{
    const std::string str = "zaaazaaaz";

    const u64 result_wanted = 0;
    const u64 result = ztd::count(str, 'w');

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__char__empty)
{
    const std::string str = "";

    const u64 result_wanted = 0;
    const u64 result = ztd::count(str, 'w');

    EXPECT_EQ(result, result_wanted);
}

/**
 * count (start, end) overload
 */
TEST(string_python, count__start_end__empty)
{
    const std::string str = "";

    const u64 result_wanted = 0;
    const u64 result = ztd::count(str, "w", 0, std::string_view::npos);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__start_end)
{
    const std::string str = "zaaazaaaz";

    const u64 result_wanted = 3;
    const u64 result = ztd::count(str, "a", 4, 15);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__start_end__multichar)
{
    const std::string str = "zaaazaaaz";

    const u64 result_wanted = 1;
    const u64 result = ztd::count(str, "aaa", 4, 15);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__start_end__zero)
{
    const std::string str = "zaaazaaaz";

    const u64 result_wanted = 0;
    const u64 result = ztd::count(str, "w", 0, 15);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__start_end_2)
{
    const std::string str = "zaaazaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    const u64 result_wanted = 3;
    const u64 result = ztd::count(str, "a", 0, 4);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__start_end__same)
{
    const std::string str = "aaaa";

    const u64 result_wanted = 0;
    const u64 result = ztd::count(str, "a", 1, 1);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__start_end__large_start)
{
    const std::string str = "aaaa";

    const u64 result_wanted = 0;
    const u64 result = ztd::count(str, "a", 3, 2);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__start_end__large_end)
{
    const std::string str = "aaaa";

    const u64 result_wanted = 4;
    const u64 result = ztd::count(str, "a", 0, 100);

    EXPECT_EQ(result, result_wanted);
}

/**
 * count (start, end) char overload
 */
TEST(string_python, count__char__start_end__empty)
{
    const std::string str = "";

    const u64 result_wanted = 0;
    const u64 result = ztd::count(str, 'w', 0, std::string_view::npos);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__char__start_end)
{
    const std::string str = "zaaazaaaz";

    const u64 result_wanted = 3;
    const u64 result = ztd::count(str, 'a', 4, 15);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__char__start_end__zero)
{
    const std::string str = "zaaazaaaz";

    const u64 result_wanted = 0;
    const u64 result = ztd::count(str, 'w', 0, 15);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__char__start_end_2)
{
    const std::string str = "zaaazaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    const u64 result_wanted = 3;
    const u64 result = ztd::count(str, 'a', 0, 4);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__char__start_end__same)
{
    const std::string str = "aaaa";

    const u64 result_wanted = 0;
    const u64 result = ztd::count(str, 'a', 1, 1);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__char__start_end__large_start)
{
    const std::string str = "aaaa";

    const u64 result_wanted = 0;
    const u64 result = ztd::count(str, 'a', 3, 2);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, count__char__start_end__large_end)
{
    const std::string str = "aaaa";

    const u64 result_wanted = 4;
    const u64 result = ztd::count(str, 'a', 0, 100);

    EXPECT_EQ(result, result_wanted);
}

/**
 * expandtabs
 */
TEST(string_python, expandtabs__4)
{
    const std::string str = "01\t012\t0123\t01234";
    const std::string result_wanted = "01  012 0123    01234";

    const std::string result = ztd::expandtabs(str, 4);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, expandtabs__8)
{
    const std::string str = "01\t012\t0123\t01234";
    const std::string result_wanted = "01      012     0123    01234";

    const std::string result = ztd::expandtabs(str, 8);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, expandtabs__LF)
{
    const std::string str = "01\t012\t0123\t01234\n012345\t0123";
    const std::string result_wanted = "01      012     0123    01234\n012345  0123";

    const std::string result = ztd::expandtabs(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, expandtabs__CR)
{
    const std::string str = "01\t012\t0123\t01234\r012345\t0123";
    const std::string result_wanted = "01      012     0123    01234\r012345  0123";

    const std::string result = ztd::expandtabs(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, expandtabs__CRLF)
{
    const std::string str = "01\t012\t0123\t01234\r\n012345\t0123";
    const std::string result_wanted = "01      012     0123    01234\r\n012345  0123";

    const std::string result = ztd::expandtabs(str);

    EXPECT_EQ(result, result_wanted);
}

/**
 * isalnum
 */
TEST(string_python, isalnum__all_alpha__true)
{
    const std::string str = "alphastring";

    EXPECT_TRUE(ztd::isalnum(str));
}

TEST(string_python, isalnum__all_digit__true)
{
    const std::string str = "69420";

    EXPECT_TRUE(ztd::isalnum(str));
}

TEST(string_python, isalnum__mixed__true)
{
    const std::string str = "alnumstring69420";

    EXPECT_TRUE(ztd::isalnum(str));
}

TEST(string_python, isalnum__special__false)
{
    const std::string str = "!@#$%^&*()_+{}";

    EXPECT_FALSE(ztd::isalnum(str));
}

TEST(string_python, isalnum__space__false)
{
    const std::string str = "not alnum string";

    EXPECT_FALSE(ztd::isalnum(str));
}

TEST(string_python, isalnum__empty)
{
    const std::string str = "";

    EXPECT_FALSE(ztd::isalnum(str));
}

/**
 * isalpha
 */
TEST(string_python, isalpha__true)
{
    const std::string str = "alphastring";

    EXPECT_TRUE(ztd::isalpha(str));
}

TEST(string_python, isalpha__false)
{
    const std::string str = "not alpha string?";

    EXPECT_FALSE(ztd::isalpha(str));
}

TEST(string_python, isalpha__empty)
{
    const std::string str = "";

    EXPECT_FALSE(ztd::isalpha(str));
}

#if 0
/**
 * isascii
 */
TEST(string_python, isascii__true)
{
    // test all ascii code point form 0-127
    for (isize i = 0; i <= 127; ++i)
    {
        unsigned char ch = char(i);
        EXPECT_TRUE(ztd::isascii(std::to_string(ch)));
    }
}

TEST(string_python, isascii__empty)
{
    EXPECT_TRUE(ztd::isascii(""));
}

TEST(string_python, isascii__false)
{
    EXPECT_FALSE(ztd::isascii("ß"));
}
#endif

/**
 * isdecimal
 */
TEST(string_python, isdecimal__true)
{
    const std::string str = "1234567890";

    EXPECT_TRUE(ztd::isdecimal(str));
}

TEST(string_python, isdecimal__empty)
{
    const std::string str = "";

    EXPECT_FALSE(ztd::isdecimal(str));
}

TEST(string_python, isdecimal__false)
{
    const std::string str = "1234567890a";

    EXPECT_FALSE(ztd::isdecimal(str));
}

/**
 * isdigit
 */
TEST(string_python, isdigit__true)
{
    const std::string str = "1234567890";

    EXPECT_TRUE(ztd::isdigit(str));
}

TEST(string_python, isdigit__empty)
{
    const std::string str = "";

    EXPECT_FALSE(ztd::isdigit(str));
}

TEST(string_python, isdigit__false)
{
    const std::string str = "1234567890a";

    EXPECT_FALSE(ztd::isdigit(str));
}

/**
 * isnumeric
 */
TEST(string_python, isnumeric__true)
{
    const std::string str = "1234567890";

    EXPECT_TRUE(ztd::isnumeric(str));
}

TEST(string_python, isnumeric__empty)
{
    const std::string str = "";

    EXPECT_FALSE(ztd::isnumeric(str));
}

TEST(string_python, isnumeric__false)
{
    const std::string str = "1234567890a";

    EXPECT_FALSE(ztd::isnumeric(str));
}

/**
 * islower
 */
TEST(string_python, islower__true)
{
    const std::string str = "string";

    EXPECT_TRUE(ztd::islower(str));
}

TEST(string_python, islower__true_special)
{
    const std::string str = "string string!@#$%^&*_+(){}[]";

    EXPECT_TRUE(ztd::islower(str));
}

TEST(string_python, islower__false)
{
    const std::string str = "STRING";

    EXPECT_FALSE(ztd::islower(str));
}

TEST(string_python, islower__empty)
{
    const std::string str = "";

    EXPECT_FALSE(ztd::islower(str));
}

/**
 * isupper
 */
TEST(string_python, isupper__true)
{
    const std::string str = "STRING";

    EXPECT_TRUE(ztd::isupper(str));
}

TEST(string_python, isupper__true_special)
{
    const std::string str = "STRING STRING!@#$%^&*_+(){}[]";

    EXPECT_TRUE(ztd::isupper(str));
}

TEST(string_python, isupper__false)
{
    const std::string str = "string";

    EXPECT_FALSE(ztd::isupper(str));
}

TEST(string_python, isupper__empty)
{
    const std::string str = "";

    EXPECT_FALSE(ztd::isupper(str));
}

/**
 * isspace
 */
TEST(string_python, isspace__true)
{
    const std::string str = "    ";

    EXPECT_TRUE(ztd::isspace(str));
}

TEST(string_python, isspace__false)
{
    const std::string str = " a ";

    EXPECT_FALSE(ztd::isspace(str));
}

TEST(string_python, isspace__empty)
{
    const std::string str = "";

    EXPECT_FALSE(ztd::isspace(str));
}

/**
 * istitle
 */
TEST(string_python, istitle__empty)
{
    const std::string str = "";

    EXPECT_FALSE(ztd::istitle(str));
}

TEST(string_python, istitle__true)
{
    const std::string str = "A String A";

    EXPECT_TRUE(ztd::istitle(str));
}

TEST(string_python, istitle__false)
{
    const std::string str = "A string A";

    EXPECT_FALSE(ztd::istitle(str));
}

TEST(string_python, istitle__from_the_python_example)
{
    const std::string str = "They'Re Bill'S Friends From The Uk";

    EXPECT_TRUE(ztd::istitle(str));
}

/**
 * title
 */
TEST(string_python, title)
{
    const std::string str = "String";

    const std::string result_wanted = "String";
    const std::string result = ztd::title(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, title__empty)
{
    const std::string str = "";

    const std::string result_wanted = "";
    const std::string result = ztd::title(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, title__all_lower)
{
    const std::string str = "string a string";

    const std::string result_wanted = "String A String";
    const std::string result = ztd::title(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, title__all_upper)
{
    const std::string str = "STRING A STRING";

    const std::string result_wanted = "String A String";
    const std::string result = ztd::title(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, title__mixed)
{
    const std::string str = "StRiNg a sTrInG";

    const std::string result_wanted = "String A String";
    const std::string result = ztd::title(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, title__special)
{
    const std::string str = "String ~!@#$%^&*()-_+{}|<>?,./";

    const std::string result_wanted = "String ~!@#$%^&*()-_+{}|<>?,./";
    const std::string result = ztd::title(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, title__from_the_python_example)
{
    const std::string str = "they're bill's friends from the UK";

    const std::string result_wanted = "They'Re Bill'S Friends From The Uk";
    const std::string result = ztd::title(str);

    EXPECT_EQ(result, result_wanted);
}

/**
 * swapcase
 */
TEST(string_python, swapcase)
{
    const std::string str = "String";

    const std::string result_wanted = "sTRING";
    const std::string result = ztd::swapcase(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, swapcase__empty)
{
    const std::string str = "";

    const std::string result_wanted = "";
    const std::string result = ztd::swapcase(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, swapcase__all_lower)
{
    const std::string str = "string string";

    const std::string result_wanted = "STRING STRING";
    const std::string result = ztd::swapcase(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, swapcase__all_upper)
{
    const std::string str = "STRING STRING";

    const std::string result_wanted = "string string";
    const std::string result = ztd::swapcase(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, swapcase__mixed)
{
    const std::string str = "StRiNg sTrInG";

    const std::string result_wanted = "sTrInG StRiNg";
    const std::string result = ztd::swapcase(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, swapcase__special)
{
    const std::string str = "String ~!@#$%^&*()-_+{}|<>?,./";

    const std::string result_wanted = "sTRING ~!@#$%^&*()-_+{}|<>?,./";
    const std::string result = ztd::swapcase(str);

    EXPECT_EQ(result, result_wanted);
}

/**
 * ljust
 */
TEST(string_python, ljust)
{
    const std::string str = "string";

    const std::string result_wanted = "string    ";
    const std::string result = ztd::ljust(str, 10);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, ljust__empty)
{
    const std::string str = "";

    const std::string result_wanted = "          ";
    const std::string result = ztd::ljust(str, 10);

    EXPECT_EQ(result, result_wanted);
}

/**
 * rjust
 */
TEST(string_python, rjust)
{
    const std::string str = "string";

    const std::string result_wanted = "    string";
    const std::string result = ztd::rjust(str, 10);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rjust__empty)
{
    const std::string str = "";

    const std::string result_wanted = "          ";
    const std::string result = ztd::rjust(str, 10);

    EXPECT_EQ(result, result_wanted);
}

/**
 * lstrip
 */
TEST(string_python, lstrip)
{
    const std::string str = "  a  ";

    const std::string result_wanted = "a  ";
    const std::string result = ztd::lstrip(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, lstrip__chars)
{
    const std::string str = "z a z";

    const std::string result_wanted = " a z";
    const std::string result = ztd::lstrip(str, "z");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, lstrip__empty)
{
    const std::string str = "";

    const std::string result_wanted = "";
    const std::string result = ztd::lstrip(str);

    EXPECT_EQ(result, result_wanted);
}

/**
 * rstrip
 */
TEST(string_python, rstrip)
{
    const std::string str = "  a  ";

    const std::string result_wanted = "  a";
    const std::string result = ztd::rstrip(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rstrip__chars)
{
    const std::string str = "z a z";

    const std::string result_wanted = "z a ";
    const std::string result = ztd::rstrip(str, "z");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, rstrip__empty)
{
    const std::string str = "";

    const std::string result_wanted = "";
    const std::string result = ztd::rstrip(str);

    EXPECT_EQ(result, result_wanted);
}

/**
 * strip
 */
TEST(string_python, strip)
{
    const std::string str = "  a  ";

    const std::string result_wanted = "a";
    const std::string result = ztd::strip(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, strip__chars)
{
    const std::string str = "z a z";

    const std::string result_wanted = " a ";
    const std::string result = ztd::strip(str, "z");

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, strip__chars_all)
{
    const std::string str = "\n\r\t ";

    const std::string result_wanted = "";
    const std::string result = ztd::strip(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, strip__empty)
{
    const std::string str = "";

    const std::string result_wanted = "";
    const std::string result = ztd::strip(str);

    EXPECT_EQ(result, result_wanted);
}

/**
 * removeprefix
 */
TEST(string_python, removeprefix)
{
    const std::string str1 = "foobar test string";
    const std::string str2 = "foobar ";

    const std::string result_wanted = "test string";
    const std::string result = ztd::removeprefix(str1, str2);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, removeprefix__missing)
{
    const std::string str1 = "foobar test string";
    const std::string str2 = "zbar";

    const std::string result_wanted = "foobar test string";
    const std::string result = ztd::removeprefix(str1, str2);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, removeprefix__str_empty)
{
    const std::string str1 = "";
    const std::string str2 = "foobar";

    const std::string result_wanted = "";
    const std::string result = ztd::removeprefix(str1, str2);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, removeprefix__prefix_empty)
{
    const std::string str1 = "foobar";
    const std::string str2 = "";

    const std::string result_wanted = "foobar";
    const std::string result = ztd::removeprefix(str1, str2);

    EXPECT_EQ(result, result_wanted);
}

/**
 * removeprefix char overload
 */
TEST(string_python, removeprefix__char)
{
    const std::string str1 = "@foobar@";

    const std::string result_wanted = "foobar@";
    const std::string result = ztd::removeprefix(str1, '@');

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, removeprefix__char__missing)
{
    const std::string str1 = "@foobar@";

    const std::string result_wanted = "@foobar@";
    const std::string result = ztd::removeprefix(str1, 'Z');

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, removeprefix__char__str_empty)
{
    const std::string str1 = "";

    const std::string result_wanted = "";
    const std::string result = ztd::removeprefix(str1, '@');

    EXPECT_EQ(result, result_wanted);
}

/**
 * removesuffix
 */
TEST(string_python, removesuffix)
{
    const std::string str1 = "foobar test string";
    const std::string str2 = " string";

    const std::string result_wanted = "foobar test";
    const std::string result = ztd::removesuffix(str1, str2);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, removesuffix__missing)
{
    const std::string str1 = "foobar test string";
    const std::string str2 = "zbar";

    const std::string result_wanted = "foobar test string";
    const std::string result = ztd::removesuffix(str1, str2);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, removesuffix__str_empty)
{
    const std::string str1 = "";
    const std::string str2 = "foobar";

    const std::string result_wanted = "";
    const std::string result = ztd::removesuffix(str1, str2);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, removesuffix__prefix_empty)
{
    const std::string str1 = "foobar";
    const std::string str2 = "";

    const std::string result_wanted = "foobar";
    const std::string result = ztd::removesuffix(str1, str2);

    EXPECT_EQ(result, result_wanted);
}

/**
 * removesuffix char overload
 */
TEST(string_python, removesuffix__char)
{
    const std::string str1 = "@foobar@";

    const std::string result_wanted = "@foobar";
    const std::string result = ztd::removesuffix(str1, '@');

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, removesuffix__char__missing)
{
    const std::string str1 = "@foobar@";

    const std::string result_wanted = "@foobar@";
    const std::string result = ztd::removesuffix(str1, 'Z');

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, removesuffix__char__str_empty)
{
    const std::string str1 = "";

    const std::string result_wanted = "";
    const std::string result = ztd::removesuffix(str1, '@');

    EXPECT_EQ(result, result_wanted);
}

/**
 * partition
 */
TEST(string_python, partition)
{
    const std::string str = "foobar$foobar$foobar";

    const std::string result_wanted_1 = "foobar";
    const std::string result_wanted_2 = "$";
    const std::string result_wanted_3 = "foobar$foobar";

    const auto result = ztd::partition(str, "$");

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

TEST(string_python, partition__str_empty)
{
    const std::string str = "";

    const std::string result_wanted_1 = "";
    const std::string result_wanted_2 = "";
    const std::string result_wanted_3 = "";

    const auto result = ztd::partition(str, "$");

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

TEST(string_python, partition__sep_empty)
{
    const std::string str = "foobar$foobar$foobar";

    const std::string result_wanted_1 = "foobar$foobar$foobar";
    const std::string result_wanted_2 = "";
    const std::string result_wanted_3 = "";

    const auto result = ztd::partition(str, "");

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

TEST(string_python, partition__missing)
{
    const std::string str = "foobar$foobar$foobar";

    const std::string result_wanted_1 = "foobar$foobar$foobar";
    const std::string result_wanted_2 = "";
    const std::string result_wanted_3 = "";

    const auto result = ztd::partition(str, "^");

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

TEST(string_python, partition__recombine)
{
    const std::string str = "split/split/split";

    const std::string recombine_wanted = str;

    const std::string result_wanted_1 = "split";
    const std::string result_wanted_2 = "/";
    const std::string result_wanted_3 = "split/split";

    const auto result = ztd::partition(str, "/");

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);

    const auto recombine = std::format("{}{}{}", result[0], result[1], result[2]);

    EXPECT_EQ(recombine_wanted, recombine);
}

TEST(string_python, partition__multi)
{
    const std::string str = "test.tar.tar.test";

    const std::string result_wanted_1 = "test";
    const std::string result_wanted_2 = ".tar.";
    const std::string result_wanted_3 = "tar.test";

    const auto result = ztd::partition(str, ".tar.");

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

/**
 * partition
 */
TEST(string_python, partition__char)
{
    const std::string str = "foobar$foobar$foobar";

    const std::string result_wanted_1 = "foobar";
    const std::string result_wanted_2 = "$";
    const std::string result_wanted_3 = "foobar$foobar";

    const auto result = ztd::partition(str, '$');

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

TEST(string_python, partition__char__str_empty)
{
    const std::string str = "";

    const std::string result_wanted_1 = "";
    const std::string result_wanted_2 = "";
    const std::string result_wanted_3 = "";

    const auto result = ztd::partition(str, '$');

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

TEST(string_python, partition__char__missing)
{
    const std::string str = "foobar$foobar$foobar";

    const std::string result_wanted_1 = "foobar$foobar$foobar";
    const std::string result_wanted_2 = "";
    const std::string result_wanted_3 = "";

    const auto result = ztd::partition(str, '^');

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

TEST(string_python, partition__char__recombine)
{
    const std::string str = "split/split/split";

    const std::string recombine_wanted = str;

    const std::string result_wanted_1 = "split";
    const std::string result_wanted_2 = "/";
    const std::string result_wanted_3 = "split/split";

    const auto result = ztd::partition(str, '/');

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);

    const auto recombine = std::format("{}{}{}", result[0], result[1], result[2]);

    EXPECT_EQ(recombine_wanted, recombine);
}

/**
 * rpartition
 */
TEST(string_python, rpartition)
{
    const std::string str = "foobar$foobar$foobar";

    const std::string result_wanted_1 = "foobar$foobar";
    const std::string result_wanted_2 = "$";
    const std::string result_wanted_3 = "foobar";

    const auto result = ztd::rpartition(str, "$");

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

TEST(string_python, rpartition__str_empty)
{
    const std::string str = "";

    const std::string result_wanted_1 = "";
    const std::string result_wanted_2 = "";
    const std::string result_wanted_3 = "";

    const auto result = ztd::rpartition(str, "$");

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

TEST(string_python, rpartition__sep_empty)
{
    const std::string str = "foobar$foobar$foobar";

    const std::string result_wanted_1 = "";
    const std::string result_wanted_2 = "";
    const std::string result_wanted_3 = "foobar$foobar$foobar";

    const auto result = ztd::rpartition(str, "");

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

TEST(string_python, rpartition__missing)
{
    const std::string str = "foobar$foobar$foobar";

    const std::string result_wanted_1 = "";
    const std::string result_wanted_2 = "";
    const std::string result_wanted_3 = "foobar$foobar$foobar";

    const auto result = ztd::rpartition(str, "^");

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

TEST(string_python, rpartition__recombine)
{
    const std::string str = "split/split/split";

    const std::string recombine_wanted = str;

    const std::string result_wanted_1 = "split/split";
    const std::string result_wanted_2 = "/";
    const std::string result_wanted_3 = "split";

    const auto result = ztd::rpartition(str, "/");

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);

    const auto recombine = std::format("{}{}{}", result[0], result[1], result[2]);

    EXPECT_EQ(recombine_wanted, recombine);
}

TEST(string_python, rpartition__multi)
{
    const std::string str = "test.tar.tar.test";

    const std::string result_wanted_1 = "test.tar";
    const std::string result_wanted_2 = ".tar.";
    const std::string result_wanted_3 = "test";

    const auto result = ztd::rpartition(str, ".tar.");

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

/**
 * rpartition char overload
 */
TEST(string_python, rpartition__char)
{
    const std::string str = "foobar$foobar$foobar";

    const std::string result_wanted_1 = "foobar$foobar";
    const std::string result_wanted_2 = "$";
    const std::string result_wanted_3 = "foobar";

    const auto result = ztd::rpartition(str, '$');

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

TEST(string_python, rpartition__char__str_empty)
{
    const std::string str = "";

    const std::string result_wanted_1 = "";
    const std::string result_wanted_2 = "";
    const std::string result_wanted_3 = "";

    const auto result = ztd::rpartition(str, '$');

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

TEST(string_python, rpartition__char__missing)
{
    const std::string str = "foobar$foobar$foobar";

    const std::string result_wanted_1 = "";
    const std::string result_wanted_2 = "";
    const std::string result_wanted_3 = "foobar$foobar$foobar";

    const auto result = ztd::rpartition(str, '^');

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);
}

TEST(string_python, rpartition__char__recombine)
{
    const std::string str = "split/split/split";

    const std::string recombine_wanted = str;

    const std::string result_wanted_1 = "split/split";
    const std::string result_wanted_2 = "/";
    const std::string result_wanted_3 = "split";

    const auto result = ztd::rpartition(str, '/');

    const auto result_1 = result[0];
    const auto result_2 = result[1];
    const auto result_3 = result[2];

    EXPECT_EQ(result_1, result_wanted_1);
    EXPECT_EQ(result_2, result_wanted_2);
    EXPECT_EQ(result_3, result_wanted_3);

    const auto recombine = std::format("{}{}{}", result[0], result[1], result[2]);

    EXPECT_EQ(recombine_wanted, recombine);
}

#if 0
/**
 * splitlines
 */
TEST(string_python, splitlines__newline__keepends)
{
    const std::string str = "foo\nfoo";

    const std::vector<std::string> result_wanted = {"foo", "foo"};
    const std::vector<std::string> result = ztd::splitlines(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, splitlines__python_example_1)
{
    const std::string str = "ab c\n\nde fg\rkl\r\n";

    const std::vector<std::string> result_wanted = {"ab c", "", "de fg", "kl"};
    const std::vector<std::string> result = ztd::splitlines(str);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, splitlines__python_example_2)
{
    const std::string str = "ab c\n\nde fg\rkl\r\n";

    const std::vector<std::string> result_wanted = {"ab c\n", "\n", "de fg\r", "kl\r\n"};
    const std::vector<std::string> result = ztd::splitlines(str);

    EXPECT_EQ(result, result_wanted);
}
#endif

/**
 * zfill
 */
TEST(string_python, zfill__str)
{
    const std::string str = "string";

    const std::string result_wanted = "0000string";
    const std::string result = ztd::zfill(str, 10);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, zfill__str_pos)
{
    const std::string str = "+string";

    const std::string result_wanted = "+000string";
    const std::string result = ztd::zfill(str, 10);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, zfill__str_neg)
{
    const std::string str = "-string";

    const std::string result_wanted = "-000string";
    const std::string result = ztd::zfill(str, 10);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, zfill__str_int)
{
    const std::string str = "420";

    const std::string result_wanted = "0000000420";
    const std::string result = ztd::zfill(str, 10);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, zfill__str_int_pos)
{
    const std::string str = "+420";

    const std::string result_wanted = "+000000420";
    const std::string result = ztd::zfill(str, 10);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, zfill__str_int_neg)
{
    const std::string str = "-420";

    const std::string result_wanted = "-000000420";
    const std::string result = ztd::zfill(str, 10);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, zfill__empty)
{
    const std::string str = "";

    const std::string result_wanted = "0000000000";
    const std::string result = ztd::zfill(str, 10);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, zfill__sign_pos_only)
{
    const std::string str = "+";

    const std::string result_wanted = "+000000000";
    const std::string result = ztd::zfill(str, 10);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, zfill__sign_neg_only)
{
    const std::string str = "-";

    const std::string result_wanted = "-000000000";
    const std::string result = ztd::zfill(str, 10);

    EXPECT_EQ(result, result_wanted);
}

TEST(string_python, zfill__no_fill)
{
    const std::string str = "string";

    const std::string result_wanted = "string";
    const std::string result = ztd::zfill(str, str.size());

    EXPECT_EQ(result, result_wanted);
}
