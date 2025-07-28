#!/bin/bash

find ./include/ztd -iname '*.cxx' -o -iname '*.hxx' | xargs --max-args=$(nproc) clang-format -i
find ./tests/src -iname '*.cxx' -o -iname '*.hxx' | xargs --max-args=$(nproc) clang-format -i
find ./benchmarks/src -iname '*.cxx' -o -iname '*.hxx' | xargs --max-args=$(nproc) clang-format -i
