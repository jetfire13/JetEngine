#!/bin/bash
cd ..
cmake -DCMAKE_BUILD_TYPE=DEBUG . -DGLFW_BUILD_WAYLAND=1 -DCMAKE_EXPORT_COMPILE_COMMANDS=1
