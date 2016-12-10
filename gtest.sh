#!/bin/bash

set -e

mkdir -p cmake-build-release
pushd cmake-build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make

for PROBLEM in 2*-*; do
	pushd ${PROBLEM}
	./AoC-${PROBLEM}-gtest
	popd
done

popd

