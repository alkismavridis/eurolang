#This script compiles and runs all unit tests
clear
clear
clear
cd ../test


mkdir ../src/__autoGenerated__


flex -o ../src/__autoGenerated__/EulLexer.cpp ../src/lexer/lex.l
bison -d --file-prefix=../src/__autoGenerated__/EulParser ../src/parser/parser.yy

clang++ \
    -std=c++11 \
    -o program \
    -Wno-unknown-warning-option `llvm-config --cxxflags --ldflags --system-libs --libs core` \
    -fexceptions \
    -Wno-unused-variable \
    -Wno-unused-private-field \
    ../src/__autoGenerated__/EulParser.tab.cc \
    ../src/__autoGenerated__/EulLexer.cpp \
    MainTest.cpp

./program



#clean up
rm -rf ../src/__autoGenerated__
rm program