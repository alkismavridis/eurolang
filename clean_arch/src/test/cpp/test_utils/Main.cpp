#include <iostream>
#include <vector>
#include <memory>

#include "UnitTest.h"
#include "../entities/values/leaf_values/LeafValuesTest.h"
#include "../entities/scope/EulScopeTest.h"

using namespace std;

int main() {
  cout << endl << endl << "===== Initializing Eul test suite ====" << endl << endl;

  const vector<shared_ptr<UnitTest>> tests {
    make_shared<LeafValuesTest>(),
    make_shared<EulScopeTest>()
  };

  for (shared_ptr<UnitTest> test : tests) {
    test->runAll();
  }

  cout << endl << endl << "===== All Tests succeeded ====" << endl << endl << endl;
}
