#include "UnitTest.h"
#include "Assert.h"


using namespace std;


// SECTION UNIT TEST
UnitTest::UnitTest(const string& tn) :
  displayName(tn),
  currentCaseName("") {}


const string UnitTest::getName() const { return displayName; }
const string UnitTest::getCurrentTestName() const { return currentCaseName; }

const string UnitTest::getCurrentTestFullName() const {
  return displayName + "." + currentCaseName;
}


UnitTest* UnitTest::logStart() {
  cout << endl << endl << "# " << this->displayName << endl;
  return this;
}

UnitTest* UnitTest::run(const string testName, void (testCallback)(UnitTest*)) {
  this->currentCaseName = testName;

  cout
    << "RUN: "
    << this->displayName
    << "."
    << testName
    << endl;

  testCallback(this);
  return this;
};

UnitTest* UnitTest::warnNotTested(const string& testName) {
  cout
    << "TODO: "
    << this->getName()
    << "."
    << testName
    << endl;

    return this;
}



//SECTION ASSERT
void Assert::equals(long int expected, long int actual, const UnitTest* t, const std::string& label) {
  if (expected == actual) return;
  std::cout << "\n\n" << t->getCurrentTestFullName() << " " << label << "\n\tExpected: "<< expected <<",\n\tFound: " << actual << ".\n\n";
  exit(1);
}

void Assert::equalsUnsigned(unsigned long int expected, unsigned long int actual, const UnitTest* t, const std::string& label) {
  if (expected == actual) return;
  std::cout << "\n\n" << t->getCurrentTestFullName() << " " << label << "\n\tExpected: "<< expected <<",\n\tFound: " << actual << ".\n\n";
  exit(1);
}

void Assert::equals(double expected, double actual, double tolerance, const UnitTest* t, const std::string& label) {
  if (std::abs(expected-actual)<tolerance) return;
  std::cout << "\n\n" << t->getCurrentTestFullName() << " " << label << "\n\tExpected: "<< expected <<",\n\tFound: " << actual << "\n\n";
  exit(1);
}


void Assert::equals(const std::string& expected, const std::string& actual, const UnitTest* t, const std::string& label) {
  if (expected==actual) return;
  std::cout << "\n\n" << t->getCurrentTestFullName() << " " << label << "\n\tExpected: "<< expected <<",\n\tFound: " << actual << "\n\n";
  exit(1);
}

void Assert::charEquals(char expected, char actual, const UnitTest* t, const std::string& label) {
  if (expected==actual) return;
  std::cout << "\n\n" << t->getCurrentTestFullName() << " " << label << "\n\tExpected: "<< expected <<",\n\tFound: " << actual << "\n\n";
  exit(1);
}

void Assert::that(char cond, const UnitTest* t, const std::string& label) {
  if (cond) return;
  std::cout << "\n\n"<< t->getCurrentTestFullName() << " " << label << "\n\tAssert true failed.\n\n";
  exit(1);
}

void Assert::thatNot(char cond, const UnitTest* t, const std::string& label) {
  if (!cond) return;
  std::cout << "\n\n"<< t->getCurrentTestFullName() << " " << label << "\n\tAssert false failed.\n\n";
  exit(1);
}

void Assert::same(void* expected, void* actual, const UnitTest* t, const std::string& label) {
  if (expected==actual) return;
  std::cout << "\n\n"<< t->getCurrentTestFullName() << " " << label << "\n\tAssert equals pointers failed.\n\n";
  exit(1);
}

void Assert::null(void* ptr, const UnitTest* t, const std::string& label) {
  if (ptr==0) return;
  std::cout << "\n\n"<< t->getCurrentTestFullName() << " " << label << "\n\tAssert null failed.\n\n";
  exit(1);
}

void Assert::notNull(void* ptr, const UnitTest* t, const std::string& label) {
  if (ptr!=0) return;
  std::cout << "\n\n"<< t->getCurrentTestFullName() << " " << label << "\n\tAssert not null failed.\n\n";
  exit(1);
}

void Assert::fail(const UnitTest* t, const std::string& message) {
  std::cout << "\n\nFAILED: " << t->getCurrentTestFullName() << " " << message << std::endl << std::endl;
  exit(1);
}
