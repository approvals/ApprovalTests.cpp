mkdir -p cmake-build-space
cd       cmake-build-space
cmake ..
cmake --build .
ctest .
