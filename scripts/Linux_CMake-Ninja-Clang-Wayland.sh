#!/bin/bash
if ! which cmake; then
	echo "Could Not find CMake"
	PAUSE
	EXIT 1
fi

if ! which ninja; then
	echo "Could Not find ninja"
	exit 1
fi

if ! which clang; then
	echo "Could Not find clang compiler"
	exit 1
fi

if ! which clang; then
	echo "Could Not find clang++ compiler"
	exit 1
fi

cd ..
cmake -DCMAKE_BUILD_TYPE=DEBUG . -GNinja -DCMAKE_CXX_COMPILER="clang++" -DCMAKE_C_COMPILER="clang" -DGLFW_BUILD_WAYLAND=1 -DCMAKE_EXPORT_COMPILE_COMMANDS=1
