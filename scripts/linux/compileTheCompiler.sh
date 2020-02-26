. ./Config.sh
cd ../../src

mkdir -p __autoGenerated__

$EUL_FLEX -o __autoGenerated__/EulLexer.cpp lexer/lex.l
$EUL_BISON -d -v --file-prefix=__autoGenerated__/EulParser parser/parser.yy


$EUL_CPP_COMPILER -g -O3 \
    -std=c++11 \
    -o ../out/eulc \
    -Wno-unknown-warning-option ` $EUL_LLVM_CONFIG --cxxflags --ldflags --system-libs --libs core` \
    -fexceptions \
    -Wno-unused-variable \
    -Wno-unused-private-field \
    -Wno-overloaded-virtual \
    __autoGenerated__/EulParser.tab.cc \
    __autoGenerated__/EulLexer.cpp \
    Main.cpp


#clean up
rm -rf ./__autoGenerated__