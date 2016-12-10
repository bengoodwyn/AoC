#!/bin/bash

set -e

./build.sh

pushd cmake-build-release
for PROBLEM in 2*-*; do
	pushd ../${PROBLEM}
	echo "${PROBLEM} - Part 1"
	RESULT=$(../cmake-build-release/${PROBLEM}/AoC-${PROBLEM} 1)
	if [ -e integration-part1.out ]; then
		EXPECTED=$(cat integration-part1.out)
		if [ "${RESULT}" != "${EXPECTED}" ]; then
			echo "Expected:"
			echo ${EXPECTED}
			echo "Actual:"
			echo ${RESULT}
			exit 1
		fi
	else
		echo "WARNING: No expected output"
	fi
	echo "${PROBLEM} - Part 2"
	RESULT=$(../cmake-build-release/${PROBLEM}/AoC-${PROBLEM} 2)
	if [ -e integration-part2.out ]; then
		EXPECTED=$(cat integration-part2.out)
		if [ "${RESULT}" != "${EXPECTED}" ]; then
			echo "Expected:"
			echo ${EXPECTED}
			echo "Actual:"
			echo ${RESULT}
			exit 1
		fi
	else
		echo "WARNING: No expected output"
	fi
	popd
done
popd
