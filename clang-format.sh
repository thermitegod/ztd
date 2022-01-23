#!/bin/bash

find ./src -maxdepth 1 -o -iname *.hxx -o -iname *.cxx -o -iname *.ixx | xargs clang-format -i

