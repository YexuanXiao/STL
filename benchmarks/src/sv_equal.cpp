// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <benchmark/benchmark.h>
#include <string_view>

using namespace std::string_view_literals;
std::string_view haystack[] = {"Lorem"sv, "ipsum"sv, "dolor"sv, "sit a"sv, "met c"sv, "onsec"sv, "tetur"sv, " adip"sv,
    "iscin"sv, "g eli"sv, "t. Nu"sv, "llam "sv};

std::string_view haystack1[std::extent_v<decltype(haystack)>]{};


bool current_equal(const void* lhs, const void* rhs, std::size_t lsize, std::size_t rsize) {
    return lsize == rsize && __builtin_memcmp(lhs, rhs, lsize);
}

bool check_zero_equal(const void* lhs, const void* rhs, std::size_t lsize, std::size_t rsize) {
    if (lsize != rsize) {
        return false;
    }
    if (lsize == 0u) {
        return true;
    }
    return __builtin_memcmp(lhs, rhs, lsize);
}

void curr_short(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(haystack);
        for (auto& i : haystack) {
            benchmark::DoNotOptimize(i);
            auto res = current_equal(i.data(), haystack[0].data(), i.size(), haystack[0].size());
            benchmark::DoNotOptimize(res);
        }
    }
}

void czl_short(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(haystack);
        for (auto& i : haystack) {
            benchmark::DoNotOptimize(i);
            auto res = check_zero_equal(i.data(), haystack[0].data(), i.size(), haystack[0].size());
            benchmark::DoNotOptimize(res);
        }
    }
}

void curr_empty(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(haystack1);
        for (auto& i : haystack1) {
            benchmark::DoNotOptimize(i);
            auto res = current_equal(i.data(), haystack1[0].data(), i.size(), haystack1[0].size());
            benchmark::DoNotOptimize(res);
        }
    }
}

void czl_empty(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(haystack1);
        for (auto& i : haystack1) {
            benchmark::DoNotOptimize(i);
            auto res = check_zero_equal(i.data(), haystack1[0].data(), i.size(), haystack1[0].size());
            benchmark::DoNotOptimize(res);
        }
    }
}


BENCHMARK(curr_empty);
BENCHMARK(czl_empty);
BENCHMARK(curr_short);
BENCHMARK(czl_short);


BENCHMARK_MAIN();
