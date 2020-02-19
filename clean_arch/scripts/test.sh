#This script compiles and runs all unit tests
cd ../src/test/cpp


ALL_PRODUCTION_FILES=$(find . -type f -name "*.cpp")
ALL_TEST_FILES=$(find ../../main/cpp -type f -name "*.cpp")
clang++ \
    -std=c++14 \
    -fexceptions \
    -o program \
    $ALL_PRODUCTION_FILES $ALL_TEST_FILES


if [ $? -eq 0 ]; then
  ./program
  rm program
fi
