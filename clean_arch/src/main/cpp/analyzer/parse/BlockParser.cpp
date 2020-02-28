#include "ast/statements/StatementType.h"
#include "ast/statements/FunctionDeclarationStatement.h"
#include "analyzer/model/types/FunctionType.h"

#include "BlockParser.h"

using namespace std;

void BlockParser::parseBlock(list<unique_ptr<const EulStatement>>& statements) {
  return;
}

void BlockParser::declareTypes(list<unique_ptr<const EulStatement>>& statements) {
  return;
}



/*
 Responsibilities:
  - Create scopes where is needed
  - Declare symbols in scope (functions, variables, clases)
  - Assign types to every  value (including expressions, functions)


 Error detection:
  - Symbol not found
  - Duplicated symbol declaration
  - Use non-type as type
  - Invalid char size
  - Invalid expression combination.
  - Assignment statement to a const
  - Const definition without a value
*/
void foo() {
  //BlockParser::parse();
}
// PSEUDOCODE:
