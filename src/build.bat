cmake -S . -B ./build -A x64 -DUSD_ROOT=C:/USD -DPYTHON_ROOT=C:/Users/mhamid/anaconda3/envs/cometpy37
cmake --build ./build --config Release
cmake --install ./build