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

#include <memory>

#include "ztd/ztd.hxx"

// Counter for destructors to ensure no leaks.
i32 global_smart_cache_destructor_count{0};

struct smart_cache_data
{
    smart_cache_data() {}
    ~smart_cache_data() { ++global_smart_cache_destructor_count; }

    int data{0};
};

std::shared_ptr<smart_cache_data>
create_smart_cache_data()
{
    return std::make_shared<smart_cache_data>();
}

/**
 * ztd::smart_cache weak_smart_cache
 */

TEST(weak_smart_cache, weak_smart_cache)
{
    global_smart_cache_destructor_count = 0;

    ztd::weak_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    auto value_1 = smart_cache.get("value_1");
    auto value_2 = smart_cache.get("value_2");
    auto value_3 = smart_cache.get("value_3");
    auto value_4 = smart_cache.get("value_4");
    auto value_5 = smart_cache.get("value_5");

    value_1->data = 1;
    value_2->data = 2;
    value_3->data = 3;
    value_4->data = 4;
    value_5->data = 5;

    // Check that .get() gets the correct object, while a ref is being held
    ASSERT_EQ(smart_cache.get("value_1")->data, 1);
    ASSERT_EQ(smart_cache.get("value_2")->data, 2);
    ASSERT_EQ(smart_cache.get("value_3")->data, 3);
    ASSERT_EQ(smart_cache.get("value_4")->data, 4);
    ASSERT_EQ(smart_cache.get("value_5")->data, 5);

    // remove ref to objects, destroy the object in cache
    value_1 = nullptr;
    value_2 = nullptr;
    value_3 = nullptr;
    value_4 = nullptr;
    value_5 = nullptr;

    // Check that .get() gets a new object, since no ref is held
    ASSERT_EQ(smart_cache.get("value_1")->data, 0);
    ASSERT_EQ(smart_cache.get("value_2")->data, 0);
    ASSERT_EQ(smart_cache.get("value_3")->data, 0);
    ASSERT_EQ(smart_cache.get("value_4")->data, 0);
    ASSERT_EQ(smart_cache.get("value_5")->data, 0);

    // Check that the created shared_ptr are freed
    smart_cache.clear();
    ASSERT_EQ(global_smart_cache_destructor_count, 10);
}

TEST(weak_smart_cache, self_assign)
{
    global_smart_cache_destructor_count = 0;

    ztd::weak_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    auto value_1 = smart_cache.get("value_1");
    value_1->data = 1;

    value_1 = smart_cache.get("value_1");
    ASSERT_EQ(value_1->data, 1);
    value_1 = nullptr;

    // Check that the externaly created shared_ptr are freed
    smart_cache.clear();
    ASSERT_EQ(global_smart_cache_destructor_count, 1);
}

TEST(weak_smart_cache, remove)
{
    ztd::weak_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    auto value_1 = smart_cache.get("value_1");
    auto value_2 = smart_cache.get("value_2");
    auto value_3 = smart_cache.get("value_3");
    auto value_4 = smart_cache.get("value_4");
    auto value_5 = smart_cache.get("value_5");

    smart_cache.erase("value_1");
    smart_cache.erase("value_2");
    smart_cache.erase("value_3");
    smart_cache.erase("value_4");
    smart_cache.erase("value_5");

    // Check that objects have been removed
    ASSERT_EQ(smart_cache.get("value_1", true), nullptr);
    ASSERT_EQ(smart_cache.get("value_2", true), nullptr);
    ASSERT_EQ(smart_cache.get("value_3", true), nullptr);
    ASSERT_EQ(smart_cache.get("value_4", true), nullptr);
    ASSERT_EQ(smart_cache.get("value_5", true), nullptr);
}

