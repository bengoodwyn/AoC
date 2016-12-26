#!/bin/bash
cat input | \
	sed 's/first/1/g' | \
	sed 's/second/2/g' | \
	sed 's/third/3/g' | \
	sed 's/fourth/4/g' | \
	sed 's/,//g' | \
	sed 's/The //g' | \
	sed 's/a //g' | \
	sed 's/and //g' | \
	sed 's/\.//g' | \
	sed 's/nothing relevant//g' | \
	sed 's/floor //g' | \
	sed 's/-compatible//g' | \
	sed 's/contains //g' | \
	sed 's/  *$//g' | \
	awk 'BEGIN {print "1"} {vals=(NF-1)/2; print $1 " " vals " "; for (i = 2; i <= NF; i++) print $i " "  }' \
	> preprocessed-input
