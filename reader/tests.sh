#!/usr/bin/env bash

V=$(echo "hello world" | ./demo/reader-demo)
if [[ "$V" != $'read command line: hello world\nexiting...' ]]; then
	echo 'FAILED `echo "hello world" | ./demo/reader-demo`'
	echo "'$V'"
	exit 1
fi

