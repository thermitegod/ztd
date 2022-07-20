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

#include <string>
#include <string_view>

#include <vector>

#include <benchmark/benchmark.h>

#include <fmt/format.h>

#include "ztd/ztd.hxx"

#include "src/utils.hxx"

/**
 *
 * Benchmarks
 *
 */

/*
 * split
 */
static void
BM_python__split(benchmark::State& state)
{
    const std::string str = "foo ";

    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string test_str = create_repeat_string(str, state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::split(test_str, " "));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__split)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/*
 * rsplit
 */
static void
BM_python__rsplit(benchmark::State& state)
{
    const std::string str = "foo ";

    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string test_str = create_repeat_string(str, state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::rsplit(test_str, " "));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__rsplit)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/*
 * join
 */
static void
BM_python__join(benchmark::State& state)
{
    const std::string str = "foobar";

    for (auto _ : state)
    {
        state.PauseTiming();
        const std::vector<std::string> test_vec = create_repeat_vector(str, state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::join(test_vec, " "));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__join)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/*
 * lower
 */
static void
BM_python__lower(benchmark::State& state)
{
    const std::string str = "ABCDEFGHIJKLMNOPQRSTUVWXY";

    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string test_str = create_repeat_string(str, state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::lower(test_str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__lower)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/*
 * upper
 */
static void
BM_python__upper(benchmark::State& state)
{
    const std::string str = "abcdefghijklmnopqrstuvwxy";

    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string test_str = create_repeat_string(str, state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::upper(test_str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__upper)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * replace
 */
static void
BM_python__replace(benchmark::State& state)
{
    const std::string str = "foobar";

    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string test_str = create_repeat_string(str, state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::replace(test_str, "foo", "bar"));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__replace)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * capitalize
 */
static void
BM_python__capitalize(benchmark::State& state)
{
    const std::string str = "foobar";

    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string test_str = create_repeat_string(str, state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::capitalize(test_str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__capitalize)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * capitalize
 */
static void
BM_python__center(benchmark::State& state)
{
    const std::string str = "foobar";

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(ztd::center(str, state.range(0)));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__center)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * count
 */
static void
BM_python__count(benchmark::State& state)
{
    const std::string str = "foobar";

    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string test_str = create_repeat_string(str, state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::count(test_str, "f"));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__count)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/*
 * endswith
 */
static void
BM_python__endswith(benchmark::State& state)
{
    const std::string str = "foobar";

    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string test_str = create_repeat_string(str, state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::endswith(test_str, "bar"));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__endswith)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * endswith vector overload
 */
static void
BM_python__endswith_vector1(benchmark::State& state)
{
    const std::string str = "foobar";
    const std::vector<std::string> suffixes = {"bar"};

    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string test_str = create_repeat_string(str, state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::endswith(test_str, suffixes));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__endswith_vector1)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

static void
BM_python__endswith_vector2(benchmark::State& state)
{
    const std::string str = "foobar";
    const std::vector<std::string> suffixes = {"foo", "bar"};

    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string test_str = create_repeat_string(str, state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::endswith(test_str, suffixes));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__endswith_vector2)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/*
 * startswith
 */
static void
BM_python__startswith(benchmark::State& state)
{
    const std::string str = "foobar";

    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string test_str = create_repeat_string(str, state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::startswith(test_str, "foo"));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__startswith)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * startswith vector overload
 */
static void
BM_python__startswith_vector1(benchmark::State& state)
{
    const std::string str = "foobar";
    const std::vector<std::string> suffixes = {"bar"};

    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string test_str = create_repeat_string(str, state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::startswith(test_str, suffixes));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__startswith_vector1)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

static void
BM_python__startswith_vector2(benchmark::State& state)
{
    const std::string str = "foobar";
    const std::vector<std::string> suffixes = {"foo", "bar"};

    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string test_str = create_repeat_string(str, state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::startswith(test_str, suffixes));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__startswith_vector2)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/*
 * expandtabs
 */
static void
BM_python__expandtabs(benchmark::State& state)
{
    const std::string str = "01\t012\t0123\t01234";

    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string test_str = create_repeat_string(str, state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::expandtabs(test_str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__expandtabs)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * isalnum
 */
static void
BM_python__isalnum(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string str = create_repeat_string("a1", state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::isalnum(str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__isalnum)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * isalpha
 */
static void
BM_python__isalpha(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string str = create_repeat_string("a", state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::isalpha(str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__isalpha)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * isdecimal
 */
static void
BM_python__isdecimal(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string str = create_repeat_string("5", state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::isdecimal(str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__isdecimal)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * islower
 */
static void
BM_python__islower(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string str = create_repeat_string("a", state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::islower(str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__islower)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * isupper
 */
static void
BM_python__isupper(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string str = create_repeat_string("A", state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::isupper(str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__isupper)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * isspace
 */
static void
BM_python__isspace(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string str = create_repeat_string(" ", state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::isspace(str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__isspace)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * istitle
 */
static void
BM_python__istitle(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string str = create_repeat_string("Title ", state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::istitle(str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__istitle)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * title
 */
static void
BM_python__title(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string str = create_repeat_string("title ", state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::title(str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__title)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * swapcase
 */
static void
BM_python__swapcase(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string str = create_repeat_string("StRiNg", state.range(0));
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::swapcase(str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__swapcase)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * ljust
 */
static void
BM_python__ljust(benchmark::State& state)
{
    const std::string str = "ZZZ";

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(ztd::ljust(str, state.range(0)));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__ljust)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * rjust
 */
static void
BM_python__rjust(benchmark::State& state)
{
    const std::string str = "ZZZ";

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(ztd::rjust(str, state.range(0)));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__rjust)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * lstrip
 */
static void
BM_python__lstrip(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string end = "ZZZ";
        const std::string padding = create_repeat_string(" ", state.range(0));
        const std::string str = fmt::format("{}{}", padding, end);
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::lstrip(str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__lstrip)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * rstrip
 */
static void
BM_python__rstrip(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string start = "ZZZ";
        const std::string padding = create_repeat_string(" ", state.range(0));
        const std::string str = fmt::format("{}{}", start, padding);
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::rstrip(str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__rstrip)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * strip
 */
static void
BM_python__strip(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string start = "ZZZ";
        const std::string padding = create_repeat_string(" ", state.range(0));
        const std::string str = fmt::format("{}{}{}", padding, start, padding);
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::rstrip(str));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__strip)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * removeprefix
 */
static void
BM_python__removeprefix(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string start = "ZZZ";
        const std::string prefix = create_repeat_string("X", state.range(0));
        const std::string str = fmt::format("{}{}", prefix, start);
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::removeprefix(str, prefix));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__removeprefix)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * removesuffix
 */
static void
BM_python__removesuffix(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string start = "ZZZ";
        const std::string suffix = create_repeat_string("X", state.range(0));
        const std::string str = fmt::format("{}{}", start, suffix);
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::removesuffix(str, suffix));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__removesuffix)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * partition
 */
static void
BM_python__partition__single(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string sep = "Z";
        const std::string ends = create_repeat_string("x", state.range(0));
        const std::string str = fmt::format("{}{}{}", ends, sep, ends);
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::partition(str, sep));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__partition__single)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

static void
BM_python__partition__multi(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string sep = "bar";
        const std::string ends = create_repeat_string("x", state.range(0));
        const std::string str = fmt::format("{}{}{}", ends, sep, ends);
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::partition(str, sep));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__partition__multi)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * rpartition
 */
static void
BM_python__rpartition__single(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string sep = "Z";
        const std::string ends = create_repeat_string("x", state.range(0));
        const std::string str = fmt::format("{}{}{}", ends, sep, ends);
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::rpartition(str, sep));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__rpartition__single)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

static void
BM_python__rpartition__multi(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        const std::string sep = "bar";
        const std::string ends = create_repeat_string("x", state.range(0));
        const std::string str = fmt::format("{}{}{}", ends, sep, ends);
        state.ResumeTiming();

        benchmark::DoNotOptimize(ztd::rpartition(str, sep));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__rpartition__multi)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

/**
 * zfill
 */
static void
BM_python__zfill(benchmark::State& state)
{
    const std::string str = "foobar";

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(ztd::zfill(str, state.range(0)));
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_python__zfill)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);
