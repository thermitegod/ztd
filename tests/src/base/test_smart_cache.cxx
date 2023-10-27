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

#include <functional>

#include <memory>

#include "ztd/ztd.hxx"

// Counter for destructors to ensure no leaks.
i32 global_smart_cache_destructor_count{0};

struct smart_cache_data
{
    smart_cache_data(const i32 data) : data(data) {}
    ~smart_cache_data() { ++global_smart_cache_destructor_count; }

    static const std::shared_ptr<smart_cache_data> create(const i32 data) noexcept;

    i32 data{0};
};

const std::shared_ptr<smart_cache_data>
smart_cache_data::create(const i32 data) noexcept
{
    return std::make_shared<smart_cache_data>(data);
}

/**
 * ztd::smart_cache smart_cache
 */

TEST(smart_cache, smart_cache)
{
    global_smart_cache_destructor_count = 0;

    ztd::smart_cache<std::string, smart_cache_data> smart_cache;

    auto value_1 = smart_cache.create("value_1", std::bind(&smart_cache_data::create, 1));
    auto value_2 = smart_cache.create("value_2", std::bind(&smart_cache_data::create, 2));
    auto value_3 = smart_cache.create("value_3", std::bind(&smart_cache_data::create, 3));
    auto value_4 = smart_cache.create("value_4", std::bind(&smart_cache_data::create, 4));
    auto value_5 = smart_cache.create("value_5", std::bind(&smart_cache_data::create, 5));

    // Check that .at() gets the correct object, while a ref is being held
    ASSERT_EQ(smart_cache.at("value_1")->data, 1);
    ASSERT_EQ(smart_cache.at("value_2")->data, 2);
    ASSERT_EQ(smart_cache.at("value_3")->data, 3);
    ASSERT_EQ(smart_cache.at("value_4")->data, 4);
    ASSERT_EQ(smart_cache.at("value_5")->data, 5);

    // remove ref to objects, destroy the object in cache
    value_1 = nullptr;
    value_2 = nullptr;
    value_3 = nullptr;
    value_4 = nullptr;
    value_5 = nullptr;

    // Check that .at() fails, since no ref is held
    ASSERT_EQ(smart_cache.at("value_1"), nullptr);
    ASSERT_EQ(smart_cache.at("value_2"), nullptr);
    ASSERT_EQ(smart_cache.at("value_3"), nullptr);
    ASSERT_EQ(smart_cache.at("value_4"), nullptr);
    ASSERT_EQ(smart_cache.at("value_5"), nullptr);

    // Check that the created shared_ptr are freed
    smart_cache.clear();
    ASSERT_EQ(global_smart_cache_destructor_count, 5);
}

TEST(smart_cache, self_assign)
{
    global_smart_cache_destructor_count = 0;

    ztd::smart_cache<std::string, smart_cache_data> smart_cache;

    auto value_1 = smart_cache.create("value_1", std::bind(&smart_cache_data::create, 1));

    value_1 = smart_cache.at("value_1");
    ASSERT_EQ(value_1->data, 1);
    value_1 = nullptr;

    // Check that the externaly created shared_ptr are freed
    smart_cache.clear();
    ASSERT_EQ(global_smart_cache_destructor_count, 1);
}

TEST(smart_cache, remove)
{
    ztd::smart_cache<std::string, smart_cache_data> smart_cache;

    auto value_1 = smart_cache.create("value_1", std::bind(&smart_cache_data::create, 1));
    auto value_2 = smart_cache.create("value_2", std::bind(&smart_cache_data::create, 2));
    auto value_3 = smart_cache.create("value_3", std::bind(&smart_cache_data::create, 3));
    auto value_4 = smart_cache.create("value_4", std::bind(&smart_cache_data::create, 4));
    auto value_5 = smart_cache.create("value_5", std::bind(&smart_cache_data::create, 5));

    smart_cache.erase("value_1");
    smart_cache.erase("value_2");
    smart_cache.erase("value_3");
    smart_cache.erase("value_4");
    smart_cache.erase("value_5");

    // Check that objects have been removed
    ASSERT_EQ(smart_cache.at("value_1"), nullptr);
    ASSERT_EQ(smart_cache.at("value_2"), nullptr);
    ASSERT_EQ(smart_cache.at("value_3"), nullptr);
    ASSERT_EQ(smart_cache.at("value_4"), nullptr);
    ASSERT_EQ(smart_cache.at("value_5"), nullptr);
}

TEST(smart_cache, contains)
{
    ztd::smart_cache<std::string, smart_cache_data> smart_cache;

    auto value_1 = smart_cache.create("value_1", std::bind(&smart_cache_data::create, 1));
    auto value_2 = smart_cache.create("value_2", std::bind(&smart_cache_data::create, 2));
    auto value_3 = smart_cache.create("value_3", std::bind(&smart_cache_data::create, 3));
    auto value_4 = smart_cache.create("value_4", std::bind(&smart_cache_data::create, 4));
    auto value_5 = smart_cache.create("value_5", std::bind(&smart_cache_data::create, 5));

    // Check cache after create
    ASSERT_TRUE(smart_cache.contains("value_1"));
    ASSERT_TRUE(smart_cache.contains("value_2"));
    ASSERT_TRUE(smart_cache.contains("value_3"));
    ASSERT_TRUE(smart_cache.contains("value_4"));
    ASSERT_TRUE(smart_cache.contains("value_5"));

    // Check cache after delete
    value_1 = nullptr;
    value_2 = nullptr;
    value_3 = nullptr;
    value_4 = nullptr;
    value_5 = nullptr;

    ASSERT_FALSE(smart_cache.contains("value_1"));
    ASSERT_FALSE(smart_cache.contains("value_2"));
    ASSERT_FALSE(smart_cache.contains("value_3"));
    ASSERT_FALSE(smart_cache.contains("value_4"));
    ASSERT_FALSE(smart_cache.contains("value_5"));

    // Check keys not in cache
    ASSERT_FALSE(smart_cache.contains("value_6"));
    ASSERT_FALSE(smart_cache.contains("value_7"));
    ASSERT_FALSE(smart_cache.contains("value_8"));
    ASSERT_FALSE(smart_cache.contains("value_9"));
    ASSERT_FALSE(smart_cache.contains("value_10"));
}

