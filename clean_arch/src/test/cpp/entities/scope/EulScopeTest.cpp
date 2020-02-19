#include <memory>

#include "../../test_utils/Assert.h"
#include "EulScopeTest.h"
#include "../../../../main/cpp/entities/scope/SymbolChangeType.h"
#include "../../../../main/cpp/entities/scope/EulScope.h"
#include "../../../../main/cpp/entities/types/AnyType.h"
#include "../../../../main/cpp/entities/values/leaf_values/BooleanNode.h"
#include "../../../../main/cpp/entities/error/VariableAlreadyDeclaredException.h"

using namespace std;



//utils
shared_ptr<SymbolDeclaration> makeDummySymbol() {
  return make_shared<SymbolDeclaration>(
    SymbolChangeType::VAR,
    make_shared<AnyType>().get(),
    make_shared<BooleanNode>(true).get()
  );
}



//SECTION TESTS

//tests for get()
void getShouldReturnExistingSymbol(UnitTest* t) {
  auto scope = make_unique<EulScope>(nullptr);
  auto firstSymbol = makeDummySymbol();
  auto secondSymbol = makeDummySymbol();

  scope->declare("first", firstSymbol.get());
  scope->declare("second", secondSymbol.get());

  Assert::same(firstSymbol.get(), scope->get("first"), t, "1");
  Assert::same(secondSymbol.get(), scope->get("second"), t, "2");
}

void getShouldReturnNullForNotExistingSymbol(UnitTest* t) {
  auto scope = make_unique<EulScope>(nullptr);
  auto firstSymbol = makeDummySymbol();
  auto secondSymbol = makeDummySymbol();

  scope->declare("first", firstSymbol.get());
  scope->declare("second", secondSymbol.get());

  Assert::null(scope->get("somthingElse"), t, "1");
}

void getShouldReturnSymbolFromParentScope(UnitTest* t) {
  auto parent = make_unique<EulScope>(nullptr);
  auto scope = make_unique<EulScope>(parent.get());

  auto firstSymbol = makeDummySymbol();
  auto secondSymbol = makeDummySymbol();

  parent->declare("first", firstSymbol.get());
  parent->declare("second", secondSymbol.get());

  Assert::same(firstSymbol.get(), scope->get("first"), t, "1");
  Assert::same(secondSymbol.get(), scope->get("second"), t, "2");
}

void getShouldGivePriorityToSymbolFromChildScope(UnitTest* t) {
  auto parent = make_unique<EulScope>(nullptr);
  auto scope = make_unique<EulScope>(parent.get());

  auto firstSymbolInParent = makeDummySymbol();
  auto secondSymbolInParent = makeDummySymbol();
  auto firstSymbolInChild = makeDummySymbol();

  parent->declare("first", firstSymbolInParent.get());
  parent->declare("second", secondSymbolInParent.get());
  scope->declare("first", firstSymbolInChild.get());

  Assert::same(firstSymbolInChild.get(), scope->get("first"), t, "1");
  Assert::same(secondSymbolInParent.get(), scope->get("second"), t, "2");
}


//tests for declare()
void declareShouldCreateEntry(UnitTest* t) {
  auto scope = make_unique<EulScope>(nullptr);
  auto someSymbol = makeDummySymbol();

  scope->declare("someSymbol", someSymbol.get());
  Assert::same(someSymbol.get(), scope->get("someSymbol"), t, "1");
}

void declareShouldCreateEntryEvenIfItExistsInParentScope(UnitTest* t) {
  auto parent = make_unique<EulScope>(nullptr);
  auto scope = make_unique<EulScope>(parent.get());

  auto symbolForParent = makeDummySymbol();
  auto symbolForChild = makeDummySymbol();

  parent->declare("someSymbol", symbolForParent.get());
  scope->declare("someSymbol", symbolForChild.get());

  Assert::same(symbolForParent.get(), parent->get("someSymbol"), t, "1");
  Assert::same(symbolForChild.get(), scope->get("someSymbol"), t, "2");
}

void declareShouldFailIfSymbolExistsInSameScope(UnitTest* t) {
  auto scope = make_unique<EulScope>(nullptr);

  auto someSymbol = makeDummySymbol();
  auto someOtherSymbol = makeDummySymbol();
  scope->declare("someSymbol", someSymbol.get());

  auto ex = Assert::throws<VariableAlreadyDeclaredException>(
    [&]()-> void { scope->declare("someSymbol", someOtherSymbol.get()); },
    t,
    "1"
  );
  Assert::equals("Variable someSymbol is already defined.", ex.message, t, "2");
}


// glue code
void EulScopeTest::runAll() {
    this
      ->logStart()
      ->run("getShouldReturnExistingSymbol", getShouldReturnExistingSymbol)
      ->run("getShouldReturnNullForNotExistingSymbol", getShouldReturnNullForNotExistingSymbol)
      ->run("getShouldReturnSymbolFromParentScope", getShouldReturnSymbolFromParentScope)
      ->run("getShouldGivePriorityToSymbolFromChildScope", getShouldGivePriorityToSymbolFromChildScope)

      ->run("declareShouldCreateEntry", declareShouldCreateEntry)
      ->run("declareShouldCreateEntryEvenIfItExistsInParentScope", declareShouldCreateEntryEvenIfItExistsInParentScope)
      ->run("declareShouldFailIfSymbolExistsInSameScope", declareShouldFailIfSymbolExistsInSameScope)
      ;
}
