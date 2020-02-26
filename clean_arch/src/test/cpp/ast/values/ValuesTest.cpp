#include "test_utils/Assert.h"
#include "ValuesTest.h"

using namespace std;

void constructorTest(UnitTest* t) {
  //Assert::equals(1, 0, t, "hazo");
}

void ValuesTest::runAll() {
    this
      ->logStart()
      ->warnNotTested("sdfsdf")
      ->run("constructorTest", constructorTest);
}
