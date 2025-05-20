#!/bin/bash

TARGET_GROUP=${1:-test}
cmake -GNinja -DTARGET_GROUP=$TARGET_GROUP -DCMAKE_C_COMPILER=clang-19 -S . -B build/$TARGET_GROUP
