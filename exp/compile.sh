clang++ -g -O3 \
    -std=c++11 \
    -o run \
    -Wno-unknown-warning-option `llvm-config --cxxflags --ldflags --system-libs --libs core` \
    -fexceptions \
    -Wno-unused-variable \
    -Wno-unused-private-field \
    Main.cpp