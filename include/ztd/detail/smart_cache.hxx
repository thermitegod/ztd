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

#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <vector>

#include "panic.hxx"

// Based on <https://gist.github.com/reyoung/87f230ebc0dfc242ad90>

namespace ztd
{
/**
 * Smart Pointer Key-Value Cache
 *
 * smart_cache, the cache instance will release when nobody hold a reference to it.
 *
 * It store a object instance global. User can invoke get method by key.
 * If there is a instance stored in cache, then it will return a shared_ptr of it,
 * otherwise, it will return a nullptr;
 *
 * The KType is the key type.
 * The VType is the value type.
 */
template<typename KType, typename VType> class smart_cache final
{
  public:
    smart_cache() = default;
    smart_cache(const smart_cache&) = delete;
    smart_cache& operator=(const smart_cache&) = delete;
    smart_cache(smart_cache&&) noexcept = delete;
    smart_cache& operator=(smart_cache&&) noexcept = delete;
    ~smart_cache() = default;

    // Element access

    [[nodiscard]] std::shared_ptr<VType>
    at(const KType& key) const noexcept
    {
        std::shared_lock lock(lock_);

        auto it = storage_.find(key);
        if (it != storage_.end())
        {
            return it->second.lock();
        }
        return nullptr;
    }

    // Lookup

    [[nodiscard]] auto
    count(const KType& key) const noexcept
    {
        std::shared_lock lock(lock_);

        return storage_.count(key);
    }

    [[nodiscard]] bool
    contains(const KType& key) const noexcept
    {
        std::shared_lock lock(lock_);

        auto it = storage_.find(key);
        if (it != storage_.end())
        {
            return (it->second.lock() != nullptr);
        }
        return false;
    }

    [[nodiscard]] std::vector<KType>
    keys() const noexcept
    {
        std::shared_lock lock(lock_);

        std::vector<KType> keys;
        for (const auto& [key, val] : storage_)
        {
            if (val.lock() != nullptr)
            {
                keys.emplace_back(key);
            }
        }
        return keys;
    }

    [[nodiscard]] std::vector<std::shared_ptr<VType>>
    items() const noexcept
    {
        std::shared_lock lock(lock_);

        std::vector<std::shared_ptr<VType>> items;
        for (const auto& [key, val] : storage_)
        {
            auto shared_ptr = val.lock();
            if (shared_ptr != nullptr)
            {
                items.emplace_back(shared_ptr);
            }
        }
        return items;
    }

    // Modifiers

    [[nodiscard]] std::shared_ptr<VType>
    create(const KType& key, std::copyable_function<std::shared_ptr<VType>()> creator,
           const bool keep_internal_reference = false)
    {
        std::unique_lock lock(lock_);

        auto it = storage_.find(key);
        if (it != storage_.end())
        {
            if (auto ret_val = it->second.lock(); ret_val != nullptr)
            {
                return ret_val;
            } // else fall through because it is a weak_ptr cache.
        }

        std::shared_ptr<VType> shared_ptr;
        try
        {
            shared_ptr = creator();
        }
        catch (...)
        {
            return nullptr;
        }

        std::shared_ptr<VType> ret_val(shared_ptr);
        storage_.insert_or_assign(key, ret_val);

        if (keep_internal_reference)
        {
            storage_permanent_.insert_or_assign(key, ret_val);
        }

        return ret_val;
    }

    void
    clear() noexcept
    {
        std::unique_lock lock(lock_);

        storage_permanent_.clear();
        storage_.clear();
    }

    void
    erase(const KType& key) noexcept
    {
        std::unique_lock lock(lock_);

        storage_permanent_.erase(key);
        storage_.erase(key);
    }

    // Capacity

    [[nodiscard]] bool
    empty() const noexcept
    {
        std::shared_lock lock(lock_);

        for (const auto& [key, val] : storage_)
        {
            if (val.lock() != nullptr)
            {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] auto
    size() const noexcept
    {
        std::shared_lock lock(lock_);

        std::size_t count = 0;
        for (const auto& [key, val] : storage_)
        {
            if (val.lock() != nullptr)
            {
                count += 1;
            }
        }
        return count;
    }

  private:
    mutable std::shared_mutex lock_;

    std::unordered_map<KType, std::weak_ptr<VType>> storage_;
    // This is only used to hold a reference to prevent an object from being deleted
    // when no one else holds a reference.
    std::unordered_map<KType, std::shared_ptr<VType>> storage_permanent_;
};
} // namespace ztd
