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

#include <benchmark/benchmark.h>
#include <glibmm.h>

#include "ztd/ztd.hxx"

#define HASH_FILENAME
#define GLIB_CHECKSUM

/**
 *
 * Benchmarks
 *
 */

#if !defined(HASH_FILENAME)
static constexpr auto HASH_STRING =
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed et risus ac felis posuere mattis. Pellentesque "
    "semper mi nunc, at efficitur tellus facilisis quis. Suspendisse euismod massa in lacus commodo varius. Nulla "
    "facilisi. Nulla bibendum eget lectus id consectetur. Sed eu velit tristique, elementum dolor in, vehicula "
    "leo. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Cras vel "
    "sagittis nisl. Nulla facilisi. Proin congue mauris enim, eget maximus sapien tristique eu.";
#else
static constexpr auto HASH_STRING =
    "/usr/lib/llvm/18/include/llvm/Transforms/AggressiveInstCombine/AggressiveInstCombine.h";
#endif

//////////////////////////////

/*
 * ztd::Checksum::Type::MD5
 */
static void
BM_checksum__md5(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)ztd::compute_checksum(ztd::checksum::type::md5, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__md5);

#if defined(GLIB_CHECKSUM)
/*
 * Glib::Checksum::Type::MD5
 */
static void
BM_checksum__md5_glib(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)Glib::Checksum::compute_checksum(Glib::Checksum::Type::MD5, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__md5_glib);
#endif

//////////////////////////////

/*
 * ztd::Checksum::Type::SHA1
 */
static void
BM_checksum__sha1(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)ztd::compute_checksum(ztd::checksum::type::sha1, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__sha1);

#if defined(GLIB_CHECKSUM)
/*
 * Glib::Checksum::Type::SHA1
 */
static void
BM_checksum__sha1_glib(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)Glib::Checksum::compute_checksum(Glib::Checksum::Type::SHA1, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__sha1_glib);
#endif

//////////////////////////////

/*
 * ztd::Checksum::Type::SHA224
 */
static void
BM_checksum__sha224(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)ztd::compute_checksum(ztd::checksum::type::sha224, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__sha224);

//////////////////////////////

/*
 * ztd::Checksum::Type::SHA256
 */
static void
BM_checksum__sha256(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)ztd::compute_checksum(ztd::checksum::type::sha256, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__sha256);

#if defined(GLIB_CHECKSUM)
/*
 * Glib::Checksum::Type::SHA256
 */
static void
BM_checksum__sha256_glib(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)Glib::Checksum::compute_checksum(Glib::Checksum::Type::SHA256, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__sha256_glib);
#endif

//////////////////////////////

/*
 * ztd::Checksum::Type::SHA384
 */
static void
BM_checksum__sha384(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)ztd::compute_checksum(ztd::checksum::type::sha384, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__sha384);

#if defined(GLIB_CHECKSUM)
/*
 * Glib::Checksum::Type::SHA384
 */
static void
BM_checksum__sha384_glib(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)Glib::Checksum::compute_checksum(Glib::Checksum::Type::SHA384, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__sha384_glib);
#endif

//////////////////////////////

/*
 * ztd::Checksum::Type::SHA512
 */
static void
BM_checksum__sha512(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)ztd::compute_checksum(ztd::checksum::type::sha512, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__sha512);

#if defined(GLIB_CHECKSUM)
/*
 * Glib::Checksum::Type::SHA512
 */
static void
BM_checksum__sha512_glib(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)Glib::Checksum::compute_checksum(Glib::Checksum::Type::SHA512, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__sha512_glib);
#endif

//////////////////////////////

/*
 * ztd::Checksum::Type::SHA3_224
 */
static void
BM_checksum__sha3_224(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)ztd::compute_checksum(ztd::checksum::type::sha3_224, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__sha3_224);

//////////////////////////////

/*
 * ztd::Checksum::Type::SHA3_256
 */
static void
BM_checksum__sha3_256(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)ztd::compute_checksum(ztd::checksum::type::sha3_256, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__sha3_256);

//////////////////////////////

/*
 * ztd::Checksum::Type::SHA384
 */
static void
BM_checksum__sha3_384(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)ztd::compute_checksum(ztd::checksum::type::sha3_384, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__sha3_384);

//////////////////////////////

/*
 * ztd::Checksum::Type::SHA512
 */
static void
BM_checksum__sha3_512(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)ztd::compute_checksum(ztd::checksum::type::sha3_512, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__sha3_512);

//////////////////////////////

/*
 * ztd::Checksum::Type::BLAKE2S256
 */
static void
BM_checksum__blake2s256(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)ztd::compute_checksum(ztd::checksum::type::blake2s256, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__blake2s256);

//////////////////////////////

/*
 * ztd::Checksum::Type::BLAKE2B512
 */
static void
BM_checksum__blake2b512(benchmark::State& state)
{
    for (auto _ : state)
    {
        (void)ztd::compute_checksum(ztd::checksum::type::blake2b512, HASH_STRING);
    }
}
BENCHMARK(BM_checksum__blake2b512);
