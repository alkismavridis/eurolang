#pragma once





class NotOperatorTest {
  public: static void performPrefix(const std::string& t) {
    Assert::warnNotTested("NotOperatorTest.performPrefix");
  }


  public: static void runAll() {
    performPrefix("NotOperatorTest.performPrefix ");
  }
};
