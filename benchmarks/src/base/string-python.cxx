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

#include <format>
#include <string>
#include <string_view>
#include <vector>

#include <benchmark/benchmark.h>

#include "src/utils.hxx"
#include "ztd/ztd.hxx"

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

        (void)ztd::split(test_str, " ");
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

        (void)ztd::rsplit(test_str, " ");
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

        (void)ztd::join(test_vec, " ");
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

        (void)ztd::lower(test_str);
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

        (void)ztd::upper(test_str);
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

        (void)ztd::replace(test_str, "foo", "bar");
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

        (void)ztd::capitalize(test_str);
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
        (void)ztd::center(str, state.range(0));
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

        (void)ztd::count(test_str, "f");
    }
}
BENCHMARK(BM_python__count)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);

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

        (void)ztd::expandtabs(test_str);
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

        (void)ztd::isalnum(str);
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

        (void)ztd::isalpha(str);
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

        (void)ztd::isdecimal(str);
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

        (void)ztd::islower(str);
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

        (void)ztd::isupper(str);
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

        (void)ztd::isspace(str);
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

        (void)ztd::istitle(str);
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

        (void)ztd::title(str);
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

        (void)ztd::swapcase(str);
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
        (void)ztd::ljust(str, state.range(0));
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
        (void)ztd::rjust(str, state.range(0));
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
        const std::string str = std::format("{}{}", padding, end);
        state.ResumeTiming();

        (void)ztd::lstrip(str);
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
        const std::string str = std::format("{}{}", start, padding);
        state.ResumeTiming();

        (void)ztd::rstrip(str);
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
        const std::string str = std::format("{}{}{}", padding, start, padding);
        state.ResumeTiming();

        (void)ztd::rstrip(str);
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
        const std::string str = std::format("{}{}", prefix, start);
        state.ResumeTiming();

        (void)ztd::removeprefix(str, prefix);
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
        const std::string str = std::format("{}{}", start, suffix);
        state.ResumeTiming();

        (void)ztd::removesuffix(str, suffix);
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
        const std::string str = std::format("{}{}{}", ends, sep, ends);
        state.ResumeTiming();

        (void)ztd::partition(str, sep);
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
        const std::string str = std::format("{}{}{}", ends, sep, ends);
        state.ResumeTiming();

        (void)ztd::partition(str, sep);
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
        const std::string str = std::format("{}{}{}", ends, sep, ends);
        state.ResumeTiming();

        (void)ztd::rpartition(str, sep);
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
        const std::string str = std::format("{}{}{}", ends, sep, ends);
        state.ResumeTiming();

        (void)ztd::rpartition(str, sep);
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
        (void)ztd::zfill(str, state.range(0));
    }
}
BENCHMARK(BM_python__zfill)->Arg(1)->Arg(10)->Arg(100)->Arg(1000);
