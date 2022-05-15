#!/bin/bash

find ./src/impl -type f | xargs clang-format -i
find ./tests/src -type f | xargs clang-format -i
