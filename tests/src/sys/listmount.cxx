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

#include <algorithm>
#include <expected>
#include <filesystem>
#include <limits>
#include <system_error>
#include <unordered_set>
#include <vector>

#include <cstdint>

#include <doctest/doctest.h>

#include "ztd/detail/sys/listmount.hxx"
#include "ztd/detail/sys/statmount.hxx"

TEST_SUITE("ztd::listmount")
{
    TEST_CASE("create")
    {
        SUBCASE("default")
        {
            const auto result = ztd::listmount::create();

            REQUIRE(result.has_value());

            CHECK_FALSE(result->empty());
            CHECK(result->size() > 0uz);
        }

        SUBCASE("unique mount IDs")
        {
            const auto result = ztd::listmount::create();

            REQUIRE(result.has_value());

            std::unordered_set<std::uint64_t> unique_ids;

            for (const auto mnt_id : *result)
            {
                CHECK(mnt_id != 0);
                CHECK(unique_ids.insert(mnt_id).second);
            }
        }

        SUBCASE("check iteration")
        {
            const auto result = ztd::listmount::create();

            REQUIRE(result.has_value());

            std::size_t count = 0;
            for (const auto _ : *result)
            {
                ++count;
            }

            CHECK(count == result->size());
        }

        SUBCASE("repeated calls")
        {
            const auto first = ztd::listmount::create();
            const auto second = ztd::listmount::create();

            REQUIRE(first.has_value());
            REQUIRE(second.has_value());

            CHECK(first->size() == second->size());
        }

        SUBCASE("invalid parent mount ID")
        {
            // note, LSMT_ROOT is UINT64_MAX
            const auto result =
                ztd::listmount::create(std::numeric_limits<std::uint64_t>::max() - 1);

            REQUIRE_FALSE(result.has_value());

            CHECK(result.error());
        }

        SUBCASE("builtin statmount creator")
        {
            const auto mounts = ztd::listmount::create();

            REQUIRE(mounts.has_value());
            REQUIRE_FALSE(mounts->empty());

            CHECK(mounts->statmounts().size() == mounts->size());
        }

#if defined(NON_PORTABLE_TESTS)
        SUBCASE("pagination batch size testing")
        {
            // test pagination using a small batch_size get all mounts
            const auto result = ztd::listmount::create();

            REQUIRE(result.has_value());

            CHECK_FALSE(result->empty());
            CHECK(result->size() == 46uz);
        }

        SUBCASE("builtin statmount creator testing")
        {
            const auto mounts = ztd::listmount::create();

            REQUIRE(mounts.has_value());
            REQUIRE_FALSE(mounts->empty());

            auto statmounts = mounts->statmounts();

            CHECK(statmounts.size() == mounts->size());

            CHECK(mounts->size() == 46uz);
            CHECK(statmounts.size() == 46uz);
        }
#endif
    }
}

TEST_SUITE("ztd::statmount")
{
    TEST_CASE("create")
    {
        SUBCASE("retrieves metadata for a valid mount ID")
        {
            const auto mounts = ztd::listmount::create();

            REQUIRE(mounts.has_value());
            REQUIRE_FALSE(mounts->empty());

            const auto mnt_id = mounts->front();
            const auto result = ztd::statmount::create(mnt_id);

            REQUIRE(result.has_value());

            CHECK(result->mnt_id() == mnt_id);
            CHECK(result->mnt_parent_id() != 0);
        }

        SUBCASE("filesystem information")
        {
            const auto mounts = ztd::listmount::create();

            REQUIRE(mounts.has_value());
            REQUIRE_FALSE(mounts->empty());

            const auto result = ztd::statmount::create(mounts->front());

            REQUIRE(result.has_value());

            CHECK_FALSE(result->root().empty());
            CHECK_FALSE(result->mount_point().empty());
            CHECK_FALSE(result->fs_type().empty());
        }

        SUBCASE("manually create statmounts from listmount")
        {
            const auto mounts = ztd::listmount::create();

            REQUIRE(mounts.has_value());
            REQUIRE_FALSE(mounts->empty());

            std::vector<ztd::statmount> statmounts;

            for (const auto mnt_id : *mounts)
            {
                const auto result = ztd::statmount::create(mnt_id);

                REQUIRE(result.has_value());
                CHECK(result->mnt_id() == mnt_id);

                statmounts.emplace_back(*result);
            }

            CHECK(mounts->size() == statmounts.size());
        }

        SUBCASE("invalid mount ID")
        {
            const auto result = ztd::statmount::create(std::numeric_limits<std::uint64_t>::max());

            REQUIRE_FALSE(result.has_value());

            CHECK(result.error());
        }

#if defined(NON_PORTABLE_TESTS)
        SUBCASE("testing")
        {
            const auto mounts = ztd::listmount::create();

            REQUIRE(mounts.has_value());
            REQUIRE_FALSE(mounts->empty());

            const auto mnt_id = mounts->front();
            const auto result = ztd::statmount::create(mnt_id);

            REQUIRE(result.has_value());

            // Mount identification
            CHECK(result->mnt_id() == 2147483724);
            CHECK(result->mnt_parent_id() == 2147483650);
            CHECK(result->mnt_id_old() == 52);
            CHECK(result->mnt_parent_id_old() == 1);
            CHECK(result->mnt_ns_id() == 4);

            // Superblock information
            CHECK(result->dev() == 24);
            CHECK(result->dev_major() == 0);
            CHECK(result->dev_minor() == 24);
            CHECK(result->magic() == 801189825);
            CHECK(result->sb_flags() == 0);

            // Mount attributes and propagation
            CHECK(result->mnt_attr() == 16);
            CHECK(result->mnt_propagation() == 1048576);
            CHECK(result->mnt_peer_group() == 1);
            CHECK(result->mnt_master() == 0);
            CHECK(result->propagate_from() == 0);

            // Filesystem
            CHECK(result->root() == "/");
            CHECK(result->mount_point() == "/");
            CHECK(result->fs_type() == "zfs");
            CHECK(result->fs_subtype() == "");
            CHECK(result->source() == "zroot/ROOT/gentoo");
            CHECK(result->options() == "xattr,posixacl,casesensitive");
        }
#endif
    }
}
