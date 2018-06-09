#include <iostream>
#include <forward_list>
#include <sstream>
#include <map>
#include <cstdlib>
#include <cstring>


#include "./core/EulToken/EulTokenType.h"
#include "./core/EulToken/EulToken.h"
#include "./core/EulToken/EulIntToken.h"
#include "./core/EulToken/EulCharToken.h"
#include "./core/EulToken/EulFloatToken.h"
#include "./core/EulToken/EulIdToken.h"
#include "./core/EulToken/EulStringToken.h"

#include "./core/EulAst/EulAstType.h"
#include "./core/EulAst/EulAst.h"

#include "./core/EulAst/EulStatement/EulStatementType.h"
#include "./core/EulAst/EulStatement/EulStatement.h"
#include "./core/EulAst/EulStatement/EulImportStatement.h"
#include "./core/EulAst/EulStatement/EulExportStatement.h"
#include "./core/EulAst/EulSymbol.h"

#include "./core/EulSourceFile/EulSourceFile.h"
#include "./core/EulProgram/EulProgram.h"
#include "./core/Compiler/Compiler.h"




//region ERROR HANDLING
void handleError(Compiler* comp) {
    std::cout << comp->errorMessage << std::endl;
}
//endregion



int main( const int argc, const char **argv ) {
   /** check for the right # of arguments **/
   if( argc == 2 )
   {
      /** instantiate driver object **/
      Compiler compiler(handleError);
      /** example for piping input from terminal, i.e., using cat **/
      if( std::strncmp( argv[ 1 ], "-o", 2 ) == 0 ) {
         compiler.compile( "dummyFile.eul", &std::cin );
      }
      /** simple help menu **/
      else if( std::strncmp( argv[ 1 ], "-h", 2 ) == 0 )
      {
         std::cout << "use -o for pipe to std::cin\n";
         std::cout << "just give a filename to count from a file\n";
         std::cout << "use -h to get this menu\n";
         return( EXIT_SUCCESS );
      }
      /** example reading input from a file **/
      else
      {
         /** assume file, prod code, use stat to check **/
         compiler.compile( "dummyFile.eul", &std::cin );
      }
      std::cout << "\n";
   }
   else
   {
      /** exit with failure condition **/
      return ( EXIT_FAILURE );
   }
   return( EXIT_SUCCESS );
}