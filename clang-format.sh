#!/bin/bash

find ./src -type f | xargs clang-format -i
find ./include/ztd -type f | xargs clang-format -i
find ./tests/src -type f | xargs clang-format -i
