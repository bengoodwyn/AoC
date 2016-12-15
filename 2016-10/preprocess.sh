#!/bin/bash
cat input | \
	sed 's/gives low to //g' | \
	sed 's/and high to //g' | \
	sed 's/goes to //g' | \
	sed 's/  *$//g' > preprocessed-input
