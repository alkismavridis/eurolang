#pragma once

class EulFuncDeclarationStatementTest {
  public: static void generateStatement(const std::string& t) {
    Assert::warnNotTested("EulFuncDeclarationStatementTest.generateStatement");
  }

  public: static void performPreParsing(const std::string& t) {
    Assert::warnNotTested("EulFuncDeclarationStatementTest.performPreParsing");
  }


  public: static void runAll() {
    generateStatement("EulFuncDeclarationStatementTest.generateStatement ");
    performPreParsing("EulFuncDeclarationStatementTest.performPreParsing ");
  }
};
