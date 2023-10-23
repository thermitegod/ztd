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
     * weak_smart_cache, the cache instance will release when nobody hold a reference to it.
     *
     * It store a object instance global. User can invoke get method by key.
     * If there is a instance stored in cache, then it will return a shared_ptr of it,
     * otherwise, it will invoke creator callback, create a new instance store global,
     * and return it.
     *
     * The KType is the key type.
     * The VType is the value type.
     */
    template<typename KType, typename VType> class weak_smart_cache
    {
      public:
        weak_smart_cache(const std::function<std::shared_ptr<VType>()>& creator) : creator_(creator) {}

        [[nodiscard]] std::shared_ptr<VType>
        get(const KType& key, const bool existing_only = false)
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

            if (existing_only)
            {
                return nullptr;
            }

            auto shared_ptr = this->creator_();
            assert(shared_ptr != nullptr);
            std::shared_ptr<VType> ret_val(shared_ptr);
            this->storage_.insert({key, ret_val});
            return ret_val;
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

        // Modifiers

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
        [[nodiscard]] auto max_size() const noexcept { return this->storage_.max_size(); }

        // Iterators

        [[nodiscard]] auto begin() const noexcept { return this->storage_.cbegin(); }
        [[nodiscard]] auto cbegin() const noexcept { return this->storage_.cbegin(); }

        [[nodiscard]] auto end() const noexcept { return this->storage_.cend(); }
        [[nodiscard]] auto cend() const noexcept { return this->storage_.cend(); }

        [[nodiscard]] auto rbegin() const noexcept { return this->storage_.crbegin(); }
        [[nodiscard]] auto crbegin() const noexcept { return this->storage_.crbegin(); }

        [[nodiscard]] auto rend() const noexcept { return this->storage_.crend(); }
        [[nodiscard]] auto crend() const noexcept { return this->storage_.crend(); }

        // Hash policy

        void reserve(std::size_t count) { this->storage_.reserve(count); }

        // clang-format on

      private:
        std::mutex lock_;
        std::function<std::shared_ptr<VType>()> creator_;
        std::unordered_map<KType, std::weak_ptr<VType>, std::hash<KType>> storage_;
    };

    /**
     * Smart Pointer Key-Value Cache
     *
     * strong_smart_cache, the cache instance will never release.
     *
     * It store a object instance global. User can invoke get method by key.
     * If there is a instance stored in cache, then it will return a shared_ptr of it,
     * otherwise, it will invoke creator callback, create a new instance store global,
     * and return it.
     *
     * The KType is the key type.
     * The VType is the value type.
     */
    template<typename KType, typename VType> class strong_smart_cache
    {
      public:
        strong_smart_cache(const std::function<std::shared_ptr<VType>()>& creator) : creator_(creator) {}

        [[nodiscard]] std::shared_ptr<VType>
        get(const KType& key, const bool existing_only = false)
        {
            std::scoped_lock<std::mutex> lock(this->lock_);

            if (this->storage_.contains(key))
            {
                auto& val = this->storage_.at(key);
                return val;
            }
            else
            {
                if (existing_only)
                {
                    return nullptr;
                }

                auto shared_ptr = this->creator_();
                assert(shared_ptr != nullptr);
                std::shared_ptr<VType> ret_val(shared_ptr);
                this->storage_.insert({key, ret_val});
                return ret_val;
            }
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
                return this->storage_.at(key) != nullptr;
            }
            return false;
        }

        // Modifiers

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
        [[nodiscard]] auto max_size() const noexcept { return this->storage_.max_size(); }

        // Iterators

        [[nodiscard]] auto begin() const noexcept { return this->storage_.cbegin(); }
        [[nodiscard]] auto cbegin() const noexcept { return this->storage_.cbegin(); }

        [[nodiscard]] auto end() const noexcept { return this->storage_.cend(); }
        [[nodiscard]] auto cend() const noexcept { return this->storage_.cend(); }

        [[nodiscard]] auto rbegin() const noexcept { return this->storage_.crbegin(); }
        [[nodiscard]] auto crbegin() const noexcept { return this->storage_.crbegin(); }

        [[nodiscard]] auto rend() const noexcept { return this->storage_.crend(); }
        [[nodiscard]] auto crend() const noexcept { return this->storage_.crend(); }

        // Hash policy

        void reserve(std::size_t count) { this->storage_.reserve(count); }

        // clang-format on

      private:
        std::mutex lock_;
        std::function<std::shared_ptr<VType>()> creator_;
        std::unordered_map<KType, std::shared_ptr<VType>, std::hash<KType>> storage_;
    };
} // namespace ztd
