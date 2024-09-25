#!/usr/bin/env bash

set -e

./build.sh
ctest --test-dir build --verbose
