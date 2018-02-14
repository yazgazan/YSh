#!/usr/bin/env bash

cd $(dirname $0)

docker build -t yazgazan/ysh-dev:latest ..
