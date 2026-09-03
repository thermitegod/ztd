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

template<typename T> struct json_test final
{
    T value = T::unchecked_create(100);
};

TEST_SUITE("glz::meta ztd::integer<T> " * doctest::description(""))
{
    TEST_CASE_TEMPLATE("operator& ",
                       Integer,
                       // Signed
                       ztd::i8,
                       ztd::i16,
                       ztd::i32,
                       ztd::i64,
                       ztd::isize,
                       // Unsigned
                       ztd::u8,
                       ztd::u16,
                       ztd::u32,
                       ztd::u64,
                       ztd::usize)
    {
        using test_struct = json_test<Integer>;

        SUBCASE("basic")
        {
            test_struct t;

            const auto serialized = glz::write_json(t);
            REQUIRE(serialized.has_value());

            // ERROR: CHECK_EQ( serialized.value(), R"({"value":100}})" ) is NOT correct!
            //        values: CHECK_EQ( {"value":100}, {"value":100}} )
            // CHECK_EQ(serialized.value(), R"({"value":100}})");

            const auto deserialized = glz::read_json<test_struct>(serialized.value());
            REQUIRE(deserialized.has_value());

            CHECK_EQ(deserialized->value, t.value);
        }
    }
}
