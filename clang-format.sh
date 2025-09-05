#!/usr/bin/env bash

find \
    ./include \
    ./tests \
    ./benchmarks \
    -iname '*.cxx' -o -iname '*.hxx' | \
    clang-format -i --files=/dev/stdin
