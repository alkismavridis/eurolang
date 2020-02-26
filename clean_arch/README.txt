The compiler has 5 modules.

======= ast =======
  DEPENDS ON: nothing.

  HAS:
    Literals, types, operators, expressions, Statements and the relationships between them.

  HAS NOT:
    - Any knowledge of the exact syntax and grammar of the language.
    - Any semantic evaluation. ast does not care whether the ast is semantically valid or not.
    - Does not throw nor handle errors (maybe in VERY special occasions, but better avoid that)



======= analyzer =======
  DEPENDS ON: ast

  HAS:
    - Scope information
    - Checks types of each expression.
    - Checks that variables are properly declared.
    - Checks that numbers have the correct amount of bits.
    - Checks for unreachable statements.
    - Throws exceptions if anything goes wrong (or maybe directly log errors?)

  HAS NOT:
    - Any knowledge of the exact syntax and grammar of the language.



======= parser =======
  DEPENDS ON: ast

  EXTERNAL DEPENDENCIES: flex, bison

  HAS:
    - All the flex and bison magic.
    - This is the only module that deals with the syntax and grammar of the language.
    - Its goal is to parse the file and produce an AST (probably as a vector of EulStatements)
    - Its goal is to parse the file and produce an AST (probably as a vector of EulStatements)

  HAS NOT:
    - Evaluation of the ast that it parsed. The parser does not care if the ast was semantically valid or not.


======= codegen =======
  DEPENDS ON: ast, analyzer

  EXTERNAL DEPENDENCIES: llvm

  HAS:
    - Accepts a valid and analyzed AST.
    - Generates the precious .o file out of it.



======= cli =======
  DEPENDS ON: ast, analyzer, parser, codegen

  HAS:
    - Gets the input parameters from the user and makes sense of them.
    - Provides small glue code to guide the whole process.
    - main() goes here.
