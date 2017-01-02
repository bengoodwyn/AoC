#!/bin/bash
cat input | \
	sed 's/^.* \([0-9]*\) positions.*position \([0-9]*\).*$/\1 \2/g' \
	> preprocessed-input
