#!/bin/sh

set -xe

clang main.c -o main -lm
./main