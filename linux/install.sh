#!/bin/bash

mkdir -p build
cd build
cmake -DBOX2D_BUILD_UNIT_TESTS:BOOLEAN=False -DBOX2D_BUILD_TESTBED:BOOLEAN=False .. && make
