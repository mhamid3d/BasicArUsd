#!/bin/bash

source /opt/rh/devtoolset-9/enable

rm -rf ./build/Linux
rm -rf ./install/Linux

cmake -S . -B ./build/Linux -DUSD_ROOT=/opt/USD
cmake --build ./build/Linux
cmake --install ./build/Linux