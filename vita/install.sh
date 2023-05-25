#!/bin/bash

mkdir -p build
cd build
cmake -DBUILD_VITA:BOOLEAN=true .. && make
