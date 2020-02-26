#This script compiles and runs all unit tests
cd ../src


ALL_PRODUCTION_FILES=$(find ./main/cpp -type f -name "*.cpp")
ALL_TEST_FILES=$(find ./test/cpp -type f -name "*.cpp")
SOURCE_ROOT=$(pwd)

clang++ \
    -I $SOURCE_ROOT/main/cpp \
    -I $SOURCE_ROOT/test/cpp \
    -std=c++14 \
    -fexceptions \
    -o program \
    $ALL_PRODUCTION_FILES $ALL_TEST_FILES


if [ $? -eq 0 ]; then
  ./program
  rm program
fi
