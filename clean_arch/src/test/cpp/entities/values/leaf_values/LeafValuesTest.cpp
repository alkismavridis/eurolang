#include "LeafValuesTest.h"
#include "../../../test_utils/Assert.h"

using namespace std;

void constructorTest(UnitTest* t) {
  //Assert::equals(1, 0, t, "hazo");
}

void LeafValuesTest::runAll() {
    this
      ->logStart()
      ->warnNotTested("sdfsdf")
      ->run("constructorTest", constructorTest);
}
