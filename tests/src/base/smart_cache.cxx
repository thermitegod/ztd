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

#include <algorithm>
#include <functional>
#include <memory>
#include <ranges>
#include <string>
#include <vector>

#include <doctest/doctest.h>

#include "ztd/detail/smart_cache.hxx"
#include "ztd/detail/string_python.hxx"
#include "ztd/detail/string_random.hxx"
#include "ztd/detail/types.hxx"

// Counter for destructors to ensure no leaks.
static ztd::i32 global_smart_cache_destructor_count{0};

struct smart_cache_data final
{
    smart_cache_data(const ztd::i32 d) : data(d) {}
    ~smart_cache_data() { global_smart_cache_destructor_count += 1_i32; }

    static std::shared_ptr<smart_cache_data> create(const ztd::i32 data) noexcept;

    ztd::i32 data{0};
};

std::shared_ptr<smart_cache_data>
smart_cache_data::create(const ztd::i32 data) noexcept
{
    return std::make_shared<smart_cache_data>(data);
}

TEST_SUITE("ztd::smart_cache")
{
    TEST_CASE("smart_cache")
    {
        global_smart_cache_destructor_count = 0;

        ztd::smart_cache<std::string, smart_cache_data> smart_cache;

        auto value_1 = smart_cache.create("value_1", std::bind(&smart_cache_data::create, 1_i32));
        auto value_2 = smart_cache.create("value_2", std::bind(&smart_cache_data::create, 2_i32));
        auto value_3 = smart_cache.create("value_3", std::bind(&smart_cache_data::create, 3_i32));
        auto value_4 = smart_cache.create("value_4", std::bind(&smart_cache_data::create, 4_i32));
        auto value_5 = smart_cache.create("value_5", std::bind(&smart_cache_data::create, 5_i32));

        REQUIRE(value_1->data == 1);
        REQUIRE(value_2->data == 2);
        REQUIRE(value_3->data == 3);
        REQUIRE(value_4->data == 4);
        REQUIRE(value_5->data == 5);

        SUBCASE("at")
        {
            // Check that .at() gets the correct object, while a ref is being held
            CHECK(smart_cache.at("value_1")->data == 1_i32);
            CHECK(smart_cache.at("value_2")->data == 2_i32);
            CHECK(smart_cache.at("value_3")->data == 3_i32);
            CHECK(smart_cache.at("value_4")->data == 4_i32);
            CHECK(smart_cache.at("value_5")->data == 5_i32);

            // remove ref to objects, destroy the object in cache
            value_1 = nullptr;
            value_2 = nullptr;
            value_3 = nullptr;
            value_4 = nullptr;
            value_5 = nullptr;

            // Check that .at() fails, since no ref is held
            CHECK(smart_cache.at("value_1") == nullptr);
            CHECK(smart_cache.at("value_2") == nullptr);
            CHECK(smart_cache.at("value_3") == nullptr);
            CHECK(smart_cache.at("value_4") == nullptr);
            CHECK(smart_cache.at("value_5") == nullptr);

            // Check that the created shared_ptr are freed
            smart_cache.clear();
            REQUIRE(global_smart_cache_destructor_count == 5);
        }

        SUBCASE("remove")
        {
            smart_cache.erase("value_1");
            smart_cache.erase("value_2");
            smart_cache.erase("value_3");
            smart_cache.erase("value_4");
            smart_cache.erase("value_5");

            // Check that objects have been removed
            CHECK(smart_cache.at("value_1") == nullptr);
            CHECK(smart_cache.at("value_2") == nullptr);
            CHECK(smart_cache.at("value_3") == nullptr);
            CHECK(smart_cache.at("value_4") == nullptr);
            CHECK(smart_cache.at("value_5") == nullptr);
        }

        SUBCASE("contains")
        {
            // Check cache after create
            CHECK(smart_cache.contains("value_1"));
            CHECK(smart_cache.contains("value_2"));
            CHECK(smart_cache.contains("value_3"));
            CHECK(smart_cache.contains("value_4"));
            CHECK(smart_cache.contains("value_5"));

            // Check cache after delete
            value_1 = nullptr;
            value_2 = nullptr;
            value_3 = nullptr;
            value_4 = nullptr;
            value_5 = nullptr;

            CHECK_FALSE(smart_cache.contains("value_1"));
            CHECK_FALSE(smart_cache.contains("value_2"));
            CHECK_FALSE(smart_cache.contains("value_3"));
            CHECK_FALSE(smart_cache.contains("value_4"));
            CHECK_FALSE(smart_cache.contains("value_5"));

            // Check keys not in cache
            CHECK_FALSE(smart_cache.contains("value_6"));
            CHECK_FALSE(smart_cache.contains("value_7"));
            CHECK_FALSE(smart_cache.contains("value_8"));
            CHECK_FALSE(smart_cache.contains("value_9"));
            CHECK_FALSE(smart_cache.contains("value_10"));
        }

        SUBCASE("count")
        {
            // count in cache
            CHECK(smart_cache.count("value_1") == 1);
            CHECK(smart_cache.count("value_2") == 1);
            CHECK(smart_cache.count("value_3") == 1);
            CHECK(smart_cache.count("value_4") == 1);
            CHECK(smart_cache.count("value_5") == 1);

            // count not in cache
            CHECK(smart_cache.count("value_6") == 0);
            CHECK(smart_cache.count("value_7") == 0);
            CHECK(smart_cache.count("value_8") == 0);
            CHECK(smart_cache.count("value_9") == 0);
            CHECK(smart_cache.count("value_10") == 0);
        }

        SUBCASE("size")
        {
            CHECK(smart_cache.size() == 5);
            smart_cache.clear();
            CHECK(smart_cache.size() == 0);
        }

        SUBCASE("keys")
        {
            const auto keys = smart_cache.keys();
            std::vector<std::string> check_keys = {"value_1",
                                                   "value_2",
                                                   "value_3",
                                                   "value_4",
                                                   "value_5"};
            REQUIRE(keys.size() == check_keys.size());
            for (const auto& key : check_keys)
            {
                CHECK(std::ranges::contains(keys, key));
            }

            // check iter lookup values match
            for (const auto& key : keys)
            {
                const auto value = smart_cache.at(key);
                CHECK(value->data == std::stoi(ztd::remove_prefix(key, "value_")));
            }

            // delete some values and run checks again.
            value_4 = nullptr;
            value_5 = nullptr;

            const auto keys2 = smart_cache.keys();
            std::vector<std::string> check_keys2 = {"value_1", "value_2", "value_3"};
            REQUIRE(keys2.size() == check_keys2.size());
            for (const auto& key : check_keys2)
            {
                CHECK(std::ranges::contains(keys2, key));
            }

            // check iter lookup values match
            for (const auto& key : keys2)
            {
                const auto value = smart_cache.at(key);
                CHECK(value->data == std::stoi(ztd::remove_prefix(key, "value_")));
            }
        }

        SUBCASE("items")
        {
            const auto items = smart_cache.items();
            REQUIRE(items.size() == 5);
            for (const auto& item : items)
            {
                item->data = 10_i32;
            }

            CHECK(value_1->data == 10_i32);
            CHECK(value_2->data == 10_i32);
            CHECK(value_3->data == 10_i32);
            CHECK(value_4->data == 10_i32);
            CHECK(value_5->data == 10_i32);
        }
    }

    TEST_CASE("smart_cache with internal reference")
    {
        global_smart_cache_destructor_count = 0;

        ztd::smart_cache<std::string, smart_cache_data> smart_cache;

        {
            auto value_1 =
                smart_cache.create("value_1", std::bind(&smart_cache_data::create, 1_i32), true);
            auto value_2 =
                smart_cache.create("value_2", std::bind(&smart_cache_data::create, 2_i32), true);
            auto value_3 =
                smart_cache.create("value_3", std::bind(&smart_cache_data::create, 3_i32), true);
            auto value_4 =
                smart_cache.create("value_4", std::bind(&smart_cache_data::create, 4_i32), true);
            auto value_5 =
                smart_cache.create("value_5", std::bind(&smart_cache_data::create, 5_i32), true);
        }

        // Check that .at() gets the correct object, ref is held by the cache
        CHECK(smart_cache.at("value_1")->data == 1_i32);
        CHECK(smart_cache.at("value_2")->data == 2_i32);
        CHECK(smart_cache.at("value_3")->data == 3_i32);
        CHECK(smart_cache.at("value_4")->data == 4_i32);
        CHECK(smart_cache.at("value_5")->data == 5_i32);

        // Check that the created shared_ptr are freed
        smart_cache.clear();
        CHECK(global_smart_cache_destructor_count == 5);
    }

    TEST_CASE("self assign")
    {
        global_smart_cache_destructor_count = 0;

        ztd::smart_cache<std::string, smart_cache_data> smart_cache;

        auto value_1 = smart_cache.create("value_1", std::bind(&smart_cache_data::create, 1_i32));

        value_1 = smart_cache.at("value_1");
        CHECK(value_1->data == 1);
        value_1 = nullptr;

        // Check that the externaly created shared_ptr are freed
        smart_cache.clear();
        CHECK(global_smart_cache_destructor_count == 1);
    }

    TEST_CASE("empty")
    {
        ztd::smart_cache<std::string, smart_cache_data> smart_cache;

        CHECK(smart_cache.empty());

        auto value_1 = smart_cache.create("value_1", std::bind(&smart_cache_data::create, 1_i32));

        CHECK_FALSE(smart_cache.empty());
    }

    TEST_CASE("cached objects destructor")
    {
        global_smart_cache_destructor_count = 0;

        ztd::smart_cache<std::string, smart_cache_data> smart_cache;

        // const ztd::i32 count = 1000_i32;
        const ztd::i32 count = 100_i32;

        for (const auto i : std::views::iota(0z, count.data()))
        {
            auto value = smart_cache.create(
                ztd::random_hex(),
                std::bind(&smart_cache_data::create, ztd::i32(ztd::i32::integer_type(i))));
            CHECK(value->data == i);

            // only one valid object is in the cache
            CHECK(smart_cache.size() == 1);
        }

        // all objects have had their destructor run
        CHECK(smart_cache.size() == 0);
        smart_cache.clear();

        CHECK(global_smart_cache_destructor_count == count);
    }
}
