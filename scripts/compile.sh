cd ../src

mkdir __autoGenerated__


flex -o __autoGenerated__/EulLexer.cpp lexer/lex.l
bison -d -v --file-prefix=__autoGenerated__/EulParser parser/parser.yy

clang++ -g -O3 \
    -std=c++11 \
    -o ../out/eulc \
    -Wno-unknown-warning-option `llvm-config --cxxflags --ldflags --system-libs --libs core` \
    -fexceptions \
    -Wno-unused-variable \
    -Wno-unused-private-field \
    __autoGenerated__/EulParser.tab.cc \
    __autoGenerated__/EulLexer.cpp \
    Main.cpp


#clean up
rm -rf ./__autoGenerated__