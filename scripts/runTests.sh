#!/usr/bin/env bash

cd $(dirname $0)

docker run --rm -it -v $PWD/..:/ysh yazgazan/ysh-dev:latest make re tests

