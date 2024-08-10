/**
 * Copyright (C) 2025 Brandon Zorn <brandonzorn@cock.li>
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

#include <doctest/doctest.h>

#include "ztd/detail/types.hxx"
#include "ztd/extra/glaze.hxx"

// Can not have structs defined in the TEST_CASE

struct test_i8
{
    ztd::i8 value = ztd::i8::integer_type(100);
};

struct test_i16
{
    ztd::i16 value = ztd::i16::integer_type(100);
};

struct test_i32
{
    ztd::i32 value = ztd::i32::integer_type(100);
};

struct test_i64
{
    ztd::i64 value = ztd::i64::integer_type(100);
};

struct test_isize
{
    ztd::isize value = ztd::isize::integer_type(100);
};

struct test_u8
{
    ztd::u8 value = ztd::u8::integer_type(100);
};

struct test_u16
{
    ztd::u16 value = ztd::u16::integer_type(100);
};

struct test_u32
{
    ztd::u32 value = ztd::u32::integer_type(100);
};

struct test_u64
{
    ztd::u64 value = ztd::u64::integer_type(100);
};

struct test_usize
{
    ztd::usize value = ztd::usize::integer_type(100);
};

TEST_SUITE("glz::meta ztd::integer<T>" * doctest::description(""))
{
    TEST_CASE("i8")
    {
        test_i8 t;

        const auto serialized = glz::write_json(t);
        REQUIRE(serialized.has_value());

        // ERROR: CHECK_EQ( serialized.value(), R"({"value":100}})" ) is NOT correct!
        //        values: CHECK_EQ( {"value":100}, {"value":100}} )
        // CHECK_EQ(serialized.value(), R"({"value":100}})");

        const auto deserialized = glz::read_json<test_i8>(serialized.value());
        REQUIRE(deserialized.has_value());

        CHECK_EQ(deserialized->value, t.value);
    }

    TEST_CASE("i16")
    {
        test_i16 t;

        const auto serialized = glz::write_json(t);
        REQUIRE(serialized.has_value());

        // ERROR: CHECK_EQ( serialized.value(), R"({"value":100}})" ) is NOT correct!
        //        values: CHECK_EQ( {"value":100}, {"value":100}} )
        // CHECK_EQ(serialized.value(), R"({"value":100}})");

        const auto deserialized = glz::read_json<test_i16>(serialized.value());
        REQUIRE(deserialized.has_value());

        CHECK_EQ(deserialized->value, t.value);
    }

    TEST_CASE("i32")
    {
        test_i32 t;

        const auto serialized = glz::write_json(t);
        REQUIRE(serialized.has_value());

        // ERROR: CHECK_EQ( serialized.value(), R"({"value":100}})" ) is NOT correct!
        //        values: CHECK_EQ( {"value":100}, {"value":100}} )
        // CHECK_EQ(serialized.value(), R"({"value":100}})");

        const auto deserialized = glz::read_json<test_i32>(serialized.value());
        REQUIRE(deserialized.has_value());

        CHECK_EQ(deserialized->value, t.value);
    }

    TEST_CASE("i64")
    {
        test_i64 t;

        const auto serialized = glz::write_json(t);
        REQUIRE(serialized.has_value());

        // ERROR: CHECK_EQ( serialized.value(), R"({"value":100}})" ) is NOT correct!
        //        values: CHECK_EQ( {"value":100}, {"value":100}} )
        // CHECK_EQ(serialized.value(), R"({"value":100}})");

        const auto deserialized = glz::read_json<test_i64>(serialized.value());
        REQUIRE(deserialized.has_value());

        CHECK_EQ(deserialized->value, t.value);
    }

    TEST_CASE("isize")
    {
        test_isize t;

        const auto serialized = glz::write_json(t);
        REQUIRE(serialized.has_value());

        // ERROR: CHECK_EQ( serialized.value(), R"({"value":100}})" ) is NOT correct!
        //        values: CHECK_EQ( {"value":100}, {"value":100}} )
        // CHECK_EQ(serialized.value(), R"({"value":100}})");

        const auto deserialized = glz::read_json<test_isize>(serialized.value());
        REQUIRE(deserialized.has_value());

        CHECK_EQ(deserialized->value, t.value);
    }

    TEST_CASE("u8")
    {
        test_u8 t;

        const auto serialized = glz::write_json(t);
        REQUIRE(serialized.has_value());

        // ERROR: CHECK_EQ( serialized.value(), R"({"value":100}})" ) is NOT correct!
        //        values: CHECK_EQ( {"value":100}, {"value":100}} )
        // CHECK_EQ(serialized.value(), R"({"value":100}})");

        const auto deserialized = glz::read_json<test_u8>(serialized.value());
        REQUIRE(deserialized.has_value());

        CHECK_EQ(deserialized->value, t.value);
    }

    TEST_CASE("u16")
    {
        test_u16 t;

        const auto serialized = glz::write_json(t);
        REQUIRE(serialized.has_value());

        // ERROR: CHECK_EQ( serialized.value(), R"({"value":100}})" ) is NOT correct!
        //        values: CHECK_EQ( {"value":100}, {"value":100}} )
        // CHECK_EQ(serialized.value(), R"({"value":100}})");

        const auto deserialized = glz::read_json<test_u16>(serialized.value());
        REQUIRE(deserialized.has_value());

        CHECK_EQ(deserialized->value, t.value);
    }

    TEST_CASE("32")
    {
        test_u32 t;

        const auto serialized = glz::write_json(t);
        REQUIRE(serialized.has_value());

        // ERROR: CHECK_EQ( serialized.value(), R"({"value":100}})" ) is NOT correct!
        //        values: CHECK_EQ( {"value":100}, {"value":100}} )
        // CHECK_EQ(serialized.value(), R"({"value":100}})");

        const auto deserialized = glz::read_json<test_u32>(serialized.value());
        REQUIRE(deserialized.has_value());

        CHECK_EQ(deserialized->value, t.value);
    }

    TEST_CASE("u64")
    {
        test_u64 t;

        const auto serialized = glz::write_json(t);
        REQUIRE(serialized.has_value());

        // ERROR: CHECK_EQ( serialized.value(), R"({"value":100}})" ) is NOT correct!
        //        values: CHECK_EQ( {"value":100}, {"value":100}} )
        // CHECK_EQ(serialized.value(), R"({"value":100}})");

        const auto deserialized = glz::read_json<test_u64>(serialized.value());
        REQUIRE(deserialized.has_value());

        CHECK_EQ(deserialized->value, t.value);
    }

    TEST_CASE("usize")
    {
        test_usize t;

        const auto serialized = glz::write_json(t);
        REQUIRE(serialized.has_value());

        // ERROR: CHECK_EQ( serialized.value(), R"({"value":100}})" ) is NOT correct!
        //        values: CHECK_EQ( {"value":100}, {"value":100}} )
        // CHECK_EQ(serialized.value(), R"({"value":100}})");

        const auto deserialized = glz::read_json<test_usize>(serialized.value());
        REQUIRE(deserialized.has_value());

        CHECK_EQ(deserialized->value, t.value);
    }
}