TEST(smart_cache, count)
{
    ztd::smart_cache<std::string, smart_cache_data> smart_cache;

    auto value_1 = smart_cache.create("value_1", std::bind(&smart_cache_data::create, 1));
    auto value_2 = smart_cache.create("value_2", std::bind(&smart_cache_data::create, 2));
    auto value_3 = smart_cache.create("value_3", std::bind(&smart_cache_data::create, 3));
    auto value_4 = smart_cache.create("value_4", std::bind(&smart_cache_data::create, 4));
    auto value_5 = smart_cache.create("value_5", std::bind(&smart_cache_data::create, 5));

    ASSERT_EQ(smart_cache.count("value_1"), 1);
    ASSERT_EQ(smart_cache.count("value_2"), 1);
    ASSERT_EQ(smart_cache.count("value_3"), 1);
    ASSERT_EQ(smart_cache.count("value_4"), 1);
    ASSERT_EQ(smart_cache.count("value_5"), 1);

    ASSERT_EQ(smart_cache.count("value_6"), 0);
    ASSERT_EQ(smart_cache.count("value_7"), 0);
    ASSERT_EQ(smart_cache.count("value_8"), 0);
    ASSERT_EQ(smart_cache.count("value_9"), 0);
    ASSERT_EQ(smart_cache.count("value_10"), 0);
}

TEST(smart_cache, empty)
{
    ztd::smart_cache<std::string, smart_cache_data> smart_cache;

    ASSERT_TRUE(smart_cache.empty());

    auto value_1 = smart_cache.create("value_1", std::bind(&smart_cache_data::create, 1));

    ASSERT_FALSE(smart_cache.empty());
}

TEST(smart_cache, size)
{
    ztd::smart_cache<std::string, smart_cache_data> smart_cache;

    auto value_1 = smart_cache.create("value_1", std::bind(&smart_cache_data::create, 1));
    auto value_2 = smart_cache.create("value_2", std::bind(&smart_cache_data::create, 2));
    auto value_3 = smart_cache.create("value_3", std::bind(&smart_cache_data::create, 3));
    auto value_4 = smart_cache.create("value_4", std::bind(&smart_cache_data::create, 4));
    auto value_5 = smart_cache.create("value_5", std::bind(&smart_cache_data::create, 5));

    ASSERT_EQ(value_1->data, 1);
    ASSERT_EQ(value_2->data, 2);
    ASSERT_EQ(value_3->data, 3);
    ASSERT_EQ(value_4->data, 4);
    ASSERT_EQ(value_5->data, 5);

    ASSERT_EQ(smart_cache.size(), 5);
    smart_cache.clear();
    ASSERT_EQ(smart_cache.size(), 0);
}

TEST(smart_cache, iterators)
{
    ztd::smart_cache<std::string, smart_cache_data> smart_cache;

    auto value_1 = smart_cache.create("value_1", std::bind(&smart_cache_data::create, 1));
    auto value_2 = smart_cache.create("value_2", std::bind(&smart_cache_data::create, 2));
    auto value_3 = smart_cache.create("value_3", std::bind(&smart_cache_data::create, 3));
    auto value_4 = smart_cache.create("value_4", std::bind(&smart_cache_data::create, 4));
    auto value_5 = smart_cache.create("value_5", std::bind(&smart_cache_data::create, 5));

    ASSERT_EQ(value_1->data, 1);
    ASSERT_EQ(value_2->data, 2);
    ASSERT_EQ(value_3->data, 3);
    ASSERT_EQ(value_4->data, 4);
    ASSERT_EQ(value_5->data, 5);

    i32 iter_smart_cache_count = 0;
    for (const auto& e : smart_cache)
    {
        (void)e;
        ++iter_smart_cache_count;
    }
    ASSERT_EQ(smart_cache.size(), iter_smart_cache_count);
}

TEST(smart_cache, cached_objects_destructor)
{
    global_smart_cache_destructor_count = 0;

    ztd::smart_cache<std::string, smart_cache_data> smart_cache;

    // const i32 count = 1000;
    const i32 count = 100;

    smart_cache.reserve(count);
    for (const auto i : ztd::range(0, count))
    {
        auto value = smart_cache.create(ztd::randhex(), std::bind(&smart_cache_data::create, i));
        ASSERT_EQ(value->data, i);
    }

    ASSERT_EQ(smart_cache.size(), count);
    smart_cache.clear();

    ASSERT_EQ(global_smart_cache_destructor_count, count);
}
