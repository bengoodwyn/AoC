#!/bin/bash
cat input | \
	grep '^\/dev' | \
	sed 's/^.*-x\([0-9]*\)-y\([0-9]*\) *\([0-9]*\)T *\([0-9]*\)T *\([0-9]*\)T.*$/\1 \2 \4 \5/g' \
	> preprocessed-input