TEST(weak_smart_cache, contains)
{
    ztd::weak_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    auto value_1 = smart_cache.get("value_1");
    auto value_2 = smart_cache.get("value_2");
    auto value_3 = smart_cache.get("value_3");
    auto value_4 = smart_cache.get("value_4");
    auto value_5 = smart_cache.get("value_5");

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

TEST(weak_smart_cache, count)
{
    ztd::weak_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    auto value_1 = smart_cache.get("value_1");
    auto value_2 = smart_cache.get("value_2");
    auto value_3 = smart_cache.get("value_3");
    auto value_4 = smart_cache.get("value_4");
    auto value_5 = smart_cache.get("value_5");

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

TEST(weak_smart_cache, empty)
{
    ztd::weak_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    ASSERT_TRUE(smart_cache.empty());

    auto value_1 = smart_cache.get("value_1");

    ASSERT_FALSE(smart_cache.empty());
}

TEST(weak_smart_cache, size)
{
    ztd::weak_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    auto value_1 = smart_cache.get("value_1");
    auto value_2 = smart_cache.get("value_2");
    auto value_3 = smart_cache.get("value_3");
    auto value_4 = smart_cache.get("value_4");
    auto value_5 = smart_cache.get("value_5");

    value_1->data = 1;
    value_2->data = 2;
    value_3->data = 3;
    value_4->data = 4;
    value_5->data = 5;

    ASSERT_EQ(smart_cache.size(), 5);
    smart_cache.clear();
    ASSERT_EQ(smart_cache.size(), 0);
}

TEST(weak_smart_cache, iterators)
{
    ztd::weak_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    auto value_1 = smart_cache.get("value_1");
    auto value_2 = smart_cache.get("value_2");
    auto value_3 = smart_cache.get("value_3");
    auto value_4 = smart_cache.get("value_4");
    auto value_5 = smart_cache.get("value_5");

    value_1->data = 1;
    value_2->data = 2;
    value_3->data = 3;
    value_4->data = 4;
    value_5->data = 5;

    i32 iter_smart_cache_count = 0;
    for (const auto& e : smart_cache)
    {
        (void)e;
        ++iter_smart_cache_count;
    }
    ASSERT_EQ(smart_cache.size(), iter_smart_cache_count);
}

TEST(weak_smart_cache, cached_objects_destructor)
{
    global_smart_cache_destructor_count = 0;

    ztd::weak_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    // const i32 count = 1000;
    const i32 count = 100;

    smart_cache.reserve(count);
    for (const auto i : ztd::range(0, count))
    {
        auto value = smart_cache.get(ztd::randhex());
        value->data = i;
    }

    ASSERT_EQ(smart_cache.size(), count);
    smart_cache.clear();

    ASSERT_EQ(global_smart_cache_destructor_count, count);
}

/**
 * ztd::smart_cache strong_smart_cache
 */

TEST(strong_smart_cache, strong_smart_cache)
{
    global_smart_cache_destructor_count = 0;

    ztd::strong_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    auto value_1 = smart_cache.get("value_1");
    auto value_2 = smart_cache.get("value_2");
    auto value_3 = smart_cache.get("value_3");
    auto value_4 = smart_cache.get("value_4");
    auto value_5 = smart_cache.get("value_5");

    value_1->data = 1;
    value_2->data = 2;
    value_3->data = 3;
    value_4->data = 4;
    value_5->data = 5;

    // Check that .get() gets the correct object, while a ref is being held
    ASSERT_EQ(smart_cache.get("value_1")->data, 1);
    ASSERT_EQ(smart_cache.get("value_2")->data, 2);
    ASSERT_EQ(smart_cache.get("value_3")->data, 3);
    ASSERT_EQ(smart_cache.get("value_4")->data, 4);
    ASSERT_EQ(smart_cache.get("value_5")->data, 5);

    // remove ref to objects, the object is still held in cache
    value_1 = nullptr;
    value_2 = nullptr;
    value_3 = nullptr;
    value_4 = nullptr;
    value_5 = nullptr;

    // Check that .get() gets the same object
    ASSERT_EQ(smart_cache.get("value_1")->data, 1);
    ASSERT_EQ(smart_cache.get("value_2")->data, 2);
    ASSERT_EQ(smart_cache.get("value_3")->data, 3);
    ASSERT_EQ(smart_cache.get("value_4")->data, 4);
    ASSERT_EQ(smart_cache.get("value_5")->data, 5);

    // Check that the created shared_ptr are freed
    smart_cache.clear();
    ASSERT_EQ(global_smart_cache_destructor_count, 5);
}

TEST(strong_smart_cache, self_assign)
{
    global_smart_cache_destructor_count = 0;

    ztd::strong_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    auto value_1 = smart_cache.get("value_1");
    value_1->data = 1;

    value_1 = smart_cache.get("value_1");
    ASSERT_EQ(value_1->data, 1);
    value_1 = nullptr;

    // Check that the externaly created shared_ptr are freed
    smart_cache.clear();
    ASSERT_EQ(global_smart_cache_destructor_count, 1);
}

TEST(strong_smart_cache, remove)
{
    ztd::strong_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    auto value_1 = smart_cache.get("value_1");
    auto value_2 = smart_cache.get("value_2");
    auto value_3 = smart_cache.get("value_3");
    auto value_4 = smart_cache.get("value_4");
    auto value_5 = smart_cache.get("value_5");

    smart_cache.erase("value_1");
    smart_cache.erase("value_2");
    smart_cache.erase("value_3");
    smart_cache.erase("value_4");
    smart_cache.erase("value_5");

    // Check that objects have been removed
    ASSERT_EQ(smart_cache.get("value_1", true), nullptr);
    ASSERT_EQ(smart_cache.get("value_2", true), nullptr);
    ASSERT_EQ(smart_cache.get("value_3", true), nullptr);
    ASSERT_EQ(smart_cache.get("value_4", true), nullptr);
    ASSERT_EQ(smart_cache.get("value_5", true), nullptr);
}

TEST(strong_smart_cache, contains)
{
    ztd::strong_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    auto value_1 = smart_cache.get("value_1");
    auto value_2 = smart_cache.get("value_2");
    auto value_3 = smart_cache.get("value_3");
    auto value_4 = smart_cache.get("value_4");
    auto value_5 = smart_cache.get("value_5");

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

    ASSERT_TRUE(smart_cache.contains("value_1"));
    ASSERT_TRUE(smart_cache.contains("value_2"));
    ASSERT_TRUE(smart_cache.contains("value_3"));
    ASSERT_TRUE(smart_cache.contains("value_4"));
    ASSERT_TRUE(smart_cache.contains("value_5"));

    // Check keys not in cache
    ASSERT_FALSE(smart_cache.contains("value_6"));
    ASSERT_FALSE(smart_cache.contains("value_7"));
    ASSERT_FALSE(smart_cache.contains("value_8"));
    ASSERT_FALSE(smart_cache.contains("value_9"));
    ASSERT_FALSE(smart_cache.contains("value_10"));
}

TEST(strong_smart_cache, count)
{
    ztd::strong_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    auto value_1 = smart_cache.get("value_1");
    auto value_2 = smart_cache.get("value_2");
    auto value_3 = smart_cache.get("value_3");
    auto value_4 = smart_cache.get("value_4");
    auto value_5 = smart_cache.get("value_5");

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

TEST(strong_smart_cache, empty)
{
    ztd::strong_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    ASSERT_TRUE(smart_cache.empty());

    auto value_1 = smart_cache.get("value_1");

    ASSERT_FALSE(smart_cache.empty());
}

TEST(strong_smart_cache, size)
{
    ztd::strong_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    auto value_1 = smart_cache.get("value_1");
    auto value_2 = smart_cache.get("value_2");
    auto value_3 = smart_cache.get("value_3");
    auto value_4 = smart_cache.get("value_4");
    auto value_5 = smart_cache.get("value_5");

    value_1->data = 1;
    value_2->data = 2;
    value_3->data = 3;
    value_4->data = 4;
    value_5->data = 5;

    ASSERT_EQ(smart_cache.size(), 5);
    smart_cache.clear();
    ASSERT_EQ(smart_cache.size(), 0);
}

TEST(strong_smart_cache, iterators)
{
    ztd::strong_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    auto value_1 = smart_cache.get("value_1");
    auto value_2 = smart_cache.get("value_2");
    auto value_3 = smart_cache.get("value_3");
    auto value_4 = smart_cache.get("value_4");
    auto value_5 = smart_cache.get("value_5");

    value_1->data = 1;
    value_2->data = 2;
    value_3->data = 3;
    value_4->data = 4;
    value_5->data = 5;

    i32 iter_smart_cache_count = 0;
    for (const auto& e : smart_cache)
    {
        (void)e;
        ++iter_smart_cache_count;
    }
    ASSERT_EQ(smart_cache.size(), iter_smart_cache_count);
}

TEST(strong_smart_cache, cached_objects_destructor)
{
    global_smart_cache_destructor_count = 0;

    ztd::strong_smart_cache<std::string, smart_cache_data> smart_cache(create_smart_cache_data);

    // const i32 count = 1000;
    const i32 count = 100;

    smart_cache.reserve(count);
    for (const auto i : ztd::range(0, count))
    {
        auto value = smart_cache.get(ztd::randhex());
        value->data = i;
    }

    ASSERT_EQ(smart_cache.size(), count);
    smart_cache.clear();

    ASSERT_EQ(global_smart_cache_destructor_count, count);
}
