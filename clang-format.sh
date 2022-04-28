#!/bin/bash

find ./src/impl -type f | xargs clang-format -i
find ./test/src -type f | xargs clang-format -i
