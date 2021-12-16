#!/bin/sh

set -xe

clang -O3 main.c -o main -lm 
./main