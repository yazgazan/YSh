#!/usr/bin/env bash

make -C demo || exit $?

V=$(echo "hello world" | ./demo/reader-demo)
if [[ "$V" != $'read command line: hello world\nexiting...' ]]; then
	echo 'FAILED `echo "hello world" | ./demo/reader-demo`'
	exit 1
fi

