#!/bin/bash

set -e

./build.sh

pushd cmake-build-release
for PROBLEM in 2*-*; do
	pushd ${PROBLEM}
	./AoC-${PROBLEM}-gtest
	popd
done
popd

