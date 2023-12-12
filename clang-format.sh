#!/bin/bash

find ./include/ztd -type f | xargs clang-format -i
find ./tests/src -type f | xargs clang-format -i
find ./benchmarks/src -type f | xargs clang-format -i
