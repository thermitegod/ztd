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

#include <doctest/doctest.h>

#include <string>

#include "ztd/detail/checksum.hxx"

// clang-format off
static const std::string HASH_STRING =
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed et risus ac felis posuere mattis. Pellentesque "
    "semper mi nunc, at efficitur tellus facilisis quis. Suspendisse euismod massa in lacus commodo varius. Nulla "
    "facilisi. Nulla bibendum eget lectus id consectetur. Sed eu velit tristique, elementum dolor in, vehicula "
    "leo. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Cras vel "
    "sagittis nisl. Nulla facilisi. Proin congue mauris enim, eget maximus sapien tristique eu.";

static const std::string HASH_STRING_MD5 = "24c2eda70fe378d52b14be0b08385170";
static const std::string HASH_STRING_SHA1 = "0b617f03be4df1295156d598985c86532fefc814";
static const std::string HASH_STRING_SHA224 = "64a761dca9403cf5d6fd4f16240445582848040eabc99b81c4ed3e3c";
static const std::string HASH_STRING_SHA256 = "7c1ea8dd661ab58ee467bf59a8e598c382c0166c8b0e2e8902fe537f0d50911f";
static const std::string HASH_STRING_SHA384 = "5aaa5890106767a06cf42ede47049173a4ce2e7e27e854f2de96220cc6fa84bacd2ffb64edfef57a4722a7fc01f4fc43";
static const std::string HASH_STRING_SHA512 = "b03d5c3bab6f0d56499a017879e1c9cb3ac7a23ef5efec9d5ad843f13a941e24bebaff5adca3dd91cd27403e48a9ca58863da5e1c70359529c65fbffedc650ea";
static const std::string HASH_STRING_SHA3_224 = "64a6174b935c5ae6a8b7be031d4776f2aea426bdc38993f75492b81b";
static const std::string HASH_STRING_SHA3_256 = "1fa7e4fcfd5d4986bd66137f8f5e15f4e5bf372eccef5f1eb1bb68e45c23a42e";
static const std::string HASH_STRING_SHA3_384 = "97747cbc84befb6994656a95fd8ece0ae9db510e237079440151993334f40a6cb91ec25c933263e39a503daa7f0d890e";
static const std::string HASH_STRING_SHA3_512 = "a6049eb09e4156cd7806a4c68c7ea53980eb42c2b7e86c301ddb57dbba3417e8ff5fd5f70ded39f87f703fb0f74ca2858febdd7a13dc766186fc8e1fa7bf9b10";
static const std::string HASH_STRING_BLAKE2S256 = "9e4705a0c5d7a1dbf7724b4dde5c087290acf88b505938d71227c334b7544e9a";
static const std::string HASH_STRING_BLAKE2B512 = "dace550f0dc407d7d399a3aff1e2798c7d87107d1fb8754cd590fe54564703c93f667cbb9b962b85572f76da74c7eca29bb4db23d47f0ef5162aa8ebcbf64923";
// clang-format on

TEST_SUITE("ztd::checksum" * doctest::description(""))
{
    TEST_CASE("ztd::checksum()")
    {
        auto check = ztd::checksum();

        SUBCASE("md5")
        {
            const auto hash = check.compute_checksum(ztd::checksum::type::md5, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_MD5);
        }
        SUBCASE("sha1")
        {
            const auto hash = check.compute_checksum(ztd::checksum::type::sha1, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA1);
        }
        SUBCASE("sha224")
        {
            const auto hash = check.compute_checksum(ztd::checksum::type::sha224, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA224);
        }
        SUBCASE("sha256")
        {
            const auto hash = check.compute_checksum(ztd::checksum::type::sha256, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA256);
        }
        SUBCASE("sha384")
        {
            const auto hash = check.compute_checksum(ztd::checksum::type::sha384, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA384);
        }
        SUBCASE("sha512")
        {
            const auto hash = check.compute_checksum(ztd::checksum::type::sha512, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA512);
        }
        SUBCASE("sha3_224")
        {
            const auto hash = check.compute_checksum(ztd::checksum::type::sha3_224, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA3_224);
        }
        SUBCASE("sha3_256")
        {
            const auto hash = check.compute_checksum(ztd::checksum::type::sha3_256, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA3_256);
        }
        SUBCASE("sha3_384")
        {
            const auto hash = check.compute_checksum(ztd::checksum::type::sha3_384, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA3_384);
        }
        SUBCASE("sha3_512")
        {
            const auto hash = check.compute_checksum(ztd::checksum::type::sha3_512, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA3_512);
        }
        SUBCASE("blake2b512")
        {
            const auto hash = check.compute_checksum(ztd::checksum::type::blake2b512, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_BLAKE2B512);
        }
        SUBCASE("blake2s256")
        {
            const auto hash = check.compute_checksum(ztd::checksum::type::blake2s256, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_BLAKE2S256);
        }
    }

    TEST_CASE("compute_checksum()")
    {
        SUBCASE("md5")
        {
            const auto hash = ztd::compute_checksum(ztd::checksum::type::md5, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_MD5);
        }
        SUBCASE("sha1")
        {
            const auto hash = ztd::compute_checksum(ztd::checksum::type::sha1, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA1);
        }
        SUBCASE("sha224")
        {
            const auto hash = ztd::compute_checksum(ztd::checksum::type::sha224, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA224);
        }
        SUBCASE("sha256")
        {
            const auto hash = ztd::compute_checksum(ztd::checksum::type::sha256, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA256);
        }
        SUBCASE("sha384")
        {
            const auto hash = ztd::compute_checksum(ztd::checksum::type::sha384, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA384);
        }
        SUBCASE("sha512")
        {
            const auto hash = ztd::compute_checksum(ztd::checksum::type::sha512, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA512);
        }
        SUBCASE("sha3_224")
        {
            const auto hash = ztd::compute_checksum(ztd::checksum::type::sha3_224, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA3_224);
        }
        SUBCASE("sha3_256")
        {
            const auto hash = ztd::compute_checksum(ztd::checksum::type::sha3_256, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA3_256);
        }
        SUBCASE("sha3_384")
        {
            const auto hash = ztd::compute_checksum(ztd::checksum::type::sha3_384, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA3_384);
        }
        SUBCASE("sha3_512")
        {
            const auto hash = ztd::compute_checksum(ztd::checksum::type::sha3_512, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_SHA3_512);
        }
        SUBCASE("blake2b512")
        {
            const auto hash = ztd::compute_checksum(ztd::checksum::type::blake2b512, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_BLAKE2B512);
        }
        SUBCASE("blake2s256")
        {
            const auto hash = ztd::compute_checksum(ztd::checksum::type::blake2s256, HASH_STRING);
            CHECK_EQ(hash, HASH_STRING_BLAKE2S256);
        }
    }
}
