#!/bin/sh

compiler="gcc"

build_dir="build"
build_name="llawi-build"
build_version="0-1"

main_dir="./src"
main="app.c"


include_extra="src/include"

$compiler -I$include_extra "$main_dir/$main" -o "$build_dir/$build_name-$build_version.out"

