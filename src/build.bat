echo y|rmdir /s build\Windows
echo y|rmdir /s install\Windows

cmake -S . -B build/Windows -A x64 -DUSD_ROOT=C:/builds/USD/22.08
cmake --build build/Windows --config Release
cmake --install build/Windows