#!/bin/bash

set -e

mkdir -p cmake-build-release
pushd cmake-build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
