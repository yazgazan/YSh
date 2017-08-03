#!/usr/bin/env bash

V=$(echo "hello world" | PS1="" ./demo/reader-demo)

echo $V | grep 'read command line: hello world' > /dev/null
if [[ $? != 0 ]]; then
	echo 'FAILED `echo "hello world" | ./demo/reader-demo`'
	echo "should contain 'read command line: hello world'"
	exit 1
fi

echo $V | grep 'exiting...' > /dev/null
if [[ $? != 0 ]]; then
	echo 'FAILED `echo "hello world" | ./demo/reader-demo`'
	echo "should contain 'exiting...'"
	exit 1
fi
