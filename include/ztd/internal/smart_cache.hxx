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

#pragma once

#include <vector>

#include <mutex>

#include <memory>

#include <unordered_map>

#include <functional>

#include <cassert>

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
    template<typename KType, typename VType> class smart_cache
    {
      public:
        smart_cache(){};

        // Element access

        [[nodiscard]] const std::shared_ptr<VType>
        at(const KType& key) const
        {
            if (this->storage_.contains(key))
            {
                auto& val = this->storage_.at(key);
                auto ret_val = val.lock();
                return ret_val;
            }
            // throw std::out_of_range("");
            return nullptr;
        }

        // Lookup

        [[nodiscard]] auto
        count(const KType& key) const
        {
            return this->storage_.count(key);
        }

        [[nodiscard]] bool
        contains(const KType& key) const
        {
            if (this->storage_.contains(key))
            {
                auto& val = this->storage_.at(key);
                auto ret_val = val.lock();
                return (ret_val != nullptr);
            }
            return false;
        }

        [[nodiscard]] const std::vector<KType>
        keys() const noexcept
        {
            std::vector<KType> keys;
            for (const auto& pair : this->storage_)
            {
                const auto& key = pair.first;
                if (this->contains(key))
                { // only add valid keys
                    keys.emplace_back(key);
                }
            }
            return keys;
        }

        // Modifiers

        [[nodiscard]] const std::shared_ptr<VType>
        create(const KType& key, const std::function<std::shared_ptr<VType>()>& creator)
        {
            std::scoped_lock<std::mutex> lock(this->lock_);

            if (this->storage_.contains(key))
            {
                auto& val = this->storage_.at(key);
                auto ret_val = val.lock();
                if (ret_val != nullptr)
                {
                    return ret_val;
                } // else fall trough. Because it is weak_ptr cache.
            }

            auto shared_ptr = creator();
            assert(shared_ptr != nullptr);
            std::shared_ptr<VType> ret_val(shared_ptr);
            this->storage_.insert({key, ret_val});
            return ret_val;
        }

        void
        clear() noexcept
        {
            this->storage_.clear();
        }

        void
        erase(const KType& key)
        {
            std::scoped_lock<std::mutex> lock(this->lock_);

            if (this->storage_.contains(key))
            {
                this->storage_.erase(key);
            }
        }

        // clang-format off

        // Capacity

        [[nodiscard]] bool empty() const noexcept { return this->storage_.empty(); }
        [[nodiscard]] auto size() const noexcept { return this->storage_.size(); }

        // Hash policy

        void reserve(std::size_t count) { this->storage_.reserve(count); }

        // clang-format on

      private:
        std::mutex lock_;
        std::unordered_map<KType, std::weak_ptr<VType>, std::hash<KType>> storage_;
    };
} // namespace ztd
